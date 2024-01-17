/* geometry.cpp
   A program to compute areas of geometric figures
   Author: Jeremy Ecker
*/

#include <iostream>
#include <cmath>
using namespace std;

//  -- change values to inches
void to_inches(float &height_ft, float &height_in, float &width_ft, float &width_in)
{
    height_in = height_ft*12 + height_in;
    width_in = width_ft*12 + width_in;
}

// -- Calculate circlular segment radius
float radius(float height_in, float width_in)
{
    float r = ((height_in/2) + (pow(width_in,2.0)/(8*height_in)));
    return r;
}

// -- Calculate circular segment area
float circseg_area(float radius, float height_in)
{
    float a = (pow(radius,2.0)*(acos((radius-height_in)/radius))-((radius-height_in)*(sqrt(2*radius*height_in-(pow(height_in,2.0))))));
    a = (a / 144);
    return a;
}

// -- Get user input
void get_input(float &height_ft, float &height_in, float &width_ft, float &width_in)
{
    cout << "Enter height feet: ";
    cin >> height_ft;
    cout << "Enter height inches: ";
    cin >> height_in;
    cout << "Enter width feet: ";
    cin >> width_ft;
    cout << "Enter width inches: ";
    cin >> width_in;
}

// -- Calculate rectangle area
float rect_area(float width_in, float height_in)
{
    float a = (width_in * height_in);
    a = (a / 144);
    return a;
}

// -- Calculate triangle area
float triangle_area(float width_in, float height_in)
{   
    float a = ((width_in * height_in)*0.5);
    a = (a / 144);
    return a;
}

// MAIN LOOP:
int main(int argc, char *argv[])
{
    // Variable declarations
    int choice;
    float hf;
    float hi;
    float wf;
    float wi;

    cout << "\n-------------------------------------------------\n";
    cout << "Welcome to the Geometry Area Calculator\n";
    cout << "Author: Jeremy Ecker\n";
    cout << "This program computes areas of geometric figures.\n";
    cout << "-------------------------------------------------\n\n";

    do
    { // Display menu
        cout << "-------------------------------------------------\n";
        cout << "Geometry main menu:\n";
        cout << "-------------------------------------------------\n";
        cout << "1 Rectangle area\n";
        cout << "2 Triangle area\n";
        cout << "3 Circular segment (arch) area\n";    
        cout << "4 Quit program\n";
        cout << "-------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "\n";

        if (choice < 1 || choice > 4) // Error handler
        {
            cout << "You have entered an invalid input. Try again.\n\n";
        }
        else if (choice == 1) // Rectangle area
        {
            get_input(hf, hi, wf, wi);
            to_inches(hf, hi, wf, wi);
            float ra = rect_area(wi, hi);
            cout << "Rectangle area: " << ra << " square feet\n\n";
        }
        else if (choice == 2) // Triangle area
        {
            get_input(hf, hi, wf, wi);
            to_inches(hf, hi, wf, wi);
            float ta = triangle_area(wi, hi);
            cout << "Area: " << ta << " square feet\n\n";
        }
        else if (choice == 3) // Circular segment area
        {
            get_input(hf, hi, wf, wi);
            to_inches(hf, hi, wf, wi);
            float rad = radius(hi, wi);
            cout << "Radius: " << rad << " inches\n";
            float csa = circseg_area(rad, hi);
            cout << "Area: " << csa << " square feet\n\n";
        }
    }
    while (choice != 4);

    cout << "-------------------------------------------------\n";
    cout << "Thank you for using Geometry\n";
    cout << "Written by Jeremy Ecker\n";
    cout << "-------------------------------------------------\n\n";

    return 0;
}

