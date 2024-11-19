import requests

# Lấy danh sách các tệp G-code
response = requests.get('http://117.3.0.23:8400/api/gcodes')
files = response.json()
print(files)

# Lấy nội dung của một tệp G-code
filename = 'example.dtgc'
response = requests.get(f'http://117.3.0.23:8400/api/gcode/{filename}')
content = response.json()
# Lấy nội dung của key 'content' và in ra
print(content['content'])


