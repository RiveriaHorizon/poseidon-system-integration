#!/usr/bin/env python

import cv2
import imutils
import numpy
import pyzbar.pyzbar as pyzbar
import rospy
from time import sleep
from cv_bridge import CvBridge, CvBridgeError
from sensor_msgs.msg import Image
from psi.msg import DirectionError
from psi.msg import MissionStatus


class ImageAnalysis:
    def __init__(self):
        rospy.init_node('image_analysis', anonymous=False)

        self.bridge = CvBridge()
        rospy.Subscriber('usb_cam/image_raw',
                         Image, self.line_image_cb, queue_size=1, buff_size=2**30)

        self.qr_code_scanner = rospy.Subscriber('usb_cam/image_raw',
                                                Image, self.qr_image_cb, queue_size=1, buff_size=2**30)

        self.de_msg = DirectionError()
        self.direction_error_pub = rospy.Publisher(
            'drive/direction_error', DirectionError, queue_size=1)

        self.mission_status = ""
        self.ms_msg = MissionStatus()
        self.mission_status_pub = rospy.Publisher(
            'mission_status', MissionStatus, queue_size=1)
        rospy.Subscriber("mission_status", MissionStatus,
                         self.mission_status_cb)

    def mission_status_cb(self, data):
        self.mission_status = data.mission_status

    def line_image_cb(self, data):
        # Grab the image from the image message and convert it to opencv format
        image = self.bridge.imgmsg_to_cv2(
            data, desired_encoding='bgr8')

        # Resize the image to allow for faster processing, then blur it,
        # finally converting it to HSV colour space
        blurred_image = cv2.GaussianBlur(image, (11, 11), 0)
        hsv = cv2.cvtColor(blurred_image, cv2.COLOR_BGR2HSV)

        # Construct a mask for the color "black", then perform a
        # series of erosions and dilations to remove any small blobs
        # left in the mask
        lower_black = numpy.array([0,   0,   0])
        # Black color tuning in HSV color space
        # https://stackoverflow.com/questions/25398188/black-color-object-detection-hsv-range-in-opencv
        upper_black = numpy.array([180, 255, 60])
        mask_black = cv2.inRange(hsv, lower_black, upper_black)
        mask_black = cv2.erode(mask_black, None, iterations=2)
        mask_black = cv2.dilate(mask_black, None, iterations=2)

        extraction_black = cv2.bitwise_and(
            blurred_image, blurred_image, mask=mask_black)

        h, w, d = blurred_image.shape

        # find contours in the mask and initialize the current
        # (x, y) center of the ball
        cnts = cv2.findContours(mask_black.copy(), cv2.RETR_EXTERNAL,
                                cv2.CHAIN_APPROX_SIMPLE)
        cnts = imutils.grab_contours(cnts)

        if len(cnts) > 0:
            M_black = cv2.moments(mask_black)
            cx = int(M_black['m10']/M_black['m00'])
            cy = int(M_black['m01']/M_black['m00'])
            cv2.circle(blurred_image, (cx, cy), 20, (0, 0, 255), -1)
            self.de_msg.direction_error = cx - w/2
            self.direction_error_pub.publish(self.de_msg)

        cv2.imshow("Line Following Window",
                   numpy.hstack([blurred_image, extraction_black, hsv]))

        cv2.waitKey(1)

    def qr_image_cb(self, data):
        # Grab the image from the image message and convert it to opencv format
        image = self.bridge.imgmsg_to_cv2(
            data, desired_encoding='bgr8')

        # Get result from the incoming image publisher
        decoded_objects = pyzbar.decode(image)
        for obj in decoded_objects:
            self.ms_msg.mission_status = obj.data
            self.mission_status_pub.publish(self.ms_msg)
            if "Wait" in obj.data:
                self.qr_code_scanner.unregister()

        # Displays the scanned QR Code
        # Loop over all decoded objects
        for decoded_object in decoded_objects:
            points = decoded_object.polygon

            # If the points do not form a quad, find convex hull
            if len(points) > 4:
                hull = cv2.convexHull(
                    numpy.array([point for point in points], dtype=numpy.float32))
                hull = list(map(tuple, numpy.squeeze(hull)))
            else:
                hull = points

            # Number of points in the convex hull
            n = len(hull)

            # Draw the convext hull
            for j in range(0, n):
                cv2.line(image, hull[j], hull[(j+1) % n], (255, 0, 0), 3)

            cv2.imshow("QRCode Image Window", image)

        cv2.waitKey(1)

    def start(self):
        while not rospy.is_shutdown():
            if "Home" in self.mission_status:
                self.qr_code_scanner = rospy.Subscriber('usb_cam/image_raw',
                                                        Image, self.qr_image_cb, queue_size=1, buff_size=2**30)
            rospy.sleep(1)


if __name__ == "__main__":
    try:
        ia = ImageAnalysis()
        ia.start()
    except rospy.ROSInterruptException:
        pass
