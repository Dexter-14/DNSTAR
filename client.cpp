#include<bits/stdc++.h>
#include<ctime>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include "ConfigManager.hpp"

#define MAX_INPUT_SIZE 512

using namespace std;

// typedef struct Connection
// {
//     uint16_t UDPSize;
//     string tsigRequest;
// };

// typedef struct Client
// {
//     string Net;
//     uint16_t UDPSize;
//     bool SingleInflight;
// };

int main(int argc, char* argv[])
{
    ConfigManager lConfigManager;

    try
    {
        lConfigManager.parseArgs(argc, argv);
    }
    catch(ParseException & e)
    {
        cerr << "Error: " << e.what() << "\n";
        return -2;
    }
    catch(FileIOException & e)
    {
        cerr << "Error: " << e.what() << "\n";
        return -3;
    }
    catch(...)
    {
        cerr << "Error: unhandled exception.\n";
        return -1;
    }

    int sockfd = socket(AF_INET,SOCK_DGRAM, 0);

    if(sockfd < 0)
    {
        cerr << "Socket craetion failed." << endl;
        return -1;
    }

    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO)

    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);


}