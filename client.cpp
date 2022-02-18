#include <bits/stdc++.h>
#include "client.h"
#include "dns_message.h"
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <ctime>
#ifdef __WIN32__
#include <winsock2.h>
#else
# include <sys/socket.h>
#endif
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>



#include<iostream>
#include<fstream>
#include<cstring>
#include<sstream>
#include <typeinfo>
#include "key_expand.h"
#include "encoding.h"
#include "decoding.h"
#include <unistd.h>

#define PORT 8089

typedef int SOCKET;

using namespace std;

void aes_enc() {
    int extendedlength=0;
    string myText;
    ifstream File;
    string filepath = "encryption.aes";
    File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc );
    if (!File.is_open() || File.fail())
    {
    File.close();
    printf("\nError : failed to erase file content !");
    }
    File.close();
    fstream newfile;
    newfile.open("input.txt",ios::in);
    if (newfile.is_open()){ 
    string tp;
    while(getline(newfile, tp)){ 
    int messlength=tp.length();
    int extendedlength;
    if((messlength%16)!=0)
    {
    extendedlength=messlength+(16-(messlength%16));
    }
    else
    {
    extendedlength=messlength;
    }
    unsigned char* encryptedtext=new unsigned char[extendedlength];
    for(int i=0;i<extendedlength;i++)
    {
    if(i<messlength)
    encryptedtext[i]=tp[i];
    else
    encryptedtext[i]=0;
    }
    string k;
    ifstream infile;
    infile.open("key.txt");
    if (infile.is_open())
    {
    getline(infile, k); 
    infile.close();
    }

    istringstream tempkey(k);
    unsigned char key[16];
    unsigned int x;
    for(int i=0;i<16;i++)
    {
    tempkey>>hex>>x;
    key[i] = x;
    }
    unsigned char extendedkeys[176];
    Key_extenxion(key,extendedkeys);

    for(int i=0;i<extendedlength;i+=16)
    {
    unsigned char* temp=new unsigned char[16];
    for(int j=0;j<16;j++)
    {
    temp[j]=encryptedtext[i+j];
    }	
    encryption(temp , extendedkeys);
    for(int j=0;j<16;j++)
    {
    encryptedtext[i+j]=temp[j];
    }	
    }
    ofstream fout;  
    ifstream fin;
    fin.open("encryption.aes");
    fout.open ("encryption.aes",ios::app); 
    if(fin.is_open())
    fout<<encryptedtext<<"\n"; 
    fin.close();
    fout.close(); 
    }
    newfile.close(); 
    }
}

void aes_dec() {

    int extendedlength=0;
    string myText;

    string tp;
    ifstream File;
    string filepath = "outputtext.txt";
    File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc );
    if (!File.is_open() || File.fail())
    {
    File.close();
    printf("\nError : failed to erase file content !");
    }
    File.close();

    ifstream MyReadFile;
    MyReadFile.open("encryption.aes", ios::in | ios::binary);
    if(MyReadFile.is_open())
    {
    while( getline (MyReadFile, myText) )
    {
    cout.flush();
    char * x;
    x=&myText[0];
    int messlength=strlen(x);
    char * msg = new char[myText.size()+1];

    strcpy(msg, myText.c_str());

    int n = strlen((const char*)msg);
    unsigned char * decryptedtext = new unsigned char[n];
    
    for (int i = 0; i < n; i++) {
    decryptedtext[i] = (unsigned char)msg[i];
    }

    string k;
    ifstream infile;
    infile.open("key.txt");
    if (infile.is_open())
    {
    getline(infile, k);
    infile.close();
    }

    else cout << "Unable to open file";
    istringstream tempkey(k);
    unsigned char key[16];
    unsigned int x1;
    for(int i=0;i<16;i++)
    {
    tempkey>>hex>>x1;
    key[i] = x1;
    }
    
    unsigned char extendedkeys[176];
    Key_extenxion(key,extendedkeys);
    
    for (int i = 0; i < messlength; i += 16)
    {
    unsigned char * temp=new unsigned char[16];
    for(int j=0;j<16;j++)
    temp[j]=decryptedtext[i+j];
    decryption(temp , extendedkeys);
    for(int j=0;j<16;j++)
    decryptedtext[i+j]=temp[j];
    }
    for(int i=0;i<messlength;i++)
    {
    if(decryptedtext[i]==0 && decryptedtext[i-1]==0 )
    break;
    }
    cout<<endl;
    ofstream fout;  
    ifstream fin;
    fin.open("outputtext.txt");
    fout.open ("outputtext.txt",ios::app); 
    if(fin.is_open())
    fout<<decryptedtext<<"\n";

    fin.close();
    fout.close(); 
    }
    }
    else
    {
    cout<<"Can not open input file\n ";
    }
    MyReadFile.close();
}

void ChangetoDnsNameFormat(unsigned char* header, unsigned char* domain_name)
{
	int lock = 0, i;
	strcat((char*)domain_name, ".");

	for(i = 0; i < (int)strlen((char*)domain_name); i++)
	{
		if(domain_name[i] == '.')
		{
			*header++ = (i - lock) + '0';
			for(; lock < i; lock++)
			{
				*header++ = domain_name[lock];
			}
			lock++; 
		}
	}
    *header++ = '\0';
}

int format_query(unsigned char *domain) 
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
    // header->cd = 0; 
    // header->ad = 0;     
    header->z = 0;
    header->ra = 0;
    header->q_count = htons(1);
    header->ans_count = 0;
    header->ns_count = 0;
    header->rr_count = 0;
    
    QUESTION *ques = NULL;

    unsigned char *name = (unsigned char*)&buf[sizeof(DNS_HEADER)];
    
    ChangetoDnsNameFormat(name, domain);

    string query(reinterpret_cast<char*>(name));
    const char *path = "input.txt";
    ofstream out(path);
    out << query;
    out.close();

    aes_enc();

    ques = (QUESTION*)&buf[sizeof(DNS_HEADER) + (strlen((const char*)name) + 1)];
    ques->qtype = htons(1); 
    // ques->qclass = htons(1);
    
    int s = socket(AF_INET,SOCK_STREAM,0); 
    sockaddr_in dest;

    dest.sin_family = AF_INET;
    dest.sin_port = htons(PORT);
    dest.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    if(inet_pton(AF_INET, "127.0.0.1", &dest.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return 0;
    }
   
    if (connect(s, (struct sockaddr *)&dest, sizeof(dest)) < 0)
    {
        printf("\nConnection Failed \n");
        return 0;
    }

    printf("Connection successful");

    send(s, (char*)buf, sizeof(struct DNS_HEADER) + (strlen((const char*)name) + 1) + sizeof(struct QUESTION), 0);

    return 0;
}

int main() {
    string hostname = "www.google.com";
    unsigned char host[100];

    for(int i = 0; i < hostname.length(); i++) {
        host[i] = hostname[i];
    }

    format_query(host);
}