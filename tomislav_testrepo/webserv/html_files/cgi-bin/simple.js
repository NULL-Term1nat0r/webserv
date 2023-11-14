#!/usr/bin/env node

const http = require('http');
const url = require('url');

const server = http.createServer((req, res) => {
    const queryObject = url.parse(req.url, true).query;
    const name = queryObject.name;

    res.writeHead(200, { 'Content-Type': 'text/html' });
    res.write('<!DOCTYPE html>');
    res.write('<html>');
    res.write('<head><title>CGI Example</title></head>');
    res.write('<body>');

    if (name) {
        res.write(`<h1>Hello, ${name}!</h1>`);
    } else {
        res.write('<h1>No name provided.</h1>');
    }

    res.write('</body>');
    res.write('</html>');
    res.end();
});

const PORT = 8000;
server.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});