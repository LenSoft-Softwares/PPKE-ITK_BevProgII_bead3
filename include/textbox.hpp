#ifndef TEXTBOX_HPP_INCLUDED
#define TEXTBOX_HPP_INCLUDED

#include "widgets.hpp"

class TextBox : public Widget
{
protected:
    std::string itemText;
public:
    TextBox(App * a, int x, int y, int sx, int sy, std::string _text = "") : Widget(a, x, y, sx, sy)
    {
        itemText = _text;
        draw();
    }
    std::string getText(){return itemText;}
    void setText(std::string _text) {itemText = _text;}
    virtual void draw();
    virtual void handle(genv::event ev);
};

#endif // TEXTBOX_HPP_INCLUDED
