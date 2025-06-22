# Process Communication Using Signals (SIGUSR1)

## Description

This C program demonstrates inter-process communication between a parent and a child process using the `SIGUSR1` signal.

- The parent process creates a child process using `fork()`.
- Every 2 seconds, the parent sends a `SIGUSR1` signal to the child process.
- The child process catches the signal and prints a message.
- After sending the signal 5 times, the parent terminates the child process.

## How It Works

### Child Process

- Registers a signal handler for `SIGUSR1` using `signal(SIGUSR1, handler)`.
- Waits for incoming signals using `pause()`.

### Parent Process

- Sends the `SIGUSR1` signal to the child process every 2 seconds using `kill()`.
- Repeats this 5 times.
- Sends `SIGKILL` to terminate the child process after communication.
- Waits for the child to terminate using `wait()`.

## Key Functions Used

- `fork()` – Creates a new child process.
- `signal()` – Sets up a signal handler for the child.
- `kill()` – Sends a signal from parent to child.
- `pause()` – Suspends the child process until a signal is received.
- `sleep()` – Delays signal sending in parent.
- `wait()` – Waits for child termination.

## Sample Output

