#!/usr/bin/env python

from __future__ import print_function
import math
import rospy
from psi.msg import JoystickInput
from psi.msg import CardinalDirection


class Drive_Manager:
    def __init__(self):
        rospy.init_node('drive_manager', anonymous=False)

        self.cardinal_direction = ""
        self.location = ""
        self.x_input = 0
        self.y_input = 0

        self.ji_msg = JoystickInput()
        self.joystick_input_pub = rospy.Publisher(
            'drive/joystick_input', JoystickInput, queue_size=1)

        rospy.Subscriber('drive/cardinal_direction',
                         CardinalDirection, self.cardinal_direction_cb)

    def joystick_input_talker(self):
        rospy.loginfo("Publishing Joystick inputs.")
        self.ji_msg.header.stamp = rospy.Time.now()
        self.ji_msg.header.frame_id = "base_link"
        self.ji_msg.x_input = self.x_input
        self.ji_msg.y_input = self.y_input
        self.joystick_input_pub.publish(self.ji_msg)

    def cardinal_direction_cb(self, data):
        self.cardinal_direction = data.cardinal_direction

    def map_cardinal_to_joystick_input(self):
        # joystick input range from 25 to 220, where 125 is the midpoint
        rospy.loginfo("Mapping Cardinal inputs to Joystick inputs.")
        if "N" in self.cardinal_direction:
            # If speeds are negative, vary the position of the joystick
            # depending on left or right
            if self.cardinal_direction == "N":
                rospy.loginfo("Vehicle approaching South.")
                self.y_input = 15
                self.x_input = 125
            elif self.cardinal_direction == "NE":
                rospy.loginfo("Vehicle approaching South East.")
                self.y_input = 125 * math.sin(math.radians(45))
                self.x_input = 125 + 125 * math.cos(math.radians(45))
            elif self.cardinal_direction == "NW":
                rospy.loginfo("Vehicle approaching South West.")
                self.y_input = 125 * math.sin(math.radians(45))
                self.x_input = 125 - 125 * math.cos(math.radians(45))

        elif "T" in self.cardinal_direction:
            # If speeds are at 0, set system to idle position
            rospy.loginfo("Vehicle stopping.")
            self.x_input = 125
            self.y_input = 125

        elif "S" in self.cardinal_direction:
            # If speeds are positive, vary the position of the joystick
            # depending on left or right
            if self.cardinal_direction == "S":
                rospy.loginfo("Vehicle approaching North.")
                self.y_input = 240
                self.x_input = 125
            elif self.cardinal_direction == "SE":
                rospy.loginfo("Vehicle approaching North East.")
                self.y_input = 125 + 125 * math.sin(math.radians(45))
                self.x_input = 125 + 125 * math.cos(math.radians(45))
            elif self.cardinal_direction == "SW":
                rospy.loginfo("Vehicle approaching North West.")
                self.y_input = 125 + 125 * math.sin(math.radians(45))
                self.x_input = 125 * math.cos(math.radians(45))

        elif "W" in self.cardinal_direction:
            rospy.loginfo("Vehicle turning right.")
            self.y_input = 125
            self.x_input = 220

        elif "E" in self.cardinal_direction:
            self.y_input = 125
            self.x_input = 25

        else:
            # Default case to set the joystick to idle position
            self.x_input = 125
            self.y_input = 125

    def start(self):
        """
        TODO: Complete mapping of joystick input method plus finish insertion
        of argument
        """
        rospy.loginfo("Initializing Drive Manager node.")
        while not rospy.is_shutdown():
            self.map_cardinal_to_joystick_input()
            self.joystick_input_talker()


if __name__ == "__main__":
    try:
        dm = Drive_Manager()
        dm.start()
    except rospy.ROSInterruptException:
        pass
