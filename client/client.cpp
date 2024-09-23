#include "socket-connector.hpp"
#include "socket-addr.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <string>

constexpr int SESSION_COUNT = 5;
constexpr int BUFFER_SIZE = 1024;
constexpr int PORT = 8080;

void sendSession() {
    // Use std::string for payload
    std::string payload_str = "Payload-00000000000000001";
    std::vector<char> payload(payload_str.begin(), payload_str.end());

    // Create and connect SocketConnector
    SocketAddr addr("127.0.0.1", PORT);
    SocketConnector connector(addr);
    connector.connect();

    // Send data
    connector.sendData(payload);

    // Receive response
    std::vector<char> buffer(BUFFER_SIZE);
    connector.recvData(buffer);
    std::cout << "Received from server: " << std::string(buffer.data(), buffer.size()) << std::endl;
}

int main() {
    std::vector<std::thread> sessions;
    sessions.reserve(SESSION_COUNT);

    for (int i = 0; i < SESSION_COUNT; ++i) {
        sessions.emplace_back(sendSession);
    }

    for (auto& session : sessions) {
        session.join();
    }

    return 0;
}
