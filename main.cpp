#include "graphics.hpp"

#include "App.h"

#include "widgets.hpp"
#include "label.hpp"
#include "numericupdown.hpp"
#include "combobox.hpp"
#include "button.hpp"
#include "checkbox.hpp"

#include <vector>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using namespace genv;

//Only even number
const int mapSize = 16;

const int XX = 160+mapSize*28;
const int YY = mapSize*28+120;
int currentPlayer = 1;

enum state {NEXT_PLAYER, WINNER_DECIDED, MAP_FULL};

struct GameLogic
{
    vector<vector<CheckBox*>>& gameMap;
    function<void(state status)> reportData;

    state gameState;

    GameLogic(vector<vector<CheckBox*>>& _gameZone, function<void(state status)> _reportData) : gameMap(_gameZone), reportData(_reportData){}

    void checkResults(CheckBox* cbox)
    {
        cbox->setPlayerValue(currentPlayer);
        cbox->setCheck();
        getGameState();
        if(gameState == NEXT_PLAYER)
        {
            nextPlayer();
        }
        reportData(gameState);

    }

    void getGameState()
    {
        for(int i = 0; i < mapSize-5; i++)
        {
            for(int j = 0; j < mapSize-5; j++)
            {
                if(equal5(gameMap[i][j], gameMap[i][j+1], gameMap[i][j+2], gameMap[i][j+3], gameMap[i][j+4]))
                {
                    cout << "WINNER";
                    gameState = WINNER_DECIDED;
                    return;
                }
            }
        }
        gameState = NEXT_PLAYER;
    }

    bool equal5(CheckBox * a, CheckBox * b, CheckBox * c, CheckBox * d, CheckBox * e)
    {
        if(a->isChecked() && b->isChecked() && c->isChecked() && d->isChecked() && e->isChecked())
        {
            return (a->getPlayerValue() == b->getPlayerValue() == c->getPlayerValue() == d->getPlayerValue() == e->getPlayerValue());
        }
        return false;
    }

    void nextPlayer()
    {
        if(currentPlayer == 1)
        {
            currentPlayer = 2;
        }
        else
        {
            currentPlayer = 1;
        }
    }
};

struct MainWindow : public App {

    vector<vector<CheckBox*>> gameZone;

    GameLogic * mainGameLogic;

    Label * lbl_title;
    Label * lbl_current_player;

    int xStart = (XX/2)-((mapSize/2))*28;
    int yStart = 90;

    MainWindow() {

        for(int i = 0; i < mapSize; i++)
        {
            vector<CheckBox*> temp;
            for(int j = 0; j < mapSize; j++)
            {
                CheckBox * cbox = new CheckBox(this,xStart+j*28,yStart+i*28,30,30, [this](CheckBox* cbox){this->mainGameLogic->checkResults(cbox);});
                temp.push_back(cbox);
            }
            gameZone.push_back(temp);
        }

        mainGameLogic = new GameLogic(gameZone, [this](state status){this->getGameData(status);});

        lbl_title = new Label(this, 10, 15, 0, 0, to_string(mapSize) + "x" + to_string(mapSize) + " amoba", false, false);
        lbl_current_player = new Label(this, 10, 35, 0, 0, "Jelenlegi jatekos: 1 [X]", false, false);
    }

    void getGameData(state status)
    {
        string sign;
        currentPlayer == 2 ? sign = "[O]" : sign = "[X]";
        lbl_current_player->setText("Jelenlegi jatekos: " + to_string(currentPlayer) + " " + sign);
    }
};

int main()
{
    gout.open(XX, YY);
    gout.load_font("LiberationSans-Regular.ttf",15,true);

    MainWindow w;
    w.mainEventLoop();
    return 0;
}
