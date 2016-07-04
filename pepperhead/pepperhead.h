#ifndef PEPPERHEAD_H
#define PEPPERHEAD_H

#include <iostream>

#include <alcommon/almodule.h>
#include <alproxies/almotionproxy.h>

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
        void moveHead();

    private:
        void setHeadStiffness(const float &value);

        //AlMotionProxy to call commands from motion module on the robot
        boost::shared_ptr<AL::ALMotionProxy> motion;
};
#endif // PEPPERHEAD_H

