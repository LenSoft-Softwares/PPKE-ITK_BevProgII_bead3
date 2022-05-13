#ifndef COMBOBOX_HPP_INCLUDED
#define COMBOBOX_HPP_INCLUDED

#include "widgets.hpp"
#include <vector>
 #include <iostream>

class ComboBox : public Widget
{
protected:
    std::vector<std::string> items;
    int selectedid = 0;
    int hoverid = -1;
    int dropitems = 0;
    int scrollid = 0;
    int scrolluplimit = 1;
    int scrolldownlimit;
    double maxvisibleitems = 0;
    bool ondownhover = false;
    bool listvisible = false;
    bool stretch = true;

    /*Csak egy próbálkozás :D
    void(*event)();*/

public:
    ComboBox(App * a, int x, int y, int sx, int sy, std::vector<std::string> _items, int _def = 0, int _dropcount = 0, bool _stretch = true) : Widget(a, x, y, sx, sy)
    {
        items = _items;


        if(_def != 0 && _def < (int)items.size() && _def > -1) selectedid =_def;

        maxvisibleitems = (400-_y-_size_y)/_size_y;
        dropitems = _dropcount;

        setProperties();

        if(sx<50) _size_x = 50;
        if(sy<30) _size_y = 30;

        stretch = _stretch;
        if(stretch) _size_x = autoSize();

        draw();
    }

    void setProperties()
    {
        if(dropitems == 0 || dropitems>(int)items.size() || dropitems<0) dropitems = items.size();
        if(dropitems>=maxvisibleitems) dropitems = maxvisibleitems;
        scrolldownlimit = items.size()-dropitems;
    }

    int autoSize()
    {
        int _max = 0;
        for(std::string item : items)
        {
            int currentLenght = genv::gout.twidth(item);
            if(_max < currentLenght) _max = currentLenght;
        }
        return _max + 25;
    }

    virtual void draw();
    virtual void handle(genv::event ev);
    virtual void removeItem(int i);
    void insertItem(std::string item){items.push_back(item);setProperties();}
    void setItems(std::vector<std::string> _items){items = _items; setProperties();}
    std::string getSelectedItem(){return items[selectedid];}
    int getSelectedIndex(){return selectedid;}
};
#endif // COMBOBOX_HPP_INCLUDED
