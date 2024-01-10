import cv2
import numpy as np
import detect_socket
import time
import sys

def draw_plus(image, center_x, center_y, len):
    # Set the line thickness and color
    thickness = 2
    color = (0, 0, 255)

    # Draw the horizontal lines
    cv2.line(image, (center_x - 20, center_y), (center_x + 20, center_y), color, thickness)

    # Draw the vertical lines
    cv2.line(image, (center_x, center_y - 20), (center_x, center_y + 20), color, thickness)

    return image

def find_worm_pick_position(image, dir = 'top'):

    blurImage = image

    if image.shape[2] > 2:
        # # Convert the image to the HSV color space
        # hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

        # # Define the range of pink colors in the HSV color space
        # lower_pink = np.array([0, 74, 45])
        # upper_pink = np.array([53, 255, 255])

        # # Threshold the image to only select pink colors
        # mask = cv2.inRange(hsv, lower_pink, upper_pink)

        # blurImage = cv2.medianBlur(mask, 7)

        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)       
        blurImage = cv2.threshold(gray, 60, 255, cv2.THRESH_BINARY)[1]
        blurImage = cv2.medianBlur(blurImage, 3)

    find_center(blurImage, image)
    
    cv2.imshow("Image", blurImage)
    # cv2.waitKey(1)
    sum = 0

    x_pick, y_pick = 0, 0

    for i in range(blurImage.shape[0]):
        if dir == 'bottom':
            i = blurImage.shape[0] - i - 1
            
            # Count the number of white pixels in the row
            count = cv2.countNonZero(blurImage[i, :])
            # print(count)

            if count == 0:
                sum = 0

            sum = sum + count
            if sum > 2000:
                y_pick = i

                x_pick = np.where(blurImage[i, :] == 255)[0]
                # print(len(x_pick))
                x_pick = x_pick[len(x_pick) // 2]
                break

        if dir == 'left':
            i = blurImage.shape[1] - i - 1

            # Count the number of white pixels in the column
            count = cv2.countNonZero(blurImage[:, i])
            # print(count)

            if count == 0:
                sum = 0

            sum = sum + count
            if sum > 300:
                x_pick = i

                y_pick = np.where(blurImage[:, i] == 255)[0]
                # print(len(y_pick))
                y_pick = y_pick[len(y_pick) // 2]
                break

    # Find contours in the mask
    contours, hierarchy = cv2.findContours(blurImage, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)

    # Filter contours by size
    min_size = 100
    large_contours = [cnt for cnt in contours if cv2.contourArea(cnt) > min_size]

    # Draw the contours on the image
    # cv2.drawContours(image, large_contours, -1, (0, 255, 0), 3)

    image = draw_plus(image, x_pick, y_pick, 20)

    # cv2.imshow("thres", blurImage)
    cv2.imshow("result", image)

    return int(x_pick), int(y_pick)

def find_center(thres, img):
    contours, hierarchy = cv2.findContours(thres, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    for contour in contours:
        area = cv2.contourArea(contour)
        # print(area)
        if area < 300 or area > 5000:
            continue
        print(area)
        # cv2.drawContours(img, contour, -1, (0, 255, 0), 3)
        img = draw_intersection_and_midpoint(img, thres, contour)

    # Hiển thị ảnh
    cv2.imshow('Image with worm contour and center', img)
    # cv2.waitKey(0)

def centroid(contour):
    M = cv2.moments(contour)
    
    if M['m00'] == 0:
        raise ValueError("Moment 'm00' is zero, cannot calculate centroid.")
    
    cx = int(M['m10'] / M['m00'])
    cy = int(M['m01'] / M['m00'])
    return np.array([cx, cy])


def calculate_direction(contour):
    # Chuyển đổi contour sang mảng numpy và chỉnh lại kích thước của mảng
    contour_points = np.array(contour).reshape(-1, 2).astype(np.float32)
    
    # Tính toán phân tích thành phần chính (PCA)
    mean, eigenvectors = cv2.PCACompute(contour_points, mean=None)
    
    return eigenvectors[0]

def find_best_suction_point(image, worm_contours):
    best_point = None
    max_score = -np.inf

    for contour in worm_contours:
        # Áp dụng PCA để tìm trục chính của giun
        contour_points = np.squeeze(contour)
        pca = PCA(n_components=2)
        pca.fit(contour_points)

        # Tính toán chiều dài giun dựa trên trục chính
        length = np.sqrt(pca.explained_variance_ratio_[0]) * np.sqrt(pca.singular_values_[0])

        # Tìm trung điểm của trục chính
        center = pca.mean_
        direction = pca.components_[0]
        midpoint = center + direction * length / 2

        # Chuyển đổi toạ độ trung điểm từ PCA về không gian ảnh gốc
        midpoint_homogeneous = np.append(midpoint, 1)
        inverse_rotation_matrix = np.linalg.inv(rotation_matrix)
        transformed_midpoint = np.dot(inverse_rotation_matrix, midpoint_homogeneous)[:2]

        # Đánh giá điểm này
        score = length
        if score > max_score:
            max_score = score
            best_point = transformed_midpoint

    return tuple(map(int, best_point))


def draw_intersection_and_midpoint(image, binary_image, contour):

    best_suction_point = find_best_suction_point(image, contour)

    # Đánh dấu điểm hút trên ảnh
    cv2.circle(image, best_suction_point, 5, (0, 255, 0), -1)

    return image

def main2():
    # Load the image
    image = cv2.imread('giun1.jpg')

    # Get the original image size
    height, width, _ = image.shape

    # Specify the new size
    new_height = 600
    new_width = int(width * new_height / height)

    # Resize the image
    image = cv2.resize(image, (new_width, new_height), interpolation=cv2.INTER_LINEAR)
    cv2.imshow("origin", image)

    find_worm_pick_position(image)

    cv2.waitKey(0)

def main():
    HOST = "192.168.101.135"
    PORT = 8844
    detect_socket.ConnectToSoftware(HOST, PORT)

    while True:
        try:
            image = detect_socket.Get_Image()
            x, y = find_worm_pick_position(image, 'bottom')
            
            # print("x:" + str(x) + " y:" + str(y))

            mess = "#Object = "
            mess  += str(0)
            mess  += ", " + str(x)
            mess  += ", " + str(y)
            mess  += ", " + str(30)
            mess  += ", " + str(30)
            mess  += ", " + str(0) +";"
            mess += "\n"

            detect_socket.Software_Socket.sendall(mess.encode())

            # cv2.imshow("Image", image)
            cv2.waitKey(1)
            
        except:
            print("Error:", sys.exc_info()[1])
            detect_socket.ConnectToSoftware(HOST, PORT)
            time.sleep(2)

if __name__ == "__main__":  
    main()

