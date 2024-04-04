import cv2
import numpy as np

# Đọc ảnh
img = cv2.imread('script-example/basic shape/shapes.jpg')

# Chuyển sang ảnh xám
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# Làm mờ ảnh
blurred = cv2.GaussianBlur(gray, (5, 5), 0)

# Tìm cạnh
edges = cv2.Canny(blurred, 10, 255)
cv2.imshow('Edges', edges)

# Tìm contours
contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Duyệt qua các contours
for cnt in contours:
    # Tính số cạnh gần đúng
    approx = cv2.approxPolyDP(cnt, 0.04 * cv2.arcLength(cnt, True), True)
    
    # Nếu contour có 6 cạnh thì là hình lục giác
    if len(approx) == 6:
        cv2.drawContours(img, [cnt], 0, (0, 255, 0), 2)
        cv2.putText(img, "Hexagon", tuple(cnt[0][0]), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
    
    # Nếu contour có diện tích lớn và tỉ lệ chu vi/diện tích gần hình tròn thì là hình tròn
    area = cv2.contourArea(cnt)
    perimeter = cv2.arcLength(cnt, True)
    if area > 500 and 0.8 < 4 * np.pi * area / (perimeter ** 2) < 1.2:
        cv2.drawContours(img, [cnt], 0, (0, 0, 255), 2)
        cv2.putText(img, "Circle", tuple(cnt[0][0]), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)

# Hiển thị kết quả
cv2.imshow('Shapes Detection', img)
cv2.waitKey(0)
cv2.destroyAllWindows()