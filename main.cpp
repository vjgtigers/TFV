#include <iostream>
#include <Windows.h>
#include <vector>
#include <thread>
#include <string>

#include "drawLayout.h"
#include "keyTracker.h"
#include "terminalCommands.h"
#include "miscFunctions.h"

#define  WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

//escape sequence
#define ESC "\x1b"
//commonly used escape sequence for commands
#define CSI "\x1b["

using namespace std;

fd_display_data nameView {true, 20}; //no particularly recommended size
fd_display_data extentionView {true, 5};//if file then display type, if folder then fldr
fd_display_data sizeView {true, 6}; //recommended size is 6 or 7
fd_display_data modifiedView {true, 14}; //recommended size is 14
fd_display_data createdView {true, 14}; //recommended size is 14

//TODO: xy-avalible should probably be in the draw functions to update teh window on resize

int fileSelectionPointer;
xy currentPointerLocation {0,2};
vector<fileInfoStruct> fileInformation;
renderCodesTemplate renderCodes = {char(62), char(179), char(196), char(194), char(193)};


int main() {
    string path_dir = "C:\\Users\\vjgti\\CLionProjects\\TFV\\cmake-build-debug";
    //path will be SAVED ON COMMIT


    //YOU CAN NOT PUT THINGS THAT DEPEND ON TERMINAL SIZE UP HERE
    //initilization settings
    if (engineInit() == -1) {return -1;}
    //end init settings
    //TODO: globalStateCalc needs to be in the function that reads in files to determin global state then



    drawBaseLayout();
    fileInput(fileInformation, path_dir);

    displayFileInfo(fileInformation);
    drawSelectionPointer({0,2});

    while(true) {
        debugOutput("Global State: " + to_string(globalState),-1);
        const int key = key_press(); // blocks until a key is pressed
        xy available = detectSize();
        debugOutput(to_string(key) +" "+(char)key +" " + to_string(available.x) + " " + to_string(available.y), 0);


        if(key == 'q') {toggleVT(false);return 0;}
        if(key == 'c') {clearScreen();}

        if(key == 'r') {
            refreshScreen(fileInformation);
        }
        if(key == 'R') {
            displayFileInfo(fileInformation);
        }
        if(key == -40) {(fileSelectionPointer+1 < fileInformation.size()) ? (fileSelectionPointer += 1) : true; updateCursorandPointerSync(fileInformation); }
        if(key == -38) {(fileSelectionPointer > 0) ? (fileSelectionPointer -= 1) : true; updateCursorandPointerSync(fileInformation); }

    }

    return 0;
}
