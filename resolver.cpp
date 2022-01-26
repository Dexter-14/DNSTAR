#include<bits/stdc++.h>
#include <client.h>
#include <resolver.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <iostream>

void resolveQuery(string server, string query_name, usigned int query_type) 
{
    Client client = new Client();
    client.ReadTimeout = time(2);

    msg = &dns.Msg{
		MsgHdr: dns.MsgHdr{
			RecursionDesired: true,
			Opcode:           dns.OpcodeQuery,
		},
		Question: make([]dns.Question, 1),
	}
	options = &dns.OPT{
		Hdr: dns.RR_Header{
			Name:   ".",
			Rrtype: dns.TypeOPT,
		},
	}
	msg.Extra = append(msg.Extra, options);
	options.SetDo();
	options.SetUDPSize(uint16(MaxDNSPacketSize));
	msg.Question[0] = dns.Question{Name: qName, Qtype: qType, Qclass: dns.ClassINET};
	msg.Id = dns.Id();
	for(int i = 0; i < 3; i++) {
		response, rtt, err = client.Exchange(msg, server);
		if neterr, ok := err.(net.Error); ok && neterr.Timeout() {
			client.ReadTimeout *= 2;
			continue;
		}
		_ = rtt;
		if err != nil {
			return nil, err;
		}
		// return response, nil;
	}
	// return nil, errors.New("Timeout")
}

#include<bits/stdc++.h>
using namespace std;

void resolve(string server, string name,bool singleResolver)
{
    //-
    string parts = 
    if( parts.lengt()==2 )
    {
        name = parts[0];
        server = parts[1];
        singleResolver = true;
    }

    //-
    if (host=="0.0.0.0")
    {
        host = "127.0.0.1";
    }
    else if(host=="[::]")
    {
        host = "[::1]";
    }
     //-
    server = cout << host <<":" <<port;
    
    cout << "Resolving " << name <<"using "<<host << "port "<<port; 
    //-
    name = dns.gethostname(name);
    //-cname

    for()

    
}

int main()
{
    cout << "Hey";

    return 0;
}