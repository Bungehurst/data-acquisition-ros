#!/bin/bash
gnome-terminal --working-directory='/home/nvidia/rs_collect_catkin/devel/' --tab -e "bash -c 'source setup.bash; roslaunch realsense2_camera rs_camera.launch'" \
--tab -t "subscribed to [/camera/depth/color/points]" -e "sh -c 'sleep 10; rostopic hz /camera/depth/color/points'" \
--tab -t "subscribed to [/camera/color/image_raw]" -e "sh -c 'sleep 10; rostopic hz /camera/color/image_raw'" \

gnome-terminal --tab -t "mavros node" -e 'rosrun mavros mavros_node' \
--tab -t "subscribed to [/mavros/imu/data_raw]" -e "sh -c 'sleep 5; rostopic hz /mavros/imu/data_raw'" \
--tab -t "subscribed to [/mavros/imu/data]" -e "sh -c 'sleep 5; rostopic hz /mavros/imu/data'" \