#!/usr/bin/env python

import rospy
from psi.msg import ArmControl
from psi.msg import ArmFeedback
from psi.msg import MissionStatus


class Arm_Manager:
    def __init__(self):
        rospy.init_node('arm_manager', anonymous=False)

        self.mission_status = ""

        self.left_arm = self._Arm("left")
        self.ac_msg = ArmControl()
        self.arm_control_pub = rospy.Publisher(
            'arm/control', ArmControl, queue_size=1)

        self.ms_msg = MissionStatus()
        self.mission_status_pub = rospy.Publisher(
            "mission_status", MissionStatus, queue_size=1)
        rospy.Subscriber("mission_status", MissionStatus,
                         self.mission_status_cb)

        rospy.Subscriber("arm/feedback", ArmFeedback, self.arm_feedback_cb)

    def mission_status_cb(self, data):
        self.mission_status = data.mission_status

    def arm_feedback_cb(self, data):
        if "Extend Complete" in data.wormgear_status:
            self.mission_status = "Continue Backward"
        elif "Retract Complete" in data.wormgear_status:
            pass
        else:
            self.mission_status = "Wait"

    def horizontal_arm_control(self):
        self.ac_msg.header.stamp = rospy.Time.now()
        # frame_id needs to be changed when another arm is implemented
        self.ac_msg.header.frame_id = "left_arm_lower"
        if "Retract" in self.mission_status:
            self.ac_msg.wormgear_direction = "Reverse"
            self.ac_msg.wormgear_theta_in = 0.0
        elif "Extend" in self.mission_status:
            self.ac_msg.wormgear_direction = "Forward"
            self.ac_msg.wormgear_theta_in = 45.0
        elif "Pause" in self.mission_status:
            self.ac_msg.wormgear_direction = "Pause"
            self.ac_msg.wormgear_theta_in = 0.0
        self.arm_control_pub.publish(self.ac_msg)

    def start(self):
        while not rospy.is_shutdown():
            self.horizontal_arm_control()

            self.ms_msg.mission_status = self.mission_status
            if self.mission_status:
                self.ms_msg.header.stamp = rospy.Time.now()
                self.ms_msg.header.frame_id = "left_arm_lower"
                self.mission_status_pub.publish(self.ms_msg)

            rospy.sleep(1)

    class _Arm:
        def __init__(self, arm_type):
            self.arm_type = arm_type


if __name__ == '__main__':
    try:
        am = Arm_Manager()
        am.start()
    except rospy.ROSInterruptException:
        pass
