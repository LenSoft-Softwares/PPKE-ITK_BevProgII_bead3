#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include "widgets.hpp"
#include <vector>


class App{
protected:
    std::vector<Widget*> widgets;
public:
    void add_widget(Widget * w) {widgets.push_back(w);}
    void mainEventLoop();

    virtual void esemeny(){}

};

#endif // APP_H_INCLUDED
