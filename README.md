# 42-minitalk

A 42 project to implement inter-process communication between two Unix processes using POSIX signals. The client sends a message to the server, one bit at a time, and the server reconstructs and prints it.

## Learning outcomes

- Understanding low-level inter-process communication (IPC)
- Encoding and decoding characters bit by bit using binary
- Handling asynchronous Unix signals (SIGUSR1, SIGUSR2)
- Managing synchronization between processes
- Designing robust signal-based protocols with acknowledgments

## Implementation details

The client encodes each character of the message into binary and sends each bit to the server using signals:
- **SIGUSR1** represents a binary **0**
- **SIGUSR2** represents a binary **1**

The server receives each signal, records the bit, and sends back:
- **SIGUSR1** to acknowledge a bit recieved
- **SIGUSR2** to acknowledge end of message **'\0'** recieved
  
This synchronization allows reliable communication at high speeds, avoiding the need to slow down with usleep after each bit.

The server prints to terminal every time 4 complete bytes have been receieved (allowing support for unicode chars).

## Compilation

```bash
make
```

This builds both **client** and **server** executables.

## Usage

In one terminal, start the server:

```bash
./server
```

The server prints its PID. Then, in another terminal, send a message:

```bash
./client <server_pid> "Your message here"
```

Example:

```bash
./client 12345 "Hello from the client! 👋✨"
```
Server will print the message and go back to listening.
Client will print "Delivered" once full message is sent and acknowledged then exit. It can be relaunched to send more messages to the same server.

## Project structure

```
minitalk/
├── client.c            # Sends the message bit by bit, waiting for server ack
├── server.c            # Reconstructs the message and sends bit-level acks
├── minitalk.h          # Shared header file
├── *_bonus.*           # Each ack is printed to demonstrate, otherwise same - standard includes bonus requirements
├── Makefile            # Compiles the project
└── README.md
```

## Notes

- Communication is one-way (client → server), but the server sends signals back to confirm each bit, ensuring reliability for large messages (70k+ words tested many times without error)
- The client includes a retry mechanism when waiting for bit acknowledgements. If no acknowledgment is received after 10 attempts (with short delays in between), the program exits with an error. This prevents the client from hanging indefinitely if the server fails to respond.

> ⚠️ **Norminette Compliance**  
> This project follows the [42 Norminette](https://github.com/42School/norminette) — a strict C coding style guide. It enforces rules like max 25 lines per function, separate declarations/assignments, and consistent formatting. Code is written for readability and structure over brevity.
