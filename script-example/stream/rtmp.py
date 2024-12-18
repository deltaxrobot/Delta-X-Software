import cv2
import subprocess

def test_ffmpeg_rtmp():
    # Đường dẫn tới RTMP server
    rtmp_url = "rtmp://13.88.44.47/stream/live"

    # Mở webcam (0 là camera mặc định)
    cap = cv2.VideoCapture(0)

    # Kiểm tra nếu webcam không mở được
    if not cap.isOpened():
        print("Không thể mở webcam!")
        return

    # Lấy thông số từ webcam
    fps = int(cap.get(cv2.CAP_PROP_FPS)) or 30  # Tốc độ khung hình, mặc định 30
    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

    print(f"Đang truyền với độ phân giải {width}x{height} @ {fps} FPS")

    # Lệnh ffmpeg để mã hóa và gửi lên RTMP server
    ffmpeg_cmd = [
        "ffmpeg",
        "-y",  # Ghi đè nếu có
        "-f", "rawvideo",  # Định dạng dữ liệu thô
        "-vcodec", "rawvideo",  # Bộ mã hóa
        "-pix_fmt", "bgr24",  # Định dạng màu (OpenCV cung cấp BGR)
        "-s", f"{width}x{height}",  # Độ phân giải
        "-r", str(fps),  # Tốc độ khung hình
        "-i", "-",  # Input từ stdin
        "-c:v", "libx264",  # Bộ mã hóa video H.264
        '-pix_fmt', 'yuv420p',
        "-preset", "veryfast",  # Giảm độ trễ
        "-tune", "zerolatency",  # Tinh chỉnh để giảm trễ
        "-f", "flv",  # Định dạng output
        rtmp_url  # URL RTMP server
    ]

    # Khởi chạy ffmpeg qua subprocess
    process = subprocess.Popen(ffmpeg_cmd, stdin=subprocess.PIPE)

    try:
        while True:
            # Đọc frame từ webcam
            ret, frame = cap.read()
            if not ret:
                print("Không thể đọc frame từ webcam!")
                break

            # Gửi frame đến ffmpeg qua stdin
            process.stdin.write(frame.tobytes())

    except KeyboardInterrupt:
        print("Đã dừng truyền!")

    finally:
        # Dọn dẹp
        cap.release()
        process.stdin.close()
        process.wait()
        print("Đã dừng ffmpeg và giải phóng tài nguyên.")

if __name__ == "__main__":
    test_ffmpeg_rtmp()
