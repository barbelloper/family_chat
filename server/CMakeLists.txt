add_executable(chatserver src/chat_server.cpp)
include_directories(include/)
link_libraries(pthread)