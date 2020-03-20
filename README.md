# Chat-App
### A basic chat app using sockets and threads with C language.
#### Tested only on linux.
#### In order to run it:
* Replace the ip address at line 45 in client.c with your server's ip address (127.0.0.0 if you want to run both on the same machine).
* Compile your client program: ``` gcc client.c -o  client -pthread ```
* Compile your server program: ``` gcc server.c -o  server -pthread ```
* Run first your server program then your client program.
