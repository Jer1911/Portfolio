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
    int z = 0; //counter variable to step through the string
    char x; //placeholder char
    string n; //placeholder string
    
    while (y[z] != '\0')
    {
        x = y[z];
        if (x < 'A' && x != ' ') //get rid of invalid chars, leave spaces
        {
            z++;
            continue;
        }
        if (x > 'Z' && x < 'a') //dealing with more invalid chars
        {
            z++;
            continue;
        }
        if (x > 'z') //dealing with more invalid chars
        {
            z++;
            continue;
        }
        x++;
        if (x == '!') //dealing with spaces
            x--;
        if (x == '[') //dealing with capital Z
            x = 'A';
        if (x == '{') //dealing with lowercase z
            x = 'a';
        n += x; //concatenate the new char to the end of the new string
        z++;
    }
    priv_str = n; //update the private member string
}

// get() method:
string EncryptedString::get()
{
    int z = 0;
    char x;
    string n;

    while (priv_str[z] != '\0')
    {
        x = priv_str[z];
        x--;
        if(x == 31) //dealing with spaces
            x++;
        if(x == 64) //dealing with capital A
            x = 90;
        if(x == 96) //dealing with lowercase a
            x = 122;
        n += x;
        z++;
    }
    return n;
}

// getEncrypted method:
string EncryptedString::getEncrypted()
{
    return priv_str;
}


