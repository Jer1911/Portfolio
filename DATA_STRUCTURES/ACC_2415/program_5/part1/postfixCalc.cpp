/***************************************************************
postfixCalc.cpp
Author: Jeremy Ecker
Assignment: 5
COSC-2436 (Programming Fundamentals III: Data Structures, 18736)
Date: 3/31/2017
***************************************************************/

#include <iostream>
#include <string>
#include "ArrayStack.h"
using namespace std;

// function get_input : gets a string from the user.
string get_input()
{
    string in_string;
    cout << endl << "Enter a postfix expression: " << endl;
/*
    if(cin.peek() == ' ') // ignores spaces in the input string
        cin.ignore();
*/
    getline(cin, in_string);
    cout << in_string << endl; // FOR TESTING
    return in_string;
}

// function convert : evaluates the postfix expression and returns result.
int convert(string in_string, ArrayStack<int> pf_array)
{
    int k = 0;
    char ch;
    int value, output, op1, op2;
    while(k < in_string.length())
    {
        ch = in_string[k];
        if((ch>='0') && (ch<='9')) // if char is a digit
        {
            value = ch - '0';
            pf_array.push(value);
        }
        else if((ch=='+')||(ch=='-')||(ch=='*')||(ch=='/')) // if char is an operator
        {
            op2 = pf_array.peek();
            pf_array.pop();
            op1 = pf_array.peek();
            pf_array.pop();
            if(ch=='+')
            {
                output = op1 + op2;
                pf_array.push(output);
            }
            if(ch=='-')
            {
                output = op1 - op2;
                pf_array.push(output);
            }
            if(ch=='*')
            {
                output = op1 * op2;
                pf_array.push(output);
            }
            if(ch=='/')
            {
                output = op1 / op2;
                pf_array.push(output);
            }
        }
        k++;
    }
    output = pf_array.peek();
    pf_array.pop();
    return output;
}

// function display_output : displays an integer on the screen.
void display_output(int output)
{
    cout << endl << "The value of the expression is " << output << endl << endl;
}

// function looper : asks the user if they want to evaluate another expression.
char looper()
{
    char more;
    cout << "Evaluate another expression (y or n)? ";
    cin >> more;
    cin.ignore(99, '\n');
    return more;
}

int main()
{
    char more = 'y';
    string in_string;
    int output;
    ArrayStack<int> pf_array;
    do
    {
        in_string = get_input();
        output = convert(in_string, pf_array);
        display_output(output);
        more = looper();
    }
    while((more == 'y') && (more != 'n'));
    return 0;
}


