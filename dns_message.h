#ifndef DNS_MESSAGE
#define DNS_MESSAGE

struct DNS_HEADER 
{
    unsigned short id; 
    unsigned char rd;
    unsigned char tc;
    unsigned char aa;
    unsigned char opcode; 
    unsigned char qr;  
    unsigned char rcode;
    unsigned char cd; 
    unsigned char ad;     
    unsigned char z;
    unsigned char ra;
    unsigned short q_count;
    unsigned short ans_count;
    unsigned short ns_count;
    unsigned short rr_count;
};

struct QUESTION
{
    unsigned short qtype;
    unsigned short qclass;
};

struct RESOURCE_DATA
{
    unsigned short type;
    unsigned short _class;
    unsigned int ttl;
    unsigned short rd_len;
};

struct RESOURCE_RECORD 
{
    unsigned char *name;
    struct RESOURCE_DATA *resource;
    unsigned char *rdata;
};

struct QUERY
{
    unsigned char *name;
    struct QUESTION *ques;
};

#endif