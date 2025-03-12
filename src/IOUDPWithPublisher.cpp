#include "interface/IOUDPWithPublisher.h"

IOUDPWithPublisher::IOUDPWithPublisher(const char* IP, uint port, ros::NodeHandle& nh, size_t timeOutUs, bool showInfo)
    : IOUDP(IP, port, timeOutUs, showInfo), _nh(nh) {

    _jointStatePub = _nh.advertise<sensor_msgs::JointState>("joint_states", 10);
    _has_gripper_service = _nh.advertiseService("has_gripper", &IOUDPWithPublisher::_hasGripperCallback, this);
}

IOUDPWithPublisher::~IOUDPWithPublisher() {
    // Destructor implementation (if needed)
}

bool IOUDPWithPublisher::sendRecv(const LowlevelCmd *cmd, LowlevelState *state) {
    bool result = IOUDP::sendRecv(cmd, state);

    if (result) {
        sensor_msgs::JointState jointStateMsg;
        jointStateMsg.header.stamp = ros::Time::now();

        // Assuming LowlevelState has fields q, dq, ddq, and tau
        for (size_t i = 0; i < state->q.size(); ++i) {
            if (i == 6) {
            jointStateMsg.name.push_back("jointGripper");
            } else {
            jointStateMsg.name.push_back("joint" + std::to_string(i + 1));
            }
            jointStateMsg.position.push_back(state->q[i]);
            jointStateMsg.velocity.push_back(state->dq[i]);
            jointStateMsg.effort.push_back(state->tau[i]);
        }

        _jointStatePub.publish(jointStateMsg);
    }

    return result;
}

bool IOUDPWithPublisher::_hasGripperCallback(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res) {
    // Implement the logic to determine if the arm has a gripper
    res.success = hasGripper;
    res.message = "Gripper status retrieved";
    return true;
}