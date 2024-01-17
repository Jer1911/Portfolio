// encrypt.h

#include<iostream>
#include<string>

#ifndef ENCRYPT_H
#define ENCRYPT_H

class EncryptedString
{
    private:
        std::string priv_str;

    public:
        EncryptedString();
        EncryptedString(std::string in_str);
        void set(std::string y);
        std::string getEncrypted();
        std::string get();
};

#endif

