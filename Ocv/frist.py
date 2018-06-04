import cv2
import numpy as np
import matplotlib.pyplot as plt

img=cv2.imread('download.png',cv2.IMREAD_GRAYSCALE)
# cv2.imshow('img',img)
# cv2.waitKey(0)

plt.imshow(img,cmap='gray',interpolation='bicubic')
plt.show()
