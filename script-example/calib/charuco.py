import cv2
import numpy as np
import time

# Đọc ảnh
image = cv2.imread('charuco.jpg')

if image is None:
    print("Không thể đọc file ảnh charuco.jpg")
    exit()

# Giảm độ phân giải của ảnh
image = cv2.resize(image, (0, 0), fx=0.5, fy=0.5)

# Tạo bản copy để xử lý chessboard
image_chessboard = image.copy()

# Tạo dictionary và parameters
aruco_dict = cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_4X4_50)
parameters = cv2.aruco.DetectorParameters()

# Tạo detector
detector = cv2.aruco.ArucoDetector(aruco_dict, parameters)

# Phát hiện markers
corners, ids, rejectedImgPoints = detector.detectMarkers(image)

# Vẽ markers được phát hiện
if ids is not None:
    image_with_markers = cv2.aruco.drawDetectedMarkers(image, corners, ids)
    print(f"Phát hiện được {len(ids)} markers")

# Vẽ tọa độ tâm của marker id = 0
for i in range(len(ids)):
    if ids[i] == 0:
        c = corners[i][0]
            center_x = int(c[:, 0].mean())
            center_y = int(c[:, 1].mean())
            cv2.circle(image_with_markers, (center_x, center_y), 10, (0, 0, 255), -1)
            print(f"Tâm marker ID 0: ({center_x}, {center_y})")
else:
    image_with_markers = image
    print("Không phát hiện được markers nào")

# ===================== CHESSBOARD DETECTION =====================
print("\n--- Nhận diện Chessboard ---")

# Chuyển ảnh sang grayscale để phát hiện chessboard
gray = cv2.cvtColor(image_chessboard, cv2.COLOR_BGR2GRAY)

# ===================== TỰ ĐỘNG NHẬN DIỆN KÍCH THƯỚC CHESSBOARD =====================
print("🔍 Bắt đầu tự động nhận diện kích thước chessboard...")

# Tạo danh sách kích thước thông minh - thử các kích thước phổ biến trước
def generate_smart_sizes():
    """Tạo danh sách kích thước ưu tiên các kích thước phổ biến"""
    # Kích thước phổ biến nhất
    common_sizes = [
        (7, 7), (6, 8), (8, 6), (5, 7), (7, 5), (6, 6), (8, 8),
        (9, 7), (7, 9), (10, 8), (8, 10), (5, 8), (8, 5),
        (4, 6), (6, 4), (9, 9), (10, 10), (4, 4), (5, 5)
    ]
    
    # Tạo danh sách đầy đủ cho các kích thước còn lại
    all_sizes = []
    for w in range(3, 13):  # Giảm range để tối ưu
        for h in range(3, 13):
            if (w, h) not in common_sizes:
                all_sizes.append((w, h))
    
    # Kết hợp: kích thước phổ biến trước, sau đó là các kích thước khác
    return common_sizes + all_sizes

possible_sizes = generate_smart_sizes()
print(f"📊 Sẽ thử {len(possible_sizes)} kích thước (ưu tiên kích thước phổ biến)...")

# Lưu trữ tất cả kết quả tìm được
detected_results = []

# Sử dụng các flags để cải thiện detection
flags = cv2.CALIB_CB_ADAPTIVE_THRESH + cv2.CALIB_CB_NORMALIZE_IMAGE + cv2.CALIB_CB_FAST_CHECK

print("🔎 Đang quét các kích thước...")
start_time = time.time()
early_stop_threshold = 30  # Nếu tìm thấy chessboard với >= 30 corners, có thể dừng sớm

for i, size in enumerate(possible_sizes):
    if i % 25 == 0:  # Progress indicator
        print(f"   Đã thử {i}/{len(possible_sizes)} kích thước...")
    
    ret_temp, corners_temp = cv2.findChessboardCorners(gray, size, flags)
    
    if ret_temp:
        # Tính toán chất lượng detection
        quality_score = len(corners_temp)  # Có thể cải thiện thêm với các metrics khác
        detected_results.append({
            'size': size,
            'corners': corners_temp,
            'quality': quality_score,
            'total_corners': len(corners_temp)
        })
        print(f"✅ Tìm thấy: {size} với {len(corners_temp)} corners")
        
        # Early stopping nếu tìm thấy kết quả rất tốt và đã thử ít nhất 5 kích thước
        if quality_score >= early_stop_threshold and i >= 5:
            print(f"🚀 Early stopping: Tìm thấy chessboard chất lượng cao ({quality_score} corners)")
            break
        
        # Nếu tìm thấy 2 kích thước tốt trong top 15 (kích thước phổ biến)
        if len(detected_results) >= 2 and i < 15:
            # Kiểm tra xem có kết quả nào >= 25 corners không
            best_so_far = max(r['quality'] for r in detected_results)
            if best_so_far >= 25:
                print(f"🎯 Early stopping: Tìm thấy {len(detected_results)} kết quả tốt trong top kích thước phổ biến")
                break
        
        # Nếu tìm thấy 3 kích thước và đã thử ít nhất 20 kích thước
        if len(detected_results) >= 3 and i >= 20:
            print(f"🎯 Tìm thấy đủ kích thước ({len(detected_results)} kết quả), dừng tìm kiếm")
            break

# Chọn kết quả tốt nhất
ret = False
corners = None
chessboard_size = None

