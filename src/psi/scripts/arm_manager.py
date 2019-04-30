#!/usr/bin/env python

import json
import rospy
from psi.msg import ArmControl
from psi.msg import ArmFeedback
from psi.msg import MissionStatus


class Arm_Manager:
    def __init__(self):
        rospy.init_node('arm_manager', anonymous=False)

        self.mission_data = ""
        self.prev_mission_data = ""

        self.left_arm = self._Arm("left")

        self.ac_msg = ArmControl()
        self.arm_control_pub = rospy.Publisher(
            'arm/control', ArmControl, queue_size=1)

        rospy.Subscriber("arm/mission_status", MissionStatus,
                         self.mission_status_cb)

        rospy.Subscriber("arm/feedback", ArmFeedback, self.arm_feedback_cb)

    def mission_status_cb(self, data):
        self.mission_data = data.mission_status
        if self.mission_data != self.prev_mission_data:
            temp_mission_data = json.loads(self.mission_data)
            # Single arm implementation
            # This should be changed when a new arm is implemented
            self.left_arm.horizontal_action = temp_mission_data['Horizontal-Action']
            self.left_arm.vertical_action = temp_mission_data['Vertical-Action']
            self.left_arm.horizontal = temp_mission_data['Horizontal']
            self.left_arm.vertical = temp_mission_data['Vertical']

            self.arm_control()

    def arm_feedback_cb(self, data):
        pass

    def horizontal_action(self):
        # Vertical motion to not move is by sending the same distance over
        # This should be changed in the future since the vertical motion of
        # the arm is independant of arm type.
        if "Extend" in self.left_arm.horizontal_action:
            # self.ac_msg.horizontal_distance = self.left_arm.horizontal
            self.ac_msg.horizontal_distance = self.left_arm.horizontal
        elif "Retract" in self.left_arm.horizontal_action:
            self.ac_msg.horizontal_distance = self.left_arm.NO_ACTION
            # self.ac_msg.vertical_distance = self.left_arm.vertical
        elif "Pause" in self.left_arm.horizontal_action:
            self.ac_msg.horizontal_distance = self.left_arm.horizontal
            # self.ac_msg.vertical_distance = self.left_arm.vertical
        else:
            rospy.logerr_once("Invalid arm action.")

        self.arm_control_pub.publish(self.ac_msg)

    def vertical_action(self):
        if "Raise" in self.left_arm.vertical_action:
            # self.ac_msg.horizontal_distance = self.left_arm.NO_ACTION
            self.ac_msg.vertical_distance = self.left_arm.vertical
        elif "Drop" in self.left_arm.vertical_action:
            # self.ac_msg.horizontal_distance = self.left_arm.NO_ACTION
            self.ac_msg.vertical_distance = self.left_arm.vertical
        elif "Pause" in self.left_arm.vertical_action:
            # self.ac_msg.horizontal_distance = self.left_arm.NO_ACTION
            self.ac_msg.vertical_distance = self.left_arm.vertical
        else:
            rospy.logerr_once("Invalid arm action.")

        self.arm_control_pub.publish(self.ac_msg)

    def arm_control(self):
        self.ac_msg.header.stamp = rospy.Time.now()
        # Single arm implementation
        # This should be changed when a new arm is implemented
        self.ac_msg.header.frame_id = "left_arm_lower"
        self.ac_msg.arm_type = "Left"

        self.vertical_action()
        self.horizontal_action()

    def start(self):
        while not rospy.is_shutdown():
            rospy.sleep(1)

    class _Arm:
        def __init__(self, arm_type):
            self.NO_ACTION = 0

            self.arm_type = arm_type
            self.horizontal_action = ""
            self.vertical_action = ""
            self.horizontal = 0.0
            self.vertical = 0.0


if __name__ == '__main__':
    try:
        am = Arm_Manager()
        am.start()
    except rospy.ROSInterruptException:
        pass
