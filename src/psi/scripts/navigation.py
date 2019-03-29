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
        self.junction = False
        self.follow_up = False
        self.end_block = False
        self.end_mission = False
        self.water_mission = False

        self.drive_mission_data = ""
        self.prev_drive_mission_data = ""
        self.direction = ""
        self.follow_up_direction = ""
        self.wait = False
        self.delay = 0.0
        self.direction_error = 0.0
        self.prev_direction_error = 0.0
        self.cardinal_direction = ""

        self.orientation_z = 0.0
        self.prev_orientation_z = 0.0

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

        rospy.Subscriber('sensors/imu', Imu, self.imu_cb)

    def drive_ms_cb(self, data):
        self.drive_mission_data = data.mission_status
        if self.drive_mission_data != self.prev_drive_mission_data:
            temp_mission_data = json.loads(self.drive_mission_data)
            self.direction = temp_mission_data['Direction']
            self.follow_up_direction = temp_mission_data['Follow-up-Direction']
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
                self.navigate()
                rospy.sleep(1)
            self.wait = False
            self.direction = prev_direction

        self.navigate()

    def imu_cb(self, data):
        self.orientation_z = data.orientation.z

    def navigate(self):
        self.cd_msg.header.stamp = rospy.Time.now()
        # This shoud change in the future when the wheel base link is
        # created and implemented in the urdf
        self.cd_msg.header.frame_id = "base_link"

        # Stop is always the first priority. If a stop is detected, execute the motion immediately.
        if "Stop" in self.direction:
            self.cardinal_direction = "T"
        # If there isn't a stop, determine the decision tree path to execute.
        else:
            # Determine if there is a junction.
            if self.junction:
                # Check if we have already reached the end of the block aisle
                # If the end_block flag has been triggered, we reverse the turn direction.
                if self.end_block:
                    # Execute the direction, which is a turn action, however, we reverse the turn direction.
                    if "Left" in self.direction:
                        # Determine the heading, and check if we have turned 90 degrees
                        self.prev_orientation_z = self.orientation_z
                        self.cardinal_direction = "E"
                        # Publish the message to turn the robot
                        self.cd_msg.cardinal_direction = self.cardinal_direction
                        self.cardinal_direction_pub.publish(self.cd_msg)
                        while (self.orientation_z - self.prev_orientation_z < 90):
                            self.cardinal_direction = "E"
                            # Publish as long as the vehicle hasn't reach the 90 degrees
                            self.cd_msg.cardinal_direction = self.cardinal_direction
                            self.cardinal_direction_pub.publish(self.cd_msg)
                            rospy.sleep(1)
                        if self.follow_up:
                            if "Forward" in self.follow_up_direction:
                                self.direction = self.follow_up_direction
                                # Publish message to move robot
                                self.cd_msg.cardinal_direction = self.cardinal_direction
                                self.cardinal_direction_pub.publish(
                                    self.cd_msg)
                    elif "Right" in self.direction:
                        # Determine the heading, and check if we have turned 90 degrees
                        self.prev_orientation_z = self.orientation_z
                        self.cardinal_direction = "W"
                        # Publish the message to turn the robot
                        self.cd_msg.cardinal_direction = self.cardinal_direction
                        self.cardinal_direction_pub.publish(self.cd_msg)
                        while (self.orientation_z - self.prev_orientation_z < 90):
                            self.cardinal_direction = "W"
                            # Publish the message to turn the vehicle as long as the heading hasn't reach 90 degrees
                            self.cd_msg.cardinal_direction = self.cardinal_direction
                            self.cardinal_direction_pub.publish(self.cd_msg)
                            rospy.sleep(1)
                        if self.follow_up:
                            if "Forward" in self.follow_up_direction:
                                self.direction = self.follow_up_direction
                                # Publish the message to move robot
                                self.cd_msg.cardinal_direction = self.cardinal_direction
                                self.cardinal_direction_pub.publish(
                                    self.cd_msg)
                else:  # If the end_block flag hasn't been triggered, we follow the motion in the qr code.
                    # Execute the direction, which is a turn action
                    if "Left" in self.direction:
                        # Determine the heading, and check if we have turned 90 degrees
                        self.prev_orientation_z = self.orientation_z
                        self.cardinal_direction = "W"
                        # Publish the message to turn the robot
                        self.cd_msg.cardinal_direction = self.cardinal_direction
                        self.cardinal_direction_pub.publish(self.cd_msg)
                        while (self.orientation_z - self.prev_orientation_z < 90):
                            self.cardinal_direction = "W"
                            # Publish the message to turn the robot as long as the desired heading hasn't reach
                            self.cd_msg.cardinal_direction = self.cardinal_direction
                            self.cardinal_direction_pub.publish(self.cd_msg)
                            rospy.sleep(1)
                        if self.follow_up:
                            if "Forward" in self.follow_up_direction:
                                self.direction = self.follow_up_direction
                                # Publish message to move the robot
                                self.cd_msg.cardinal_direction = self.cardinal_direction
                                self.cardinal_direction_pub.publish(
                                    self.cd_msg)
                    elif "Right" in self.direction:
                        # Determine the heading, and check if we have turned 90 degrees
                        self.prev_orientation_z = self.orientation_z
                        self.cardinal_direction = "E"
                        # Publish message to turn the robot
                        self.cd_msg.cardinal_direction = self.cardinal_direction
                        self.cardinal_direction_pub.publish(self.cd_msg)
                        while (self.orientation_z - self.prev_orientation_z < 90):
                            self.cardinal_direction = "E"
                            # Publish message as long as the desired heading hasn't been reached
                            self.cd_msg.cardinal_direction = self.cardinal_direction
                            self.cardinal_direction_pub.publish(self.cd_msg)
                            rospy.sleep(1)
                        if self.follow_up:
                            if "Forward" in self.follow_up_direction:
                                self.direction = self.follow_up_direction
                                # Publish message to move the robot
                                self.cd_msg.cardinal_direction = self.cardinal_direction
                                self.cardinal_direction_pub.publish(
                                    self.cd_msg)

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
            self.follow_up = temp_mission_data['Follow-up']
            self.end_block = temp_mission_data['EndBlock']
            self.end_mission = temp_mission_data['EndMission']

    def start(self):
        while not rospy.is_shutdown():
            rospy.sleep(1)


if __name__ == "__main__":
    try:
        nav = Navigation()
        nav.start()
    except rospy.ROSInterruptException:
        pass
