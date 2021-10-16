#pragma once
#include <string>

class Logger;
class LogClient
{
    public:
        void init();
        void info(const std::string& message);
        void deinit();
};
