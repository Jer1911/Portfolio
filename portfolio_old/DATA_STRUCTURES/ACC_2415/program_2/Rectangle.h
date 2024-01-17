/** @file Rectangle.h */

#ifndef RECTANGLE_
#define RECTANGLE_

#include "RectangleInterface.h"

class Rectangle : public RectangleInterface
{
public:
    Rectangle();
    bool set(double newLength, double newWidth);
    double getLength() const;
    double getWidth() const;
    double getArea() const;
private:
    double length;
    double width;
};
#endif

