import cv2
import numpy as np

img = "./pic1.png"

origin_img = cv2.imread(img)
input_img = cv2.imread(img)
gray = cv2.cvtColor(input_img, cv2.COLOR_BGR2GRAY)
gray = np.float32(gray)
dst = cv2.cornerHarris(gray, 2, 3, 0.04)
dst = cv2.dilate(dst, None)
input_img[dst > 0.01 * dst.max()] = [0, 0, 255]
cv2.imshow('Original', origin_img)
cv2.imshow('Harris', input_img)
if cv2.waitKey(0) & 0xff == 27:
    cv2.destroyAllWindows()
