cmake_minimum_required(VERSION 2.8.3)
project(my_image_proc)

add_definitions(-std=c++11)  
set(CMAKE_BUILD_TYPE Release)  
set(DCMAKE_BUILD_TYPE Release)  

find_package(catkin REQUIRED COMPONENTS
  cv_bridge  
  image_transport  
  message_filters  
  roscpp  
  sensor_msgs  
  std_msgs  
  stereo_msgs  
  image_geometry  
  image_proc  
  message_generation 
)

catkin_package(  
INCLUDE_DIRS include  
DEPENDS Eigen  
)  

include_directories(  
${catkin_INCLUDE_DIRS}  
include   
)  

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse3")  
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")  

add_executable(image_resize src/image_resize.cpp  
)  
  
target_link_libraries(image_resize 
 -L/usr/local/lib 
${catkin_LIBRARIES}  
)
