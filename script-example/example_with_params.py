#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Example Python script showing how to receive parameters from Delta X Software
This script demonstrates parameter parsing and basic object detection setup.

Parameters passed from software:
- script_path: Path to this script
- -ip: Server IP address (default: 127.0.0.1)
- -port: Server port (default: 8844)
- -type: Image source type
- -model: Model file path
- -ow: Object width
- -oh: Object height
- -project: Project name
"""

import sys
import socket
import time
import argparse
import os
from pathlib import Path

def parse_arguments():
    """Parse command line arguments passed from Delta X Software"""
    parser = argparse.ArgumentParser(description='Delta X External Script with Parameters')
    
    # Network parameters
    parser.add_argument('-ip', '--host', default='127.0.0.1', 
                       help='Server IP address (default: 127.0.0.1)')
    parser.add_argument('-port', '--port', type=int, default=8844,
                       help='Server port (default: 8844)')
    
    # Detection parameters
    parser.add_argument('-type', '--image-type', default='Original Image',
                       help='Image source type from software')
    parser.add_argument('-model', '--model-path', default='models/best.pt',
                       help='Path to AI model file')
    parser.add_argument('-ow', '--object-width', type=int, default=50,
                       help='Expected object width in pixels')
    parser.add_argument('-oh', '--object-height', type=int, default=50,
                       help='Expected object height in pixels')
    
    # Project parameters
    parser.add_argument('-project', '--project-name', default='project0',
                       help='Project name from software')
    
    return parser.parse_args()

def validate_model_path(model_path):
    """Validate and find the model file"""
    if os.path.exists(model_path):
        print(f"✓ Model found at: {model_path}")
        return model_path
    
    # Try alternative paths
    possible_paths = [
        f"models/{os.path.basename(model_path)}",
        f"../models/{os.path.basename(model_path)}",
        "models/best.pt",
        "models/yolov8n.pt"
    ]
    
    for path in possible_paths:
        if os.path.exists(path):
            print(f"✓ Model found at alternative path: {path}")
            return path
    
    print(f"⚠ Model file not found. Searched paths:")
    print(f"  - {model_path}")
    for path in possible_paths:
        print(f"  - {path}")
    return None

def connect_to_software(host, port, max_retries=5):
    """Connect to Delta X Software with retry mechanism"""
    for attempt in range(max_retries):
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.settimeout(10)  # 10 second timeout
            sock.connect((host, port))
            print(f"✓ Connected to Delta X Software at {host}:{port}")
            return sock
        except ConnectionRefusedError:
            print(f"⚠ Connection attempt {attempt + 1}/{max_retries} failed. Retrying in 3 seconds...")
            time.sleep(3)
        except Exception as e:
            print(f"✗ Connection error: {e}")
            time.sleep(3)
    
    print(f"✗ Failed to connect after {max_retries} attempts")
    return None

def simulate_object_detection(args):
    """Simulate object detection with the given parameters"""
    print("🔍 Simulating object detection...")
    print(f"   Image Type: {args.image_type}")
    print(f"   Expected Object Size: {args.object_width}x{args.object_height}")
    
    # Simulate detection result
    # In real implementation, this would process the actual image
    detected_objects = [
        {
            'id': 0,
            'x': 320,  # Center X
            'y': 240,  # Center Y
            'width': args.object_width,
            'height': args.object_height,
            'angle': 0,
            'confidence': 0.95
        }
    ]
    
    return detected_objects

def format_detection_result(objects):
    """Format detection results for Delta X Software"""
    if not objects:
        return "#Object = ;\n"
    
    result_parts = []
    for obj in objects:
        # Format: "id,x,y,width,height,angle"
        obj_str = f"{obj['id']},{obj['x']},{obj['y']},{obj['width']},{obj['height']},{obj['angle']}"
        result_parts.append(obj_str)
    
    # Combine all objects
    result = "#Object = " + ";".join(result_parts) + ";\n"
    return result

def main():
    """Main function"""
    print("=" * 60)
    print("Delta X External Script with Parameters")
    print("=" * 60)
    
    # Parse command line arguments
    args = parse_arguments()
    
    print("📋 Configuration:")
    print(f"   Host: {args.host}")
    print(f"   Port: {args.port}")
    print(f"   Project: {args.project_name}")
    print(f"   Image Type: {args.image_type}")
    print(f"   Model Path: {args.model_path}")
    print(f"   Object Size: {args.object_width}x{args.object_height}")
    
    # Validate model file
    model_path = validate_model_path(args.model_path)
    if not model_path:
        print("⚠ Continuing without model file...")
    
    # Connect to software
    sock = connect_to_software(args.host, args.port)
    if not sock:
        print("✗ Exiting due to connection failure")
        return 1
    
    print("\n🚀 Starting detection loop...")
    print("Press Ctrl+C to stop")
    
    try:
        detection_count = 0
        while True:
            try:
                # Simulate receiving image from software
                # In real implementation, you would receive image data here
                
                # Simulate object detection
                detected_objects = simulate_object_detection(args)
                
                # Format results for software
                result = format_detection_result(detected_objects)
                
                # Send results back to software
                sock.sendall(result.encode('utf-8'))
                
                detection_count += 1
                if detection_count % 10 == 0:
                    print(f"📊 Processed {detection_count} frames")
                
                # Simulate processing time
                time.sleep(0.1)
                
            except socket.error as e:
                print(f"🔗 Socket error: {e}")
                print("🔄 Attempting to reconnect...")
                sock.close()
                sock = connect_to_software(args.host, args.port)
                if not sock:
                    break
                    
    except KeyboardInterrupt:
        print(f"\n⏹ Stopped by user after processing {detection_count} frames")
    
    finally:
        if sock:
            sock.close()
            print("🔌 Connection closed")
    
    print("✅ Script completed successfully")
    return 0

if __name__ == "__main__":
    exit_code = main()
    sys.exit(exit_code) 