import math
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy

def calculate_sphere_coordinates(x, y, radius, sphere_center=(0, 0, 0)):
    # Kiểm tra xem điểm có nằm ngoài hình cầu hay không. Nếu có thì gán z = sphere_center[2]
    if (x - sphere_center[0]) ** 2 + (y - sphere_center[1]) ** 2 > radius ** 2:
        return x, y, sphere_center[2]
    
    # Tính toán tọa độ z
    z = math.sqrt(radius ** 2 - (x - sphere_center[0]) ** 2 - (y - sphere_center[1]) ** 2) + sphere_center[2]
    return x, y, z

points = []
radius = 40

sphere_center = (80, 61, -600)

# Cho x thay đổi từ -radius đến radius
for x in range(-radius - 30, radius + 1 + 30):
    y = 0
    try:
        coordinates = calculate_sphere_coordinates(x + sphere_center[0], y + sphere_center[1], radius, sphere_center)
        print(coordinates)
    except ValueError:
        # Nếu điểm không nằm trên hoặc trong hình cầu thì bỏ qua
        print("ValueError")
        continue

    # Thêm điểm vào danh sách
    points.append(coordinates)

# Hiển thị points ra plot
fig = plt.figure()

ax = fig.add_subplot(111, projection='3d')

for point in points:
    ax.scatter(point[0], point[1], point[2], c='r', marker='o')

ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

plt.show()







