from cv2 import *
import numpy as np

frame=VideoCapture(0)
while True:
	ret,img=frame.read()
	fresh=img
	grey=cvtColor(img,COLOR_BGR2GRAY)
	grey=GaussianBlur(grey,(7,7),0)
	rows,columns,channels=img.shape
	#grey1=GaussianBlur(grey,(1,1),1)
	gauss=adaptiveThreshold(grey,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,11,2)
	#gauss1=adaptiveThreshold(grey,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,11,2)
	#imshow('gauss',gauss)
	gauss_inv=bitwise_not(gauss)
	blue=img
	blue[0:rows,0:columns]=(150,150,0)
	anded=bitwise_and(blue,blue,mask=gauss_inv)
	#anded1=bitwise_and(frame,frame,mask=gauss)
	added=addWeighted(anded,0.5,anded,0.5,0)
	imshow('anded',frame)
	imshow('added',anded)

	if waitKey(1) & 0xFF == ord('q'):
		break

frame.release()