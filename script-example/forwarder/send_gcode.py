import socket
import sys

# Connection settings.
HOST = '116.110.209.249'
PORT = 8855


def connect(host=HOST, port=PORT, timeout=10):
    try:
        print(f"Connecting to {host}:{port}...")
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.settimeout(timeout)
        sock.connect((host, port))
        print(f"Connected to {host}:{port}")
        return sock
    except socket.timeout:
        print(f"Error: connection to {host}:{port} timed out")
        return None
    except ConnectionRefusedError:
        print(f"Error: connection to {host}:{port} was refused")
        return None
    except socket.gaierror:
        print(f"Error: could not resolve host {host}")
        return None
    except Exception as e:
        print(f"Connection error: {e}")
        return None

def send_gcode(sock, gcode, timeout=5):
    if sock is None:
        print("Error: socket is not connected")
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
                    print("The server closed the connection")
                    return None
                
                response_data += chunk
                
                if b'\n' in response_data:
                    response = response_data.decode('utf-8').strip()
                    print(f"Response: {response}")
                    return response
                    
            except socket.timeout:
                print(f"Timeout: no complete response after {timeout}s")
                return None
        
    except Exception as e:
        print(f"Command send failed: {e}")
        return None

def send_coordinates(sock, x, y, z=-450, timeout=5):
    
    if sock is None:
        print("Error: socket is not connected")
        return None
    
    try:
        command = f"G01 X{x} Y{y} Z{z}\n"
        
        # Send the command.
        print(command.strip())
        sock.sendall(command.encode('utf-8'))
        
        sock.settimeout(timeout)
        
        # Read until a newline terminates the response.
        response_data = b""
        while True:
            try:
                chunk = sock.recv(1024)
                if not chunk:
                    print("The server closed the connection")
                    return None
                
                response_data += chunk
                
                # Stop after receiving a newline.
                if b'\n' in response_data:
                    response = response_data.decode('utf-8').strip()
                    print(f"Response: {response}")
                    return response
                    
            except socket.timeout:
                print(f"Timeout: no complete response after {timeout}s")
                return None
        
    except Exception as e:
        print(f"Command send failed: {e}")
        return None


def disconnect(sock):
    if sock:
        try:
            sock.close()
            print("Connection closed")
        except Exception as e:
            print(f"Connection close failed: {e}")


if __name__ == "__main__":
    sock = connect()
    
    if sock:
        # Send X=100, Y=100, Z=-450 with the default five-second timeout.
        response = send_coordinates(sock, x=100, y=100, z=-430)
        response = send_coordinates(sock, x=100, y=100, z=-450)
        response = send_coordinates(sock, x=100, y=50, z=-450)
        response = send_coordinates(sock, x=100, y=50, z=-430)
                
        # Additional commands may use a custom timeout.
        # response = send_coordinates(sock, x=200, y=150, z=-400, timeout=10)
        
        disconnect(sock)
    else:
        print("Could not connect to the server")
        sys.exit(1)

