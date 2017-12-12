#pragma once

// std
#include <string>
// CoreLog
#include "CoreLog_Utils.h"
// CoreString
#include "CoreString/CoreString.h"

NS_CORELOG_BEGIN

class Logger
{
    //------------------------------------------------------------------------//
    // Enum / Constants / Typedefs                                            //
    //------------------------------------------------------------------------//
public:
    struct PseudoFilename
    {
        static constexpr const char *Default = ":Default:";
    };


public:
    //--------------------------------------------------------------------------
    // Level
    enum {
        LOG_LEVEL_NONE    = 0,
        LOG_LEVEL_DEBUG   = 1 << 0,
        LOG_LEVEL_INFO    = 1 << 1,
        LOG_LEVEL_WARN    = 1 << 2,
        LOG_LEVEL_ERROR   = 1 << 3,
        LOG_LEVEL_VERBOSE = LOG_LEVEL_DEBUG |
                            LOG_LEVEL_INFO  |
                            LOG_LEVEL_WARN  |
                            LOG_LEVEL_ERROR
    };

    typedef unsigned int Level;


    //--------------------------------------------------------------------------
    // Type
    enum {
        LOG_TYPE_CONSOLE = 1 << 0,
        LOG_TYPE_FILE    = 1 << 1,
        LOG_TYPE_ALL     = LOG_TYPE_CONSOLE | LOG_TYPE_FILE
    };

    typedef unsigned int Type;


    //--------------------------------------------------------------------------
    // Color
    enum {
        LOG_COLOR_ENABLE,
        LOG_COLOR_DISABLE
    };

    typedef unsigned int Color;


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    explicit Logger(
        Level              level    = LOG_LEVEL_VERBOSE,
        Type               type     = LOG_TYPE_CONSOLE,
        Color              color    = LOG_COLOR_ENABLE,
        const std::string &filename = PseudoFilename::Default);


    //------------------------------------------------------------------------//
    // Level                                                                  //
    //------------------------------------------------------------------------//
public:
    void  SetLevel(Level level) noexcept;
    Level GetLevel() const noexcept;


    //------------------------------------------------------------------------//
    // Type                                                                   //
    //------------------------------------------------------------------------//
public:
    void SetType(
        Level level,
        const std::string &filename = PseudoFilename::Default) noexcept;
    Type GetType();

    const std::string& Filename() const noexcept ;


    //------------------------------------------------------------------------//
    // Color                                                                  //
    //------------------------------------------------------------------------//
public:
    void  SetColor(Color color) noexcept;
    Color GetColor() noexcept;


    //------------------------------------------------------------------------//
    // Log Functions                                                          //
    //------------------------------------------------------------------------//
    template <typename ...Value>
    void D(const std::string &fmt, Value && ...args)
    {
        _Log(
            LOG_LEVEL_DEBUG,
             "Debug",
             CoreString::Format(fmt, std::forward<Value>(args)...)
        );
    }

    template <typename ...Value>
    void I(const std::string &fmt, Value && ...args)
    {
        _Log(
            LOG_LEVEL_INFO,
            "Info",
            CoreString::Format(fmt, std::forward<Value>(args)...)
        );
    }

    template <typename ...Value>
    void W(const std::string &fmt, Value && ...args)
    {
        _Log(
            LOG_LEVEL_WARN,
            "Warning",
            CoreString::Format(fmt, std::forward<Value>(args)...)
        );
    }

    template <typename ...Value>
    void E(const std::string &fmt, Value && ...args)
    {
        _Log(
            LOG_LEVEL_ERROR,
            "Error",
            CoreString::Format(fmt, std::forward<Value>(args)...)
        );
    }


    //------------------------------------------------------------------------//
    // Private Methos                                                         //
    //------------------------------------------------------------------------//
private:
    void _Log (Level level, const std::string &type, const std::string &message);
    void _Open(const std::string &filename);
    void _Close();


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    Level m_level;
    Type  m_type;
    Color m_color;

    const std::string  m_filename;
    FILE              *m_pFile;
};

NS_CORELOG_END
