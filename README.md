# z1_controller

Package for controlling the Unitree Z1 arm.

## Installation

**Note**: read all documentation listed at the bottom of this page before attempting to install and use this package.

### Non-ROS Setup (do not attempt if using ROS)

1. Clone these repositories:
	```bash
    git clone --recurse-submodules git@github.com:ori-drs/unitree_ros.git
	git clone git@github.com:ori-drs/z1_controller.git
	```
2. Build the executibles:
    ```bash
	cd z1_controller/ && \
	rm -rf build && \
	mkdir build && \
	cd build && \
	cmake .. && make
	```

You should now be able to start the arm controller and command the real arm via keyboard by navigating to the `z1_controller/build` folder you created and running `./z1_ctrl k`.

### ROS Setup
1. Clone these repositories:
	```bash
    git clone --recurse-submodules git@github.com:ori-drs/unitree_ros.git
	git clone git@github.com:ori-drs/z1_controller.git
	```
2. Build the package:
    ```bash
	catkin build
	```

You should now be able to start the arm controller and command the arm via keyboard using the following:
- Real arm: `ROS_NAMESPACE=<your_arm_namespace> rosrun z1_controller z1_ctrl k`
- Gazebo arm: `ROS_NAMESPACE=<your_arm_namespace> rosrun z1_controller sim_ctrl k`

**Note**: if using the Unitree SDK, omit the `k` argument (keyboard control) from the run command.


## Documentation

- [Original](http://dev-z1.unitree.com) (official docs)
- [ORI](https://oxfordrobotics.atlassian.net/wiki/spaces/DRSC/pages/29400010/Unitree+Z1+Arm) (corrections, updates and changes -- read this after the original docs)