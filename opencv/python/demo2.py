#!/usr/bin/env python3
# -*- encoding: utf-8 -*-

import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import cv2 as cv

def show(img):
    matplotlib.use('Agg')

    if img.ndim == 2: #这句话是用来判断是否为灰度图的
        plt.imshow(img, cmap='gray', vmin=0, vmax=255)
    else:
        plt.imshow(cv.cvtColor(img, cv.COLOR_BGR2RGB))


img = cv.imread("./pic1.png")
show(img)