if detected_results:
    # Sắp xếp theo chất lượng (số corners nhiều nhất)
    detected_results.sort(key=lambda x: x['quality'], reverse=True)
    
    best_result = detected_results[0]
    ret = True
    corners = best_result['corners']
    chessboard_size = best_result['size']
    
    detection_time = time.time() - start_time
    
    print(f"\n🎯 KẾT QUẢ TỰ ĐỘNG NHẬN DIỆN:")
    print(f"   ✅ Kích thước tốt nhất: {chessboard_size}")
    print(f"   📍 Số corners: {len(corners)}")
    print(f"   🏆 Tổng số kích thước tìm thấy: {len(detected_results)}")
    print(f"   ⏱️  Thời gian nhận diện: {detection_time:.2f} giây")
    print(f"   🔢 Đã thử {i+1}/{len(possible_sizes)} kích thước")
    
    if len(detected_results) > 1:
        print("   🔍 Các kích thước khác được tìm thấy:")
        for j, result in enumerate(detected_results[1:6]):  # Hiển thị top 5
            print(f"      {j+2}. {result['size']} ({result['total_corners']} corners)")
else:
    print("❌ Không tìm thấy chessboard pattern nào")
    print("💡 Thử điều chỉnh ánh sáng hoặc góc chụp ảnh")

if ret:
    print(f"✅ Phát hiện được chessboard với {len(corners)} corners")
    print(f"Kích thước chessboard: {chessboard_size}")
    
    # Tinh chỉnh độ chính xác của corners
    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
    corners_refined = cv2.cornerSubPix(gray, corners, (11, 11), (-1, -1), criteria)
    
    # Vẽ chessboard corners
    cv2.drawChessboardCorners(image_chessboard, chessboard_size, corners_refined, ret)
    
    # Vẽ 4 góc của chessboard với màu sắc đặc biệt
    cols, rows = chessboard_size
    
    # Xác định 4 góc của chessboard
    corner_indices = [
        0,                      # Top-left
        cols - 1,               # Top-right  
        (rows - 1) * cols,      # Bottom-left
        rows * cols - 1         # Bottom-right
    ]
    
    corner_labels = ["Top-Left", "Top-Right", "Bottom-Left", "Bottom-Right"]
    corner_colors = [(0, 255, 0), (255, 0, 0), (0, 0, 255), (255, 255, 0)]  # Green, Blue, Red, Cyan
    
    print("📍 4 Góc của Chessboard:")
    corner_points = []
    
    for i, (idx, label, color) in enumerate(zip(corner_indices, corner_labels, corner_colors)):
        if idx < len(corners_refined):
            x, y = corners_refined[idx][0]
            corner_points.append((int(x), int(y)))
            
            # Vẽ circle lớn cho 4 góc
            cv2.circle(image_chessboard, (int(x), int(y)), 15, color, -1)
            # Vẽ border trắng
            cv2.circle(image_chessboard, (int(x), int(y)), 15, (255, 255, 255), 3)
            # Thêm text label
            cv2.putText(image_chessboard, str(i+1), (int(x-8), int(y+8)), 
                       cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 0, 0), 2)
            print(f"  {i+1}. {label}: ({x:.1f}, {y:.1f})")
    
    # Vẽ đường kết nối giữa 4 góc tạo thành hình chữ nhật
    if len(corner_points) == 4:
        # Vẽ 4 cạnh của hình chữ nhật
        cv2.line(image_chessboard, corner_points[0], corner_points[1], (255, 255, 255), 3)  # Top
        cv2.line(image_chessboard, corner_points[1], corner_points[3], (255, 255, 255), 3)  # Right
        cv2.line(image_chessboard, corner_points[3], corner_points[2], (255, 255, 255), 3)  # Bottom
        cv2.line(image_chessboard, corner_points[2], corner_points[0], (255, 255, 255), 3)  # Left
        print("  ✓ Đã vẽ đường kết nối giữa 4 góc")
    
    # In tọa độ một số corners đầu tiên
    print("\nTọa độ một số corners đầu tiên:")
    for i in range(min(5, len(corners_refined))):
        x, y = corners_refined[i][0]
        print(f"  Corner {i}: ({x:.1f}, {y:.1f})")
    
    # Lưu ảnh chessboard kết quả
    chessboard_output = 'chessboard_result.jpg'
    cv2.imwrite(chessboard_output, image_chessboard)
    print(f"Đã lưu ảnh chessboard kết quả vào: {chessboard_output}")
    
else:
    print("❌ Không phát hiện được chessboard pattern")
    print("Thử điều chỉnh kích thước chessboard_size hoặc kiểm tra ảnh")

# ===================== LƯU KẾT QUẢ TỔNG HỢP =====================
# Tạo ảnh kết hợp cả ArUco và Chessboard
combined_image = np.hstack((image_with_markers, image_chessboard))

# Lưu ảnh kết quả ArUco
aruco_output = 'aruco_result.jpg'
cv2.imwrite(aruco_output, image_with_markers)
print(f"\nĐã lưu ảnh ArUco kết quả vào: {aruco_output}")

# Lưu ảnh kết hợp
combined_output = 'combined_result.jpg'
cv2.imwrite(combined_output, combined_image)
print(f"Đã lưu ảnh kết hợp vào: {combined_output}")

# ===================== TÓM TẮT KẾT QUẢ =====================
print("\n" + "="*50)
print("TÓM TẮT KẾT QUẢ PHÁT HIỆN")
print("="*50)
print(f"📍 ArUco Markers: {len(ids) if ids is not None else 0} markers")
if ids is not None and 0 in ids:
    print("   ✓ Marker ID 0 được tìm thấy")
    
if ret and chessboard_size:
    print(f"🏁 Chessboard: Kích thước {chessboard_size} ({len(corners)} corners)")
else:
    print("🏁 Chessboard: Không phát hiện được")
    
print(f"📁 Files được tạo:")
print(f"   - {aruco_output}")
if ret:
    print(f"   - chessboard_result.jpg")
print(f"   - {combined_output}")
print("="*50)