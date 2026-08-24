import cv2
import numpy as np
from PyQt5.QtCore import QPointF
from PyQt5.QtGui import QTransform, QPolygonF

def calculate_matrix(source_polygon, dest_polygon):
    # Validate the inputs.
    if len(source_polygon) < 4 or len(dest_polygon) < 4:
        raise ValueError("Need at least 4 points in both polygons.")

    # Convert QPolygonF to a NumPy array.
    src_points = np.array([(point.x(), point.y()) for point in source_polygon])
    dst_points = np.array([(point.x(), point.y()) for point in dest_polygon])

    # Calculate the transformation matrix with OpenCV.
    transform_matrix = cv2.getPerspectiveTransform(src_points.astype(np.float32), dst_points.astype(np.float32))

    return transform_matrix



# Source polygon.
source_polygon = QPolygonF([
    QPointF(0, 0),
    QPointF(0, 160),
    QPointF(160, 160),
    QPointF(160, 0)
])

# Destination polygon.
dest_polygon = QPolygonF([
    QPointF(41.5, -160.5),
    QPointF(-118.5, -135.5),
    QPointF(-89.3, 26.3),
    QPointF(71.2, 1.8)
])

# Calculate the transformation matrix.
transform_matrix = calculate_matrix(source_polygon, dest_polygon)

# Validate the calculated matrix.
print("\nTesting the transform matrix:")
for i in range(len(source_polygon)):
    # Read the source point.
    source_point = source_polygon[i]
    # Convert the source point to a NumPy array.
    source_point_array = np.array([source_point.x(), source_point.y(), 1])
    # Calculate the destination point.
    transformed_point = np.dot(transform_matrix, source_point_array)
    # Convert the destination point to QPointF.
    transformed_point = QPointF(transformed_point[0] / transformed_point[2], transformed_point[1] / transformed_point[2])

    # Print the result.

    print(f"Source Point: ({source_polygon[i].x()}, {source_polygon[i].y()})")
    print(f"Transformed Point: ({transformed_point.x()}, {transformed_point.y()})")
    print(f"Destination Point: ({dest_polygon[i].x()}, {dest_polygon[i].y()})")
    print("---")
