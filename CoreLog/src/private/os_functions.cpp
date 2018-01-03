
// Header
#include "os_functions.h"
// std
#include <stdlib.h>

// Usings
USING_NS_CORELOG;

#ifdef __linux__

    const std::string& Private::get_program_name()
    {
        static std::string s_program_name(program_invocation_name);
        return s_program_name;
    }

#elif __FreeBSD__
    const std::string& Private::get_program_name()
    {
        static std::string s_program_name(getprogname());
        return s_program_name;
    }
#endif // __linux__
