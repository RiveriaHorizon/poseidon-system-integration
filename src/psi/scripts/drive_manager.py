#!/usr/bin/env python

from __future__ import print_function
import math
import rospy
from psi.msg import JoystickInput
from psi.msg import CardinalDirection


class Drive_Manager:
    def cardinal_direction_cb(self, data):
        self.cardinal_direction = data.cardinal_direction
        self.map_cardinal_to_joystick_input()
        self.joystick_input_talker()

    def map_cardinal_to_joystick_input(self):
        # joystick input range from 25 to 225, where 125 is the midpoint
        # radius of circle is 100
        if "N" in self.cardinal_direction:
            # If speeds are negative, vary the position of the joystick
            # depending on left or right
            if self.cardinal_direction == "N":
                self.y_input = 90
                self.x_input = 125
            elif self.cardinal_direction == "NW":
                self.y_input = 125 - 100 * math.cos(math.radians(35))
                self.x_input = 125 - 100 * math.sin(math.radians(35))
            elif self.cardinal_direction == "NE":
                self.y_input = 125 - 100 * math.cos(math.radians(35))
                self.x_input = 125 + 100 * math.sin(math.radians(35))

        elif "T" in self.cardinal_direction:
            # If speeds are at 0, set system to idle position
            self.x_input = 125
            self.y_input = 125

        elif "S" in self.cardinal_direction:
            # If speeds are positive, vary the position of the joystick
            # depending on left or right
            if self.cardinal_direction == "S":
                self.y_input = 195
                self.x_input = 125
            elif self.cardinal_direction == "SE":
                self.y_input = 125 + 100 * math.sin(math.radians(35))
                self.x_input = 125 + 100 * math.cos(math.radians(35))
            elif self.cardinal_direction == "SW":
                self.y_input = 125 + 100 * math.sin(math.radians(35))
                self.x_input = 125 - 100 * math.cos(math.radians(35))

        elif "W" in self.cardinal_direction:
            self.y_input = 125
            self.x_input = 225

        elif "E" in self.cardinal_direction:
            self.y_input = 125
            self.x_input = 25

        else:
            # Default case to set the joystick to idle position
            self.x_input = 125
            self.y_input = 125

    def joystick_input_talker(self):
        self.ji_msg.header.stamp = rospy.Time.now()
        self.ji_msg.header.frame_id = "base_link"
        self.ji_msg.x_input = self.x_input
        self.ji_msg.y_input = self.y_input
        self.joystick_input_pub.publish(self.ji_msg)

    def start(self):
        rospy.init_node('drive_manager', anonymous=False)

        self.cardinal_direction = ""
        self.prev_cardinal_direction = ""
        self.location = ""
        self.x_input = 0
        self.y_input = 0

        self.ji_msg = JoystickInput()
        self.joystick_input_pub = rospy.Publisher(
            '/psi/drive/joystick_input', JoystickInput, queue_size=1)

        rospy.Subscriber('/psi/drive/cardinal_direction',
                         CardinalDirection, self.cardinal_direction_cb)

        rospy.spin()


if __name__ == "__main__":
    try:
        dm = Drive_Manager()
        dm.start()
    except rospy.ROSInterruptException:
        pass
