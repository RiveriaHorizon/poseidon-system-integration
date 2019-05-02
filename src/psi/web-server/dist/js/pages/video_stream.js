var publishImmediately = true;
var robot_IP;
var manager;
var ros;

window.onload = function () {
  // determine robot address automatically
  // robot_IP = location.hostname;
  // set robot address statically
  robot_IP = location.hostname;

  // // Init handle for rosbridge_websocket
  ros = new ROSLIB.Ros({
    url: "ws://" + robot_IP + ":9090"
  });

  // get handle for video placeholder
  unaltered_video = document.getElementById("unaltered_video");
  // Populate video source
  unaltered_video.src =
    "http://" +
    robot_IP +
    ":8080/stream?topic=/psi/drive/unaltered_image_scaled&type=mjpeg&quality=80";

  // get handle for video placeholder
  blurred_video = document.getElementById("blurred_video");
  // Populate video source
  blurred_video.src =
    "http://" +
    robot_IP +
    ":8080/stream?topic=/psi/drive/blurred_image&type=mjpeg&quality=80";

  // get handle for video placeholder
  extracted_color_video = document.getElementById("extracted_color_video");
  // Populate video source
  extracted_color_video.src =
    "http://" +
    robot_IP +
    ":8080/stream?topic=/psi/drive/mask_extracted_image&type=mjpeg&quality=80";

  // get handle for video placeholder
  binary_video = document.getElementById("binary_video");
  // Populate video source
  binary_video.src =
    "http://" +
    robot_IP +
    ":8080/stream?topic=/psi/drive/binary_image&type=mjpeg&quality=80";

  // get handle for video placeholder
  otsu_video = document.getElementById("otsu_video");
  // Populate video source
  otsu_video.src =
    "http://" +
    robot_IP +
    ":8080/stream?topic=/psi/drive/qr_otsu_image&type=mjpeg&quality=80";

  // get handle for video placeholder
  detected_image = document.getElementById("detected_image");
  // Populate video source
  detected_image.src =
    "http://" +
    robot_IP +
    ":8080/stream?topic=/psi/drive/qr_detected_image&type=mjpeg&quality=80";
};
