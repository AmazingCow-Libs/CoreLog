#ifdef __linux__

// Header
#include "os_functions.h"

// Usings
USING_NS_CORELOG;

const std::string& Private::get_program_name()
{
    static std::string s_program_name(program_invocation_name);
    return s_program_name;
}

#endif // __linux__
