#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *recieve_msg(void *id){
	char phrase[255];
	int socketID = (int) id;
	do
	{
		printf("\n Reception message");
		if (strcmp(phrase, "EXIT") != 0)
		{
			memset(phrase, 0, 255);
			recv(socketID, phrase, 255, 0);
			printf("phrase reçu: %s\n", phrase);
		}
	} while (strcmp(phrase, "EXIT") != 0);
}

void *send_msg(void *id){
	char phrase[255];
	int socketID = (int) id;
	do
	{
		printf("\nEntrer message : ");
		scanf("\n%s", phrase);

		if ((send(socketID, phrase, strlen(phrase), 0)) == -1)
			perror("send");
		else
			printf("\n message envoyé");

	} while (strcmp(phrase, "EXIT") != 0);
}

int main()
{
	struct sockaddr_in informations;
	informations.sin_family = AF_INET;
	informations.sin_port = htons(6666);
	informations.sin_addr.s_addr = inet_addr("192.168.43.244");
	char phrase[255];
	void *status;

	int socketID = socket(AF_INET, SOCK_STREAM, 0);
	if (socketID == -1)
	{
		perror("socket");
		exit(-1);
	}

	if ((connect(socketID, (struct sockaddr *)&informations, sizeof(struct sockaddr_in))) == 1)
	{
		perror("connect");
		exit(-1);
	}

	pthread_t thread_rcv;
	pthread_t thread_send;

	int rc = pthread_create(&thread_rcv,NULL,recieve_msg,(void *)socketID);
	int rc2 = pthread_create(&thread_send,NULL,send_msg,(void *)socketID);

	pthread_join(thread_rcv, &status);
	pthread_join(thread_send, &status);

	shutdown(socketID, SHUT_RDWR);
}

