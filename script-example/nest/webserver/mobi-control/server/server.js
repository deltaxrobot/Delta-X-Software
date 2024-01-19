const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');

const app = express();
app.use(cors());
app.use(bodyParser.json());

app.post('/control', (req, res) => {
    console.log(req.body);
    // Thêm mã để gửi lệnh đến robot hoặc server A ở đây

    res.status(200).send('Command received');
});

const PORT = 5000;
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});
