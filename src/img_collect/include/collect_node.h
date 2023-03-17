#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ros/ros.h>

#include "std_msgs/String.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#include <mutex> 

using namespace std;

static const std::string OPENCV_WINDOW = "Image window";

class ImageConverter
{
private:
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    // std::mutex mtx;
    // volatile int counter(0);
    
public:
    ImageConverter(): it_(nh_)
    {
        // image_sub_ = it_.subscribe("/camera/color/image_raw", 1, &ImageConverter::imageCb, this);
        image_sub_ = it_.subscribe("/camera/color/image_raw", 1, &ImageConverter::split_callback, this);
        cv::namedWindow(OPENCV_WINDOW);
    }

    ~ImageConverter()
    {
        cv::destroyWindow(OPENCV_WINDOW);
    }
    
    void split_callback(const sensor_msgs::ImageConstPtr& msg){
        static int init_flag = 0;
        static int photo_num = 0;
        static std::chrono::high_resolution_clock::time_point old_time,time_now;
        cv_bridge::CvImagePtr cv_ptr;
        try
        {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
            init_flag = 1;
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }
        if(!init_flag){
            time_now = chrono::high_resolution_clock::now();
            old_time = time_now;
        }else{
            time_now = chrono::high_resolution_clock::now();
        }
        auto err = cv::imwrite("/home/nvidia/rs_collect_catkin/src/img_collect/data/"+to_string(photo_num)+".jpg",cv_ptr->image);
        photo_num++;
        cv::putText(cv_ptr->image, //target image
            "no."+to_string(photo_num), //text
            cv::Point(10, 50), //top-left position
            cv::FONT_HERSHEY_DUPLEX,
            1.0,
            CV_RGB(255, 0, 0), //font color
            2);
        // Update GUI Window
        cv::imshow(OPENCV_WINDOW, cv_ptr->image);
        cv::waitKey(1);
    }

    void imageCb(const sensor_msgs::ImageConstPtr& msg)
    {
        static int init_flag = 0;
        static int photo_num = 0;
        static std::chrono::high_resolution_clock::time_point old_time,time_now;
        cv_bridge::CvImagePtr cv_ptr;
        try
        {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
            init_flag = 1;
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }
        if(!init_flag){
            time_now = chrono::high_resolution_clock::now();
            old_time = time_now;
        }else{
            time_now = chrono::high_resolution_clock::now();
        }
        auto duration = chrono::duration_cast<std::chrono::milliseconds>(time_now - old_time);
        ROS_INFO("time duration:%ld",duration.count());
        
        if(duration > std::chrono::milliseconds(2000)){
            auto err = cv::imwrite("/home/nvidia/rs_collect_catkin/src/img_collect/data/"+to_string(photo_num)+".jpg",cv_ptr->image);
            // if(!err) ROS_INFO("Successfully save image to file!");
            photo_num++;
            old_time = time_now;
        }
        if(duration < std::chrono::milliseconds(1500)){
            cv::putText(cv_ptr->image, //target image
            "Ready", //text
            cv::Point(cv_ptr->image.cols - 150, 50), //top-left position
            cv::FONT_HERSHEY_DUPLEX,
            1.0,
            CV_RGB(0, 255, 0), //font color
            2);
        }else{
            cv::putText(cv_ptr->image, //target image
            "Holding", //text
            cv::Point(cv_ptr->image.cols - 150, 50), //top-left position
            cv::FONT_HERSHEY_DUPLEX,
            1.0,
            CV_RGB(255, 0, 0), //font color
            2);
        }
        cv::putText(cv_ptr->image, //target image
            "no."+to_string(photo_num), //text
            cv::Point(10, 50), //top-left position
            cv::FONT_HERSHEY_DUPLEX,
            1.0,
            CV_RGB(255, 0, 0), //font color
            2);
        // Update GUI Window
        cv::imshow(OPENCV_WINDOW, cv_ptr->image);
        cv::waitKey(1);
    }

};