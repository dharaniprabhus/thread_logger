#include <chrono>
#include <logger.h>
#include <iostream>
#include <optional>


class ConsoleBackend : public ILogBackend
{
    public:
        enum Type{Console};
        void write(MessageType msgType, uint64_t ts, const std::string& message) override
        {
            std::cout << ts << " " << message << "\n";
        }
        ~ConsoleBackend(){}
};

std::shared_ptr<ILogBackend> make_backend(ILogBackend::Type type)
{
    return std::make_shared<ConsoleBackend>();
}

Logger& Logger::getInstane()
{
    if(!m_instance){
        m_instance = new Logger();
    }
    return *m_instance;
}

void Logger::deleteInstane()
{
    m_instance->m_running = false;
    std::cout.flush();
    m_instance->m_thread.join();
    delete m_instance;
    m_instance = nullptr;
}

Logger::Logger(): m_queue(), m_backends() ,m_lock(), m_thread(&Logger::loop, this), m_running(true){
}

void Logger::push(const log::Message& message)
{
    std::scoped_lock lock(m_lock);
    m_queue.push_back(message);
}

void Logger::addBackend(ILogBackendPtr backend){
    m_backends.push_back(backend);
}

void Logger::loop(){
    while(1){
        std::optional<log::Message> msg;
        std::scoped_lock lock(m_lock);
        if (!m_queue.empty()){
            msg = std::move(m_queue.front());
            m_queue.pop_front();
        }
        if (msg){
            for(auto b: m_backends){
                b->write(msg.value().type,msg.value().timestamp,msg.value().message);
            }
        }else{
            std::this_thread::sleep_for(std::chrono::microseconds(500));
            if (!m_running)break;
        }
    }
}
