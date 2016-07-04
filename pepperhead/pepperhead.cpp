#include "pepperhead.h"

#include <iostream>

#include <alerror/alerror.h>
#include <alcommon/albroker.h>

Pepperhead::Pepperhead(boost::shared_ptr<AL::ALBroker> broker,
                       const std::string& name) : AL::ALModule(broker, name)
{
    // Describe the module here. This will appear on the webpage
    setModuleDescription("Module for moving pepper's head up and down.");

    /**
     * setReturn(<return_name>, <return_description>);
     * This enables to document the return of the method.
     * It is not compulsory to write this line.
     */
    functionName("moveHead", getName(), "move head joint");
    BIND_METHOD(Pepperhead::moveHead);
}

Pepperhead::~Pepperhead()
{
    setHeadStiffness(0.0f);
}

void Pepperhead::init()
{
    /**
     * Init is called just after construction.
     * Do something or not
     */
    std::cout << "init Pepperhead" << std::endl;

    // Get the motion proxy
    motion = getParentBroker()->getMotionProxy();
 
    setHeadStiffness(1.0f);
}

void Pepperhead::moveHead()
{
    std::cout << "started moving head" << std::endl;
  
    std::cout << "move head" << std::endl;
    //names of the joint to be moved
    AL::ALValue joint_name      = AL::ALValue("HeadPitch");
    //set the time to move, in seconds.
    AL::ALValue target_time     = 1.0f;
    //specify that the desired angle is absolute
    bool is_absolute            = true;
    //set the target angles in radians
    AL::ALValue target_angle_1    = AL::ALValue(0.3f);
    //set the target angles in radians
    AL::ALValue target_angle_2    = AL::ALValue(-0.3f);
    
    //call the angle interpolation method
    motion->angleInterpolation(joint_name, target_angle_1, target_time, is_absolute);
    qi::os::sleep(1.0f);

    //call the angle interpolation method
    motion->angleInterpolation(joint_name, target_angle_2, target_time, is_absolute);
    qi::os::sleep(1.0f);
    
    return;
}

void Pepperhead::setHeadStiffness(const float &value)
{
    //make the head stiff to be able to move it
    AL::ALValue stiffness = AL::ALValue(value);
    //time (in seconds) to reach the target
    AL::ALValue time      = 1.0f;

    //call the stiffness interpolation method
    motion->stiffnessInterpolation("Head", stiffness, time);

    return;
}

