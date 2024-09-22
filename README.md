# Socket Acceptor-Connector Thread Per-Session
C++20 POSA 2 Socket Acceptor-Connector Design Pattern for Client and Server using Thread-Per-Session (TPS) from ACE C++ Framework

## Thread Per-Connection vs Thread Per-Session Differences

The following are the differences of Thread Per-Connection vs Thread Per-Session.

- Client (client.cpp): The client simulates multiple sessions by creating threads that each establish a connection, send data, and then close the connection.

- Server (server.cpp): The server accepts each connection and spawns a thread to handle a single session (request/response). After processing, the thread and the connection are closed.

## Compiling the Project

To compile the project, create a `dist` directory and from the root of the project.

```shell
cmake -S . -B ./dist 
```

Next produce the exes.

```shell
cmake --build ./dist
```

This root-level CMakeLists.txt will call on the `client/CMakeLists.txt` and `server/CMakeLists.txt` files that in-turn will require to create the `svckit` Unix shared library.

## Project Structure

The project structure is as follows.

```shell
├── CMakeLists.txt
├── Dockerfile.client
├── Dockerfile.server
├── README.md
├── client
│   ├── CMakeLists.txt
│   └── client.cpp
├── docker-compose.yaml
├── server
│   ├── CMakeLists.txt
│   └── server.cpp
└── svckit
    ├── CMakeLists.txt
    ├── socket-acceptor.cpp
    ├── socket-acceptor.hpp
    ├── socket-addr.cpp
    ├── socket-addr.hpp
    ├── socket-connector.cpp
    ├── socket-connector.hpp
    ├── thread.cpp
    └── thread.hpp
```
