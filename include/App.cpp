#include <App.h>
#include "graphics.hpp"
#include <iostream>

using namespace genv;

void clear()
{
    gout << move_to(0,0) << color(0,0,0) << box(400,400);
}

void App::mainEventLoop() {
    event ev;
    int focus = -1;
    while(gin >> ev) {
        if (ev.type == ev_mouse && ev.button==btn_left) {
            for (size_t i=0;i<widgets.size();i++) {
                if (widgets[i]->isSelected(ev.pos_x, ev.pos_y)) {
                    focus = i;
                }
            }
        }

        if (focus!=-1) {
            widgets[focus]->handle(ev);
        }

        clear();
        for (Widget * w : widgets) {
            w->draw();
        }
        if(focus>-1) widgets[focus]->draw();

        gout << refresh;
    }
}
