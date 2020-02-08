const express = require ('express');
const app = express();
// const fs = require("fs");
app.use(express.static('public'));
app.get('/index.html', function (req, res) { 
    res.sendFile( __dirname + "/index.html");
});
app.listen(3000);