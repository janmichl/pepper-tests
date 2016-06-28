#ifndef PEPPERHEAD_H
#define PEPPERHEAD_H

# include <iostream>
# include <alcommon/almodule.h>

namespace AL
{
  // This is a forward declaration of AL:ALBroker which
  // avoids including <alcommon/albroker.h> in this header
  class ALBroker;
}

/**
 * This class inherits AL::ALModule. This allows it to bind methods
 * and be run as a remote executable within NAOqi
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

    // moves the head up and down
    void moveHead();
};
#endif // PEPPERHEAD_H

