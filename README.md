# Threads, Sempahores & Message Passing implementation from scratch
The idea is to use low level C libraries to implement user level threads, semaphores and message passing between these threads. Then a client server application is created using our own threads, semaphores and message passing system.
- Using functions from `ucontext.h` we created a simple user level thread library (a tiny version of POSIX threads) in C
 - Check `thread.h` for details
- Using these threads, we implemented `wait()` and `signal()` functions for semaphores
 - Check `Sem.h` for details
- To check correctness of the sempahore library created above, we implemented the classic readers-writers problem
- Using the semaphore library created above, we implemented a single machine message passing system among threads we created above. The idea is to build ports which threads use to send and receive messages from. Each port is a buffer and controlled using semaphores like a producer consumer problem. As this is a single machine implementation, we have shared memory. You can think of it like message passing between processes on a single machine. These processes share memory at kernel level, we mimiced the same at user level among threads
 - Check `msgs.h` for details
- To check the correctness of the message passing system we built above, we implemented a server-client model with 3 clients and one server
![screen shot 2015-12-11 at 12 45 37 pm](https://cloud.githubusercontent.com/assets/670556/11753950/7e26d54e-a005-11e5-99ba-6ef8ec0e99f2.png)
 - Check `cl-srv.c` for implementation details

# To Run
Requires linux OS to run

`gcc tcb.h && gcc q.h && gcc thread.h && gcc Sem.h && gcc  && ./a.out`
