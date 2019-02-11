import cv2
import pytesseract
import time
import json
import os
import sys

from PIL import Image
from picamera import PiCamera
from picamera.array import PiRGBArray

camera = PiCamera()

while True:
    rawCapture = PiRGBArray(camera)
    time.sleep(0.1)

    camera.capture(rawCapture, format='bgr')
    image = rawCapture.array
    grayImage = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    cv2.imwrite('capture.jpg', grayImage)

    text = pytesseract.image_to_string(image)
#    print(text)

#    cv2.imshow('Image', image)
#    cv2.waitKey(0)

#cv2.imshow('Image', image)
#cv2.waitKey(0)

#IMAGE_FILE = 'capture.jpg'


#img = Image.open('hello.png')
#text = pytesseract.image_to_string(img)
#    print(text.rstrip())
    ocrList = text.split('\n')
    finalList = ' '.join(ocrList).split()

    valueName = ['first','second','third']
    if len(finalList) == len(valueName):
        idx = 0
        dic = {}
        for i in finalList:
            dic[valueName[idx]] = finalList[idx]
            idx += 1

        print(json.dumps(dic, ensure_ascii=False))
        with open('ocr.json', 'w', encoding="utf-8") as make_file:
            json.dump(dic, make_file, ensure_ascii=False)

        os.system('sudo cp ocr.json /var/www/html/webopi')

#    time.sleep(2)

#f = open('ocr.txt', 'w')
#f.write(dic)

#for x in ocrList: 
#  print(x)
