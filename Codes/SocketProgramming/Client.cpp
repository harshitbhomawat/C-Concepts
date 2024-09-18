#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<bits/stdc++.h>
using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* Sender(void* args)
{
	int* clientsocket = reinterpret_cast<int*>(args);
	while(true)
	{
		string msg;
		pthread_mutex_lock(&mutex);
		cout<<"Enter message, or enter q to quit"<<endl;
		getline(cin,msg);
		cout<<"message entered: "<<msg<<endl;
		cin.clear();
		pthread_mutex_unlock(&mutex);
		if(msg == "q" or msg == "Q")
		{
			cout<<"closing connection"<<endl;
			break;
		}
		send(*clientsocket,msg.c_str(),msg.size(),0);
	}
}
void* Receiver(void* args)
{
	int* clientsocket = reinterpret_cast<int*>(args);
	while(true)
	{
		char buffer[4096];
		int bytes_received = recv(*clientsocket, buffer, sizeof(buffer),0);
		if(bytes_received == 0)
		{
			cout<<"Server Disconnected."<<endl;
			break;
		}
		string msg(buffer,bytes_received);
		cout<<"Message received: "<<msg<<endl;
	}
}

int main()
{
	int clientsocket = socket(AF_INET,SOCK_STREAM,0);
	if(clientsocket<0)
	{
	cout<<"Socket creation failed!"<<endl;
	return 0;
	}
	string ip = "192.168.1.150";
	int port = 8080;

	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port  = htons(port);
	servaddr.sin_addr.s_addr = inet_addr(ip.c_str());
	while(true)
	{
		if(connect(clientsocket,reinterpret_cast<struct sockaddr*>(&servaddr),sizeof(servaddr))<0)
		{
			cout<<"Unable to connect to server!"<<endl;
			usleep(1000);
		}
		else
		{
			break;
		}
	}
	pthread_t sendth, recvth;
	pthread_create(&sendth,NULL,Sender,reinterpret_cast<void*>(&clientsocket));
	pthread_create(&recvth,NULL,Receiver,reinterpret_cast<void*>(&clientsocket));
	pthread_join(sendth,NULL);
	pthread_join(recvth,NULL);
	
}
