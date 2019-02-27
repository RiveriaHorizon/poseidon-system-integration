#!/usr/bin/env python

from __future__ import print_function
import rospy
from geometry_msgs.msg import Twist
from psi.msg import DriveControl

'''
Primary functions of the Arduino includes:
1. Wheel encoders for distance travelled
2. IMU for straight driving
3. Driving the robot
'''


class Arduino:
    def __init__(self):
        self.arduino_sim_msg = Twist()
        rospy.Subscriber('drive_control',
                         DriveControl, self.drive_cs_cb)
        self.arduino_sim_pub = rospy.Publisher(
            'diff_drive_controller/cmd_vel', Twist, queue_size=3
        )

    def drive_cs_cb(self, data):
        self.arduino_sim_msg.linear = data.cmd_vel.linear
        self.arduino_sim_msg.angular = data.cmd_vel.angular

    def arduino_sim_talker(self):
        self.arduino_sim_pub.publish(self.arduino_sim_msg)

    def start(self):
        rospy.init_node('arduino_sim', anonymous=False)
        while not rospy.is_shutdown():
            self.arduino_sim_talker()
            rospy.sleep(0.5)


if __name__ == "__main__":
    try:
        arduino_sim = Arduino()
        arduino_sim.start()
    except rospy.ROSInterruptException:
        pass
