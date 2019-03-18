#!/usr/bin/env python

import json
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

        self.mission_data = ""
        self.prev_mission_data = ""
        self.direction = ""
        self.direction_error = 0.0
        self.prev_direction_error = 0.0
        self.cardinal_direction = ""
        self.range = 0

        self.cd_msg = CardinalDirection()
        self.cardinal_direction_pub = rospy.Publisher(
            'drive/cardinal_direction', CardinalDirection, queue_size=1)

        rospy.Subscriber('drive/mission_status', MissionStatus,
                         self.mission_status_cb)

        rospy.Subscriber('drive/direction_error', DirectionError,
                         self.drive_turn_control_cb)

    def mission_status_cb(self, data):
        self.mission_data = data.mission_status
        if self.mission_data != self.prev_mission_data:
            temp_mission_data = json.loads(self.mission_data)
            self.direction = temp_mission_data['Direction']
            self.prev_mission_data = self.mission_data

    def drive_turn_control_cb(self, data):
        self.direction_error = -float(data.direction_error) / 100
        self.translate_sensordata_to_cardinal()

    def translate_sensordata_to_cardinal(self):
        self.cd_msg.header.stamp = rospy.Time.now()
        # This shoud change in the future when the wheel base link is
        # created and implemented in the urdf
        self.cd_msg.header.frame_id = "base_link"

        if "Stop" in self.direction:
            self.cardinal_direction = "T"
        else:
            if "Left" in self.direction:
                self.cardinal_direction = "W"
            elif "Right" in self.direction:
                self.cardinal_direction = "E"
            elif "Forward" in self.direction:
                if self.direction_error < -0.2:
                    self.cardinal_direction = "NW"
                elif self.direction_error > 0.2:
                    self.cardinal_direction = "NE"
                else:
                    self.cardinal_direction = "N"
            elif "Backward" in self.direction:
                if self.direction_error < -0.2:
                    self.cardinal_direction = "SW"
                elif self.direction_error > 0.2:
                    self.cardinal_direction = "SE"
                else:
                    self.cardinal_direction = "S"
            else:
                self.cardinal_direction = "T"

        self.cd_msg.cardinal_direction = self.cardinal_direction
        self.cardinal_direction_pub.publish(self.cd_msg)

    def start(self):
        while not rospy.is_shutdown():
            rospy.sleep(1)


if __name__ == "__main__":
    try:
        nav = Navigation()
        nav.start()
    except rospy.ROSInterruptException:
        pass
