This assignment contains 4 programs, out of which 2 belong to the UDP 
pair and the other 2 belong to the TCP pair. For the TCP client and server,
the server program must be run first in order to run the client program. The 
TCP server starts out by establishing socket, then it waits passively for 
the TCP client to set up the socket and establish the connection. The TCP client
prompts the user to enter a string, which would be send to the server without 
any verification. The verification process is done on server side, which sends
the "Sorry, cannot compute!" message back to the client if the string is invalid.
If the string is valid, the server uses a for loop to add up all the digit and 
sends the result back to the client. The client then appends this result to the 
"From Server: " string and prints out the result. Then it send this new total back 
to the server and repeats the above process. If at any time the server detects a 
string with length 1 (only 1 digit), it sends the last response and closes the 
socket. The client also has a similar implementation where it checks for a single 
length string and shuts down the port. In addition to the basic functionality, a
"setsocketopt" function with the value "SO_REUSEADDR" was implemented at the 
beginning to allow the port to be reused after the server programs finishes. The 
UDP server and client follow a similar set of rules for passing and processing 
strings between each other, however it uses recvfrom/sendto instead of read/write 
since no prior connection is established at the beginning and the program would 
require the destination of the message for the internet to route.
