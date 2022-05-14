#include "graphics.hpp"
#include "label.hpp"

using namespace genv;

Label::Label(App * a, int x, int y, int sx, int sy, std::string _text, bool _box, bool _align): Widget(a, x,y,sx,sy){
    itemText = _text;
    wbox = _box;
    alignleft = _align;
    draw();
}

void Label::draw()
{
    if(wbox)
    {
        gout << move_to(_x, _y) << color(140,140,140) << box(_size_x, _size_y);
    }
    if(alignleft)
    {
        gout << move_to(_x+_size_x-gout.twidth(itemText)-5, _y+((_size_y/2)-(gout.cascent()+gout.cdescent())/2)) << color(255,255,255) << text(itemText);
    }
    else
    {
        if(wbox)
        {
            gout << move_to(_x+(_size_x/2)-gout.twidth(itemText)/2, _y+((_size_y/2)-(gout.cascent()+gout.cdescent())/2)) << color(255,255,255) << text(itemText);
        }
        else
        {
            gout << move_to(_x+5, _y+((_size_y/2)-(gout.cascent()+gout.cdescent())/2)) << color(255,255,255) << text(itemText);
        }

    }

}

void Label::setText(std::string text)
{
    itemText = text;
    draw();
}

std::string Label::getText()
{
    return itemText;
}
