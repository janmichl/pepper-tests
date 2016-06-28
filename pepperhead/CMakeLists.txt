cmake_minimum_required(VERSION 2.8)

project(pepperhead)

find_package(qibuild)

set(_srcs 
    pepperhead.h
    pepperhead.cpp
    main.cpp)

qi_create_lib(pepperhead SHARED ${_srcs} SUBFOLDER naoqi)

qi_use_lib(pepperhead ALCOMMON ALPROXIES BOOST)

