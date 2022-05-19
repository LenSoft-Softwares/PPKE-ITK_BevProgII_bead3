#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

#include "widgets.hpp"


class Label : public Widget{
protected:
    std::string itemText = "dummytext";
    bool wbox;
    bool alignleft = false;
public:
    Label(App * a, int x, int y, int sx, int sy, std::string _text, bool _box, bool _align);
    virtual void setText(std::string text);
    virtual std::string getText() const {return itemText;};
    virtual void draw() const;
    virtual void handle(genv::event ev){}
};

#endif // LABEL_HPP_INCLUDED
