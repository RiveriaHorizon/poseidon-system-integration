#!/usr/bin/env python

import json
import rospy
from psi.msg import MissionStatus


class Central:
    def __init__(self):
        rospy.init_node('central', anonymous=False)

        self.central_mission_data = ""
        self.prev_central_mission_data = ""

        rospy.Subscriber('central/mission_status', MissionStatus,
                         self.central_mission_cb, queue_size=1)
        self.arm_mission_pub = rospy.Publisher(
            'arm/mission_status', MissionStatus, queue_size=1)
        self.drive_mission_pub = rospy.Publisher(
            'drive/mission_status', MissionStatus, queue_size=1)
        self.status_mission_pub = rospy.Publisher(
            'status/mission_status', MissionStatus, queue_size=1)

    def central_mission_cb(self, data):
        self.central_mission_data = data.mission_status
        if self.central_mission_data != self.prev_central_mission_data:
            try:
                self.arm_mission_control()
                self.drive_mission_control()
                self.status_mission_control()
                self.prev_central_mission_data = self.central_mission_data
            except ValueError:
                rospy.logwarn_once("Invalid QR Code detected.")
                pass

    def drive_mission_control(self):
        # Temporary loading of central mission data into a dict
        temp_central = json.loads(self.central_mission_data)
        temp_drive = temp_central['Drive']
        # Send parsed Drive message
        drive_ms_msg = MissionStatus()
        drive_ms_msg.header.stamp = rospy.Time.now()
        # This should change in the future and be reflected in the
        # urdf when a wheel base link is created
        drive_ms_msg.header.frame_id = "base_link"
        drive_ms_msg.mission_status = json.dumps(temp_drive)
        self.drive_mission_pub.publish(drive_ms_msg)

    def arm_mission_control(self):
        # Temporary loading of central mission data into a dict
        temp_central = json.loads(self.central_mission_data)
        temp_arm = temp_central['Arm']
        # Send parsed Arm message
        arm_ms_msg = MissionStatus()
        arm_ms_msg.header.stamp = rospy.Time.now()
        # Frame id should be changed in the future when the implementation of
        # the right arm is done
        arm_ms_msg.header.frame_id = "left_arm_base"
        arm_ms_msg.mission_status = json.dumps(temp_arm)
        self.arm_mission_pub.publish(arm_ms_msg)

    def status_mission_control(self):
        # Temporary loading of central mission data into a dict
        temp_central = json.loads(self.central_mission_data)
        temp_status = temp_central['Mission']
        # Send parsed Arm message
        status_ms_msg = MissionStatus()
        status_ms_msg.header.stamp = rospy.Time.now()
        # Frame id should be changed in the future when the implementation of
        # the right arm is done
        status_ms_msg.header.frame_id = "base_link"
        status_ms_msg.mission_status = json.dumps(temp_status)
        self.status_mission_pub.publish(status_ms_msg)

    def start(self):
        while not rospy.is_shutdown():
            rospy.sleep(1)


if __name__ == "__main__":
    try:
        central = Central()
        central.start()
    except rospy.ROSInterruptException:
        pass
