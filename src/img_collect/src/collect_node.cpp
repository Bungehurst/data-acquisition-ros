#include "collect_node.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "collect_node");
  ImageConverter ic;
  ros::spin();
  return 0;
}