#pragma once

#include <message.h>
#include <log_backend_interface.h>
#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>

class Logger{
    public:
        static Logger& getInstane();
        static void deleteInstane();
        void addBackend(ILogBackendPtr backend);
        void push(const log::Message& message);
    private:
        void loop();
        Logger();
        static inline Logger* m_instance = nullptr;
        std::list<log::Message> m_queue;
        std::list<ILogBackendPtr> m_backends;
        mutable std::mutex m_lock;
        std::thread m_thread;
        std::condition_variable m_queueUpdated;
        bool m_running;
};
