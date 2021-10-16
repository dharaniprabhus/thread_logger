#pragma once

#include <cstdint>
#include <string>
#include <message_type.h>
#include <memory>

class ILogBackend
{
    public:
        enum Type{Console};
        virtual void write(MessageType msgType, uint64_t ts, const std::string& message) = 0;
        virtual ~ILogBackend() = 0;
};

inline ILogBackend::~ILogBackend(){}

using ILogBackendPtr = std::shared_ptr<ILogBackend>;
ILogBackendPtr make_backend(ILogBackend::Type type);
