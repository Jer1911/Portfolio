// encrypt.h

#include<iostream>
#include<string>

#ifndef ENCRYPT_H
#define ENCRYPT_H

class ENCRYPT
{
    public:
        std::string EncryptedString();
        std::string EncryptedString(std::string str);
        
        std::string set(std::string y);
};

#endif

