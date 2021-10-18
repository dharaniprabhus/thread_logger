cmake_minimum_required(VERSION "3.10")

project (logger)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_FLAGS "-g")
find_package(Threads)

add_library(logger STATIC
    include/log_client.h 
    include/log_backend_interface.h
    src/message.h
    src/logger.h
    src/logger.cpp
    src/log_client.cpp
    )
target_include_directories(logger 
    PUBLIC 
    include
    PRIVATE 
    src)
target_link_libraries(logger PRIVATE Threads::Threads)

add_executable(app app/main.cpp)
target_link_libraries(app PRIVATE logger)
