#!/usr/bin/python3
import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt

t1 = 50
t2 = 150

cap = cv.VideoCapture(0)
if not cap.isOpened():
    print("Cannot open camera")
    exit()

while True:
    ret, frame = cap.read()
    if not ret:
        print("Can't receive frame (stream end?). Exiting ...")
        break

    edges_image = cv.Canny(frame, t1, t2)
    cv.imshow('Canny', edges_image)
    if cv.waitKey(1) == ord('q'):
        break

cap.release()
cv.destroyAllWindows()