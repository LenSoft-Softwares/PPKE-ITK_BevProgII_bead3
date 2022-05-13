#ifndef CHECKBOX_HPP_INCLUDED
#define CHECKBOX_HPP_INCLUDED

#include "widgets.hpp"
#include <functional>

class CheckBox : public Widget {
protected:
    bool checked = false;
    int checkValue = 0;
    std::function<void(CheckBox * cbox)> checkChanged;
public:
    CheckBox(App * a, int x, int y, int sx, int sy, std::function<void(CheckBox * cbox)> _fv);
    virtual void draw() ;
    virtual void handle(genv::event ev);
    virtual bool isChecked();
    int getPlayerValue(){return checkValue;}
    void setPlayerValue(int val){checkValue = val;}
    void setCheck(){if(!checked) checked = true;}
};

#endif // CHECKBOX_HPP_INCLUDED
