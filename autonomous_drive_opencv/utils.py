import cv2
import numpy as np


def threshold(img):
    img_hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    lower_white = np.array([0, 0, 0])
    upper_white = np.array([179, 255, 255])
    mask_white = cv2.inRange(img_hsv, lower_white, upper_white)

def warp(img, points, w, h):



