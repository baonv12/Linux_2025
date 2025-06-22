# Pipe Communication Between Multiple Processes in C

This project demonstrates **inter-process communication (IPC)** using **multiple unnamed pipes** in C.  
It simulates a message flow across a chain of processes: from the **parent** ➜ to **child 1** ➜ to **child 2**.

---

## 🧠 Program Overview

The program creates two pipes and forks two child processes:

1. **Parent process:**
   - Sends a text message `"Hello from parent"` to **Child 1** through `pipe 1`.

2. **Child 1:**
   - Receives the message from parent.
   - Appends `" and child 1!"` to the message.
   - Sends the modified message to **Child 2** through `pipe 2`.

3. **Child 2:**
   - Receives the final message and prints it.

---

## 📊 Process Flow Diagram

Parent
|
| pipe1 (fds1)
v
Child 1
|
| pipe2 (fds2)
v
Child 2