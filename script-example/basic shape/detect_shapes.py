import cv2
import numpy as np

def convert_background(image):
    # Chuyển ảnh sang không gian màu HSV
    hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    
    # Xác định khoảng giá trị HSV của màu xanh lá cây
    lower_green = np.array([50, 0, 0])
    upper_green = np.array([80, 255, 255])
    
    # Tạo mặt nạ nhị phân cho nền xanh lá cây
    mask_green = cv2.inRange(hsv, lower_green, upper_green)

    # làm mờ ảnh để loại bỏ nhiễu
    mask_green = cv2.GaussianBlur(mask_green, (1, 1), 0)
    
    # Tạo mặt nạ nghịch đảo cho các đối tượng còn lại
    mask_objects = cv2.bitwise_not(mask_green)
    
    # Tạo ảnh kết quả với nền đen và các đối tượng trắng
    result = np.zeros_like(image)
    result[mask_objects > 0] = (255, 255, 255)
    
    return result

def Find_Hexagon_And_Circle(gray):

    # Làm mờ ảnh
    blurred = cv2.GaussianBlur(gray, (5, 5), 0)

    # Tìm cạnh
    edges = cv2.Canny(blurred, 100, 255)

    # Tìm contours
    contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Duyệt qua các contours
    for cnt in contours:
        # Tính số cạnh gần đúng
        approx = cv2.approxPolyDP(cnt, 0.04 * cv2.arcLength(cnt, True), True)

        print(len(approx))
        
        # Nếu contour có 6 cạnh thì là hình lục giác
        if len(approx) == 6:
            cv2.drawContours(img, [cnt], 0, (0, 255, 0), 2)
            cv2.putText(img, "Hexagon", tuple(cnt[0][0]), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

            continue
        
        # Nếu contour có diện tích lớn và tỉ lệ chu vi/diện tích gần hình tròn thì là hình tròn
        area = cv2.contourArea(cnt)
        perimeter = cv2.arcLength(cnt, True)
        if area > 500 and 0.8 < 4 * np.pi * area / (perimeter ** 2) < 1.2:
            cv2.drawContours(img, [cnt], 0, (0, 0, 255), 2)
            cv2.putText(img, "Circle", tuple(cnt[0][0]), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
    return img

# Đọc ảnh
img = cv2.imread('script-example/basic shape/shapes2.jpg')

# # Chuyển sang ảnh xám
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

result = Find_Hexagon_And_Circle(gray)

# Dùng threshold để lọc ra hình khối màu đen
_, gray2 = cv2.threshold(gray, 150, 255, cv2.THRESH_BINARY_INV)

result2 = Find_Hexagon_And_Circle(gray2)
cv2.imshow('Image', gray2)



# Hiển thị kết quả
cv2.imshow('Shapes Detection', result)
cv2.waitKey(0)
cv2.destroyAllWindows()