# Ignore SIGTSTP Signal (Ctrl+Z)

## Description

This program demonstrates how to override the default behavior of the `SIGTSTP` signal (triggered by pressing **Ctrl+Z**). 

Normally, pressing Ctrl+Z suspends (pauses) the running process. In this program, we use the `signal()` function to catch and ignore `SIGTSTP`, allowing the process to continue running and print a message instead.

## How It Works

- A signal handler is registered for `SIGTSTP` using `signal(SIGTSTP, handler)`.
- When the user presses Ctrl+Z, instead of suspending the process, the program prints:

## Note
- If the program does not handle SIGTSTP, pressing Ctrl+Z will suspend the process by default, pausing its execution until the user resumes it using the fg or bg command in the shell.