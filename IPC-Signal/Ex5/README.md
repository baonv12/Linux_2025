# Poll-based Input and Signal Handling in C

## Description

This program demonstrates how to use the `poll()` system call to wait for user input from the keyboard while also handling signals like `SIGINT` and `SIGTERM` concurrently.

It combines:
- **Non-blocking input handling** using `poll()` on standard input (`stdin`).
- **Asynchronous signal handling** using `signal()` and flag variables.

## Features

- Accepts keyboard input and prints it back.
- Responds to `SIGINT` (Ctrl+C) by printing a message.
- Responds to `SIGTERM` by printing a message and terminating the program.

## Behavior

- When the user types something and presses Enter, the input is echoed back.
- Pressing **Ctrl+C** will not terminate the program but will display "SIGINT received"
- Sending **SIGTERM** (e.g., using `kill`) will display "SIGTERM received. Exiting..." and terminate the program.
