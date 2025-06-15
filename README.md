# 42-minitalk

A 42 project to implement inter-process communication between two Unix processes using POSIX signals. The client sends a message to the server, one bit at a time, and the server reconstructs and prints it.

## Learning Outcomes

- Understanding low-level inter-process communication (IPC)
- Encoding and decoding characters bit by bit using binary
- Handling asynchronous Unix signals (`SIGUSR1`, `SIGUSR2`)
- Managing synchronization between processes
- Designing robust signal-based protocols with acknowledgments

## How It Works

The client encodes each character of the message into binary and sends each bit to the server using signals:
- `SIGUSR1` represents a binary `0`
- `SIGUSR2` represents a binary `1`

The server receives each signal, records it and prints once a complete byte has been receieved. After receiving each bit, the server sends a confirmation signal back to the client. This synchronization allows safe communication at high speeds without artificial delays (like using usleep between sending each bit). 

## Project Structure

```
minitalk/
├── client.c            # Sends the message bit-by-bit, waiting for server ack
├── server.c            # Reconstructs the message and sends bit-level acks
├── minitalk.h          # Shared header file
├── *_bonus.*           # Each ack is printed to demonstrate, otherwise same as standard
├── Makefile            # Compiles the project
└── README.md
```

## Compilation

```bash
make
```

This builds both `client` and `server` executables.

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

The client waits for an acknowledgment from the server after each bit is sent, ensuring safe and accurate communication.

## Notes

- Each bit is sent **only after** receiving an acknowledgment from the server
- Communication is one-way (client → server), but the server sends signals back to confirm each bit, ensuring reliability for large messages (70k+ words tested)
- The server runs indefinitely and processes one client message at a time

> ⚠️ **Norminette Compliance**  
> This project follows the [42 Norminette](https://github.com/42School/norminette) — a strict C coding style guide. It enforces rules like max 25 lines per function, separate declarations/assignments, and consistent formatting. Code is written for readability and structure over brevity.
