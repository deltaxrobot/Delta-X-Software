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
   - [3.2. IF...ELIF...ELSE...ENDIF - Điều kiện](#32-ifelifelseendif---điều-kiện)
   - [3.3. FOR...ENDFOR - Vòng lặp](#33-forendfor---vòng-lặp)
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

### 3.3. 🔄 FOR...ENDFOR - Vòng lặp

GScript hỗ trợ hai loại vòng lặp FOR:

#### 3.3.1. Vòng lặp số (Numeric FOR):

```gcode
; Cú pháp: FOR var = start TO end [STEP step]
FOR #i = 1 TO 5
    G01 X[#i * 10] Y100
    M03
    G04 P1000
    M05
ENDFOR

; Với STEP tùy chỉnh
FOR #i = 0 TO 100 STEP 10
    G01 X[#i] Y200
    G04 P500
ENDFOR

; Vòng lặp ngược
FOR #i = 10 TO 1 STEP -1
    G01 X[#i * 15] Y300
    G04 P200
ENDFOR
```

#### 3.3.2. Vòng lặp qua objects (FOREACH):

```gcode
; Cú pháp: FOR EACH var IN listName
FOR EACH #obj IN objects
    ; Biến #obj chứa index của object hiện tại
    ; Tự động tạo các biến convenience:
    ; #obj_current_X, #obj_current_Y, #obj_current_Z
    ; #obj_current_W, #obj_current_L, #obj_current_A
    
    G01 X[#obj_current_X] Y[#obj_current_Y]
    G01 Z-150
    M03
    G04 P1000
    G01 Z-50
ENDFOR
```

#### 3.3.3. Nested FOR loops (FOR lồng nhau):

```gcode
; Vòng lặp lồng nhau
FOR #row = 1 TO 5
    FOR #col = 1 TO 3
        #x_pos = #col * 30
        #y_pos = #row * 40
        
        G01 X[#x_pos] Y[#y_pos]
        G01 Z-150
        M03
        G04 P500
        M05
        G01 Z-50
    ENDFOR
ENDFOR
```

#### 3.3.4. FOR kết hợp với IF:

```gcode
; Xử lý có điều kiện trong vòng lặp
FOR #i = 1 TO 10
    IF #i % 2 == 0 THEN
        ; Xử lý số chẵn
        G01 X[#i * 10] Y100
        M03
    ELSE
        ; Xử lý số lẻ  
        G01 X[#i * 10] Y200
        M04
    ENDIF
    
    G04 P800
    M05
ENDFOR
```

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

#### 6.1.1. Lệnh `MOVE` (shortcut mới)

Lệnh `MOVE` cho phép di chuyển tới biến vị trí 3D mà không cần viết lại `G01`:

```gcode
#PickPoint = (120, 40, -180)
#PlacePoint = (260, 120, -150)

MOVE #PickPoint         ; dùng tốc độ mặc định của máy
MOVE #PlacePoint F1500  ; override feed = 1500
```

Yêu cầu: biến phải chứa vector 3D (được ghi trong Variable Manager). Nếu biến không hợp lệ, lệnh sẽ bị bỏ qua.

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

### 7.6. Sử dụng FOR loops trong thực tế

```gcode
; Chương trình pick & place sử dụng FOR loop
G28 ; Về Home

; Ví dụ 1: Pick multiple objects với FOR numeric
#pick_count = 8
FOR #i = 1 TO #pick_count
    ; Tính vị trí pick
    #pick_x = 50 + (#i - 1) * 25
    #pick_y = 100
    
    ; Tính vị trí place
    #place_x = 300 + (#i - 1) * 20
    #place_y = 150
    
    ; Pick object
    G01 X[#pick_x] Y[#pick_y] Z-50 F1000
    G01 Z-150
    M03 ; Bật gripper
    G04 P800
    G01 Z-50
    
    ; Place object
    G01 X[#place_x] Y[#place_y]
    G01 Z-150
    M05 ; Tắt gripper
    G04 P500
    G01 Z-50
ENDFOR

; Ví dụ 2: Xử lý objects với FOR EACH
M98 PcaptureAndDetect ; Chụp ảnh và phát hiện
M98 PupdateTracking(0)

FOR EACH #obj IN objects
    ; Kiểm tra kích thước object
    #obj_area = #obj_current_W * #obj_current_L
    
    IF #obj_area > 1000 THEN
        ; Object lớn - xử lý đặc biệt
        G01 X[#obj_current_X] Y[#obj_current_Y] W[#obj_current_A] F800
        G01 Z-140
        M03 S100 ; Gripper mạnh hơn
        G04 P1200
        G01 Z-50
        
        ; Đặt vào khu vực A
        G01 X400 Y100
        G01 Z-140
        M05
        G01 Z-50
    ELSE
        ; Object nhỏ - xử lý thường
        G01 X[#obj_current_X] Y[#obj_current_Y] W[#obj_current_A] F1000
        G01 Z-150
        M03 S80
        G04 P1000
        G01 Z-50
        
        ; Đặt vào khu vực B
        G01 X400 Y300
        G01 Z-150
        M05
        G01 Z-50
    ENDIF
ENDFOR

; Ví dụ 3: Nested FOR loop - Quét lưới
FOR #row = 1 TO 4
    FOR #col = 1 TO 6
        #scan_x = 100 + (#col - 1) * 30
        #scan_y = 150 + (#row - 1) * 40
        
        ; Di chuyển đến vị trí quét
        G01 X[#scan_x] Y[#scan_y] Z-100 F2000
        
        ; Quét với laser hoặc sensor
        M03 S50 ; Bật laser nhẹ
        G04 P300 ; Chờ đọc sensor
        M05
        
        ; Lưu kết quả (giả sử có sensor feedback)
        #scan_result.[#row].[#col] = #sensor_value
    ENDFOR
ENDFOR

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

## 8. 🔧 Functions (Hàm)

GScript hỗ trợ tạo và gọi hàm tùy chỉnh để tái sử dụng code và tổ chức chương trình tốt hơn.

### 8.1. Khai báo hàm

```gcode
; Cú pháp: FUNCTION functionName(param1, param2, ...)
FUNCTION pickObject(x, y, z)
    G01 X[x] Y[y] Z-50 F1000
    G01 Z[z]
    M03 ; Bật gripper
    G04 P1000
    G01 Z-50
ENDFUNCTION
```

### 8.2. Gọi hàm

```gcode
; Gọi hàm không có giá trị trả về
#pickObject(100, 200, -150)

; Gọi hàm với biến
#pick_x = 150
#pick_y = 250
#pick_z = -140
#pickObject(#pick_x, #pick_y, #pick_z)
```

### 8.3. Hàm có giá trị trả về

```gcode
; Hàm tính khoảng cách giữa hai điểm
FUNCTION calculateDistance(x1, y1, x2, y2)
    #dx = x2 - x1
    #dy = y2 - y1
    #distance = #sqrt(#dx * #dx + #dy * #dy)
    RETURN #distance
ENDFUNCTION

; Sử dụng hàm với giá trị trả về
#dist = #calculateDistance(0, 0, 100, 100)
IF #dist > 50 THEN
    G01 F500 ; Tốc độ chậm cho khoảng cách xa
ELSE
    G01 F1000 ; Tốc độ nhanh cho khoảng cách gần
ENDIF
```

### 8.4. Hàm với logic phức tạp

```gcode
; Hàm xử lý pick & place thông minh
FUNCTION smartPickPlace(pick_x, pick_y, place_x, place_y)
    ; Tính khoảng cách và chọn tốc độ
    #distance = #calculateDistance(pick_x, pick_y, place_x, place_y)
    
    IF #distance > 200 THEN
        #speed = 2000
    ELIF #distance > 100 THEN
        #speed = 1500
    ELSE
        #speed = 1000
    ENDIF
    
    ; Pick object
    G01 X[pick_x] Y[pick_y] Z-50 F[#speed]
    G01 Z-150
    M03
    G04 P1000
    G01 Z-50
    
    ; Place object
    G01 X[place_x] Y[place_y]
    G01 Z-150
    M05
    G04 P500
    G01 Z-50
    
    RETURN 1 ; Thành công
ENDFUNCTION
```

### 8.5. Hàm đệ quy

```gcode
; Hàm tính giai thừa (factorial)
FUNCTION factorial(n)
    IF n <= 1 THEN
        RETURN 1
    ELSE
        #prev = #factorial(n - 1)
        RETURN n * #prev
    ENDIF
ENDFUNCTION

; Sử dụng hàm đệ quy
#result = #factorial(5) ; Kết quả: 120
```

### 8.6. Ví dụ thực tế - Hệ thống hàm cho automation

```gcode
; === SHORT MOVE MACRO ===
#DEFAULT_FEED = 1200
FUNCTION moveTo(point, optional_feed)
    IF point.X == NULL OR point.Y == NULL OR point.Z == NULL THEN
        RETURN 0
    ENDIF
    #selected_feed = optional_feed
    IF #selected_feed == NULL OR #selected_feed <= 0 THEN
        #selected_feed = #DEFAULT_FEED
    ENDIF
    G01 X[point.X] Y[point.Y] Z[point.Z] F[#selected_feed]
    RETURN 1
ENDFUNCTION

; Hàm di chuyển an toàn với kiểm tra giới hạn
FUNCTION safeMove(target_x, target_y, target_z)
    ; Kiểm tra giới hạn workspace
    IF target_x < 0 OR target_x > 500 THEN
        RETURN 0 ; Lỗi: vượt giới hạn X
    ENDIF
    
    IF target_y < 0 OR target_y > 400 THEN
        RETURN 0 ; Lỗi: vượt giới hạn Y
    ENDIF
    
    IF target_z < -200 OR target_z > 0 THEN
        RETURN 0 ; Lỗi: vượt giới hạn Z
    ENDIF
    
    ; Di chuyển an toàn
    G01 X[target_x] Y[target_y] Z[target_z] F1000
    RETURN 1 ; Thành công
ENDFUNCTION

; Hàm pick object với kiểm tra
FUNCTION safePick(x, y, z, grip_time)
    #result = #safeMove(x, y, -50)
    IF #result == 0 THEN
        RETURN 0 ; Lỗi di chuyển
    ENDIF
    
    #result = #safeMove(x, y, z)
    IF #result == 0 THEN
        RETURN 0 ; Lỗi di chuyển
    ENDIF
    
    M03 ; Bật gripper
    G04 P[grip_time]
    
    #result = #safeMove(x, y, -50)
    RETURN #result
ENDFUNCTION

; Hàm place object
FUNCTION safePlace(x, y, z, release_time)
    #result = #safeMove(x, y, -50)
    IF #result == 0 THEN
        RETURN 0
    ENDIF
    
    #result = #safeMove(x, y, z)
    IF #result == 0 THEN
        RETURN 0
    ENDIF
    
    M05 ; Tắt gripper
    G04 P[release_time]
    
    #result = #safeMove(x, y, -50)
    RETURN #result
ENDFUNCTION

; Chương trình chính sử dụng các hàm
G28 ; Về Home

FOR #i = 1 TO 5
    #pick_x = 100 + #i * 50
    #pick_y = 200
    #pick_z = -150
    
    #place_x = 400
    #place_y = 100 + #i * 40
    #place_z = -160
    
    ; Pick object
    #pick_result = #safePick(#pick_x, #pick_y, #pick_z, 1000)
    IF #pick_result == 0 THEN
        ; Xử lý lỗi pick
        GOTO 999
    ENDIF
    
    ; Place object
    #place_result = #safePlace(#place_x, #place_y, #place_z, 500)
    IF #place_result == 0 THEN
        ; Xử lý lỗi place
        GOTO 999
    ENDIF
ENDFOR

GOTO 1000 ; Kết thúc thành công

N999 ; Xử lý lỗi
    G28 ; Về Home an toàn
    ; Log lỗi hoặc dừng chương trình

N1000 ; Kết thúc
    G28 ; Về Home
```

### 8.7. Best Practices cho Functions

#### 8.7.1. Đặt tên hàm rõ ràng:
```gcode
; Tốt
FUNCTION calculatePickPosition(row, col)
FUNCTION validateObjectSize(width, length)
FUNCTION executePickSequence(object_list)

; Không tốt
FUNCTION func1(a, b)
FUNCTION process(x)
```

#### 8.7.2. Sử dụng parameters thay vì global variables:
```gcode
; Tốt - sử dụng parameters
FUNCTION moveToPosition(x, y, z, speed)
    G01 X[x] Y[y] Z[z] F[speed]
ENDFUNCTION

; Không tốt - phụ thuộc global variables
FUNCTION moveToPosition()
    G01 X[#global_x] Y[#global_y] Z[#global_z] F[#global_speed]
ENDFUNCTION
```

#### 8.7.3. Luôn có return value để báo trạng thái:
```gcode
FUNCTION criticalOperation(param1, param2)
    ; Thực hiện operation
    IF error_condition THEN
        RETURN 0 ; Lỗi
    ENDIF
    
    ; Thực hiện thành công
    RETURN 1 ; Thành công
ENDFUNCTION
```

#### 8.7.4. Tổ chức functions theo module:
```gcode
; === MOVEMENT FUNCTIONS ===
FUNCTION safeMove(x, y, z)
    ; Implementation
ENDFUNCTION

FUNCTION fastMove(x, y, z)
    ; Implementation
ENDFUNCTION

; === GRIPPER FUNCTIONS ===
FUNCTION gripObject(grip_time)
    ; Implementation
ENDFUNCTION

FUNCTION releaseObject(release_time)
    ; Implementation
ENDFUNCTION

; === VISION FUNCTIONS ===
FUNCTION detectObjects()
    ; Implementation
ENDFUNCTION

FUNCTION filterObjects(min_size, max_size)
    ; Implementation
ENDFUNCTION
```

---

⚠️ **Lưu ý về Functions:**

- Functions có thể gọi lẫn nhau (bao gồm đệ quy)
- Biến local trong function không ảnh hưởng đến biến global
- Parameters được truyền theo giá trị (pass by value)
- Luôn sử dụng RETURN để kết thúc function rõ ràng
- Tránh function quá dài (> 50 dòng), nên chia nhỏ

---

**Delta X Software** - Automation Made Simple  
© 2024 - Tài liệu hướng dẫn GScript 
