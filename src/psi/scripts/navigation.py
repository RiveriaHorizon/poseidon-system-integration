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

        self.status_mission_data = ""
        self.prev_status_mission_data = ""
        self.junction_ahead = False
        self.junction = False
        self.end_block = False
        self.end_mission = False
        self.water_mission = False

        self.drive_mission_data = ""
        self.prev_drive_mission_data = ""
        self.direction = ""
        self.wait = False
        self.delay = 0.0
        self.direction_error = 0.0
        self.prev_direction_error = 0.0
        self.cardinal_direction = ""

        self.range = 0

        self.cd_msg = CardinalDirection()
        self.cardinal_direction_pub = rospy.Publisher(
            'drive/cardinal_direction', CardinalDirection, queue_size=1)

        rospy.Subscriber('status/mission_status', MissionStatus,
                         self.status_ms_cb)

        rospy.Subscriber('drive/mission_status', MissionStatus,
                         self.drive_ms_cb)

        rospy.Subscriber('drive/direction_error', DirectionError,
                         self.drive_turn_control_cb)

    def drive_ms_cb(self, data):
        self.drive_mission_data = data.mission_status
        if self.drive_mission_data != self.prev_drive_mission_data:
            temp_mission_data = json.loads(self.drive_mission_data)
            self.direction = temp_mission_data['Direction']
            self.wait = temp_mission_data['Wait']
            self.delay = temp_mission_data['Delay']
            self.prev_drive_mission_data = self.drive_mission_data

    def drive_turn_control_cb(self, data):
        self.direction_error = -float(data.direction_error) / 100

        if self.wait:
            prev_direction = ""
            recorded_time = rospy.Time.now()
            prev_direction = self.direction
            self.direction = "Stop"
            while (rospy.Time.now() - recorded_time < rospy.Duration(self.delay)):
                self.translate_sensordata_to_cardinal()
                rospy.sleep(1)
            self.wait = False
            self.direction = prev_direction

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

    def status_ms_cb(self, data):
        self.status_mission_data = data.mission_status
        if self.status_mission_data != self.prev_status_mission_data:
            temp_mission_data = json.loads(self.status_mission_data)
            self.junction = temp_mission_data['Junction']
            self.junction_ahead = temp_mission_data['JunctionAhead']
            self.end_block = temp_mission_data['EndBlock']
            self.end_mission = temp_mission_data['EndMission']

            self.status_control()

    def status_control(self):
        if self.junction_ahead:
            if self.junction:
                if self.water_mission:
                    if "Left" in self.direction:
                        self.direction = "Right"
                        self.water_mission = False
                    elif "Right" in self.direction:
                        self.direction = "Left"
                        self.water_mission = False
                    elif "Forward" in self.direction:
                        self.direction = "Backward"
                        self.water_mission = False
                    elif "Backward" in self.direction:
                        self.direction = "Forward"
                        self.water_mission = False
            else:
                if self.end_block:
                    self.water_mission = True

    def start(self):
        while not rospy.is_shutdown():
            rospy.sleep(1)


if __name__ == "__main__":
    try:
        nav = Navigation()
        nav.start()
    except rospy.ROSInterruptException:
        pass
