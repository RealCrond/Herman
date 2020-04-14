import cv2
import matplotlib.pyplot as plt

face_cascade = cv2.CascadeClassifier('data/haarcascades/haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier('data/haarcascades/haarcascade_eye.xml')

video = cv2.VideoCapture("data/Megamind.avi")
while(True):
    ret, img = video.read()
    if img is None:
        break
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.7, 2)
    eyes = eye_cascade.detectMultiScale(gray, 1.7, 2)
    for (x, y, w, h) in faces:
        pass
        cv2.rectangle(img, (x, y), (x + w, y + h), (0, 0, 255), 2)
    for (x, y, w, h) in eyes:
        pass
        #cv2.circle(img, (x, y), w, (0, 0, 255), 2)
    if 27 == cv2.waitKey(50):
        break
    cv2.imshow("Test", img)
plt.close()
video.release()
cv2.destroyAllWindows()

'''
plt.imshow(img[:, :, ::-1])
plt.title("Physics")
plt.show()
'''