import cv2 as cv
from PIL import Image
import numpy as np
import matplotlib.pylab as pylab

img = cv.imread("./pic1.png", -1) # 读取图片并

print(img) #打印图片数值

img = cv.cvtColor(img,cv.COLOR_BGR2RGBA) #将BGR转换成RGB
pylab.imshow(img)

cv.imwrite("./pic3.png", img)
