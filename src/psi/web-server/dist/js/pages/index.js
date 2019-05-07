var robot_IP;
var ros;
var MIN = 0;
var MAX = 100;

window.onload = function () {
    // determine robot address automatically
    // robot_IP = location.hostname;
    // set robot address statically
    robot_IP = location.hostname;

    // // Init handle for rosbridge_websocket
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

    function get_random(min_input, max_input) {
        min = Math.ceil(min_input);
        max = Math.floor(max_input);
        return Math.floor(Math.random() * (max - min + 1)) + min;
    }

    // Placeholder battery service
    // get handle for battery_level
    battery_record = document.getElementById("battery_level");
    console.log(battery_record);
    battery_record.innerHTML = get_random(MIN, MAX) + "<sup style=\"font-size: 20px\">%</sup>";

    // Placeholder water level service
    // get handle for water_level
    water_record = document.getElementById("water_level");
    water_record.innerHTML = get_random(MIN, MAX) + "<sup style=\"font-size: 20px\">%</sup>";

    // Calling clock service
    var get_time_client = new ROSLIB.Service({
        ros: ros,
        name: '/rosapi/get_time',
        serviceType: 'rosapi/GetTime'
    });
    var request_time = new ROSLIB.ServiceRequest({});

    // get handle for clock placeholder
    time_record = document.getElementById("time_clocked");

    get_time_client.callService(request_time, function (result) {
        time_record.innerHTML = result.time.secs;
    });

    // Calling node service
    var get_nodes_client = new ROSLIB.Service({
        ros: ros,
        name: '/rosapi/nodes',
        serviceType: 'rosapi/Nodes'
    });
    var request_node = new ROSLIB.ServiceRequest({});

    // get handle for clock placeholder
    node_record = document.getElementById("nodes_running");

    get_nodes_client.callService(request_node, function (result) {
        node_record.innerHTML = result.nodes.length;
    });
}