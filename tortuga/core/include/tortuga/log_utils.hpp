#ifndef TA_LOG_UTILS_H
#define TA_LOG_UTILS_H

#include <type_traits>
#include <string>
#include <ostream>

namespace ta::core {

using std::ostream;

// Log criticity level
typedef unsigned int LogLevelFlag_t;
enum class LogLevelFlag : LogLevelFlag_t {
    DEBUG   = 0b0001,
    WARNING = 0b0010,
    ERROR   = 0b0100,
    FATAL   = 0b1000
};

inline constexpr LogLevelFlag operator&(LogLevelFlag op1, LogLevelFlag op2) {
    return static_cast<LogLevelFlag>(static_cast<LogLevelFlag_t>(op1) & static_cast<LogLevelFlag_t>(op2));
}

inline constexpr LogLevelFlag operator|(LogLevelFlag op1, LogLevelFlag op2) {
    return static_cast<LogLevelFlag>(static_cast<LogLevelFlag_t>(op1) | static_cast<LogLevelFlag_t>(op2));
}


// Log channel
typedef unsigned int LogChannelFlag_t;
enum class LogChannelFlag : LogChannelFlag_t {
    DEFAULT     = 0b0000001,
    RENDER      = 0b0000010,
    PHYSICS     = 0b0000100,
    INPUT       = 0b0001000,
    AI          = 0b0010000,
    RESOURCE    = 0b0100000,
    ON_SCREEN   = 0b1000000
};

inline constexpr LogChannelFlag operator&(LogChannelFlag op1, LogChannelFlag op2) {
    return static_cast<LogChannelFlag>(static_cast<LogChannelFlag_t>(op1) & static_cast<LogChannelFlag_t>(op2));
}

inline constexpr LogChannelFlag operator|(LogChannelFlag op1, LogChannelFlag op2) {
    return static_cast<LogChannelFlag>(static_cast<LogChannelFlag_t>(op1) | static_cast<LogChannelFlag_t>(op2));
}



// Log criticity level name
// indexes are related to the LogLevelFlag enum values
static const char* LOG_LEVEL_NAMES[9] = {
        "",
        "DEBUG",        // 0x01
        "WARNING",      // 0x02
        "",
        "ERROR",        // 0x04
        "", "", "",
        "FATAL"         // 0x08
};


// Log channel name
// indexes are related to the LogLevelFlag enum values
static const char* LOG_CHANNEL_NAMES[33] = {
        "",
        "DEFAULT",      // 0x01
        "RENDER",       // 0x02
        "",
        "PHYSICS",      // 0x04
        "", "", "",
        "INPUT",        // 0x08
        "", "", "", "", "", "", "",
        "AI",           // 0x10
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        "RESOURCE"      // 0x20
};


// Gather informations about a log
struct logEntry_t {
    // Criticity level of the log
    LogLevelFlag lvl;

    //Channel to use for logging this entry
    LogChannelFlag channel;

    // Line number which triggered this LogEntry registering
    uint32_t line;

    // Filename which triggered this LogEntry registering
    char file[512];

    // Message of the log
    char message[512];
};

}

#endif
