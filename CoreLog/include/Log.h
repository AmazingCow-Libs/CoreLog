#pragma once

// CoreLog
#include "CoreLog_Utils.h"
#include "Logger.h"

NS_CORELOG_BEGIN

//----------------------------------------------------------------------------//
// Logger                                                                     //
//----------------------------------------------------------------------------//
Logger& GetDefaultLogger();


//------------------------------------------------------------------------//
// Log Functions                                                          //
//------------------------------------------------------------------------//
template <typename ...Value>
void D(const std::string &fmt, Value && ...args)
{
    GetDefaultLogger().D(fmt, std::forward<Value>(args)...);
}

template <typename ...Value>
void I(const std::string &fmt, Value && ...args)
{
    GetDefaultLogger().I(fmt, std::forward<Value>(args)...);
}

template <typename ...Value>
void W(const std::string &fmt, Value && ...args)
{
    GetDefaultLogger().W(fmt, std::forward<Value>(args)...);
}

template <typename ...Value>
void E(const std::string &fmt, Value && ...args)
{
    GetDefaultLogger().E(fmt, std::forward<Value>(args)...);
}

NS_CORELOG_END
