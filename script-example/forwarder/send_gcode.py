import socket
import sys

# Thông tin kết nối
HOST = '116.110.209.249'
PORT = 8855


def connect(host=HOST, port=PORT, timeout=10):
    try:
        print(f"Đang kết nối đến {host}:{port}...")
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.settimeout(timeout)
        sock.connect((host, port))
        print(f"Đã kết nối thành công đến {host}:{port}")
        return sock
    except socket.timeout:
        print(f"Lỗi: Hết thời gian kết nối đến {host}:{port}")
        return None
    except ConnectionRefusedError:
        print(f"Lỗi: Không thể kết nối đến {host}:{port} - Kết nối bị từ chối")
        return None
    except socket.gaierror:
        print(f"Lỗi: Không thể phân giải địa chỉ {host}")
        return None
    except Exception as e:
        print(f"Lỗi kết nối: {str(e)}")
        return None

def send_gcode(sock, gcode, timeout=5):
    if sock is None:
        print("Lỗi: Socket chưa được kết nối")
        return None
    
    try:
        command = f"{gcode}\n"
        print(command.strip())
        sock.sendall(command.encode('utf-8'))
        
        sock.settimeout(timeout)
        
        response_data = b""
        while True:
            try:
                chunk = sock.recv(1024)
                if not chunk:
                    print("Kết nối bị đóng bởi server")
                    return None
                
                response_data += chunk
                
                if b'\n' in response_data:
                    response = response_data.decode('utf-8').strip()
                    print(f"Response: {response}")
                    return response
                    
            except socket.timeout:
                print(f"Timeout: Không nhận được phản hồi đầy đủ sau {timeout}s")
                return None
        
    except Exception as e:
        print(f"Lỗi khi gửi lệnh: {str(e)}")
        return None

def send_coordinates(sock, x, y, z=-450, timeout=5):
    
    if sock is None:
        print("Lỗi: Socket chưa được kết nối")
        return None
    
    try:
        command = f"G01 X{x} Y{y} Z{z}\n"
        
        # Gửi lệnh
        print(command.strip())
        sock.sendall(command.encode('utf-8'))
        
        sock.settimeout(timeout)
        
        # Nhận dữ liệu cho đến khi có ký tự xuống hàng
        response_data = b""
        while True:
            try:
                chunk = sock.recv(1024)
                if not chunk:
                    print("Kết nối bị đóng bởi server")
                    return None
                
                response_data += chunk
                
                # Kiểm tra nếu có ký tự xuống hàng
                if b'\n' in response_data:
                    response = response_data.decode('utf-8').strip()
                    print(f"Response: {response}")
                    return response
                    
            except socket.timeout:
                print(f"Timeout: Không nhận được phản hồi đầy đủ sau {timeout}s")
                return None
        
    except Exception as e:
        print(f"Lỗi khi gửi lệnh: {str(e)}")
        return None


def disconnect(sock):
    if sock:
        try:
            sock.close()
            print("Đã đóng kết nối")
        except Exception as e:
            print(f"Lỗi khi đóng kết nối: {str(e)}")


if __name__ == "__main__":
    sock = connect()
    
    if sock:
        # Gửi tọa độ X=100, Y=100, Z=-450 (timeout mặc định 5s)
        response = send_coordinates(sock, x=100, y=100, z=-430)
        response = send_coordinates(sock, x=100, y=100, z=-450)
        response = send_coordinates(sock, x=100, y=50, z=-450)
        response = send_coordinates(sock, x=100, y=50, z=-430)
                
        # Có thể gửi thêm nhiều lệnh khác với timeout tùy chỉnh
        # response = send_coordinates(sock, x=200, y=150, z=-400, timeout=10)
        
        disconnect(sock)
    else:
        print("Không thể kết nối đến server")
        sys.exit(1)

