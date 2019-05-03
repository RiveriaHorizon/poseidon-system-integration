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

    // Subscribing to cardinal direction
    var listener_cardir = new ROSLIB.Topic({
        ros: ros,
        name: '/psi/drive/cardinal_direction',
        messageType: 'psi/CardinalDirection'
    });

    cardir_display = document.getElementById("output_cardir");
    listener_cardir.subscribe(function (message) {
        cardir_display.innerHTML +=
            "header: " + "\n" +
            "  seq: " + message.header.seq + "\n" +
            "  stamp:" + "\n" +
            "    secs: " + message.header.stamp.secs + "\n" +
            "    nsecs: " + message.header.stamp.nsecs + "\n" +
            "  frame_id: " + "\"" + message.header.frame_id + "\"" + "\n" +
            "cardinal_direction: " + "\"" + message.cardinal_direction + "\"" + "\n" +
            "---" + "\n";
        cardir_display.scrollTop = cardir_display.scrollHeight - cardir_display.clientHeight;
    });

    // Subscribing to joystick input
    var listener_joyin = new ROSLIB.Topic({
        ros: ros,
        name: '/psi/drive/joystick_input',
        messageType: 'psi/JoystickInput'
    });

    joyin_display = document.getElementById("output_joyin");
    listener_joyin.subscribe(function (message) {
        joyin_display.innerHTML +=
            "header: " + "\n" +
            "  seq: " + message.header.seq + "\n" +
            "  stamp:" + "\n" +
            "    secs: " + message.header.stamp.secs + "\n" +
            "    nsecs: " + message.header.stamp.nsecs + "\n" +
            "  frame_id: " + "\"" + message.header.frame_id + "\"" + "\n" +
            "x_input: " + "\"" + message.x_input + "\"" + "\n" +
            "y_input: " + "\"" + message.y_input + "\"" + "\n" +
            "---" + "\n";
        joyin_display.scrollTop = joyin_display.scrollHeight - joyin_display.clientHeight;
    });

    // Subscribing to cardinal direction
    var listener_direrr = new ROSLIB.Topic({
        ros: ros,
        name: '/psi/drive/direction_error',
        messageType: 'psi/DirectionError'
    });

    direrr_display = document.getElementById("output_direrr");
    listener_direrr.subscribe(function (message) {
        direrr_display.innerHTML +=
            "header: " + "\n" +
            "  seq: " + message.header.seq + "\n" +
            "  stamp:" + "\n" +
            "    secs: " + message.header.stamp.secs + "\n" +
            "    nsecs: " + message.header.stamp.nsecs + "\n" +
            "  frame_id: " + "\"" + message.header.frame_id + "\"" + "\n" +
            "direction_error: " + "\"" + message.direction_error + "\"" + "\n" +
            "---" + "\n";
        direrr_display.scrollTop = direrr_display.scrollHeight - direrr_display.clientHeight;
    });

    // Subscribing to mission status
    var listener_missta = new ROSLIB.Topic({
        ros: ros,
        name: '/psi/drive/mission_status',
        messageType: 'psi/MissionStatus'
    });

    missta_display = document.getElementById("output_missta");
    listener_missta.subscribe(function (message) {
        missta_display.innerHTML +=
            "header: " + "\n" +
            "  seq: " + message.header.seq + "\n" +
            "  stamp:" + "\n" +
            "    secs: " + message.header.stamp.secs + "\n" +
            "    nsecs: " + message.header.stamp.nsecs + "\n" +
            "  frame_id: " + "\"" + message.header.frame_id + "\"" + "\n" +
            "mission_status: " + "\"" + message.mission_status + "\"" + "\n" +
            "---" + "\n";
        missta_display.scrollTop = missta_display.scrollHeight - missta_display.clientHeight;
    });
}