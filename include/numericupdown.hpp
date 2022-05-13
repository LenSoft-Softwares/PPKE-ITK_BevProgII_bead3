#ifndef NUMERICUPDOWN_HPP_INCLUDED
#define NUMERICUPDOWN_HPP_INCLUDED

#include "widgets.hpp"

class NumericUpDown : public Widget
{
protected:
    int value;
    int min_value, max_value;
    int selectedarrow = 0;
public:
    NumericUpDown(App * a, int x, int y, int sx, int sy, int _value = 0, int _min = 0, int _max = 200) : Widget(a, x, y, sx, sy)
    {
        min_value = _min;
        max_value = _max;

        value = _value;
        if(value > min_value) value = max_value;
        if(value < min_value) value = min_value;

        if(sx<50) _size_x = 50;
        if(sy<30) _size_y = 30;
        draw();
    }
    virtual void draw();
    virtual void handle(genv::event ev);
    int getValue(){return value;}
};

#endif // NUMERICUPDOWN_HPP_INCLUDED
