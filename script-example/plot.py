import plotly.graph_objects as go
import pandas as pd

# Giả sử bạn có DataFrame dữ liệu như sau:
# Tạo một DataFrame mẫu
data = {
    "Thời gian": ["2024-03-16 10:00", "2024-03-16 11:00", "2024-03-16 12:00", "2024-03-16 13:00", "2024-03-16 14:00"],
    "Giá trị cảm biến": [20, 25, 22, 19, 24]
}
df = pd.DataFrame(data)

# Chuyển đổi cột 'Thời gian' sang định dạng datetime
df['Thời gian'] = pd.to_datetime(df['Thời gian'])

# Tạo đồ thị
fig = go.Figure()

# Thêm dữ liệu vào đồ thị
fig.add_trace(go.Scatter(x=df['Thời gian'], y=df['Giá trị cảm biến'], mode='lines+markers', name='Giá trị'))

# Cài đặt tiêu đề và nhãn trục
fig.update_layout(title='Đồ thị giá trị cảm biến theo thời gian',
                   xaxis_title='Thời gian',
                   yaxis_title='Giá trị cảm biến')

# Hiển thị đồ thị
fig.show()
