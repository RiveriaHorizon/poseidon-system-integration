#!/usr/bin/env python

import time
import rospy
from psi.msg import NavigationControl


class Drive_Control_Test:
    def __init__(self):
        self.cardinal_direction = ""
        self.navi_control_msg = NavigationControl()
        self.drive_controller_test_pub = rospy.Publisher(
            '/psi/navigation_control', NavigationControl, queue_size=10)

    def navigation_control_talker(self, cardinal_direction):
        self.navi_control_msg.location = "placeholder"
        self.navi_control_msg.cardinal_direction = cardinal_direction
        self.drive_controller_test_pub.publish(self.navi_control_msg)

    def start(self):
        rospy.init_node('drive_control_test', anonymous=False)
        while not rospy.is_shutdown():
            self.navigation_control_talker("S")
            time.sleep(5)
            self.navigation_control_talker("N")


if __name__ == "__main__":
    dct = Drive_Control_Test()
    dct.start()
