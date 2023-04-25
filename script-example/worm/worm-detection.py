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
        blurImage = cv2.threshold(gray, 66, 255, cv2.THRESH_BINARY)[1]

    cv2.imshow("Image", blurImage)
    cv2.waitKey(1)
    sum = 0

    x_pick, y_pick = 0, 0

    for i in range(blurImage.shape[0]):
        if dir == 'bottom':
            i = blurImage.shape[0] - i - 1
            
            # Count the number of white pixels in the row
            count = cv2.countNonZero(blurImage[i, :])
            print(count)

            if count == 0:
                sum = 0

            sum = sum + count
            if sum > 300:
                y_pick = i

                x_pick = np.where(blurImage[i, :] == 255)[0]
                print(len(x_pick))
                x_pick = x_pick[len(x_pick) // 2]
                break

        if dir == 'left':
            i = blurImage.shape[1] - i - 1

            # Count the number of white pixels in the column
            count = cv2.countNonZero(blurImage[:, i])
            print(count)

            if count == 0:
                sum = 0

            sum = sum + count
            if sum > 300:
                x_pick = i

                y_pick = np.where(blurImage[:, i] == 255)[0]
                print(len(y_pick))
                y_pick = y_pick[len(y_pick) // 2]
                break

    # Find contours in the mask
    # contours, hierarchy = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)

    # Filter contours by size
    # min_size = 100
    # large_contours = [cnt for cnt in contours if cv2.contourArea(cnt) > min_size]

    # Draw the contours on the image
    # cv2.drawContours(image, large_contours, -1, (0, 255, 0), 3)

    # image = draw_plus(image, x_pick, y_pick, 20)

    # cv2.imshow("thres", blurImage)
    # cv2.imshow("result", image)

    return int(x_pick), int(y_pick)


# # Load the image
# image = cv2.imread('test/py/giun1.jpg')

# # Get the original image size
# height, width, _ = image.shape

# # Specify the new size
# new_height = 600
# new_width = int(width * new_height / height)

# # Resize the image
# image = cv2.resize(image, (new_width, new_height), interpolation=cv2.INTER_LINEAR)
# cv2.imshow("origin", image)

# find_worm_pick_position(image)



# cv2.waitKey(0)

def main():
    HOST = "192.168.101.135"
    PORT = 8844
    detect_socket.ConnectToSoftware(HOST, PORT)

    while True:
        try:
            image = detect_socket.Get_Image()
            x, y = find_worm_pick_position(image, 'bottom')
            
            print("x:" + str(x) + " y:" + str(y))

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
            # cv2.waitKey(1)
            
        except:
            print("Error:", sys.exc_info()[1])
            detect_socket.ConnectToSoftware(HOST, PORT)
            time.sleep(2)

if __name__ == "__main__":  
    main()

