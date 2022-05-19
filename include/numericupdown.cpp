#include "graphics.hpp"
#include "numericupdown.hpp"
#include <iostream>

using namespace genv;

void NumericUpDown::draw() const
{
    gout << color(120,120,120) << move_to(_x, _y) << box(_size_x, _size_y);
    gout << color(255,255,255) << move_to(_x+2, _y+2) << box(_size_x-4, _size_y-4);
    gout << color(160,160,160) << move_to(_x+_size_x-15-2,_y+2) << box(17-2,_size_y-4);



    //Hover effect on up-down controls
    if(selectedarrow == 1) gout << color(200,200,200) << move_to(_x+_size_x-15-2, _y+2) << box(17-2,(_size_y/2)-2);
    if(selectedarrow == 2) gout << color(200,200,200) << move_to(_x+_size_x-15-2, _y+(_size_y/2)) << box(17-2,(_size_y/2)-2);

    //Draw up-down controls
    int n = 8;
    int j = ((_size_y/2)-n)/2;
    for(int i = n; i > 0; i--)
    {
        int padding = (15-i)/2;

        gout << color(120,120,120) << move_to(_x+_size_x-16+padding,_y+(_size_y/2)-j) << line(i, 0);

        gout << color(120,120,120) << move_to(_x+_size_x-16+padding,_y+(_size_y/2)+j) << line(i, 0);
        j++;
    }

    gout << color(120,120,120) << move_to(_x+4,_y+(_size_y-gout.cascent()+gout.cdescent())/2-4) << text(std::to_string(value));
}

void NumericUpDown::handle(genv::event ev)
{
    if(ev.type == ev_key)
    {
        if(ev.keycode == key_up && value < max_value) value++;
        if(ev.keycode == key_pgup && value+10 <= max_value) value+=10;
        if(ev.keycode == key_down && value > min_value) value--;
        if(ev.keycode == key_pgdn && value-10 >= min_value) value-=10;
    }

    if(ev.type == ev_mouse)
    {
        if(ev.button == btn_wheelup) {if(value < max_value) value++;}
        if(ev.button == btn_wheeldown) {if(value > min_value) value--;}

        if(ev.pos_x > _x+_size_x-15-2 && ev.pos_x < _x+_size_x-2)
        {
            if(ev.pos_y < _y+(_size_y/2) && ev.pos_y > _y+2)
            {
                if(ev.button == btn_left) {if(value < max_value) value++;}
                selectedarrow = 1;
            }
            if(ev.pos_y > _y+(_size_y/2) && ev.pos_y < _y+_size_y-2)
            {
                if(ev.button == btn_left) {if(value > min_value) value--;}
                selectedarrow = 2;
            }
        }
        else
        {
            selectedarrow = 0;
        }
    }
}
