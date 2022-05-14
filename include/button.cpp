#include "graphics.hpp"
#include "button.hpp"
#include "App.h"
#include <iostream>

using namespace genv;

void Button::draw()
{
    if(visible)
    {
        gout << color(120,120,120) << move_to(_x, _y) << box(_size_x, _size_y);
        if(onHover)
        {
            gout << color(50,50,50) << move_to(_x+2, _y+2) << box(_size_x-4, _size_y-4);
        }
        else
        {
            gout << color(140,140,140) << move_to(_x+2, _y+2) << box(_size_x-4, _size_y-4);
        }
        gout << color(255,255,255) << move_to(_x+((_size_x/2)-(gout.twidth(itemText))/2),(_y+(_size_y)/2)-((gout.cascent()+gout.cdescent())/2)) << text(itemText);
    }
}

void Button::handle(genv::event ev)
{
    if(ev.button == btn_left && isSelected(ev.pos_x, ev.pos_y) && visible)
    {
        onPressed();
    }
    this->isSelected(ev.pos_x, ev.pos_y) ? onHover = true : onHover = false;
}
