#include<iostream>
#include<string>
using namespace std;

string convert(string y)
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

int main()
{
    string in, out;
    cout << "enter string: ";
    getline(cin, in);
    out = convert(in);
    cout << out << endl;
    return 0;
}

