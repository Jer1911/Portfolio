// encrypt.cpp

#include "encrypt.h"
using namespace std;

// Default Constructor:
EncryptedString::EncryptedString()
{
    string priv_str;
}

// Constructor with string parameter:
EncryptedString::EncryptedString(string in_str)
{
    EncryptedString::set(in_str);
}

// Set method:
void EncryptedString::set(string y)
{
    int z = 0;
    char x;
    string n; 
    
    while (y[z] != '\0')
    {
        x = y[z];
        if (x < 'A' && x != ' ')
        {
            z++;
            continue;
        }
        if (x > 'Z' && x < 'a')
        {
            z++;
            continue;
        }
        if (x > 'z')
        {
            z++;
            continue;
        }
        x++;
        if (x == '!')
            x--;
        if (x == '[')
            x = 'A';
        if (x == '{')
            x = 'a';
        n += x;
        z++;
    }
    priv_str = n;
}

// getEncrypted method:
string EncryptedString::getEncrypted()
{
    return priv_str;
}

