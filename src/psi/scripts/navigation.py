#!/usr/bin/env python

import math
import rospy
from time import sleep
from sensor_msgs.msg import Range
from sensor_msgs.msg import Imu
from sensor_msgs.msg import MagneticField
from psi.msg import CardinalDirection
from psi.msg import DirectionError
from psi.msg import MissionStatus


class Navigation:
    def __init__(self):
        rospy.init_node('navigation', anonymous=False)

        self.mission_status = "Continue"
        self.direction = "Forward"
        self.range = 0
        self.angular_z = 0.0
        self.cardinal_direction = ""

        self.cd_msg = CardinalDirection()
        self.cardinal_direction_pub = rospy.Publisher(
            'drive/cardinal_direction', CardinalDirection, queue_size=1)

        rospy.Subscriber('mission_status', MissionStatus,
                         self.mission_status_cb)

        rospy.Subscriber('drive/direction_error', DirectionError,
                         self.drive_turn_control_cb)

    def translate_sensordata_to_motorspeed(self):
        # QR code translation
        if "Wait" in self.mission_status:
            self.cardinal_direction = "T"

        elif "Continue" in self.mission_status:
            if "Forward" in self.direction:  # Moving forward
                if self.angular_z > 0.2:  # Right
                    self.cardinal_direction = "NE"
                elif self.angular_z < -0.2:  # Left
                    self.cardinal_direction = "NW"
                else:  # Forward only
                    self.cardinal_direction = "N"

            elif "Backward" in self.direction:  # Moving backward
                if self.angular_z > 0.2:  # Right
                    self.cardinal_direction = "SE"
                elif self.angular_z < -0.2:  # Left
                    self.cardinal_direction = "SW"
                else:  # Forward only
                    self.cardinal_direction = "S"

            else:  # Stop awaiting input
                self.cardinal_direction = "T"

    def mission_status_cb(self, data):
        self.mission_status = data.mission_status

    def drive_turn_control_cb(self, data):
        self.angular_z = -float(data.direction_error) / 100

    def start(self):
        while not rospy.is_shutdown():
            self.translate_sensordata_to_motorspeed()

            self.cd_msg.header.stamp = rospy.Time.now()
            # This shoud change in the future when the wheel base link is created and implemented in the urdf
            self.cd_msg.header.frame_id = "base_link"
            self.cd_msg.cardinal_direction = self.cardinal_direction
            self.cardinal_direction_pub.publish(self.cd_msg)

            rospy.sleep(1)


if __name__ == "__main__":
    try:
        nav = Navigation()
        nav.start()
    except rospy.ROSInterruptException:
        pass
