#include "socket-acceptor.hpp"
#include "socket-addr.hpp"
#include "thread.hpp"
#include <iostream>
#include <memory>
#include <cstring>
#include <unistd.h>
#include <vector>

constexpr int PORT = 8080;
constexpr int BUFFER_SIZE = 1024;

void handleSession(int clientSocket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

    if (bytesRead > 0) {
        std::cout << "Received data: " << std::string(buffer, bytesRead) << std::endl;
    }

    close(clientSocket);  // Close the connection after session
}

int main() {
    SocketAddr addr("0.0.0.0", PORT);  // Listen on all interfaces
    auto acceptor = std::make_unique<SocketAcceptor>(addr);
    std::vector<std::unique_ptr<Thread>> sessionThreads;

    acceptor->bind();
    acceptor->listen();

    std::cout << "Server is listening on port " << PORT << std::endl;

    while (true) {
        int clientSocket = acceptor->acceptConnection();

        // Store the session thread in a collection
        sessionThreads.emplace_back(std::make_unique<Thread>([clientSocket]() {
            handleSession(clientSocket);
        }));

        // Start the thread (non-blocking)
        sessionThreads.back()->start();

        // Clean up completed threads (join finished threads)
        sessionThreads.erase(
            std::remove_if(sessionThreads.begin(), sessionThreads.end(),
            [](const std::unique_ptr<Thread>& thread) {
                if (thread->joinable()) {
                    thread->join();  // Join threads that have finished
                    return true;     // Remove them from the collection
                }
                return false;
            }),
            sessionThreads.end()
        );
    }

    return 0;
}
