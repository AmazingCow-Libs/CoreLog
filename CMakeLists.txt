##~---------------------------------------------------------------------------##
##                     _______  _______  _______  _     _                     ##
##                    |   _   ||       ||       || | _ | |                    ##
##                    |  |_|  ||       ||   _   || || || |                    ##
##                    |       ||       ||  | |  ||       |                    ##
##                    |       ||      _||  |_|  ||       |                    ##
##                    |   _   ||     |_ |       ||   _   |                    ##
##                    |__| |__||_______||_______||__| |__|                    ##
##                             www.amazingcow.com                             ##
##  File      : CMakeLists.txt                                                ##
##  Project   : CoreLog                                                       ##
##  Date      : Feb 19, 2018                                                  ##
##  License   : GPLv3                                                         ##
##  Author    : n2omatt <n2omatt@amazingcow.com>                              ##
##  Copyright : AmazingCow - 2018                                             ##
##                                                                            ##
##  Description :                                                             ##
##                                                                            ##
##---------------------------------------------------------------------------~##

cmake_minimum_required(VERSION 3.5)

##------------------------------------------------------------------------------
## Project Settings.
project(CoreLog)


##------------------------------------------------------------------------------
## Sources.
add_library(CoreLog
    CoreLog/src/Log.cpp
    CoreLog/src/Logger.cpp
    CoreLog/src/private/os_functions.cpp
)


##------------------------------------------------------------------------------
## Include directories.
target_include_directories(CoreLog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

##------------------------------------------------------------------------------
## Dependencies.
target_link_libraries(CoreLog LINK_PUBLIC CoreString  )
target_link_libraries(CoreLog LINK_PUBLIC libtermcolor)