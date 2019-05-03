# ![logo](resource/PSI_resize.png) Poseidon System Integration

[![pipeline status](https://gitlab.com/riveriahorizon/poseidon-system-integration/badges/master/pipeline.svg)](https://gitlab.com/riveriahorizon/poseidon-system-integration/commits/master)
[![coverage report](https://gitlab.com/riveriahorizon/poseidon-system-integration/badges/master/coverage.svg)](https://gitlab.com/riveriahorizon/poseidon-system-integration/commits/master)

The Poseidon System Integration is a code structure that uses the Robot Operating System (ROS) to integrate the different sub systems that are included in the robot.
PSI aims to achieve modularity in the different sub-systems to allow for ease of communication between the various sub-systems and the ease of integration of new features planned in the future.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

1. Linux OS
2. ROS Melodic
3. Arduino IDE
4. Git
5. IDE of choice

### Installing

A step by step series of examples that tell you how to get a development env running

#### ROS Melodic

For more information, take a look at the ROS Melodic installation website [here](http://wiki.ros.org/melodic/Installation/Ubuntu).

```bash
# Setup your sources.list
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
# Set up your keys
sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
# Installation
sudo apt update
sudo apt install ros-melodic-desktop-full
#Initialize rosdep
sudo rosdep init
rosdep update
# Environment setup
echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
source ~/.bashrc
# Dependencies for building packages
sudo apt-get install python-rosinstall python-rosinstall-generator python-wstool build-essential
```

#### VSCode IDE setup

`TODO: Write setup instructions`

#### Initializing the repository

```bash
# Create a directory at where you want to work at
mkdir catkin_ws
# Clone the repository to the workspace
git clone https://gitlab.com/riveriahorizon/poseidon-system-integration.git
# Download package dependancies
sudo apt install ros-melodic-web-server-video
sudo apt install ros-melodic-rosbridge-suite
sudo apt install ros-melodic-imu-tools
sudo apt install ros-melodic-rosserial-arduino
sudo apt install ros-melodic-rosserial
sudo apt install ros-melodic-range-sensor-layer
sudo apt install ros-melodic-usb-cam
sudo apt install nginx
```

#### Building the PSI package

```bash
# Install relevant dependancies
rosdep install --from-paths src --ignore-src -r -y
# Run the catkin_make command
catkin_make
# Source the setup file each time the catkin_make command is invoked
source devel/setup.bash
```

#### Installing Python dependencies

```bash
# Install pyzbar
pip install pyzbar
# Install imutils
pip install imutils
```

#### Launching the PSI package

```bash
roslaunch psi psi.launch
```

## Running the tests

`TODO: Write tests to test code.`

### Break down into end to end tests

`TODO: Include a launch file for testing.`

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

`To be offloaded to Raspberry Pi, and will be updated once it reaches working stage.`

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags).

## Authors

- **Billie Thompson** - _Initial work_ - [PurpleBooth](https://github.com/PurpleBooth)
- **Yong Quan** - _Poseidon System Integration Initial README_ - [RiveriaHorizon](https://gitlab.com/riveriahorizon)

See also the list of [contributors](https://gitlab.com/riveriahorizon/poseidon-system-integration/graphs/master) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

- Hat tip to anyone whose code was used
- Inspiration
- etc
