#!/usr/bin/env python

import cv2
import imutils
import numpy
import pyzbar.pyzbar as pyzbar
import rospy
from time import sleep
from matplotlib import pyplot as plt
from cv_bridge import CvBridge, CvBridgeError
from sensor_msgs.msg import Image
from psi.msg import DirectionError
from psi.msg import MissionStatus

from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from matplotlib import colors


class ImageAnalysis:
    def __init__(self):
        rospy.init_node('image_analysis', anonymous=False)

        self.bridge = CvBridge()
        rospy.Subscriber('usb_cam/image_raw',
                         Image, self.line_image_cb,
                         queue_size=1, buff_size=2**30)

        rospy.Subscriber('usb_cam/image_raw',
                         Image, self.qr_image_cb,
                         queue_size=1, buff_size=2**30)

        self.de_msg = DirectionError()
        self.direction_error_pub = rospy.Publisher(
            'drive/direction_error', DirectionError, queue_size=1)

        self.mission_status = ""
        self.ms_msg = MissionStatus()
        self.mission_status_pub = rospy.Publisher(
            'central/mission_status', MissionStatus, queue_size=1)

    def line_image_cb(self, data):
        # Grab the image from the image message and convert it to opencv format
        image = self.bridge.imgmsg_to_cv2(
            data, desired_encoding='bgr8')

        # Resize the image by half to allow for faster processing, then blur it,
        # finally converting it to HSV colour space
        # https://medium.freecodecamp.org/getting-started-with-tesseract-part-ii-f7f9a0899b3f
        image = cv2.resize(image, (0, 0), fx=0.125, fy=0.125,
                           interpolation=cv2.INTER_AREA)
        blurred_image = cv2.GaussianBlur(image, (11, 11), 0)

        # r, g, b = cv2.split(image)
        # hsv = cv2.cvtColor(image, cv2.COLOR_RGB2HSV)
        # h, s, v = cv2.split(hsv)
        # fig = plt.figure()
        # axis = fig.add_subplot(1, 1, 1, projection="3d")
        # pixel_colors = image.reshape(
        #     (numpy.shape(image)[0]*numpy.shape(image)[1], 3))
        # norm = colors.Normalize(vmin=-1., vmax=1.)
        # norm.autoscale(pixel_colors)
        # pixel_colors = norm(pixel_colors).tolist()
        # axis.scatter(h.flatten(), s.flatten(), v.flatten(),
        #              facecolors=pixel_colors, marker=".")
        # axis.set_xlabel("Hue")
        # axis.set_ylabel("Saturation")
        # axis.set_zlabel("Value")
        # plt.show()

        hsv = cv2.cvtColor(blurred_image, cv2.COLOR_BGR2HSV)

        # Construct a mask for the color "black", then perform a
        # series of erosions and dilations to remove any small blobs
        # left in the mask
        lower_black = numpy.array([0,   0,   0])
        # Black color tuning in HSV color space
        # https://stackoverflow.com/questions/25398188/black-color-object-detection-hsv-range-in-opencv
        # vary lower and upper bound from light conditions obtained from camera
        upper_black = numpy.array([180, 255, 70])
        mask_black = cv2.inRange(hsv, lower_black, upper_black)
        mask_black = cv2.erode(mask_black, None, iterations=2)
        mask_black_higher = cv2.dilate(mask_black, None, iterations=2)

        upper_black = numpy.array([180, 255, 40])
        mask_black = cv2.inRange(hsv, lower_black, upper_black)
        mask_black = cv2.erode(mask_black, None, iterations=2)
        mask_black_lower = cv2.dilate(mask_black, None, iterations=2)

        # https://www.learnopencv.com/invisibility-cloak-using-color-detection-and-segmentation-with-opencv/
        mask_black = mask_black_higher + mask_black_lower

        black_extracted = cv2.bitwise_and(
            blurred_image, blurred_image, mask=mask_black_lower)

        # find contours in the mask and initialize the current
        # (x, y) center of the ball
        cnts = cv2.findContours(mask_black.copy(), cv2.RETR_EXTERNAL,
                                cv2.CHAIN_APPROX_SIMPLE)
        cnts = imutils.grab_contours(cnts)

        h, w, d = blurred_image.shape

        if len(cnts) > 0:
            M_black = cv2.moments(mask_black)
            cx = int(M_black['m10']/M_black['m00'])
            cy = int(M_black['m01']/M_black['m00'])
            cv2.circle(blurred_image, (cx, cy), 20, (0, 0, 255), -1)
            self.de_msg.direction_error = cx - w/2
            self.de_msg.header.stamp = rospy.Time.now()
            # This should change in the future and be reflected in the urdf
            # when a wheel base link is created
            self.de_msg.header.frame_id = "base_link"
            self.direction_error_pub.publish(self.de_msg)

        cv2.imshow("Line Following Window",
                   numpy.hstack([image, blurred_image, black_extracted]))
        cv2.imshow("Binary Mask", mask_black)

        cv2.waitKey(1)

    def qr_image_cb(self, data):
        # Grab the image from the image message and convert it to opencv format
        image = self.bridge.imgmsg_to_cv2(
            data, desired_encoding='bgr8')
        image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        blur = cv2.GaussianBlur(image, (5, 5), 0)
        # plt.hist(image.ravel(), 256, [0, 256])
        # plt.xlabel('Bins')
        # plt.ylabel('Pixel Count')
        # plt.show()
        ret3, th3 = cv2.threshold(
            blur, 0, 255, cv2.THRESH_BINARY+cv2.THRESH_OTSU)
        cv2.imshow("Quick Response Code", th3)
        # Get result from the incoming image publisher
        decoded_objects = pyzbar.decode(th3)
        for obj in decoded_objects:
            self.ms_msg.header.stamp = rospy.Time.now()
            # This should change in the future and be reflected in the
            # urdf when a wheel base link is created
            self.ms_msg.header.frame_id = "base_link"
            self.ms_msg.mission_status = obj.data
            self.mission_status_pub.publish(self.ms_msg)

        # Displays the scanned QR Code for debugging
        # Loop over all decoded objects
        for decoded_object in decoded_objects:
            points = decoded_object.polygon

            # If the points do not form a quad, find convex hull
            if len(points) > 4:
                hull = cv2.convexHull(
                    numpy.array([point for point in points],
                                dtype=numpy.float32))
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
            rospy.sleep(1)


if __name__ == "__main__":
    try:
        ia = ImageAnalysis()
        ia.start()
    except rospy.ROSInterruptException:
        pass
