#include<iostream>
#include<sys/socket.h>
#include<bits/stdc++.h>
#include<netinet/in.h>
#include<pthread.h>
using namespace std;
set<int> clients;
void* ClientPoller(void* args)
{
	int* clientsocket = (int*)args;
	int socket = *clientsocket;
	*clientsocket = -1;
	while(true)
	{
		char buffer[4096];
		int bytes_received = recv(socket, buffer, sizeof(buffer),0);
		if(bytes_received == 0)
		{
			cout<<"Client "<<clientsocket<<" Disconnected."<<endl;
			break;
		}
		string msg(buffer,bytes_received);
		cout<<"Message from client: "<<msg<<endl;
		for (set<int>::iterator it = clients.begin(); it != clients.end(); ++it) {
			int i = *it;
			if(i == socket)
			{
				continue;
			}
			if(send(i,msg.c_str(),msg.size(),0)<0)
			{
				cout<<"Couldn't send message"<<endl;
			}
		}
	}
	clients.erase(socket);
	close(socket);
}
int main()
{
	int sockint = socket(AF_INET,SOCK_STREAM,0);
	if(sockint == -1)
	{
		cout<<"Socket creation failed."<<endl;
		return 0;
	}
	int port = 8080;
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	if(bind(sockint,reinterpret_cast<struct sockaddr*>(&serv_addr),sizeof(serv_addr))<0)
	{
		cout<<"Bind Failed!"<<endl;
		close(sockint);
		return 0;
	}

	if(listen(sockint,10) < 0)
	{
		cout<<"Listen Failed"<<endl;
		close(sockint);
	}
	cout<<"Server Started listening on port "<<port<<endl;
	while(true)
	{
		int clientsocket = accept(sockint, NULL, NULL);
		if(clientsocket<=0)
		{
			cout<<"Closing ListenerPoller"<<endl;
			break;
		}
		clients.insert(clientsocket);
		pthread_t pth;
		pthread_create(&pth,NULL,ClientPoller,(void*)&clientsocket);
	}
	close(sockint);
}
