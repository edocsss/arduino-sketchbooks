$(document).ready(function () {
    var socket = io.connect("http://localhost:8888");
    $("button#led-on").click(function () {
        socket.emit("ledOn");
        console.log("ledOn");
    });
    
    $("button#led-off").click(function () {
        socket.emit("ledOff");
        console.log("ledOff");
    });
    
    $("span#question_icon").click(function () {
        swal("Number of Characters", "The LCD can only contain 16 x 2 characters!");
    });
    
    $("button#write_text").click(function () {
        var line1 = $("#lcd_text1").val();
        var line2 = $("#lcd_text2").val();
        
        if (line1.length === 0 && line2.length === 0) {
            swal("Empty Input!", "One of the textbox must be filled in!", "error");
            return;
        }
        
        // Write to the LCD!
        var data =  [line1, line2];

        socket.emit("lcdWrite", {lines: data});
        console.log("LCD Write!");
        console.log("Line 1: " + line1 + ", Line 2: " + line2);
    });
    
    $("button#reset_text").click(function () {
        $("#lcd_text1").val('');
        $("#lcd_text2").val('');
        
        socket.emit("lcdReset");
    });
    
    socket.on("ldrReading", function (value) {
        $("div#ldr-reading").text(value);
    });
});