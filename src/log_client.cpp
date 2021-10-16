#include "message_type.h"
#include <chrono>
#include <log_client.h>
#include <logger.h>
#include <log_backend_interface.h>
#include <chrono>
#include <functional>

void LogClient::init()
{
    Logger::getInstane().addBackend(make_backend(ILogBackend::Console));
}

void LogClient::info(const std::string& message)
{
    auto ts = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock().now().time_since_epoch()).count();
    auto id = std::hash<std::thread::id>{}(std::this_thread::get_id());
    Logger::getInstane().push(log::Message{id,uint64_t(ts),MessageType::INFO,message});
}

void LogClient::deinit()
{
    Logger::deleteInstane();
}
