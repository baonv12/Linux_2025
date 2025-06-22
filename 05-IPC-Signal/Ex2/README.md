# Timer Using SIGALRM Signal in C

## Description

This program demonstrates how to use the `alarm()` system call together with the `SIGALRM` signal to implement a simple timer in the C programming language on Unix/Linux systems.

The program behavior:
- Sets a timer that repeats every second.
- Each time it receives the `SIGALRM` signal:
  - It increments a second counter.
  - Prints the message: `Timer: <n> seconds`.
- After 10 seconds, it prints a message and exits.

## How It Works

1. Registers a signal handler using `signal(SIGALRM, handler)`.
2. Calls `alarm(1)` to set a timer that triggers after 1 second.
3. In the signal handler:
   - Prints the number of elapsed seconds.
   - Calls `alarm(1)` again to schedule the next signal.
   - Exits the program after 10 seconds.
4. Uses `pause()` in the main loop to wait for signals without busy-waiting.

## Technical Notes

- `alarm(seconds)` sets a one-time timer.
  - Therefore, you must call `alarm(1)` again inside the handler to repeat every second.
- If you don’t call `alarm(1)` again, the signal will only be delivered once.
- `pause()` suspends the process until a signal is received, avoiding unnecessary CPU usage.

## Compile and Run

```bash
gcc timer.c -o timer
./timer
