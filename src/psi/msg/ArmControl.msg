##*************************************************************************************##
# Arm sensor message                                                                    #
# This contains the required information to send to the Arduino to control the arms.    #
# * arm_type: Indicate either "left" or "right"                                         #
# * servo_hinge_position: Indicate the degree to turn the hinge servo                   #
# * servo_nozzle_position: Indicate the degree to turn the nozzle servo                 #
# * wormgear_speed: Indicate the speed to run the wormgear dc motor                     #
##*************************************************************************************##

Header header

string arm_type
uint16 servo_hinge_position
uint16 servo_nozzle_position

float32 wormgear_theta_in
string wormgear_direction