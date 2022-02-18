#pragma once

#include<iostream>
#include<fstream>
#include<cstring>
#include<sstream>
#include <typeinfo>
#include "key_expand.h"
#include "encoding.h"
#include "decoding.h"
#include <unistd.h>

class Aes{

    public:

        void aes_enc();
        void aes_dec();

};