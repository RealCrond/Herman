#!/bin/python3

import sys
import matplotlib.pyplot as plt
import numpy as np
import cv2 as cv
import time

print("Python Version:", sys.version)
print("Opencv Version:", cv.__version__)

x = [12, 34, 11, 43, 2, 8, 3, 1, 9, 23, 5, 6]
#冒泡排序
def popsort(arr):
    for i in range(0, len(arr)):
        for index, item in enumerate(arr[0:len(arr) - i - 1]):
            if arr[index] > arr[index + 1]:
                arr[index], arr[index + 1] = arr[index + 1], arr[index]


for n in range(0, 12, 2):
    print(n)

if( __name__ == "__main__"):
    print("/*********Done")

