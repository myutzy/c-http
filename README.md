# C-HTTP: A Simple HTTP Server in C

C-HTTP is a minimalist HTTP server written in C, designed to demonstrate core concepts of network programming, socket management, and HTTP communication.
## Features

- **Single Connection Handling**: Supports handling one client connection at a time with easy extensibility to handle multiple clients.
- **Basic Logging**: Logs server activities, including requests, responses, errors, and potential security threats.
- **Modular Design**: Organized code structure with separate modules for server setup, request handling, response generation, and logging.
- **Security Considerations**: Implements basic security measures like preventing directory traversal attacks.
- **Cross-Platform**: Written in standard C, making it portable across different operating systems.

## Getting Started

### Prerequisites

- **CMake**: Make sure CMake is installed on your system.
- **C Compiler**: Any standard C compiler like GCC or Clang.

### Building the Project

1. Clone the repository:
   ```sh
   git clone https://github.com/myutzy/c-http.git
   ```
2. Navigate to the project directory:
   ```sh
   cd c-http
   ```
3. Create a build directory and navigate into it:
   ```sh
   mkdir build && cd build
   ```
4. Generate the build files using CMake:
   ```sh
   cmake ..
   ```
5. Build the project:
   ```sh
   make
   ```

### Running the Server

1. After building the project, you can run the server:
   ```sh
   ./c-http
   ```
2. The server will start and listen for incoming connections. You can connect using a web browser or tools like `curl` or `telnet`.

### Connecting to the Server

- Use a web browser and navigate to `http://localhost:8080/`.
- Use `curl`:
  ```sh
  curl http://localhost:8080/
  ```
- Use `telnet`:
  ```sh
  telnet localhost 8080
  ```

## Project Structure

```
c-http/
├── CMakeLists.txt          # CMake configuration file
├── README.md               # Project documentation
├── include/
│   ├── server.h            # Header for server.c
│   ├── request_handler.h   # Header for request_handler.c
│   ├── response.h          # Header for response.c
│   ├── file_utils.h        # Header for file_utils.c
│   ├── logger.h            # Header for logger.c
├── public/
│   ├── index.html          # Example home page
│   ├── about.html          # Example about page
│   ├── contact.html        # Example contact page
├── src/
│   ├── main.c              # Entry point of the server
│   ├── server.c            # Server setup and connection handling
│   ├── request_handler.c   # Request processing logic
│   ├── response.c          # HTTP response generation
│   ├── file_utils.c        # File handling utilities
│   ├── logger.c            # Logging utilities
```

## Contributing

Contributions are welcome! Feel free to fork this repository, make changes, and submit a pull request. Please ensure your changes are well-documented and tested.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Special thanks to the community for providing examples and inspiration for this project.
- Thanks to [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/) for providing a great resource on socket programming.