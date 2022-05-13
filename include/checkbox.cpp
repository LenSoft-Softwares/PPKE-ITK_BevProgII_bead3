#include "checkbox.hpp"
#include "graphics.hpp"
#include "App.h"
#include <cmath>

using namespace genv;

CheckBox::CheckBox(App * a, int x, int y, int sx, int sy, std::function<void(CheckBox * cbox)> _fv) : Widget(a, x,y,sx,sy){checkChanged = _fv;}

void CheckBox::draw()
{
    gout << move_to(_x, _y) << color(255,255,255) << box(_size_x, _size_y);
    gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
    if (checked) {
        gout << color(255,255,255);
        if(checkValue == 1)
        {
            gout << move_to(_x+8, _y+8) << line(_size_x-16, _size_y-16);
            //gout << move_to(_x+10, _y+8) << line(_size_x-16, _size_y-16);
            gout << move_to(_x+_size_x-8, _y+8) << line(-_size_x+16, _size_y-16);
            //gout << move_to(_x+_size_x-10, _y+8) << line(-_size_x+16, _size_y-16);
        }
        else if(checkValue == 2)
        {
            int xkozep = _x+(_size_x/2);
            int ykozep = _y+(_size_y/2);
            int r = (_size_x/2) - 10;
            for(int i = -r; i <= r; i++)
            {
                for(int j = -r; j <= r; j++)
                {
                    int hossz = sqrt(i*i+j*j);
                    if((hossz <= r) && (hossz >= r-0.7)) gout << move_to(xkozep+i, ykozep+j) << dot;
                }
            }
        }
    }
}

void CheckBox::handle(event ev)
{
    if (ev.type == ev_key && (ev.keycode == key_enter || ev.keycode == ' ' && !checked)) {
        checkChanged(this);
    }
    if (ev.type == ev_mouse && isSelected(ev.pos_x, ev.pos_y) && ev.button==btn_left && !checked) {
        checkChanged(this);
    }
}

bool CheckBox::isChecked()
{
    return checked;
}
