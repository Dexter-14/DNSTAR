#include "client.h"
#include "dns_message.h"
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <ctime>
#ifdef __WIN32__
# include <winsock2.h>
#else
# include <sys/socket.h>
#endif
#include <stdlib.h>
//#include <netinet/in.h>
#include <string.h>
#define PORT 8080

using namespace std;

void ChangetoDnsNameFormat(unsigned char* header, unsigned char* domain_name)
{
	int lock=0 , i;

	strcat((char*)domain_name,".");

	for(i=0 ; i<(int)strlen((char*)domain_name) ; i++)
	{
		if(domain_name[i]=='.')
		{
			*header++ = i-lock;
			for(;lock<i;lock++)
			{
				*header++=domain_name[lock];
			}
			lock++; 
		}
	}

    *header++='\0';
}

void format_query(unsigned char *domain) 
{
    srand(time(NULL));
    unsigned char buf[65536];

    DNS_HEADER *header = NULL;
    header = (DNS_HEADER*)&buf;

    header->id = (unsigned short)rand();
    header->rd = 1;
    header->tc = 0;
    header->aa = 0;
    header->opcode = 0; 
    header->qr = 0;  
    header->rcode = 0;
    header->cd = 0; 
    header->ad = 0;     
    header->z = 0;
    header->ra = 0;
    header->q_count = htons(1);
    header->ans_count = 0;
    header->ns_count = 0;
    header->rr_count = 0;
    
    QUESTION *ques = NULL;

    unsigned char *name = (unsigned char*)&buf[sizeof(DNS_HEADER)];
    
    ChangetoDnsNameFormat(name, domain);

    ques = (QUESTION*)&buf[sizeof(DNS_HEADER) + (strlen((const char*)name) + 1)];
    ques->qtype = htons(1); 
    ques->qclass = htons(1);

    cout << endl;
    // for(int i = 0; i < 3; i++) {
    //     printf("%c", buf[i]);
    // }

    SOCKET s = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP); 
    sockaddr_in dest;

    dest.sin_family = AF_INET;
    dest.sin_port = htons(53);
    dest.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    printf("\nSending Packet...");
	if(sendto(s, (char*)buf, sizeof(struct DNS_HEADER) + (strlen((const char*)name) + 1) + sizeof(struct QUESTION), 0, (struct sockaddr*)&dest,sizeof(dest))==SOCKET_ERROR)
	{
		printf("%d error",WSAGetLastError());
	}
	printf("Sent");

//     int i=sizeof(dest);
// 	printf("\nReceiving answer...");
// 	if(recvfrom (s,(char*)buf, 65536, 0, (struct sockaddr*)&dest, &i) == SOCKET_ERROR)
// 	{
// 		printf("Failed. Error Code : %d", WSAGetLastError());
// 	}
// 	printf("Received.");
}

int main() {

    unsigned char hostname[100];
    cout << "\nEnter Hostname to Lookup : " << endl;
	gets((char*)hostname);

    format_query(hostname);
}