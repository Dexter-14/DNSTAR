#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <time.h>
#include "client.h"
#include "resolver.h"
#include "dns_message.h"
#include <netdb.h>

#include <sys/types.h>
#include <arpa/nameser.h>
#include <resolv.h>

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

using namespace std;

void aes_enc() {
    int extendedlength = 0;
    string myText;
    ifstream File;
    string filepath = "encryption.aes";
    File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc );
    if (!File.is_open() || File.fail()) {
        File.close();
        printf("\nError : failed to erase file content !");
    }
    File.close();
    fstream newfile;
    newfile.open("input.txt",ios::in);
    if (newfile.is_open()) { 
        string tp;
        while(getline(newfile, tp)) { 
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

void resolve() 
{
}

int lookup(string qname, unsigned short qtype, string server) 
{
    // let socket = UdpSocket::bind(("0.0.0.0", 43210))?;

    int s = socket(AF_INET,SOCK_DGRAM,0); 
    sockaddr_in dest;

    dest.sin_family = AF_INET;
    dest.sin_port = htons(53);
    dest.sin_addr.s_addr = inet_addr(server.c_str()); 

    if(inet_pton(AF_INET, server.c_str(), &dest.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return 0;
    }
   
    if (connect(s, (struct sockaddr *)&dest, sizeof(dest)) < 0)
    {
        printf("\nConnection Failed \n");
        return 0;
    }

    cout << "Connection successful" << endl;

    // let mut packet = DnsPacket::new();

    // packet.header.id = 6666;
    // packet.header.questions = 1;
    // packet.header.recursion_desired = true;
    // packet
        // .questions
        // .push(DnsQuestion::new(qname.to_string(), qtype));

    // let mut req_buffer = BytePacketBuffer::new();
    // packet.write(&mut req_buffer)?;

    unsigned char buf[65536];
    unsigned char buf_recv[65536] = {0};

    DNS_HEADER *header = NULL;
    header = (DNS_HEADER*)&buf;    

    header->id = 6666;
    header->q_count = 1;
    header->rd = 1;

    header->tc = 0;
    header->aa = 0;
    header->opcode = 0; 
    header->qr = 0;  
    header->rcode = 0;
    header->z = 0;
    header->ra = 0;
    header->ans_count = 0;
    header->ns_count = 0;
    header->rr_count = 0;
    
    // QER* q = NULL;
    // q = (QER*)&buf[sizeof(DNS_HEADER)];
    
    // unsigned char *val = new unsigned char[qname.length()+1];
    // strcpy((char *)val, qname.c_str());
    
    // q->name = val;

    QUESTION* question = NULL;
    question = (QUESTION*)&buf[sizeof(DNS_HEADER)];

    unsigned char *val = new unsigned char[qname.length()+1];
    strcpy((char *)val, qname.c_str());
    question->name = val;
    question->qtype = qtype;
    // q->ques = question;
    // question->qtype = qtype;
    // question->qclass = htons(1);

    // unsigned char *answer = (unsigned char*)&buf[sizeof(DNS_HEADER) + sizeof(QER)];

    // RESOURCE_DATA* rd = NULL;
    // rd = (RESOURCE_DATA*)&buf[sizeof(DNS_HEADER) + sizeof(QER) + (strlen((const char*)answer) + 1)];

    RESOURCE_RECORD* answers = NULL;
    answers = (RESOURCE_RECORD*)&buf[sizeof(DNS_HEADER) + sizeof(QUESTION)];

    RESOURCE_RECORD* authorities = NULL;
    authorities = (RESOURCE_RECORD*)&buf[sizeof(DNS_HEADER) + sizeof(QUESTION) + sizeof(RESOURCE_RECORD)];

    RESOURCE_RECORD* resources = NULL;
    resources = (RESOURCE_RECORD*)&buf[sizeof(DNS_HEADER) + sizeof(QUESTION) + 2 * sizeof(RESOURCE_RECORD)];

    // string hello = "Hello from client";
    // send(s, hello.c_str(), hello.length(), 0);
    sendto(s, (char*)buf, sizeof(DNS_HEADER) + sizeof(QUESTION) + 3 * sizeof(RESOURCE_RECORD), MSG_CONFIRM, (const struct sockaddr *) &dest, 
            sizeof(dest));

            cout << "sent" << endl;

    int len;
    int valread = recvfrom(s, (char*)buf_recv, sizeof(DNS_HEADER) + sizeof(QUESTION) + 3 * sizeof(RESOURCE_RECORD), MSG_WAITALL, (struct sockaddr *) &dest,
                NULL);

    cout << "Received" << endl;

   	DNS_HEADER *head = (DNS_HEADER*)&buf_recv;
    QUESTION* quesn = (QUESTION*)&buf_recv[sizeof(DNS_HEADER)];
    RESOURCE_RECORD* ans = (RESOURCE_RECORD*)&buf_recv[sizeof(DNS_HEADER) + sizeof(QUESTION)];
    RESOURCE_RECORD* auth = (RESOURCE_RECORD*)&buf_recv[sizeof(DNS_HEADER) + sizeof(QUESTION) + sizeof(RESOURCE_RECORD)];
    RESOURCE_RECORD* rs = (RESOURCE_RECORD*)&buf_recv[sizeof(DNS_HEADER) + sizeof(QUESTION) + 2 * sizeof(RESOURCE_RECORD)];

    cout << "ANSWER" << ans->name << endl;

    
    // socket.send_to(&req_buffer.buf[0..req_buffer.pos], server)?;

    // let mut res_buffer = BytePacketBuffer::new();
    // socket.recv_from(&mut res_buffer.buf)?;

    // DnsPacket::from_buffer(&mut res_buffer)
    return 0;
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    unsigned char buf[65536] = {0};
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
       
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    valread = read(new_socket, buf, 65536);
    cout << "Received" << endl;

	DNS_HEADER *header = (DNS_HEADER*)&buf;

    unsigned char *reader = &buf[sizeof(DNS_HEADER)];

    QUESTION *ques = (QUESTION*)&buf[sizeof(DNS_HEADER) + (strlen((const char*)reader) + 1)];

    unsigned char *response = (unsigned char*) malloc (1000000 * sizeof(unsigned char));

    aes_dec();

    
    string k;
    ifstream infile;
    infile.open("outputtext.txt");
    if (infile.is_open())
    {
    getline(infile, k);
    infile.close();
    }

    cout << "Doing lookup!" << endl;


    int l = lookup("3www6google3com", 1, "199.9.14.201");

    cout << "Done lookup" << endl;

	return 0;
}