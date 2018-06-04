import cv2
import numpy as np

cap=cv2.VideoCapture(0)

while True:
	ret,frame=cap.read()
	img=frame[270:450,190:370]
	frame[100:280,100:280]=img
	cv2.imshow('frame',frame)
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break

cap.release()