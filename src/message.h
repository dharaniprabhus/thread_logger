#pragma once
#include <cstdint>
#include <string>
#include <message_type.h>

namespace log
{
    struct Message
    {
        uint64_t thread_id;
        uint64_t timestamp;
        MessageType type;
        std::string message;
    };
}
