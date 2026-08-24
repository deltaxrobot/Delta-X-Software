import requests

# Retrieve the list of G-code files.
response = requests.get('http://117.3.0.23:8400/api/gcodes')
files = response.json()
print(files)

# Retrieve one G-code file.
filename = 'example.dtgc'
response = requests.get(f'http://117.3.0.23:8400/api/gcode/{filename}')
content = response.json()
# Print the value of the 'content' field.
print(content['content'])


