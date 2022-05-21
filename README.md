# Threading the sorter - Merge Sort
Here, the expectation is divided into phases -  

## For phase 1 -  
Implement the sorting/merging functions in a sequential manner following the structure given in the problem description. Read from a file and initialize the pointer to the beginning of the data segment in the array, and the data segment size as input parameters. Then, call the main driver function to invoke the sorting and merging functions multiple times with the proper input parameters.  

## For phase 2 -  
I were to utilize my code for Inter Process Communication (IPC) between Admin-Cal processes from project1. Implement the client code that accepts input requests from user (a filename), and sends them to Admin via socket. As a proof-of-concept, at each communication interface, print out what is send and what is received in Cal process.  

## For phase 3 -  
In client process, I am reading, storing, and sending multiple input files (which are to be sorted), so that, upon giving ’END’ as a filename, I can terminate the socket connection. After reading the files and saving them in a buffer, communicating the same buffer from Admin process to Child process (cal) avoiding the cost of copying the array into Sorter Array.  

## For phase 4 (final phase) -  
To create threads and assign each to either sorting or merging of Merge Sort. To synchronize threads for proper sorting and for handling multiple requests in a pipe-lining manner.  

Time spent: **15+** hours spent in total

## Steps achieved

- [X] Successfully initialized, instantiated, and brought array elements from file into the main input array of the Sorter  
- [X] Correctly sorted the input array with the assistance of a helper array (for intermediate sort and merge)
- [X] Facilitated a user input - debug command (D), for printing the intermediate steps of Sorter
- [X] Able to establish communication between a dummy server and Client
- [X] Successfully incorporated pipe communication between Admin-Cal processes in project3
- [X] Able to read sorting input requests from file and send them from Client to Admin via socket
- [X] Able to print communication in cal process
- [X] Able to sequentially send multiple files from client to Admin server. (Use END to terminate the connection)

## Screenshots of the execution
Final output -  
![image](https://user-images.githubusercontent.com/91232193/169626322-4cb14cf8-83ce-4e2e-92d4-18b189081f14.png)

## Challenges faced 
(Resolved challenges are ticked)

- [X] Faced problems while tracking pointers and sorting different segments
- [X] Passing global variables into recursive calls changes their values at unexpected places
- [ ] Multiple thread creation and dividing them to be either sorter or merger 
- [ ] Thread synchronization with select function for large input files
- [ ] Unable to establish the connection between one admin and multiple client servers
