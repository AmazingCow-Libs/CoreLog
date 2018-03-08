//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : os_functions.cpp                                              //
//  Project   : CoreLog                                                       //
//  Date      : Jan 02, 2018                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2018                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Header
#include "os_functions.h"
// std
#include <stdlib.h>
// Amazing Cow Libs
#include "acow/cpp_goodies.h"

// Usings
USING_NS_CORELOG;

#if (ACOW_OS_IS_GNU_LINUX)

    const std::string& Private::get_program_name()
    {
        static std::string s_program_name(program_invocation_name);
        return s_program_name;
    }

#elif (ACOW_OS_IS_BSD)
    const std::string& Private::get_program_name()
    {
        static std::string s_program_name(getprogname());
        return s_program_name;
    }

#elif (ACOW_OS_IS_WINDOWS)
    #include <Windows.h>

    const std::string& Private::get_program_name()
    {
		static std::string s_program_name;
		static bool initialized = false;
		
		if(!initialized)
		{
			TCHAR exe_filename[MAX_PATH];
			GetModuleFileName(nullptr, exe_filename, MAX_PATH);
			
			s_program_name = std::string(exe_filename);
		}

		return s_program_name;
    }

#endif // #if (ACOW_OS_IS_GNU_LINUX)
