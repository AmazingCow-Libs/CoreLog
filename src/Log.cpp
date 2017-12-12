// Header
#include "../include/Log.h"

// Usings
USING_NS_CORELOG;


//----------------------------------------------------------------------------//
// Logger                                                                     //
//----------------------------------------------------------------------------//
Logger& CoreLog::GetDefaultLogger()
{
    static Logger s_logger;
    return s_logger;
}

