#pragma once

// CoreLog
#include "CoreLog_Utils.h"
#include "Logger.h"

NS_CORELOG_BEGIN

//----------------------------------------------------------------------------//
// Logger                                                                     //
//----------------------------------------------------------------------------//
Logger& GetDefaultLogger();


//----------------------------------------------------------------------------//
// Debug                                                                      //
//----------------------------------------------------------------------------//
template <typename ...Value>
void D(const std::string &fmt, Value && ...args)
{
    GetDefaultLogger().D(fmt, std::forward<Value>(args)...);
}

template <typename ...Value>
void Debug(const std::string &fmt, Value && ...args)
{
    GetDefaultLogger().D(fmt, std::forward<Value>(args)...);
}

//----------------------------------------------------------------------------//
// Info                                                                       //
//----------------------------------------------------------------------------//
template <typename ...Value>
void I(const std::string &fmt, Value && ...args)
{
    GetDefaultLogger().I(fmt, std::forward<Value>(args)...);
}

template <typename ...Value>
void Info(const std::string &fmt, Value && ...args)
{
    GetDefaultLogger().I(fmt, std::forward<Value>(args)...);
}


//----------------------------------------------------------------------------//
// Warn                                                                       //
//----------------------------------------------------------------------------//
template <typename ...Value>
void W(const std::string &fmt, Value && ...args)
{
    GetDefaultLogger().W(fmt, std::forward<Value>(args)...);
}

template <typename ...Value>
void Warn(const std::string &fmt, Value && ...args)
{
    GetDefaultLogger().W(fmt, std::forward<Value>(args)...);
}


//----------------------------------------------------------------------------//
// Error                                                                      //
//----------------------------------------------------------------------------//
template <typename ...Value>
void E(const std::string &fmt, Value && ...args)
{
    GetDefaultLogger().E(fmt, std::forward<Value>(args)...);
}

template <typename ...Value>
void Error(const std::string &fmt, Value && ...args)
{
    GetDefaultLogger().E(fmt, std::forward<Value>(args)...);
}


//----------------------------------------------------------------------------//
// Fatal                                                                      //
//----------------------------------------------------------------------------//
template <typename ...Value>
void F(const std::string &fmt, Value && ...args)
{
    GetDefaultLogger().F(fmt, std::forward<Value>(args)...);
}

template <typename ...Value>
void Fatal(const std::string &fmt, Value && ...args)
{
    GetDefaultLogger().F(fmt, std::forward<Value>(args)...);
}

NS_CORELOG_END
