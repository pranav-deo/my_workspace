cmake_minimum_required(VERSION 2.8.3)
project(lane_occ)

# add_compile_options(-std=c++11)

set(CMAKE_BUILD_TYPE "RELEASE")


find_package(catkin REQUIRED COMPONENTS
  nodelet
  roscpp
  # rospy
  std_msgs
  sensor_msgs
  geometry_msgs
  nav_msgs
  # tf2
  # tf2_ros
  # cv_bridge
)

# catkin_package(
# )

catkin_package(
  INCLUDE_DIRS include
)


include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})

add_executable(lane_stitching src/lane_stitching.cpp)
target_link_libraries(lane_stitching ${catkin_LIBRARIES})

# catkin_package()
