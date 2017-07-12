# 4ChordDHT
Simulation of Chord DHT (Distributed Hash Table) using C language and UNIX environment

--------------------------------------------------------------------------------------

In this assignment you will use the Unix fork and (possibly) wait system calls, as well as IPC using pipes and (possibly) signals to simulate a limited version of the Chord DHT (described in section 2.2 of the textbook). 

Your program will read an initial set of key values from the file key.dat in the working directory. This is a text file. The keys (and nodes) will be in the range 0-63. You will have one process for each node in the logical ring making up the DHT. Each node (process) will communicate with its successor node (process) using a pipe between the two processes. Each node is assigned a random number in the range 0-63 when it is created (using the appropriate Linux syscall for random numbers). All keys are assigned to the appropriate node following the description in the book. Your program starts with a single node (with randomly assigned ID). When a new node is created, a new process is forked, pipes created and/or rearranged, and keys properly assigned, by passing data through the network of pipes to get the data items to the correct node. The new node must be inserted in the proper place in the logical ring based on the (randomly assigned) node id.

Your program should have a menu with (at least) the following items: CREATE NEW NODE; LIST CONTENTS (the keys associated with every node are listed in output in easily understandable format); ADD KEY; DELETE KEY; QUIT PROGRAM (all processes are explicitly shut down).

Adding a key starts at the initial node. Each node knows the ID of its immediate successor, but not of all of the nodes. Your menu driven process may be part of the process running the initial node, or it may be a separate process (connected to the initial process node via pipe). You will likely find the logic easier if you make your pipes non-blocking (see the web or the Nooks and Crannies book for details).
