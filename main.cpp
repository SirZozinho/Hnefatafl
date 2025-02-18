/**
 *
* @file main.cpp
*
* @brief Implementation of the Hnefatafl game.
*
* This file contains the implementation of the Hnefatafl game, including setup, gameplay, and outcome
determination.
* It also provides a testing suite for various game functions.
*
* @author Enzo
* @date 09/11/2023
*/

#include <chrono>
#include <iostream>
#include <thread> //slept_for
#include "typeDef.h"
#include "functions.h"
#include "tests.h"


using namespace std;

/**
* @brief Function to play the Hnefatafl game.
*
* This function orchestrates the Hnefatafl game, including setup, gameplay, and outcome determination.
*/
void playGame()
{
    char play;
    do{
        int nb = ATTACK;

        bool isValidSize=false, verifPos = false, isValidPos=false, isValidMove = false, isloading = false; //initialize checking to false
        bool winP1 = false, winP2 = false; //win conditions
        string filename, gamefile;
        char loadgame;
        BoardSize boardSize;
        PlayerRole playerRole;
        Position cellPosition, cellMove, save = {100, 100};

        std::chrono::seconds duree(2);

        clearConsole();     //display Hnfatafl logo
        displayHnefataflLogo(); //display the board game

        while(!isValidSize)     //while a good size isn't choosen, restart the loop
        {
            isValidSize=chooseSizeBoard(boardSize);
        }

        clearConsole();

        Cell Board[BOARD_SIZE_MAX][BOARD_SIZE_MAX];     //Creation of a board on 13x13

        do{
            displayHnefataflLogo();
            cout << "Would you load an old game ? (yes = y | no = n)" <<endl;
            cin >> loadgame;

            switch(loadgame)
            {
            case 'y':
                cout << "Name of the file (ex: file.txt)" << endl;
                cin >>filename;
                loadBoard(Board, boardSize, filename);// load the board with the file
                isloading = true;
                clearConsole();
                displayHnefataflLogo();
                cout << "Game Loaded !" << endl;
                std::this_thread::sleep_for(duree);
                clearConsole();
                break;
            case 'n':
                initializeBoard(Board, boardSize);
                isloading = true;     //Initializing of the board
                clearConsole();
                break;
            default: cout << "ERROR | not an answer" << endl;
            }
        }while(isloading == false);

        do
        {
            displayHnefataflLogo();
            displayBoard(Board, boardSize);

            if(nb%2==0)     // if nb is pair, display ATTACKER, else display DEFENDER
            {
                playerRole  = ATTACK;
                cout<<"  =============================="<<endl;
                cout<<"||           ATTACKER           ||"<<endl;
                cout<<"  =============================="<<endl << endl;
            }
            else
            {
                playerRole  = DEFENSE;
                cout<<"  =============================="<<endl;
                cout<<"||           DEFENDER          ||"<<endl;
                cout<<"  =============================="<<endl << endl;
            }

            do      //moving loop
            {
                do  //choose the pawn loop
                {
                    if(playerRole == ATTACK)        //only attacker can save
                    {
                        cout << "What piece do you want to play ? (Ex: E8) | S for save" << endl;

                        cellPosition = getPositionFromInput(playerRole, Board, boardSize);                              //requesting wich pawn player want to move
                        if (cellPosition.itsRow == save.itsRow && cellPosition.itsCol == save.itsCol)
                            return;
                    }
                    if(playerRole == DEFENSE)
                    {
                        cout << "What piece do you want to play ? (Ex: E8)" << endl;
                        cellPosition = getPositionFromInput(playerRole, Board, boardSize);                              //requesting wich pawn player want to move
                    }

                    verifPos = isValidPosition(cellPosition, boardSize);                //checking if the pawn is in the Board

                    if(verifPos == false)
                    cout << "The position is invalid" <<endl << endl;
                }while(verifPos != true);


                clearConsole();
                displayHnefataflLogo();
                displayBoard(Board, boardSize);

                if(nb%2==0)
                {
                    playerRole  = ATTACK;
                    cout<<"  =============================="<<endl;
                    cout<<"||           ATTACKER           ||"<<endl;
                    cout<<"  =============================="<<endl << endl;
                }
                else
                {
                    playerRole  = DEFENSE;
                    cout<<"  =============================="<<endl;
                    cout<<"||           DEFENDER          ||"<<endl;
                    cout<<"  =============================="<<endl << endl;
                }

                cout << "Pawn chooses :  " << (char) (cellPosition.itsRow +65) << (cellPosition.itsCol +1) << endl << endl;     //Indication of chooses pawn
                cout << "Where do you want to go ?" << endl;    //request the end position
                cellMove = getPositionFromInput(playerRole, Board, boardSize);  //receip the end pos

                isValidPos = isValidPosition(cellPosition, boardSize);      //check if it's in the board dimensions

                if(isValidPos == true)      //if the position is in the dimensions board
                {
                    isValidMove = isValidMovement(playerRole, Board, cellPosition, cellMove);       //checking if the movement is valid and if the player choses his pawn
                    if (isValidMove == true)        //if is valid
                    {
                        movePiece(Board, cellPosition, cellMove);       //Apply the changes
                        capturePieces(playerRole, Board, boardSize, cellMove);  //checking if a piece get captured
                    }
                }

            }while(isValidMove != true);

            if(isKingEscaped(Board, boardSize) == true)     //if king is in a corner board, p2 win
                winP2 = true;

            else if(isSwordLeft(Board, boardSize) == false)     //if there is not sword left, p2 win
                winP2 = true;

            else if(isKingCaptured(Board, boardSize) == true)   //if the king is captured, p1 win
                winP1 = true;

            else{       //else, change the role and clear console
                nb++;
                clearConsole();
            }
        }while(!(winP1 == true || winP2 == true));

        clearConsole();

        cout << endl<< endl;
        cout << "██╗   ██╗██╗ █████╗ ████████╗ █████╗ ██████╗ ██╗   ██╗██╗" << endl;
        cout << "██║   ██║██║██╔══██╗╚══██╔══╝██╔══██╗██╔══██╗╚██╗ ██╔╝╚═╝" << endl;
        cout << "╚██╗ ██╔╝██║██║  ╚═╝   ██║   ██║  ██║██████╔╝ ╚████╔╝    " << endl;
        cout << " ╚████╔╝ ██║██║  ██╗   ██║   ██║  ██║██╔══██╗  ╚██╔╝     " << endl;
        cout << "  ╚██╔╝  ██║╚█████╔╝   ██║   ╚█████╔╝██║  ██║   ██║   ██╗" << endl;
        cout << "   ╚═╝   ╚═╝ ╚════╝    ╚═╝    ╚════╝ ╚═╝  ╚═╝   ╚═╝   ╚═╝" << endl << endl << endl;

        if (winP1 == true)
        {
            cout << "██████╗ ██╗      █████╗ ██╗   ██╗███████╗██████╗      ██╗" << endl;
            cout << "██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██╔════╝██╔══██╗    ███║" << endl;
            cout << "██████╔╝██║     ███████║ ╚████╔╝ █████╗  ██████╔╝    ╚██║" << endl;
            cout << "██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██╔══╝  ██╔══██╗     ██║" << endl;
            cout << "██║     ███████╗██║  ██║   ██║   ███████╗██║  ██║     ██║" << endl;
            cout << "╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝     ╚═╝" << endl;
            displayBoard(Board, boardSize);
        }
        else
        {
            cout << "██████╗ ██╗      █████╗ ██╗   ██╗███████╗██████╗     ██████╗ " << endl;
            cout << "██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██╔════╝██╔══██╗    ╚════██╗" << endl;
            cout << "██████╔╝██║     ███████║ ╚████╔╝ █████╗  ██████╔╝     █████╔╝" << endl;
            cout << "██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██╔══╝  ██╔══██╗    ██╔═══╝ " << endl;
            cout << "██║     ███████╗██║  ██║   ██║   ███████╗██║  ██║    ███████╗" << endl;
            cout << "╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝    ╚══════╝" << endl;
            displayBoard(Board, boardSize);
        }

        cout << "Would you rematch ? (y or n)" << endl;
        cin >> play;
    }while(play == 'y');

    cout << "Bye !" << endl;

    return;
}

/**
* @brief Launches the testing suite.
*
* This function runs a suite of tests to validate various game functions.
*/
void launchTests(){
    cout << endl << "********* Start testing *********" << endl << endl;
    // Here you can use tests functions

    test_chooseSizeBoard();
    test_initializeBoard();
    test_getPositionFromInput();
    test_isValidPosition();
    test_isEmptyCell();
    test_isValidMovement();
    test_movePiece();
    test_capturePieces();
    test_isSwordLeft();
    test_getKingPosition();
    test_isKingEscaped();
    test_isKingCaptured();

    cout << endl << "********** End testing **********" << endl << endl;
}

/**
* @brief Main function of the game.
*
* The main function serves as the entry point for the Hnefatafl game. It can be used to start the game or run tests.
*
* @return 0 for successful execution.
*/
int main() {
    char choice;
    bool isValid = false;

    do{
        clearConsole();
        displayHnefataflLogo();
        cout << "         Play = P   |   T= Test" << endl;
        cin >> choice;

        switch(choice)
        {
        case 'P': isValid=true; playGame();break;          // Start the game

        case 'T': isValid=true; launchTests();break;       // Launch the test

        default:cout <<"Invalid choice";break;
        }
    }while(isValid !=true);

    return 0;
}
