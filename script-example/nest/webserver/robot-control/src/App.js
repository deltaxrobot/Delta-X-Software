import React, { useEffect, useState } from 'react';

function App() {
  const [data, setData] = useState(null);

  // Sử dụng useEffect để tải dữ liệu khi component được mount
  useEffect(() => {
    fetch('http://localhost:5000/get_data')
      .then(response => response.json())
      .then(data => setData(data))
      .catch((error) => console.error('Error:', error));
  }, []);

  // Render dữ liệu hoặc một thông báo nếu không có dữ liệu
  return (
    <div>
      <h1>Welcome to Delta X Software</h1>
      <button onClick={() => {
        // Post data
        fetch('http://localhost:5000/post_data', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({ message: 'Hello from Delta X Software' }),
        })
          .then(response => response.json())
          .then(data => setData(data))
          .catch((error) => console.error('Error:', error));
      }}>Send message</button>

      {data ? <p>Data: {data.message}</p> : <p>Loading data...</p>}
    </div>
  );
}

export default App;
