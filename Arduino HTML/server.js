var url = require('url');
var express = require("express");
var app = express();
var server = require('http').createServer(app);
var io = require('socket.io').listen(server);
var port = 8888;

server.listen(port, function () {
    console.log("Server listening to port", port);
});

// Routing (careful of the path!!)

/* This routing here is only for the ROOT folder request */
app.get('/', function(req,res){
    var pathname = url.parse(req.url).pathname;
    res.sendFile(__dirname + '/web' + pathname);
    //res.sendFile(__dirname + '/web/index.html');
});

/* This routing here is for any other requests! */
app.get('/*', function (req, res) {
    var pathname = url.parse(req.url).pathname;
    res.sendFile(__dirname + pathname);
});

/*
// Board communication
var five = require('johnny-five');
var board = new five.Board({ port: "COM3" });
var devices = {};

board.on('ready', function () {
	console.log("BOARD READY!!");
    
    devices.led13 = new five.Led( {
        pin: 13,
        type: "OUTPUT"
    });
    
    devices.lcd = new five.LCD({
        pins: [8, 9, 4, 5, 6, 7],
        backlight: 10,
        rows: 2,
        cols: 16
    });
    
    devices.ldr = new five.Sensor({
        pin: "A1",
        freq: 100,
        threshold: 5
    });
    
    // Listen for any communication
    io.sockets.on('connection', function (socket) {
        socket.on('ledOn', function () {
            devices.led13.on();
        });
        
        socket.on('ledOff', function () {
            devices.led13.off();
        });
        
        socket.on('lcdWrite', function (data) {
            var line1 = data.lines[0], line2 = data.lines[1];
            
            devices.lcd.home().print(line1);
            devices.lcd.cursor(1, 0).print(line2);
        });
        
        socket.on("lcdReset", function () {
            devices.lcd.clear(); 
        });
        
        devices.ldr.scale(0, 255).on("data", function () {
            socket.emit("ldrReading", this.value);
        });
    });
});
*/