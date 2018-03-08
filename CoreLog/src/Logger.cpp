//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Logger.cpp                                                    //
//  Project   : CoreLog                                                       //
//  Date      : Dec 14, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017, 2018                                       //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Header
#include "../include/Logger.h"
// std
#include <cstring>
// termcolor
#include "termcolor/termcolor.h"
// CoreAssert
#include "CoreAssert/CoreAssert.h"
// CoreLog - Private
#include "private/os_functions.h"

// Usings
USING_NS_CORELOG;


//----------------------------------------------------------------------------//
// MACROS                                                                     //
//----------------------------------------------------------------------------//
#define HAS_(_val_, _cmp_)  bool(((_val_) & (_cmp_)))


//----------------------------------------------------------------------------//
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
void print_helper(
    FILE              *pFile,
    int                color,
    const std::string &type,
    const std::string &msg,
    bool              putColor = true)
{
    COREASSERT_ASSERT(pFile, "pFile isn't valid");
    fprintf(
        pFile,
        "[%s] %s\n",
        (putColor) ? termcolor::colored(type, color).c_str() : type.c_str(),
        msg.c_str()
    );
    fflush(pFile);
}


//------------------------------------------------------------------------//
// CTOR / DTOR                                                            //
//------------------------------------------------------------------------//
Logger::Logger(
    Level              level    /* = LOG_LEVEL_VERBOSE       */,
    Type               type     /* = LOG_TYPE_CONSOLE        */,
    Color              color    /* = LOG_COLOR_ENABLE        */,
    const std::string &filename /* = PseudoFilename::Default */) :
    m_level   (   level),
    m_type    (    type),
    m_color   (   color),
    m_filename(filename),
    m_pFile   ( nullptr)
{
    if(HAS_(m_type, LOG_TYPE_FILE))
        _Open(m_filename);
}


//------------------------------------------------------------------------//
// Level                                                                  //
//------------------------------------------------------------------------//
void Logger::SetLevel(Level level) noexcept
{
    m_level = level;
}

Logger::Level Logger::GetLevel() const noexcept
{
    return m_level;
}

//------------------------------------------------------------------------//
// Type                                                                   //
//------------------------------------------------------------------------//
void Logger::SetType(Type type, const std::string &filename) noexcept
{
    // Same stuff - Just ignore...
    if(m_type == type)
        return;

    //--------------------------------------------------------------------------
    // We were logging to file, but now we don't want log to file anymore.
    auto should_close = HAS_(m_type, LOG_TYPE_FILE)
                   && !(HAS_(type,   LOG_TYPE_FILE));

    if(should_close)
        _Close();

    //--------------------------------------------------------------------------
    // We gonna start log to file. So let's open it.
    auto should_open = HAS_(type, LOG_TYPE_FILE);
    if(should_open)
        _Open(filename);

    m_type = type;
}

Logger::Type Logger::GetType()
{
    return m_type;
}


const std::string& Logger::Filename() const noexcept
{
    return m_filename;
}


//------------------------------------------------------------------------//
// Color                                                                  //
//------------------------------------------------------------------------//
void Logger::SetColor(Color color) noexcept
{
    m_color = color;

    if(HAS_(m_color, LOG_COLOR_ENABLE))
        termcolor::Config::colorMode = termcolor::Config::ColorMode::OnlyIfTerminal;

    else if(HAS_(m_color, LOG_COLOR_DISABLE))
        termcolor::Config::colorMode = termcolor::Config::ColorMode::Never;
}

Logger::Color Logger::GetColor() noexcept
{
    return m_color;
}


//----------------------------------------------------------------------------//
// Private Methods                                                            //
//----------------------------------------------------------------------------//
void Logger::_Log(
    Level level,
    const std::string &type,
    const std::string &message)
{
    //--------------------------------------------------------------------------
    // This level isn't enabled.
    bool is_fatal_log = (level == std::numeric_limits<decltype(level)>::max());
    if(!(HAS_(m_level, level)) && !is_fatal_log)
        return;

    //--------------------------------------------------------------------------
    // Choose the color based on log level.
    auto out_color = termcolor::BLUE;
    switch(level)
    {
        case LOG_LEVEL_DEBUG : out_color = termcolor::GREEN;  break;
        case LOG_LEVEL_INFO  : out_color = termcolor::BLUE;   break;
        case LOG_LEVEL_WARN  : out_color = termcolor::YELLOW; break;
        case LOG_LEVEL_ERROR : out_color = termcolor::RED;    break;
        default              : out_color = termcolor::RED;    break; // Fatal Log.
    }

    //--------------------------------------------------------------------------
    // Print the message to the files.
    if(HAS_(m_type, LOG_TYPE_CONSOLE))
        print_helper(stdout, out_color, type, message);
    if(HAS_(m_type, LOG_TYPE_FILE))
        print_helper(m_pFile, out_color, type, message, false);
}


void Logger::_Open(const std::string &filename)
{
    COREASSERT_ASSERT(!m_pFile, "Trying to open an already opened file.");

    //--------------------------------------------------------------------------
    // Using the Pseudo filename. Translate it to the actual filename.
    std::string real_filename = filename;
    if(filename == PseudoFilename::Default)
    {
        real_filename = Private::get_program_name();
        real_filename += "_core_log.txt";
    }

    //--------------------------------------------------------------------------
    // Just open the file.
    m_pFile = fopen(real_filename.c_str(), "a+");
    COREASSERT_VERIFY(
        m_pFile,
        "Cannot open file - Filename (%s) - errno: (%d) - errmsg: (%s)",
        real_filename.c_str(),
        errno,
        strerror(errno)
    );
}

void Logger::_Close()
{
    COREASSERT_ASSERT(m_pFile, "File wasn't open");
    fclose(m_pFile);
}
