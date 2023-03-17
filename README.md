# data-acquisition-ros
This repo is for image acquisition based on ROS.

- Run the following cmd to start acquisition node.
    ```bash
    roslaunch realsense2_camera rs_camera.launch 
    roslaunch collect_img collect.launch
    ```

# Data record cmd

```bash
rosbag record /camera/depth/color/points /camera/color/image_raw /camera/imu /mavros/imu/data /mavros/imu/data_raw 
```