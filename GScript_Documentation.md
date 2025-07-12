# 🤖 Hướng dẫn sử dụng GScript

**Delta X Software - Ngôn ngữ lập trình robot tự động**

## 📋 Mục lục

1. [Giới thiệu GScript](#1-giới-thiệu-gscript)
2. [Cú pháp cơ bản](#2-cú-pháp-cơ-bản)
   - [2.1. Biến (Variables)](#21-biến-variables)
   - [2.2. Chú thích (Comments)](#22-chú-thích-comments)
   - [2.3. Biểu thức toán học](#23-biểu-thức-toán-học)
3. [Luồng điều khiển](#3-luồng-điều-khiển)
   - [3.1. GOTO - Nhảy dòng](#31-goto---nhảy-dòng)
   - [3.2. IF...THEN - Điều kiện](#32-ifthen---điều-kiện)
4. [Chương trình con](#4-chương-trình-con)
5. [Hàm toán học](#5-hàm-toán-học)
6. [Điều khiển thiết bị](#6-điều-khiển-thiết-bị)
7. [Ví dụ thực tế](#7-ví-dụ-thực-tế)

---

## 1. 🌟 Giới thiệu GScript

**GScript** là ngôn ngữ lập trình tích hợp trong Delta X Software, được thiết kế đặc biệt để điều khiển robot Delta X và các thiết bị tự động hóa.

### ✅ Ưu điểm chính:
- 🎯 Dễ học, cú pháp đơn giản
- 🔧 Tích hợp sẵn điều khiển robot
- 📊 Hỗ trợ biến và biểu thức toán học
- 🔄 Chương trình con và vòng lặp
- 📷 Tích hợp xử lý hình ảnh

---

## 2. 📝 Cú pháp cơ bản

### 2.1. 🔢 Biến (Variables)

Biến trong GScript bắt đầu bằng dấu `#` và có thể lưu trữ số, chuỗi, điểm, vector.

```gcode
; Khai báo và gán biến số
#counter = 0
#speed = 100.5
#robot_name = "Delta_X"

; Biến điểm 2D
#point2d = (150, 200)

; Biến điểm 3D
#point3d = (150, 200, 80)

; Truy cập thành phần của điểm
#x_pos = #point3d.X
#y_pos = #point3d.Y
#z_pos = #point3d.Z
```

> ⚠️ **Lưu ý:** Tên biến có thể chứa chữ cái, số và dấu gạch dưới. Không được bắt đầu bằng số.

### 2.2. 💬 Chú thích (Comments)

Sử dụng dấu `;` để thêm chú thích vào code:

```gcode
; Đây là chú thích dòng đầy đủ
G01 X100 Y200 ; Chú thích cuối dòng
```

### 2.3. 🧮 Biểu thức toán học

GScript hỗ trợ các phép toán cơ bản và nâng cao:

| Toán tử | Mô tả | Ví dụ |
|---------|-------|-------|
| `+` | Cộng | `#result = #a + #b` |
| `-` | Trừ | `#result = #a - #b` |
| `*` | Nhân | `#result = #a * #b` |
| `/` | Chia | `#result = #a / #b` |
| `%` | Chia lấy dư | `#result = #a % #b` |

```gcode
; Ví dụ biểu thức toán học
#radius = 50
#height = #robot0.HOME_Z - 80
#position_x = #center_x + #radius * 2

; Sử dụng trong G-code
G01 X[#position_x] Y[#center_y] Z[#height]
```

---

## 3. 🔄 Luồng điều khiển

### 3.1. ➡️ GOTO - Nhảy dòng

Lệnh `GOTO` cho phép nhảy đến một dòng khác trong chương trình:

```gcode
N05 #counter = 0
N10 #counter = #counter + 1
N15 G01 X[#counter * 10] Y100
N20 GOTO 10 ; Nhảy về dòng N10
```

> ⚠️ **Cẩn thận:** Sử dụng GOTO có thể tạo vòng lặp vô hạn. Luôn có điều kiện dừng.

### 3.2. ❓ IF...ELIF...ELSE...ENDIF - Điều kiện

GScript hỗ trợ cấu trúc điều kiện hoàn chỉnh với IF-ELIF-ELSE-ENDIF:

#### 3.2.1. Cú pháp đơn giản (Single-line):

```gcode
; Cú pháp: IF [điều kiện] THEN [lệnh]
IF #counter == 5 THEN GOTO 100
IF #sensor_value > 50 THEN M05

; Với ELIF và ELSE
IF #temp > 80 THEN M05
ELIF #temp > 60 THEN M04
ELSE M03
```

#### 3.2.2. Cú pháp khối (Multi-line):

```gcode
; Cú pháp khối hoàn chỉnh
IF #counter < 5 THEN
    G01 X[#counter * 10] Y100
    M03
    G04 P1000
ELIF #counter < 10 THEN
    G01 X[#counter * 5] Y200
    M04
ELSE
    G01 X300 Y300
    M05
ENDIF
```

#### 3.2.3. Nested IF (IF lồng nhau):

```gcode
IF #mode == 1 THEN
    IF #counter > 5 THEN
        G01 X100 Y100
        M03
    ELSE
        G01 X200 Y200
        M04
    ENDIF
ELIF #mode == 2 THEN
    G01 X300 Y300
    M05
ELSE
    G28 ; Về Home
ENDIF
```

| Toán tử so sánh | Mô tả | Ví dụ |
|-----------------|-------|-------|
| `==` | Bằng | `IF #a == 5 THEN GOTO 100` |
| `!=` | Khác | `IF #a != 0 THEN M03` |
| `>` | Lớn hơn | `IF #temp > 60 THEN M05` |
| `<` | Nhỏ hơn | `IF #speed < 100 THEN G01 F200` |
| `>=` | Lớn hơn hoặc bằng | `IF #counter >= 10 THEN GOTO 50` |
| `<=` | Nhỏ hơn hoặc bằng | `IF #pressure <= 30 THEN M04` |

---

## 4. 🔧 Chương trình con

Sử dụng chương trình con để tái sử dụng code và tổ chức chương trình tốt hơn:

### 4.1. Định nghĩa chương trình con

```gcode
; Định nghĩa chương trình con
O2001 ; Bắt đầu chương trình con số 2001
    G01 Z[#robot0.HOME_Z - 50]
    M03 ; Bật gripper
    G04 P1000 ; Chờ 1 giây
    M05 ; Tắt gripper
M99 ; Kết thúc chương trình con
```

### 4.2. Gọi chương trình con

```gcode
; Gọi chương trình con
M98 P2001 ; Gọi chương trình con O2001
```

### 4.3. Macro Functions

| Function | Mô tả | Ví dụ |
|----------|-------|-------|
| `M98 PclearObjects` | Xóa tất cả objects | `M98 PclearObjects listName` |
| `M98 PpauseCamera` | Tạm dừng camera | `M98 PpauseCamera` |
| `M98 PcaptureCamera` | Chụp ảnh | `M98 PcaptureCamera` |
| `M98 PresumeCamera` | Tiếp tục camera | `M98 PresumeCamera` |
| `M98 Pdelay(ms)` | Chờ thời gian | `M98 Pdelay(2000)` |

---

## 5. 📐 Hàm toán học

GScript cung cấp các hàm toán học tích hợp:

| Hàm | Mô tả | Ví dụ |
|-----|-------|-------|
| `#sin(angle)` | Sin (độ) | `#y = #sin(30)` |
| `#cos(angle)` | Cos (độ) | `#x = #cos(45)` |
| `#tan(angle)` | Tan (độ) | `#slope = #tan(60)` |
| `#atan(value)` | Arctan (ra độ) | `#angle = #atan(1)` |
| `#atan2(y,x)` | Arctan2 (ra độ) | `#angle = #atan2(1,1)` |
| `#abs(value)` | Giá trị tuyệt đối | `#dist = #abs(-5)` |
| `#sqrt(value)` | Căn bậc hai | `#hyp = #sqrt(25)` |
| `#pow(base,exp)` | Lũy thừa | `#result = #pow(2,3)` |
| `#round(value)` | Làm tròn | `#int = #round(3.7)` |

### Ví dụ tính toán vị trí điểm trên đường tròn:

```gcode
#center_x = 100
#center_y = 150
#radius = 50
#angle = 45

#x = #center_x + #radius * #cos(#angle)
#y = #center_y + #radius * #sin(#angle)

G01 X[#x] Y[#y]
```

---

## 6. 🎛️ Điều khiển thiết bị

### 6.1. Robot Control

| Lệnh | Mô tả | Ví dụ |
|------|-------|-------|
| `G28` | Về Home | `G28` |
| `G01` | Di chuyển thẳng | `G01 X100 Y200 Z50 F1000` |
| `G02` | Di chuyển cung thuận chiều kim đồng hồ | `G02 X100 Y100 I50 J0` |
| `G03` | Di chuyển cung ngược chiều kim đồng hồ | `G03 X100 Y100 I50 J0` |
| `G04` | Tạm dừng (ms) | `G04 P1000` |

### 6.2. End Effector Control

| Lệnh | Mô tả | Ví dụ |
|------|-------|-------|
| `M03` | Bật Gripper/Laser | `M03 S100` |
| `M04` | Bật Gripper ngược chiều | `M04 S50` |
| `M05` | Tắt Gripper/Laser | `M05` |
| `M360` | Chọn End Effector | `M360 E1` |

### 6.3. Conveyor Control

| Lệnh | Mô tả | Ví dụ |
|------|-------|-------|
| `M310` | Chọn chế độ tốc độ | `M310 S1` |
| `M311` | Đặt tốc độ | `M311 S100` |
| `M312` | Đặt vị trí | `M312 X100` |
| `M313` | Tốc độ cho di chuyển vị trí | `M313 S200` |

### 6.4. Device Selection

```gcode
; Chọn thiết bị mặc định
SELECT robot0 ; Chọn robot
SELECT conveyor0 ; Chọn conveyor
SELECT device0 ; Chọn device

; Gửi lệnh đến thiết bị cụ thể
robot0 G01 X100 Y200
conveyor0 M311 S100
```

---

## 7. 🎯 Ví dụ thực tế

### 7.1. Chương trình Pick & Place cơ bản

```gcode
; Chương trình Pick & Place đơn giản
G28 ; Về Home
G01 F1000 ; Đặt tốc độ

; Vị trí pick
#pick_x = 100
#pick_y = 200
#pick_z = -150

; Vị trí place
#place_x = 300
#place_y = 200
#place_z = -150

; Di chuyển đến vị trí pick
G01 X[#pick_x] Y[#pick_y] Z-50
G01 Z[#pick_z]
M03 ; Bật gripper
G04 P1000 ; Chờ 1 giây
G01 Z-50

; Di chuyển đến vị trí place
G01 X[#place_x] Y[#place_y]
G01 Z[#place_z]
M05 ; Tắt gripper
G04 P500
G01 Z-50
G28 ; Về Home
```

### 7.2. Vòng lặp với điều kiện

```gcode
; Vòng lặp pick 5 objects
#counter = 0
#max_objects = 5

N10 ; Nhãn vòng lặp
    IF #counter >= #max_objects THEN GOTO 100
    
    ; Tính vị trí object tiếp theo
    #x_pos = 100 + #counter * 50
    
    ; Pick object
    G01 X[#x_pos] Y200 Z-50
    G01 Z-150
    M03
    G04 P1000
    G01 Z-50
    
    ; Place object
    G01 X300 Y[200 + #counter * 30]
    G01 Z-150
    M05
    G01 Z-50
    
    #counter = #counter + 1
    GOTO 10

N100 ; Kết thúc
G28
```

### 7.3. Sử dụng Vision và Tracking

```gcode
; Chương trình với vision tracking
M98 PcaptureCamera ; Chụp ảnh
M98 PupdateTracking(0) ; Cập nhật tracking

; Lấy object đầu tiên trong list
#object_x = #objects.0.X
#object_y = #objects.0.Y
#object_angle = #objects.0.A

; Di chuyển đến object
G01 X[#object_x] Y[#object_y] W[#object_angle]
G01 Z-150
M03

; Xóa object đã pick
M98 PdeleteFirstObject
```

### 7.4. Matrix Transformation

```gcode
; Sử dụng ma trận biến đổi
#source_point = (100, 150)
#transform_matrix = #project0.tracking0.calibMatrix

; Áp dụng biến đổi
#target_point = #transform_matrix.Map(#source_point)

; Di chuyển đến điểm đã biến đổi
G01 X[#target_point.X] Y[#target_point.Y]
```

### 7.5. Sử dụng IF-ELIF-ELSE-ENDIF nâng cao

```gcode
; Chương trình phân loại và xử lý objects theo kích thước
G28 ; Về Home
M98 PcaptureAndDetect ; Chụp ảnh và phát hiện objects

#object_count = 0
#max_objects = 20

N500 ; Vòng lặp chính
    ; Kiểm tra xem còn objects không
    IF #objects.0.X == NULL THEN
        GOTO 999 ; Kết thúc nếu hết objects
    ENDIF
    
    ; Lấy kích thước object
    #object_width = #objects.0.W
    #object_length = #objects.0.L
    #object_area = #object_width * #object_length
    
    ; Phân loại object theo kích thước
    IF #object_area > 2000 THEN
        ; Object lớn - đặt vào khu vực A
        G01 X[100 + #object_count * 40] Y100
        G01 Z-150
        M03 ; Bật gripper
        G04 P1000
        G01 Z-50
        
        ; Đặt vào khu vực A
        G01 X500 Y100
        G01 Z-150
        M05 ; Tắt gripper
        G01 Z-50
        
    ELIF #object_area > 1000 THEN
        ; Object trung bình - đặt vào khu vực B
        G01 X[100 + #object_count * 40] Y200
        G01 Z-150
        M03
        G04 P1000
        G01 Z-50
        
        ; Đặt vào khu vực B
        G01 X500 Y200
        G01 Z-150
        M05
        G01 Z-50
        
    ELIF #object_area > 500 THEN
        ; Object nhỏ - đặt vào khu vực C
        G01 X[100 + #object_count * 40] Y300
        G01 Z-150
        M03
        G04 P1000
        G01 Z-50
        
        ; Đặt vào khu vực C
        G01 X500 Y300
        G01 Z-150
        M05
        G01 Z-50
        
    ELSE
        ; Object quá nhỏ - bỏ qua hoặc loại bỏ
        G01 X[100 + #object_count * 40] Y400
        G01 Z-150
        M03
        G04 P500 ; Chờ ngắn hơn
        G01 Z-50
        
        ; Đặt vào khu vực loại bỏ
        G01 X600 Y400
        G01 Z-150
        M05
        G01 Z-50
    ENDIF
    
    ; Xóa object đã xử lý
    M98 PdeleteFirstObject
    
    #object_count = #object_count + 1
    IF #object_count < #max_objects THEN
        GOTO 500
    ENDIF

N999 ; Kết thúc
G28 ; Về Home
```

---

## ⚠️ Lưu ý quan trọng:

- Luôn test chương trình ở chế độ an toàn trước khi chạy thật
- Đảm bảo robot đã về Home trước khi bắt đầu
- Kiểm tra giới hạn workspace của robot
- Sử dụng tốc độ thấp khi test chương trình mới
- Luôn có nút Emergency Stop sẵn sàng

## 💡 Tips và Tricks:

- 🔧 Sử dụng chương trình con để tái sử dụng code
- 📝 Thêm chú thích để code dễ hiểu
- 🔢 Sử dụng biến để code linh hoạt hơn
- ⚡ Optimize bằng cách giảm số lần di chuyển không cần thiết
- 🧪 Test từng phần nhỏ trước khi ghép lại

---

**Delta X Software** - Automation Made Simple  
© 2024 - Tài liệu hướng dẫn GScript 