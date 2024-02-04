from flask import Flask, jsonify, request
from flask_cors import CORS

app = Flask(__name__)
CORS(app)

# Ví dụ đơn giản về một endpoint GET
@app.route('/get_data', methods=['GET'])
def get_data():
    # Trả về một số dữ liệu dưới dạng JSON
    data = {"message": "Hello from Python Flask!"}
    return jsonify(data)

# Ví dụ về một endpoint POST
@app.route('/post_data', methods=['POST'])
def post_data():
    # Nhận dữ liệu JSON từ request
    input_data = request.json
    # Xử lý dữ liệu đầu vào (ví dụ: log, tính toán, v.v.)
    print("Data received:", input_data)
    # Trả về phản hồi
    return jsonify({"message": "Data received successfully!"})

if __name__ == '__main__':
    app.run(debug=True, port=5000)
