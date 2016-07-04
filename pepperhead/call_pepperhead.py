#! /usr/bin/env python

#script to call pepperhead module on the robot

#broker ip is the ip of the robot, port is the port number of naoqi on the robot

import os
import sys
import time

from naoqi    import ALProxy
from optparse import OptionParser

if __name__ == "__main__":

    parser = OptionParser()
    parser.add_option("-b", "--broker-ip",   action="store", type="string", dest="IP",   default="127.0.0.1")
    parser.add_option("-p", "--broker-port", action="store", type="int",    dest="PORT", default=9559)
    (options, args) = parser.parse_args();

    print("----- Started")

    try:
        pepperhead_proxy = ALProxy("Pepperhead", options.IP, options.PORT)
    except Exception, e:
        print("Error when creating proxy")
        print(str(e))
        exit(1)

    print("----- Proxy was created")

    pepperhead_proxy.moveHead()

