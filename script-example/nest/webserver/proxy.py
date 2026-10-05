from flask import Flask, jsonify, request
from flask_cors import CORS

app = Flask(__name__)
CORS(app)

# Minimal GET endpoint example.
@app.route('/get_data', methods=['GET'])
def get_data():
    # Return sample JSON data.
    data = {"message": "Hello from Python Flask!"}
    return jsonify(data)

# POST endpoint example.
@app.route('/post_data', methods=['POST'])
def post_data():
    # Read JSON from the request.
    input_data = request.json
    # Process the input, for example logging or calculation.
    print("Data received:", input_data)
    # Return the response.
    return jsonify({"message": "Data received successfully!"})

if __name__ == '__main__':
    app.run(debug=True, port=5000)
