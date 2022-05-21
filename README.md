# Threading the sorter - Merge Sort
Here, the expection is divided into phases -  

##For phase 1 -  
Implement the sorting/merging functions in a sequential manner following the structure given in the problem description. Read from a file and initialize the pointer to the beginning of the data segment in the array, and the data segment size as input parameters. Then, call the main driver function to invoke the sorting and merging functions multiple times with the proper input parameters.  

##For phase 2 - I were to utilize my code for Inter Process Communication (IPC) between
Admin-Cal processes from project1. Implement the client code that accepts input requests
from user (a filename), and sends them to Admin via socket. As a proof-of-concept, at each
communication interface, print out what is send and what is received in Cal process.
For phase 3 - In client process, I am reading, storing, and sending multiple input files
(which are to be sorted), so that, upon giving ’END’ as a filename, I can terminate the
socket connection. After reading the files and saving them in a buffer, communicating the
same buffer from Admin process to Child process (cal) avoiding the cost of copying the array
into Sorter Array.
For phase 4 (final phase) - To create threads and assign each to either sorting or merging
of Merge Sort. To synchronize threads for proper sorting and for handling multiple requests
in a pipe-lining manner

Portrait of a cheque
Here, the expectation is to make a "cheque scanner"; transform the picture of a cheque (bank terminology), captured from different angles and with different rotations, to a front-facing image of the cheque (akin to its scanned copy).

This covers perspective transform of an image and contour detection in OpenCV.

Time spent: 6 hours spent in total

Steps achieved
 Able to approximate contour (with 4 sides) of a cheque
 Successfully warp the image of a cheque using perspective transform of an image
Screenshots of the execution
image

Challenges faced
(Unresolved challenges are unmarked)

 Determining length and width of the resultant image of the cheque
 For the input images where cheque is held in hands, or background of the image and the color of the cheque are similar, finding contours became extremely difficult task
