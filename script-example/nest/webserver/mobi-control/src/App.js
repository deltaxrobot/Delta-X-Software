import React from 'react';
import './App.css';

function App() {
  const sendCommand = (command) => {
    fetch('http://localhost:5000/control', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({ command }),
    });
  };

  return (
    <div className="App">
      <h1>Robot Control Panel</h1>
      <button onClick={() => sendCommand('X')}>Move X</button>
      <button onClick={() => sendCommand('Y')}>Move Y</button>
      <button onClick={() => sendCommand('Z')}>Move Z</button>
    </div>
  );
}

export default App;
