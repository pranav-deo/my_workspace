import cv2
import numpy as np

cap=cv2.VideoCapture(0)

while True:
	ret, frame=cap.read()
	img = frame 
	#print(ret)
	rows,columns,channels=frame.shape
	img_gray=cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
	ret,mask=cv2.threshold(img_gray,150,255,cv2.THRESH_BINARY_INV)
	#cv2.imshow('grey',mask)
	mask_inv=cv2.bitwise_not(mask)
	white_bkg=frame
	#cv2.imshow('frame',img)
	# for i in range(0,rows):
	# 	for j in range(0,columns):
	#white_bkg[0:rows,0:columns]=(0,255,0)
	#cv2.imshow('img',img)
	anded=cv2.bitwise_and(frame,frame,mask=mask)
	orred=cv2.bitwise_or(img,img,mask=mask)
	#orred=cv2.bitwise_or(frame,frame,mask=mask)
	j=cv2.addWeighted(anded,0.5,orred,0.5,0)
	print(mask[100][100])
	'''
	for row in range (rows):
		for col in range (columns):
			if (img_gray[row][col]==255):
				j[row][col]=frame[row][col]
	'''
	cv2.imshow('j',j)
	cv2.imshow('anded',anded)
	cv2.imshow('orred',orred)
	if cv2.waitKey(1) & 0xFF ==ord('q'):
		break

cap.release()