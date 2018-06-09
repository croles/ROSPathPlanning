# ROSPathPlanning
Automatic mapping and path planning with ROS and Gazebo. Developed in NVidia Jetson TX2.

This project is aimed to map a common environment and simulate navigation to pick and drop objects.

The content of the project should be used in the src directory of the ROS project.

The different functionalities can be executed with the scripts in ShellScripts directory:
 - test_slam.sh: loads the world and allows to map the world controlling the robot with keyboard
 - wall_follower.sh: uses a c++ node to make the robot follow the walls and map all the environment.
 - save_map.sh: allow to save the map created with slam.
 - test_navigation.sh: loads the environment with the saved map to test navigation in RViz.
 - home_service.sh: loads the environment and navigates to a given position. The robot simulates picking the object there. It navigates to a destiny point and drops the object there.
