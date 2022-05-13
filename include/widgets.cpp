#include "widgets.hpp"
#include "graphics.hpp"
#include "App.h"

using namespace genv;

Widget::Widget(App * a, int x, int y, int sx, int sy) : _app(a), _x(x), _y(y), _size_x(sx), _size_y(sy)
{
    _app->add_widget(this);
}

bool Widget::isSelected(int mouse_x, int mouse_y)
{
    return mouse_x>_x && mouse_x<_x+_size_x && mouse_y>_y && mouse_y<_y+_size_y;
}
