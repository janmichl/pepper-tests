#include "pepperhead.h"

#include <iostream>
#include <string>
#include <vector>

#include <alerror/alerror.h>
#include <alcommon/albroker.h>

Pepperhead::Pepperhead(boost::shared_ptr<AL::ALBroker> broker,
                       const std::string& name) : AL::ALModule(broker, name), joint_names_(JOINTS_NUM, "Device/SubDeviceList/")
{
    // Describe the module here. This will appear on the webpage
    setModuleDescription("Module for moving pepper's joints.");

    /**
     * setReturn(<return_name>, <return_description>);
     * This enables to document the return of the method.
     * It is not compulsory to write this line.
     */
    functionName("moveJoint", getName(), "move joint");
    BIND_METHOD(Pepperhead::moveJoint);
}

Pepperhead::~Pepperhead()
{
}

void Pepperhead::init()
{
    /**
     * Init is called just after construction.
     * Do something or not
     */
    std::cout << "init Pepperhead" << std::endl;

    bool is_DCM_running;
    try
    {
        is_DCM_running = getParentBroker()->getProxy("ALLauncher")->call<bool>("isModulePresent", std::string("DCM"));
    }
    catch (AL::ALError& e)
    {
        throw ALERROR(getName(), __FUNCTION__, std::string(e.what()));
    }

    if (!is_DCM_running)
    {
        throw ALERROR(getName(), __FUNCTION__, "DCM not running");
    }

    try
    {
        dcm_proxy = getParentBroker()->getDcmProxy();
    }
    catch (AL::ALError& e)
    {
        throw ALERROR(getName(), __FUNCTION__, std::string(e.what()));
    }

    try
    {
        memory_proxy = getParentBroker()->getMemoryProxy();
    }
    catch (AL::ALError& e)
    {
        throw ALERROR(getName(), __FUNCTION__, std::string(e.what()));
    }

    //init joints
    joint_names_[HEAD_PITCH]       += "HeadPitch";
    joint_names_[HEAD_YAW]         += "HeadYaw";
    joint_names_[L_ELBOW_ROLL]     += "LElbowRoll";
    joint_names_[L_ELBOW_YAW]      += "LElbowYaw";
    joint_names_[R_ELBOW_ROLL]     += "RElbowRoll";
    joint_names_[R_ELBOW_YAW]      += "RElbowYaw";
    joint_names_[L_WRIST_YAW]      += "LWristYaw";
    joint_names_[R_WRIST_YAW]      += "RWristYaw";
    joint_names_[L_SHOULDER_PITCH] += "LShoulderPitch";
    joint_names_[L_SHOULDER_ROLL]  += "LShoulderRoll";
    joint_names_[R_SHOULDER_PITCH] += "RShoulderPitch";
    joint_names_[R_SHOULDER_ROLL]  += "RShoulderRoll";
    joint_names_[HIP_PITCH]        += "HipPitch";
    joint_names_[HIP_ROLL]         += "HipRoll";
    joint_names_[KNEE_PITCH]       += "KneePitch";
    joint_names_[WHEEL_FR]         += "WheelFR";
    joint_names_[WHEEL_FL]         += "WheelFL";
    joint_names_[WHEEL_B]          += "WheelB";
    
    return;
}

void Pepperhead::moveJoint(const int &joint_id, const float &value)
{
    setJointStiffness(joint_id, 1.0f);
  
    //create alias for given joint
    try
    {
        AL::ALValue joint_alias;
        joint_alias.arraySetSize(2);
        joint_alias[1].arraySetSize(1);
        joint_alias[0] = std::string("jointActuator");
        joint_alias[1][0] = joint_names_[joint_id] + "/Position/Actuator/Value";

        dcm_proxy->createAlias(joint_alias);
    }
    catch (const AL::ALError &e)
    {
        throw ALERROR(getName(), __FUNCTION__, "cannot create alias");
    }

    //create command
    try
    {
        AL::ALValue command;
        command.arraySetSize(3);
        command[0] = std::string("jointActuator");
        command[1] = std::string("ClearAll");
        command[2].arraySetSize(1);
        command[2][0].arraySetSize(2);
        command[2][0][0] = value;
        command[2][0][1] = dcm_proxy->getTime(1000);

        dcm_proxy->set(command);
    }
    catch (const AL::ALError& e)
    {
        throw ALERROR(getName(), __FUNCTION__, "cannot send command");
    }

    setJointStiffness(joint_id, 0.0f);
    
    return;
}

void Pepperhead::setJointStiffness(const int &joint_id, const float &stiffness_value)
{
    //create alias
    if ((stiffness_value < 0) || (stiffness_value > 1))
    {
        throw ALERROR(getName(), __FUNCTION__, "wrong stiffness");
    }
  
    AL::ALValue stiffness_alias;

    stiffness_alias.arraySetSize(2);
    stiffness_alias[1].arraySetSize(1);

    stiffness_alias[0] = std::string("jointStiffness");
    stiffness_alias[1][0] = joint_names_[joint_id] + "/Hardness/Actuator/Value";
  
    try
    {
        dcm_proxy->createAlias(stiffness_alias);
    }
    catch (const AL::ALError &e)
    {
        throw ALERROR(getName(), __FUNCTION__, "cannot create stiffness alias");
    }

    try
    {
        //create command
        AL::ALValue command;

        command.arraySetSize(3);
        command[0] = std::string("jointStiffness");
        command[1] = std::string("Merge");
        command[2].arraySetSize(1);
        command[2][0].arraySetSize(2);
        command[2][0][0] = stiffness_value;
        command[2][0][1] = dcm_proxy->getTime(1000);

        dcm_proxy->set(command);
    }
    catch (const AL::ALError &e)
    {
        throw ALERROR(getName(), __FUNCTION__, "cannot send stiffness command");
    }

    return;
}

