#!/usr/bin/env python

import rospy
from psi.msg import ArmControl
from psi.msg import ArmFeedback
from psi.msg import MissionStatus


class Arm_Manager:
    def __init__(self):
        rospy.init_node('arm_manager', anonymous=False)

        self.mission_status = ""

        self.right_arm = self._Arm("right")
        self.ac_msg = ArmControl()
        self.arm_control_pub = rospy.Publisher(
            'arm/control', ArmControl, queue_size=1)

        self.ms_msg = MissionStatus()
        self.mission_status_pub = rospy.Publisher(
            "mission_status", MissionStatus, queue_size=1)

        rospy.Subscriber("arm/feedback", ArmFeedback, self.arm_feedback_cb)

    def arm_feedback_cb(self, data):
        if "Extend Complete" in data.wormgear_status:
            self.mission_status = "Continue Backward"
        elif "Retract Complete" in data.wormgear_status:
            pass
        else:
            self.mission_status = "Wait"

    def horizontal_arm_control(self):
        if "Retract" in self.mission_status:
            self.ac_msg.wormgear_direction = "Reverse"
            self.ac_msg.wormgear_theta_in = 0.0
        elif "Extend" in self.mission_status:
            self.ac_msg.wormgear_direction = "Forward"
            self.ac_msg.wormgear_theta_in = 45.0

    def start(self):
        while not rospy.is_shutdown():
            self.horizontal_arm_control()

            self.arm_control_pub.publish(self.ac_msg)

            self.ms_msg.mission_status = self.mission_status
            if self.mission_status:
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
