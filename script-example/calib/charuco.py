import cv2
import cv2.aruco as aruco

image = cv2.imread('script-example\calib\charuco.jpg')

# Giảm độ phân giải của ảnh
image = cv2.resize(image, (0, 0), fx=0.5, fy=0.5)

aruco_dict = aruco.Dictionary_get(aruco.DICT_4X4_50)
parameters = aruco.DetectorParameters_create()

corners, ids, rejectedImgPoints = aruco.detectMarkers(image, aruco_dict, parameters=parameters)

image_with_markers = aruco.drawDetectedMarkers(image, corners, ids)

# Vẽ tọa độ tâm của marker id = 0
for i in range(len(ids)):
    if ids[i] == 0:
        c = corners[i][0]
        cv2.circle(image_with_markers, (int(c[:, 0].mean()), int(c[:, 1].mean())), 10, (0, 0, 255), -1)

cv2.imshow('Detected Markers', image_with_markers)
cv2.waitKey(0)
cv2.destroyAllWindows()