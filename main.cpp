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
const int mapSize = 10;

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
        else if(gameState == MAP_FULL)
        {

        }
        reportData(gameState);

    }

    void getGameState()
    {
        bool allChecked = true;
        for(int i = 0; i < mapSize-4; i++)
        {
            for(int j = 0; j < mapSize-4; j++)
            {
                if(equal5(vector<CheckBox*>{gameMap[i][j], gameMap[i][j+1], gameMap[i][j+2], gameMap[i][j+3], gameMap[i][j+4]}) ||
                   equal5(vector<CheckBox*>{gameMap[i][j], gameMap[i+1][j], gameMap[i+2][j], gameMap[i+3][j], gameMap[i+4][j]}) ||
                   equal5(vector<CheckBox*>{gameMap[i][j], gameMap[i+1][j+1], gameMap[i+2][j+2], gameMap[i+3][j+3], gameMap[i+4][j+4]}) ||
                   equal5(vector<CheckBox*>{gameMap[mapSize-1-i][j], gameMap[mapSize-2-i][j+1], gameMap[mapSize-3-i][j+2], gameMap[mapSize-4-i][j+3], gameMap[mapSize-5-i][j+4]}))
                {
                    gameState = WINNER_DECIDED;
                    return;
                }
                else
                {
                    if(!gameMap[i][j]->isChecked() || !gameMap[i+1][j+1]->isChecked() || !gameMap[i+2][j+2]->isChecked() || !gameMap[i+3][j+3]->isChecked() || !gameMap[i+4][j+4]->isChecked()) allChecked = false;
                }
            }
        }

        allChecked ? gameState = MAP_FULL : gameState = NEXT_PLAYER;
    }

    bool equal5(vector<CheckBox*> boxes)
    {
        if(boxes[0]->isChecked() && boxes[1]->isChecked() && boxes[2]->isChecked() && boxes[3]->isChecked() && boxes[4]->isChecked())
        {
            int av = boxes[0]->getPlayerValue();
            int bv = boxes[1]->getPlayerValue();
            int cv = boxes[2]->getPlayerValue();
            int dv = boxes[3]->getPlayerValue();
            int ev = boxes[4]->getPlayerValue();

            if((av == bv && av == cv && av == dv && av == ev) && (bv == cv && bv == dv && bv == ev) && (cv == dv && cv == ev) && (dv == ev))
            {
                boxes[0]->setHighlight(true);
                boxes[1]->setHighlight(true);
                boxes[2]->setHighlight(true);
                boxes[3]->setHighlight(true);
                boxes[4]->setHighlight(true);
            }
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
        if(status == MAP_FULL) lbl_current_player->setText("Betelt a jatekter!");
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
