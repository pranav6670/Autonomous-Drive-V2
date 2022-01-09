import numpy as np
import cv2
import utils


def getLaneCurve(img):
    imgThresh = utils.threshold(img)
    cv2.imshow('Threshold Image', imgThresh)
    cv2.waitKey(1)
    return None


if __name__ == '__main__':
    cap = cv2.VideoCapture('test.mp4')
    _, frames = cap.read()
    cv2.imshow('Frames', frames)
    cv2.waitKey(1)
