var ros;
var timer = true;
var interval = 200;

window.onload = function () {
    robot_IP = location.hostname;

    ros = new ROSLIB.Ros({
        url: "ws://" + robot_IP + ":9090"
    });

    ros.on('connection', function () {
        console.log('Connected to websocket server.');
    });

    ros.on('error', function (error) {
        console.log('Error connecting to websocket server: ', error);
    });

    ros.on('close', function () {
        console.log('Connection to websocket server closed.');
    });

    // Subscribing to central mission status
    var listener_cenmissta = new ROSLIB.Topic({
        ros: ros,
        name: '/psi/central/mission_status',
        messageType: 'psi/MissionStatus'
    });

    cenmissta_display = document.getElementById("output_cenmissta");
    listener_cenmissta.subscribe(function (message) {
        cenmissta_display.innerHTML +=
            "header: " + "\n" +
            "  seq: " + message.header.seq + "\n" +
            "  stamp:" + "\n" +
            "    secs: " + message.header.stamp.secs + "\n" +
            "    nsecs: " + message.header.stamp.nsecs + "\n" +
            "  frame_id: " + "\"" + message.header.frame_id + "\"" + "\n" +
            "mission_status: " + "\"" + message.mission_status + "\"" + "\n" +
            "---" + "\n";
        cenmissta_display.scrollTop = cenmissta_display.scrollHeight - cenmissta_display.clientHeight;
    });

    // Subscribing to status mission status
    var listener_stamissta = new ROSLIB.Topic({
        ros: ros,
        name: '/psi/status/mission_status',
        messageType: 'psi/MissionStatus'
    });

    stamissta_display = document.getElementById("output_stamissta");
    listener_stamissta.subscribe(function (message) {
        stamissta_display.innerHTML +=
            "header: " + "\n" +
            "  seq: " + message.header.seq + "\n" +
            "  stamp:" + "\n" +
            "    secs: " + message.header.stamp.secs + "\n" +
            "    nsecs: " + message.header.stamp.nsecs + "\n" +
            "  frame_id: " + "\"" + message.header.frame_id + "\"" + "\n" +
            "mission_status: " + "\"" + message.mission_status + "\"" + "\n" +
            "---" + "\n";
        stamissta_display.scrollTop = stamissta_display.scrollHeight - stamissta_display.clientHeight;
    });
}