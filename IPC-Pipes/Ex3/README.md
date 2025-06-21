# Pipe Character Counter in C

This project demonstrates inter-process communication (IPC) in C using a pipe.  
A parent process sends a text message to a child process through a pipe.  
The child process receives the message, counts the number of characters, and displays the result.

---

## 🧠 How It Works

1. A pipe is created using `pipe()`.
2. The process is forked using `fork()`.
3. The parent process:
   - Closes the read-end of the pipe.
   - Writes a fixed string (`"Hello this is parent!"`) to the write-end.
4. The child process:
   - Closes the write-end of the pipe.
   - Reads the string from the read-end.
   - Counts the number of characters using `strlen()`.
   - Prints the received message and its length.

---

