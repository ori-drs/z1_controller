cmake_minimum_required(VERSION 3.0)
project(z1_controller LANGUAGES CXX)
set(PACKAGE_NAME z1_controller)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O3 -std=c++14 -pthread")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(Boost REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(
    include
    ${Boost_INCLUDE_DIRS}
    ${Eigen3_INCLUDE_DIRS}
)

link_directories(lib)

find_package(catkin QUIET)
if(${catkin_FOUND})
    # Catkin build (ROS)
    find_package(catkin REQUIRED COMPONENTS
    roscpp
    geometry_msgs
    std_msgs
    controller_manager
    genmsg
    joint_state_controller
    robot_state_publisher
    tf
    )

    include_directories(
        ${catkin_INCLUDE_DIRS}
    )

    catkin_package(
        INCLUDE_DIRS include
        LIBRARIES Z1_${CMAKE_HOST_SYSTEM_PROCESSOR}
        # DEPENDS Boost Eigen3
        CATKIN_DEPENDS roscpp geometry_msgs std_msgs controller_manager joint_state_controller robot_state_publisher tf
    )

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

    add_executable(z1_ctrl src/z1_ctrl_ros.cpp src/IOUDPWithPublisher.cpp)
    add_dependencies(z1_ctrl ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
    target_link_libraries(z1_ctrl
    Z1_${CMAKE_HOST_SYSTEM_PROCESSOR}
    ${catkin_LIBRARIES}
    )
    find_package(gazebo_ros QUIET)
    if(${gazebo_ros_FOUND})
        include_directories(
            ${GAZEBO_INCLUDE_DIRS}
        )

        link_directories(
        ${GAZEBO_LIBRARY_DIRS}
        )

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

        add_executable(sim_ctrl src/sim_ctrl.cpp src/IOROS.cpp)
        add_dependencies(sim_ctrl ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
        target_link_libraries(sim_ctrl
        Z1_${CMAKE_HOST_SYSTEM_PROCESSOR}
        ${catkin_LIBRARIES}
        )
    endif()
else()
    # Cmake build (non-ROS)
    add_executable(z1_ctrl src/main.cpp)
    target_link_libraries(z1_ctrl Z1_${CMAKE_HOST_SYSTEM_PROCESSOR})
endif()