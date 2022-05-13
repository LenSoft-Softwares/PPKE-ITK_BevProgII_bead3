#include "graphics.hpp"
#include "textbox.hpp"
#include <iostream>

using namespace genv;

void TextBox::draw()
{
    gout << color(120,120,120) << move_to(_x, _y) << box(_size_x, _size_y);
    gout << color(255,255,255) << move_to(_x+2, _y+2) << box(_size_x-4, _size_y-4);
    gout << color(120,120,120) << move_to(_x+3,_y+_size_y/4) << text(itemText);
    gout << color(120,120,120) << move_to(_x+3+gout.twidth(itemText), _y+5) << line(0,_size_y-8);
}

void TextBox::handle(genv::event ev)
{
    if(ev.type == ev_key)
    {
        if(ev.keycode == key_backspace && itemText.size()>0)
        {
            itemText.pop_back();
        }
        else if(ev.type == ev_key)
        {
            if(gout.twidth(itemText)<_size_x-12)
            {
                itemText += ev.keyutf8;
            }
        }

    }
}
