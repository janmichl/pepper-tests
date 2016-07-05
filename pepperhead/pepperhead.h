#ifndef PEPPERHEAD_H
#define PEPPERHEAD_H

#include <iostream>

#include <alcommon/almodule.h>

#include <alproxies/dcmproxy.h>
#include <alproxies/almemoryproxy.h>
#include <almemoryfastaccess/almemoryfastaccess.h>

enum jointSensorID {
    HEAD_PITCH       = 0,
    HEAD_YAW         = 1, 
    L_ELBOW_ROLL     = 2,
    L_ELBOW_YAW      = 3, 
    R_ELBOW_ROLL     = 4, 
    R_ELBOW_YAW      = 5, 
    L_WRIST_YAW      = 6, 
    R_WRIST_YAW      = 7, 
    L_SHOULDER_PITCH = 8, 
    L_SHOULDER_ROLL  = 9, 
    R_SHOULDER_PITCH = 10, 
    R_SHOULDER_ROLL  = 11, 
    HIP_PITCH        = 12, 
    HIP_ROLL         = 13, 
    KNEE_PITCH       = 14,
    WHEEL_FR         = 15, 
    WHEEL_FL         = 17, 
    WHEEL_B          = 18, 

    JOINTS_NUM       = 19
};

namespace AL
{
  // This is a forward declaration of AL:ALBroker which
  // avoids including <alcommon/albroker.h> in this header
  class ALBroker;
}

/**
 * This class inherits AL::ALModule. This allows it to bind methods
 */
class Pepperhead : public AL::ALModule
{
    public:
        Pepperhead(boost::shared_ptr<AL::ALBroker> broker,
                   const std::string &name);

        virtual ~Pepperhead();

        /**
         * Overloading ALModule::init().
         * This is called right after the module has been loaded
         */
        virtual void init();

        // After that you may add all your bind method.
        
        // moves the head up and down - advertise this fcn to others
        void moveJoint(const int &joint_id, const float &value);

    private:
        void setJointStiffness(const int &joint_id, const float &value);

        std::vector<std::string> joint_names_;
        
        boost::shared_ptr<AL::DCMProxy>           dcm_proxy;
        boost::shared_ptr<AL::ALMemoryProxy>      memory_proxy;
        boost::shared_ptr<AL::ALMemoryFastAccess> access_sensor_values;
        
};
#endif // PEPPERHEAD_H

