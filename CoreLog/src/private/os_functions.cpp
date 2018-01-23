
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
		TCHAR exe_filename[MAX_PATH];
		GetModuleFileName(nullptr, exe_filename, MAX_PATH);
		
		return std::string(exe_filename);
    }

#endif // #if (ACOW_OS_IS_GNU_LINUX)
