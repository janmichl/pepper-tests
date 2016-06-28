#include "pepperhead.h"

#include <iostream>
#include <alerror/alerror.h>
#include <alproxies/almotionproxy.h>
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
}

void Pepperhead::init()
{
    /**
     * Init is called just after construction.
     * Do something or not
     */
    std::cout << "init" << std::endl;
}

void Pepperhead::moveHead()
{
  
}

