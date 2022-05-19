#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "widgets.hpp"
#include "App.h"
#include<functional>

class Button : public Widget
{
protected:
    std::string itemText;
    bool onHover = false;
    bool visible = true;
    std::function<void()> onPressed;
public:
    Button(App * a, int x, int y, int sx, int sy, std::function<void()> _f, std::string _text = "") : Widget(a, x, y, sx, sy)
    {
        itemText = _text;
        onPressed = _f;
        draw();
    }
    virtual void draw() const;
    virtual void handle(genv::event ev);
    void setVisibility(bool val) {visible = val;}
    std::string getItemtext() const {return itemText;};
};

#endif // BUTTON_HPP_INCLUDED
