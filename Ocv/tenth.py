import cv2
import numpy as np

cap=cv2.VideoCapture(0)

while True:
	ret,frame=cap.read()
	img=frame
	cv2.imshow('img',img)
	img=cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
	img=cv2.GaussianBlur(img,(1,1),0)
	img=cv2.Laplacian(img,cv2.CV_64F)
	img=cv2.GaussianBlur(img,(1,1),0)
	cv2.imshow('img',img)

	if cv2.waitKey(1) & 0xFF == ord('q'):
		break
cap.release()