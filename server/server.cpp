#include "socket-acceptor.hpp"
#include "socket-addr.hpp"
#include "thread.hpp"
#include <iostream>
#include <memory>
#include <cstring>
#include <unistd.h>

constexpr int PORT = 8080;  // Port for server to listen on
constexpr int BUFFER_SIZE = 1024;  // Buffer size for receiving data

void handleSession(int clientSocket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

    if (bytesRead > 0) {
        std::cout << "Received data: " << std::string(buffer, bytesRead) << std::endl;
    }

    close(clientSocket);  // Close the connection after handling the session
}

int main() {
    SocketAddr addr("127.0.0.1", PORT);
    auto acceptor = std::make_unique<SocketAcceptor>(addr);

    acceptor->bind();
    acceptor->listen();

    std::cout << "Server is listening on port " << PORT << std::endl;

    while (true) {
        int clientSocket = acceptor->acceptConnection();
        
        // Create a thread for each session (thread-per-session)
        auto thread = std::make_unique<Thread>([clientSocket]() {
            handleSession(clientSocket);
        });
        
        thread->start();
        thread->join();  // Join immediately to process one session at a time
    }

    return 0;
}
