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

    // Subscribing to arm control
    var listener_armcon = new ROSLIB.Topic({
        ros: ros,
        name: '/psi/arm/control',
        messageType: 'psi/ArmControl'
    });

    armcon_display = document.getElementById("output_armcon");
    listener_armcon.subscribe(function (message) {
        armcon_display.innerHTML +=
            "header: " + "\n" +
            "  seq: " + message.header.seq + "\n" +
            "  stamp:" + "\n" +
            "    secs: " + message.header.stamp.secs + "\n" +
            "    nsecs: " + message.header.stamp.nsecs + "\n" +
            "  frame_id: " + "\"" + message.header.frame_id + "\"" + "\n" +
            "arm_type: " + "\"" + message.arm_type + "\"" + "\n" +
            "horizontal_distance: " + "\"" + message.horizontal_distance + "\"" + "\n" +
            "vertical_distance: " + "\"" + message.vertical_distance + "\"" + "\n" +
            "---" + "\n";
        armcon_display.scrollTop = armcon_display.scrollHeight - armcon_display.clientHeight;
    });

    // Subscribing to horizontal feedback
    var listener_horfee = new ROSLIB.Topic({
        ros: ros,
        name: '/psi/sensors/arm/horizontal',
        messageType: 'psi/ArmHorizontalFeedback'
    });

    horfee_display = document.getElementById("output_horfee");
    listener_horfee.subscribe(function (message) {
        horfee_display.innerHTML +=
            "header: " + "\n" +
            "  seq: " + message.header.seq + "\n" +
            "  stamp:" + "\n" +
            "    secs: " + message.header.stamp.secs + "\n" +
            "    nsecs: " + message.header.stamp.nsecs + "\n" +
            "  frame_id: " + "\"" + message.header.frame_id + "\"" + "\n" +
            "wormgear_angle: " + "\"" + message.wormgear_angle + "\"" + "\n" +
            "wormgear_desired_encoder_count: " + "\"" + message.wormgear_desired_encoder_count + "\"" + "\n" +
            "wormgear_recorded_encoder_count: " + "\"" + message.wormgear_recorded_encoder_count + "\"" + "\n" +
            "servo_midarm: " + "\"" + message.servo_midarm + "\"" + "\n" +
            "servo_nozarm: " + "\"" + message.servo_nozarm + "\"" + "\n" +
            "theta1: " + "\"" + message.theta1 + "\"" + "\n" +
            "theta2: " + "\"" + message.theta2 + "\"" + "\n" +
            "theta3: " + "\"" + message.theta3 + "\"" + "\n" +
            "---" + "\n";
        horfee_display.scrollTop = horfee_display.scrollHeight - horfee_display.clientHeight;
    });

    // Subscribing to mission status
    var listener_missta = new ROSLIB.Topic({
        ros: ros,
        name: '/psi/arm/mission_status',
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