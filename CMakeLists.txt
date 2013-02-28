cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
set(ROS_BUILD_TYPE Debug)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#simulation
set(ON_SIMULATION OFF CACHE BOOL "Whether use or not the simulation configuration")

if(ON_SIMULATION)
	message("@ Simulation enabled")
	add_definitions(-DON_SIMULATION)
endif()
       
#uncomment if you have defined messages
rosbuild_genmsg()
#uncomment if you have defined services
rosbuild_gensrv()

#C++11 standard
add_definitions(-std=c++0x)

rosbuild_add_executable(sensing_node src/sensing_node.cpp)
rosbuild_add_executable(behaviors_node src/behaviors_node.cpp)
rosbuild_add_executable(control_node src/control_node.cpp)

include_directories(
src/
${Boost_INCLUDE_DIR}
)

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})

add_subdirectory(src/base)
add_subdirectory(src/merger)
add_subdirectory(src/behaviors)

# message("@ Behavior link libraries: " ${BEHAVIOR_LINK_LIBRARIES})

# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/)

target_link_libraries(behaviors_node target_detector)
target_link_libraries(behaviors_node take_the_ball)
target_link_libraries(behaviors_node collision_avoidance)
target_link_libraries(behaviors_node move_throughward_goal)
target_link_libraries(behaviors_node stay_in_the_middle)
# target_link_libraries(behaviors_node target_detector take_the_ball collision_avoidance move_throughward_goal stay_in_the_middle)

# target_link_libraries(behaviors_node ${BEHAVIOR_LINK_LIBRARIES})
