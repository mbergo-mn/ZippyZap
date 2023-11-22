# ZippyZap

## Overview

ZippyZap is a network communication tool that provides both TCP and UDP client-server implementations. This project is designed to demonstrate fundamental network programming concepts in C, showcasing how data can be efficiently transmitted over both TCP and UDP protocols.

## Features

- **TCP Client-Server**: Implements a basic TCP client and server for reliable data transmission.
- **UDP Client-Server**: Demonstrates a UDP client and server for faster, connectionless communication.
- **Efficient Data Handling**: Uses a buffer size optimized for network transmission.
- **Error Handling**: Robust error handling in network operations.

## Getting Started

### Prerequisites

- A C compiler (like gcc)
- Basic knowledge of networking concepts

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/mbergo-mn/ZippyZap.git
   ```

2. Navigate to the TCP or UDP directory:

   ```bash
   cd ZippyZap/TCP
   ```

   or

   ```bash
   cd ZippyZap/UDP
   ```

### Running the Application

1. Compile the server and client code. For example, for the TCP server:

   ```bash
   gcc server.c -o tcpServer
   ```

2. Run the server:

   ```bash
   ./tcpServer
   ```

3. In a new terminal, compile and run the client with the required arguments:

   ```bash
   gcc client.c -o tcpClient
   ./tcpClient <filename> <IP:PORT>
   ```

## Usage

The TCP and UDP implementations can be used to test and understand the basic differences between these two protocols. You can send files or messages from the client to the server using either protocol.

## Contributing

Contributions to ZippyZap are welcome! Please read `CONTRIBUTING.md` for details on our code of conduct and the process for submitting pull requests.

## License

This project is licensed under the [MIT License](https://opensource.org/license/MIT/) - see the [License](https://opensource.org/license/MIT/) file for details.
