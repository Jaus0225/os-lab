# Lab Report: Linux Process Management and IPC

## 1. Process Lifecycle and States
- fork(): Clones the calling process into an exact child copy using Copy-On-Write. The call returns 0 inside the child and the child's PID inside the parent.
- Zombie processes: When a child exits before its parent calls wait() or waitpid(), the kernel retains its exit status and entry in the process table as defunct [Z]. Calling waitpid() reaps the child and removes the zombie.

## 2. Process Replacement (exec)
- Address space: The exec functions replace the current process memory (code, stack, heap) with a new binary. If successful, it does not return.
- Variants used: execlp takes a variable argument list and searches PATH; execvp takes an argument array and searches PATH; execve requires explicit environment and path arguments.

## 3. Pipes and IPC
- Unidirectional flow: A pipe allocates a kernel buffer with a read descriptor fd[0] and a write descriptor fd[1].
- dup2(): Redirects stdin or stdout to the pipe descriptors, allowing commands like ls and grep to communicate without modifying their code.
- File descriptor handling: Unused read and write ends must be closed in all processes so read() receives an EOF (0 bytes) rather than blocking indefinitely.

## 4. Concurrency Control
- WNOHANG: Allows waitpid() to return immediately with 0 if a child has not finished, enabling the parent to do other work while polling.
- Process pool: In Challenge 10, a concurrency cap is maintained by tracking running tasks. When the cap is reached, wait() blocks until a slot opens before forking the next task.
