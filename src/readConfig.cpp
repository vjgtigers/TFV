//
// Created by vjgti on 5/7/2024.
//

#include <iostream>
#include <fstream>
#include <string>

#include "readConfig.h"

#include <string>
#include <unordered_map>

#include "commands.h"
#include "drawLayout.h"

void setUserConfig(std::string setting, std::string data) {
    std::unordered_map<std::string, int> convToInt;
    convToInt = {
        {"rc-pt", 0},
        {"rc-vd", 1},
        {"rc-hd", 2},
        {"rc-tc", 3},
        {"rc-bc", 4},
        {"rc-ac", 5},
        {"nameV", 6},
        {"extentionV", 7},
        {"sizeV", 8},
        {"modV", 9},
        {"createV", 10},
        {"kc-up", 11},
        {"kc-down", 12},
        {"kc-quit", 13},
        {"kc-refresh", 14},
        {"kc-maintainRefresh", 15},
        {"kc-clear", 16},
        {"kc-enterFolder", 17},
        {"kc-enterPar", 18},
    };


    switch (convToInt[setting]) {
        //start render codes
        case 0:
            renderCodes.pointer = char(std::stoi(data));
            break;
        case 1:
            renderCodes.divVert  = char(std::stoi(data));
            break;
        case 2:
            renderCodes.divHori  = char(std::stoi(data));
            break;
        case 3:
            renderCodes.topCombine  = char(std::stoi(data));
            break;
        case 4:
            renderCodes.bottomCombine  = char(std::stoi(data));
            break;
        case 5:
            renderCodes.allcombine  = char(std::stoi(data));
            break;
        //end render codes

        //start view options
        case 6:
            nameView.active = true;
            nameView.size = std::stoi(data.substr(2));
            break;
        case 7:
            extentionView.active = std::stoi(data.substr(0,1));
            extentionView.size = std::stoi(data.substr(2));
            break;
        case 8:
            sizeView.active = std::stoi(data.substr(0,1));
            sizeView.size = std::stoi(data.substr(2));
            break;
        case 9:
            modifiedView.active = std::stoi(data.substr(0,1));
            modifiedView.size = std::stoi(data.substr(2));
            break;
        case 10:
            createdView.active = std::stoi(data.substr(0,1));
            createdView.size = std::stoi(data.substr(2));
            break;
        //end view options

        //start key press codes
        case 11:
            keyPressCodes.up = char(stoi(data));
            break;
        case 12:
            keyPressCodes.down = char(stoi(data));
            break;
        case 13:
            keyPressCodes.quit = char(stoi(data));
            break;
        case 14:
            keyPressCodes.refresh = char(stoi(data));
            break;
        case 15:
            keyPressCodes.maintainStateRefresh = char(stoi(data));
            break;
        case 16:
            keyPressCodes.clear = char(stoi(data));
            break;
        case 17:
            keyPressCodes.enterCurrFolder = char(stoi(data));
            break;
        case 18:
            keyPressCodes.enterParFolder = char(stoi(data));
            break;
        //end key press codes

        default:
            break;
    }
}

void readUserConfig() {
    std::fstream configFile;
    configFile.open("TFV_config.txt");
    if (configFile.is_open() == true) {
        std::string lineData;
        while(std::getline(configFile, lineData)) {
            if(lineData[0] == '1' || lineData[0] == '2' || lineData[0] == '3'){
                //debugOutput("user data: " + lineData.substr(2, lineData.find(']')-2) + " " + lineData.substr(lineData.find('(')+1, lineData.find(')')-1), -16);
                //system("PAUSE");
                setUserConfig(lineData.substr(2, lineData.find(']')-2), lineData.substr(lineData.find('(')+1, lineData.find(')')-1));
            }
        }
    }
}

