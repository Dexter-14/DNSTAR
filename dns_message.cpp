//https://gist.github.com/fffaraz/9d9170b57791c28ccda9255b48315168
//https://www.binarytides.com/dns-query-code-in-c-with-winsock/

#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <algorithm>
#include <iterator>
 
#include "dns_message.h"

using namespace std;

int main()
{
    string hostname;   
    cin >>  hostname;
    //hostname = "www.google.daksh.in.hachckh.6789";
    istringstream iss(hostname);
    vector<string> tokens;
    string token;
    while(getline(iss,token,'.'))
    {
        if(!token.empty())
        {
            tokens.push_back(token);
            //cout << token << " ";
        }
    }

    
}