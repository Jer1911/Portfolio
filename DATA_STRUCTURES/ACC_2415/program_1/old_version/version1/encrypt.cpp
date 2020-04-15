// encrypt.cpp

#include "encrypt.h"
using namespace std;

string ENCRYPT::EncryptedString(string str)
{
    string y = set(str);
    return y;
}

string ENCRYPT::set(string y)
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
    return n;
}

