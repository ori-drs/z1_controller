#ifndef IOUDPWITHPUBLISHER_H
#define IOUDPWITHPUBLISHER_H

#include "interface/IOUDP.h"
#include <ros/ros.h>
#include <ros/time.h>
#include <sensor_msgs/JointState.h>
#include <std_srvs/Trigger.h>

class IOUDPWithPublisher : public IOUDP {
public:
    IOUDPWithPublisher(const char* IP, uint port, ros::NodeHandle* nh, size_t timeOutUs = 100000, bool showInfo = true);
    ~IOUDPWithPublisher();

    bool sendRecv(const LowlevelCmd *cmd, LowlevelState *state) override;

private:
    ros::NodeHandle* _nh;
    ros::Publisher _jointStatePub;
    ros::ServiceServer _has_gripper_service;

    bool _hasGripperCallback(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res);
};

#endif  // IOUDPWITHPUBLISHER_H