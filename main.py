import cv2
from cvzone.HandTrackingModule import HandDetector
from cvzone.SerialModule import SerialObject
cap = cv2.VideoCapture(0)
if not cap.isOpened():
        print("Error: Unable to open webcam.")
prev_fingers = None
detector = HandDetector(maxHands=1, detectionCon=0.7)
mySerial = SerialObject("COM6", 9600, 1)
while True:
    success, img = cap.read()
    if not success:
            print("Error: Failed to capture frame from webcam.")
            break
    imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img = detector.findHands(imgRGB)
    if img is not None:
            cv2.imshow('Webcam', imgRGB)
    lmList, bbox = detector.findHands(imgRGB)
    if lmList:
         fingers = detector.fingersUp(lmList[0])

         if prev_fingers is None or fingers != prev_fingers:
            print(fingers)
            mySerial.sendData(fingers)

         prev_fingers = fingers
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
