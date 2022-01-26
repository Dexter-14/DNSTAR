#ifndef CLIENT
#define CLIENT

#include "dns_message.h"

void format_query();
void send_query();
void get_response();
void ChangetoDnsNameFormat(unsigned char* dns,unsigned char* host);

#endif