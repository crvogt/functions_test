#!/bin/bash

rosparam set usb_cam/pixel_format yuyv
rosrun image_transport republish raw in:=/usb_cam/image_raw raw out:=/camera/image_raw

#vocabulary and settings files need to be modified
rosrun ORB_SLAM2 Mono /home/carson/ORB_SLAM2/Vocabulary /home/carson/ORB_SLAM2/Examples/Monocular
