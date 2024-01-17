#ifndef RECTANGLE_INTERFACE_
#define RECTANGLE_INTERFACE_

//  Listing 2
/** @file RectangleInterface.h */

class RectangleInterface
{
public:
    /** Updates the dimensions of this Rectangle
     @param  newLength, newWidth, the new length and width for this Rectangle
     @pre    newLength and newWidth must be larger than zero
     @post   If newLength and newWidth are valid, the length and width
             of this object is set to newLength and newWidth
             Otherwise, the Rectangle is not updated 
     @return  True if this object is updated,
              and false otherwise. */ 
    
    virtual bool set(double newLength, double newWidth) = 0;
    
    /** Gets the length and width of this Rectangle
     @return The length and width of this Rectangle. */

    virtual double getLength() const = 0;
    virtual double getWidth() const = 0;
    
    /** Gets the area  of this Rectangle
     @return The area of this Rectangle. */
    virtual double getArea() const = 0;

    /** Destroys this Rectangle and frees its assigned memory. */
    virtual ~RectangleInterface()  {}
};
#endif

