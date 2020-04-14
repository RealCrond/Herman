import cv2 as cv
import numpy as np
import sys

print("Python version:", sys.version)
print("Opencv version:", cv.__version__)

img = cv.imread("data/noaverage.png")
if img is not None:
    print(img.shape)
    gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
    ret, thres = cv.threshold(gray, 50, 255, cv.THRESH_BINARY)
    adaptivethres = cv.adaptiveThreshold(gray, 255, cv.ADAPTIVE_THRESH_GAUSSIAN_C, cv.THRESH_BINARY, 21, 10)
    out = np.hstack((gray,thres,adaptivethres))
    cv.imshow("adaptiveThreshold", out)

    if 27 == cv.waitKey(0):
        cv.destroyAllWindows()
        print("Done")



#1. 读图片或视频
img = cv.imread("data/lene.png")
cap = cv.VideoCapture("data/vtest.avi")
#2. 转化成灰度图
gray = cv.cvtColor(img,cv.COLOR_BGR2GRAY)
#3. 阈值化处理
thres = cv.threshold(gray, 50, 255, cv.THRESH_BINARY)
adaptiveThres = cv.adaptiveThreshold(gray, 255, cv.ADAPTIVE_THRESH_GAUSSIAN_C, cv.THRESH_BINARY, 21, 10)
'''
4. 滤波(
        线性滤波:方框滤波、均值滤波、高斯滤波
        非线性滤波：中值滤波、双边滤波
        形态学滤波： 腐蚀、膨胀、开运算、闭运算、形态学梯度、顶帽、黑帽
       )
'''
'''
5. 图像变换(
            resize()
            remap()
            warpAffine()、warpPerspective()
            金字塔pyrUp、pyrDown
        )
'''
'''
6. 边缘检测
'''
'''
7. 轮廓检测
'''
'''
8. 角点检测
'''
'''
9. 特征检测（HoughLines()、HoughCircles）
'''
'''
10. 直方图
'''
'''
11. 傅里叶变换（高通、低通滤波）
'''
