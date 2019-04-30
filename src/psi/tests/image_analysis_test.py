#!/usr/bin/env python

import roslib
import unittest
import sys
PKG = 'psi'
roslib.load_manifest(PKG)


class TestImageAnalysis(unittest.TestCase):
    pass


if __name__ == '__main__':
    import rostest
    rostest.rosrun(PKG, 'test_image_analysis', TestImageAnalysis)
