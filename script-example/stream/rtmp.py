import cv2
import subprocess

def test_ffmpeg_rtmp():
    # RTMP server URL.
    rtmp_url = "rtmp://13.88.44.47/stream/live"

    # Open the default webcam (index 0).
    cap = cv2.VideoCapture(0)

    # Verify that the webcam opened successfully.
    if not cap.isOpened():
        print("Could not open the webcam")
        return

    # Read webcam properties.
    fps = int(cap.get(cv2.CAP_PROP_FPS)) or 30  # Default to 30 FPS.
    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

    print(f"Streaming at {width}x{height} @ {fps} FPS")

    # Encode with ffmpeg and publish to the RTMP server.
    ffmpeg_cmd = [
        "ffmpeg",
        "-y",  # Overwrite output when necessary.
        "-f", "rawvideo",  # Raw input format.
        "-vcodec", "rawvideo",  # Input codec.
        "-pix_fmt", "bgr24",  # OpenCV supplies BGR pixels.
        "-s", f"{width}x{height}",  # Resolution.
        "-r", str(fps),  # Frame rate.
        "-i", "-",  # Read from stdin.
        "-c:v", "libx264",  # H.264 encoder.
        '-pix_fmt', 'yuv420p',
        "-preset", "veryfast",  # Reduce latency.
        "-tune", "zerolatency",  # Optimize for low latency.
        "-f", "flv",  # Output format.
        rtmp_url  # URL RTMP server
    ]

    # Start ffmpeg as a subprocess.
    process = subprocess.Popen(ffmpeg_cmd, stdin=subprocess.PIPE)

    try:
        while True:
            # Read a webcam frame.
            ret, frame = cap.read()
            if not ret:
                print("Could not read a webcam frame")
                break

            # Send the frame to ffmpeg through stdin.
            process.stdin.write(frame.tobytes())

    except KeyboardInterrupt:
        print("Streaming stopped")

    finally:
        # Release resources.
        cap.release()
        process.stdin.close()
        process.wait()
        print("ffmpeg stopped and resources were released")

if __name__ == "__main__":
    test_ffmpeg_rtmp()
