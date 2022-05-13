#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED

#include "graphics.hpp"

//Incomplete type - forward deklaráció
class App;

class Widget {
protected:
    App * _app;
    int _x, _y, _size_x, _size_y;
public:
    Widget(App * a, int x, int y, int sx, int sy);
    virtual bool isSelected(int m_x, int m_y);
    virtual void draw() = 0;
    virtual void handle(genv::event ev) = 0;
};
#endif // WIDGETS_HPP_INCLUDED
