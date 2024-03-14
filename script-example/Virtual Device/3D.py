from vpython import cylinder, vector, color, rate

# Tạo cánh tay robot
arm_length = 4
arm_radius = 0.2
arm = cylinder(pos=vector(0, 0, 0), axis=vector(arm_length, 0, 0), radius=arm_radius, color=color.yellow)

# Tạo khớp 1
joint1_radius = 0.4
joint1 = cylinder(pos=vector(arm_length, 0, 0), axis=vector(0.5, 0, 0), radius=joint1_radius, color=color.red)

# Tạo phần tiếp theo của cánh tay
forearm_length = 3
forearm_radius = 0.15
forearm = cylinder(pos=joint1.pos + joint1.axis, axis=vector(forearm_length, 0, 0), radius=forearm_radius, color=color.green)

# Tạo khớp 2
joint2_radius = 0.3
joint2 = cylinder(pos=forearm.pos + forearm.axis, axis=vector(0.5, 0, 0), radius=joint2_radius, color=color.blue)

# Chức năng để xoay khớp
def rotate_joint(joint, arm, angle):
    joint.rotate(angle=angle, axis=vector(0, 0, 1), origin=joint.pos)
    arm.pos = joint.pos + vector(joint.radius*2, 0, 0)
    arm.axis = vector(arm_length*cos(angle), arm_length*sin(angle), 0)

# Ví dụ xoay khớp 1
from vpython import sin, cos, pi
for angle in range(0, 360, 5):
    rate(10) # Cập nhật 10 lần mỗi giây
    rotate_joint(joint1, forearm, angle*pi/180)
