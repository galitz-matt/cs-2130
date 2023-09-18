
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
	char buffer[4096];
    	int server, client;
    	struct sockaddr_in servaddr, cliaddr;
    	socklen_t length;
    	struct pollfd poll_fds[2];
	
	// Set up server mode
    	if (argc <= 2) {
		// Create socket
        	server = socket(AF_INET, SOCK_STREAM, 0);
        	memset(&servaddr, 0, sizeof(servaddr));
        	servaddr.sin_family = AF_INET;
        	servaddr.sin_addr.s_addr = INADDR_ANY;
        	servaddr.sin_port = (argc == 2) ? htons(atoi(argv[1])) : htons(0);
        	// Bind socket
		bind(server, (const struct sockaddr *)&servaddr, sizeof(servaddr));
		// Listen for connection
        	listen(server, 1);
	        length = sizeof(servaddr);
        	getsockname(server, (struct sockaddr *)&servaddr, &length);
        	// Print ip address and port number
		system("host $HOSTNAME");
		printf("Listening on port %d\n", ntohs(servaddr.sin_port));
		// Accept connection
        	length = sizeof(cliaddr);
        	client = accept(server, (struct sockaddr *)&cliaddr, &length);
        	close(server);
    	}
	// Set up client mode
	else {
		// Create socket
        	client = socket(AF_INET, SOCK_STREAM, 0);
        	memset(&servaddr, 0, sizeof(servaddr));
        	servaddr.sin_family = AF_INET;
        	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
        	servaddr.sin_port = htons(atoi(argv[2]));
		// Connect to server
        	connect(client, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    	}
	
	poll_fds[0].fd = client;
    	poll_fds[0].events = POLLIN;
    	poll_fds[1].fd = STDIN_FILENO;
    	poll_fds[1].events = POLLIN;
    	ssize_t message_length;

    	while (1) {
        	int poll_result = poll(poll_fds, 2, 60000);

	    	// Check for message and write it
		if (poll_fds[0].revents & POLLIN) {
                	message_length = read(client, buffer, 4096 - 1);
                	if (message_length > 0) {
                    		buffer[message_length] = '\0';
				write(STDOUT_FILENO, buffer, message_length);
                	}
           	}
		// Check for message and write it
            	if (poll_fds[1].revents & POLLIN) {
			message_length = read(STDIN_FILENO, buffer, 4096 - 1);
                	if (message_length > 0) {
                    		buffer[message_length] = '\0';
				write(client, buffer, message_length);
                	}
            	}
        }
    	close(client);
    	return 0;
}
