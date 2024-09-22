# Socket Acceptor-Connector Thread Per-Session (POSA 2 C++)
C++20 POSA 2 Socket Acceptor-Connector Design Pattern for Client and Server using Thread-Per-Session (TPS) from ACE C++ Framework

## Threaad Per-Connection vs Thread Per-Session Differences


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
