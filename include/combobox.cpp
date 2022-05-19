#include "graphics.hpp"
#include "combobox.hpp"
#include <iostream>

using namespace genv;

void ComboBox::draw() const
{
    gout << color(120,120,120) << move_to(_x, _y) << box(_size_x, _size_y);
    gout << color(255,255,255) << move_to(_x+2, _y+2) << box(_size_x-4, _size_y-4);
    gout << color(160,160,160) << move_to(_x+_size_x-15-2,_y+2) << box(17-2,_size_y-4);


    //Hover effect on expand controls
    if(ondownhover) gout << color(200,200,200) << move_to(_x+_size_x-15-2, _y+2) << box(17-2,_size_y-4);

    //Draw expand control (triangle)
    int n = 8;
    int j = (_size_y-n)/2;
    for(int i = n; i > 0; i--)
    {
        int padding = (15-i)/2;
        gout << color(120,120,120) << move_to(_x+_size_x-16+padding,_y+j) << line(i, 0);
        j++;
    }

    if(items.size()>0) gout << color(120,120,120) << move_to(_x+4,_y+(_size_y-gout.cascent()+gout.cdescent())/2-4) << text(items[selectedid]);

    //Draw dropdown items
    if(listvisible)
    {
        for(int i = 0; i < dropitems && i < maxvisibleitems; i++)
        {
            if(hoverid == i)
            {
                gout << color(200,200,200) << move_to(_x, _y+_size_y+i*_size_y) << box(_size_x, _size_y);
            }
            else
            {
                gout << color(255,255,255) << move_to(_x, _y+_size_y+i*_size_y) << box(_size_x, _size_y);
            }
            //Handle AutoEllipsis
            gout << color(120,120,120) << move_to(_x+4,_y+_size_y+i*_size_y+((_size_y-gout.cascent()+gout.cdescent())/2)-4) << text(items[i+scrollid]);
        }
    }
}

void ComboBox::removeItem(int i)
{
    if(items.size()>0)
    {
        items.erase(items.begin()+i);
        selectedid = 0;
        setProperties();
        draw();
    }
}

/*void ComboBox::isSelected(int mouse_x, int mouse_y) override
{
    return mouse_x>_x && mouse_x<_x+_size_x+ && mouse_y>_y && mouse_y<_y+_size_y + (dropitems*_size_y);
}*/

void ComboBox::handle(genv::event ev)
{
    if(ev.type == ev_mouse)
    {
        if(ev.pos_x > _x+_size_x-15-2 && ev.pos_x < _x+_size_x-2 && ev.pos_y > _y+2 && ev.pos_y < _y+_size_y-2)
        {
            if(ev.button == btn_left) (listvisible) ? listvisible = false : listvisible = true;
            ondownhover = true;
        }
        else
        {
            if(ev.button == btn_left) listvisible = false;
            ondownhover = false;
        }

        if(ev.pos_x > _x && ev.pos_x < _x+_size_x)
        {
            for(int i = 0; i < dropitems; i++)
            {
                if(ev.pos_y >_y+_size_y+i*_size_y && ev.pos_y < _y+_size_y+_size_y+i*_size_y)
                {
                    hoverid = i;
                    if(ev.button == btn_left) selectedid = hoverid + scrollid;
                }
            }
        }
        if(ev.button == btn_wheeldown && scrollid < scrolldownlimit) scrollid++;
        if(ev.button == btn_wheelup && scrollid >= scrolluplimit) scrollid--;
    }
    if(ev.type == ev_key)
    {
        if(ev.keycode == key_up)
        {
            if(scrollid >= scrolluplimit && hoverid == 0) scrollid--;
            if(hoverid > 0) hoverid--;
            if(hoverid == -1) hoverid = 2;
        }
        if(ev.keycode == key_down)
        {
            if(scrollid < scrolldownlimit && hoverid == dropitems-1) scrollid++;
            if(hoverid < dropitems && hoverid+scrollid+1 != (int)items.size() && hoverid != dropitems-1) hoverid++;
            if(hoverid == dropitems) hoverid = 0;
        }

        if(ev.keycode == key_enter) {selectedid = hoverid + scrollid; listvisible = false;}
    }
}
