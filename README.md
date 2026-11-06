# Operating Systems Lab I: shared memory and semaphore

A C program for Linux, made for the Operating Systems Lab I course (BOSL501) at the Syrian Virtual University (SVU), semester S23. It creates a POSIX shared memory object (`/shared_memo`, 1 KB) and a named semaphore (`/my_semaphore1`), then writes the letters A to Z into the shared memory, one letter per second, waiting on the semaphore before each write and posting it after.

## Requirements

Linux with GCC (POSIX shared memory and semaphores).

## Building

Open `Test.cbp` in Code::Blocks and build, or run:

```
gcc -Wall main.c -o Test -pthread
```

On glibc versions older than 2.34, also link `-lrt`.

## Usage

```
./Test
```

The program runs for about 26 seconds. It does not remove the shared memory object or the semaphore when it exits: they stay in `/dev/shm` (`shared_memo` and `sem.my_semaphore1`) until they are deleted or the machine restarts.

## Author

Mohammad Diab

## License

[Apache 2.0](LICENSE)
