#ifndef IOROS_H
#define IOROS_H

#include <ros/ros.h>
#include "interface/IOInterface.h"
#include "message/MotorCmd.h"
#include "message/MotorState.h"
#include <std_srvs/Trigger.h>

class IOROS : public IOInterface{
public:
    IOROS(ros::NodeHandle& nh);
    ~IOROS();
    bool sendRecv(const LowlevelCmd *cmd, LowlevelState *state);
private:
    ros::NodeHandle& _nh;
    ros::Subscriber _servo_sub[7];
    ros::Publisher _servo_pub[7];
    ros::ServiceServer _has_gripper_service;

    unitree_legged_msgs::MotorState _joint_state[7];
    unitree_legged_msgs::MotorCmd _joint_cmd[7];
    void _sendCmd(const LowlevelCmd *cmd);
    void _recvState(LowlevelState *state);
    void _initRecv();
    void _initSend();

    void _joint00Callback(const unitree_legged_msgs::MotorState& msg);
    void _joint01Callback(const unitree_legged_msgs::MotorState& msg);
    void _joint02Callback(const unitree_legged_msgs::MotorState& msg);
    void _joint03Callback(const unitree_legged_msgs::MotorState& msg);
    void _joint04Callback(const unitree_legged_msgs::MotorState& msg);
    void _joint05Callback(const unitree_legged_msgs::MotorState& msg);
    void _gripperCallback(const unitree_legged_msgs::MotorState& msg);

    bool _hasGripperCallback(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res);
};

#endif  // IOROS_H