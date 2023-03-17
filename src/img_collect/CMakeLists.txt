cmake_minimum_required(VERSION 2.8.3)
project(collect_img)

######################
### Cmake flags
######################
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g -pthread")

######################
### Packages
######################
find_package(catkin REQUIRED COMPONENTS
    tf
    roscpp
    # rospy
    # roslib
    # msg
    std_msgs
    sensor_msgs
    # geometry_msgs
    # nav_msgs
    # cv
    cv_bridge    
    image_transport
)
find_package(OpenCV REQUIRED)

######################
### Message generation
######################
# add_message_files(
#   DIRECTORY msg
#   FILES
# )

# generate_messages(
#   DEPENDENCIES
#   geometry_msgs
#   std_msgs
#   nav_msgs
#   sensor_msgs
# )

######################
### Catkin
######################
catkin_package()

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
)

link_directories(
    ${OpenCV_LIBRARY_DIRS}
)

add_executable(collect_node src/collect_node.cpp)
target_link_libraries(collect_node ${catkin_LIBRARIES} ${OpenCV_LIBS})
