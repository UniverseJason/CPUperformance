# CPU Performance
This is a multithreaded program that will allow us to measure the CPU utilization, Throughput, Turnaround time, and Waiting time in Ready Queue of the four basic CPU scheduling algorithms.

The implementation algorithms are FIFO, SJF, PR, and RR. And it will create one list to simulate processes getting into the ready queue in the CPU and another IO queue for IO burst time by giving an input file.

## Code function
The program has three main thread to implement this goal

`void* fileRead(void *arg);`<br />
This thread will have the “producer” role, which will get the information from the input file, parse it, generate a new node, and append it to the CPU ready queue. Besides, this is also the place to start the clock for one node (process), so that program could calculate the turnaround time when the node exit. When all the operation is done in the file read thread, it will wake up the CPU thread for future operation, this step is implemented via the binary semaphore.

`void *cpuSchedule(void *arg)`<br />
What the CPU Schedule thread does is apply the corresponding algorithms, get and remove them from the ready queue, then do the simulation of the CPU operation (here simply use the usleep function for CPU operation). After the information in this node has been updated, the thread will insert this node into the IO queue and wake up the IO thread for future operation.

`void* ioSystem(void *arg)`<br />
The IO system thread will have a similar job as the CPU thread, the only difference is that it removes from the IO queue and simulate the IO operation via usleep and insert the process back to the CPU ready queue.

After all the thread has been joined, the main function will calculate the statistics and information that has been collected during those threads. The usage will be shown as below:<br />
`prog -alg [FIFO|SJF|PR|RR] [-quantum [integer(ms)]] -input [file name]`

## Small issue
Besides, the ready queue is implemented as a double-linked list, so that it will have an operation like append and delete first. One interesting discovery is that when code causes the segmentation fault due to the wrong access of the linked list (like reading a NULL pointer) during the execution on the terminal, it might produce Heisenbug, in other words, it works in the GDB but not work after compile, and should pay more attention when debugging the multi-thread project.
