import cv2
import numpy as np
import matplotlib.pyplot as plt

img=cv2.imread('12.png')
img=cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
orb=cv2.ORB_create(1000)
kp=orb.detect(img,None)
kp,des = orb.compute(img,kp)
img2=img
img2=cv2.drawKeypoints(img,kp,img2,color=(255,0,0),flags=0)
plt.imshow(img2)
plt.show()
