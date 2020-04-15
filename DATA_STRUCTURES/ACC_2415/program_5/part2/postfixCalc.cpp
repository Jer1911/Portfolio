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

// global error variable:
bool error = false;

// function get_input : gets a string from the user.
string get_input()
{
    string in_string;
    cout << endl << "Enter a postfix expression: " << endl;
    getline(cin, in_string);
    return in_string;
}

// function set_error : receives error code from convert function,
// prints error message, and sets global error variable to true,
// and empties the stack.
void set_error(int error_code, ArrayStack<int> pf_array)
{
    if(error_code==1)
        cout << "Invalid character detected! ";
    else if(error_code==2)
        cout << "Malformed expression detected! ";
    cout << "Canceling operation." << endl;
    while(!pf_array.isEmpty()) // empty out the stack so it can be reused.
        pf_array.pop();
    error = true; // set the global error variable to true
}

// function convert : evaluates the postfix expression and returns result.
int convert(string in_string, ArrayStack<int> pf_array)
{
    char ch;
    int value, output, op1, op2, error_code;
    for(int k=0; k < in_string.length(); k++)
    {
        ch = in_string[k];
        if((ch>='0') && (ch<='9')) // if char is a digit, push equivalent int.
        {
            value = ch - '0';
            pf_array.push(value);
        }
        else if((ch=='+')||(ch=='-')||(ch=='*')||(ch=='/')) // if char is an operator:
        {
            if(!pf_array.isEmpty())
            {
                op2 = pf_array.peek();
                pf_array.pop();
            }
            else // empty stack error
            {
                error_code = 2;
                set_error(error_code, pf_array);
                return 0;
            }
            if(!pf_array.isEmpty())
            {
                op1 = pf_array.peek();
                pf_array.pop();
            }
            else // empty stack error
            {
                error_code = 2;
                set_error(error_code, pf_array);
                return 0;
            }
            // if no errors yet, do the specified operation:
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
        else if(ch == ' ') // if char is a space, do nothing.
            ;
        else // invalid character error
        {
            error_code = 1;
            set_error(error_code, pf_array);
            return 0;
        }
    }
    if(!pf_array.isEmpty())
    {
        output = pf_array.peek();
        pf_array.pop(); // remove the last item from the stack.
    }
    else // empty stack error
    {
        error_code = 2;
        set_error(error_code, pf_array);
        return 0;
    }
    if(pf_array.isEmpty())
        return output; // success!
    else // if stack is not empty after last value is supposed to be removed, error
    {
        error_code = 2;
        set_error(error_code, pf_array);
        return 0;
    }
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
    cin.ignore(99, '\n'); // get rid of the pesky newline character. Thanks Professor!
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
        if(!error) // only call display_output if global error is false.
            display_output(output);
        more = looper();
        error = false; // reset global error variable.
    }
    while((more == 'y') && (more != 'n'));
    return 0;
}


