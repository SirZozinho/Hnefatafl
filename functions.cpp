/**
 * @file fonctions.cpp
 *
 * @brief All functions for the Hnefatafl game.
 *
 * This file contains all the various functions used in the Hnefatafl game, including
 * board initialization, display, piece movement, capturing, and game state checks.
 *
 * @author Enzo - IUT Informatique La Rochelle
 * @date 09/11/2023
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>
#include "typeDef.h"
#include "functions.h"

using namespace std;


/**
 * @brief Clears the console screen based on the operating system.
 *
 * This function clears the console screen by executing system commands specific to the operating system.
 * On Windows, it uses the "cls" command, and on Linux and macOS, it uses the "clear" command.
 */
void clearConsole()
{
#ifdef _WIN32               //if gamer are on windows
    system("cls");          //clear the consol screen
#else                       //if gamer are on MacOS or Linux
    system("clear");        //clear the consol screen
#endif
}


/**
 * @brief Displays the game logo.
 *
 * This function prints the game logo to the console, which includes ASCII art text and additional information about the game.
 */
void displayHnefataflLogo()
{
    cout << endl << endl;
    cout << "  █████   █████ ██████   █████ ██████████ ███████████   █████████   ███████████   █████████   ███████████ █████       " << endl;
    cout << "  ░░███   ░░███ ░░██████ ░░███ ░░███░░░░░█░░███░░░░░░█  ███░░░░░███ ░█░░░███░░░█  ███░░░░░███ ░░███░░░░░░█░░███       " << endl;
    cout << "   ░███    ░███  ░███░███ ░███  ░███  █ ░  ░███   █ ░  ░███    ░███ ░   ░███  ░  ░███    ░███  ░███   █ ░  ░███       " << endl;
    cout << "   ░███████████  ░███░░███░███  ░██████    ░███████    ░███████████     ░███     ░███████████  ░███████    ░███       " << endl;
    cout << "   ░███░░░░░███  ░███ ░░██████  ░███░░█    ░███░░░█    ░███░░░░░███     ░███     ░███░░░░░███  ░███░░░█    ░███       " << endl;
    cout << "   ░███    ░███  ░███  ░░█████  ░███ ░   █ ░███  ░     ░███    ░███     ░███     ░███    ░███  ░███  ░     ░███      █" << endl;
    cout << "   █████   █████ █████  ░░█████ ██████████ █████       █████   █████    █████    █████   █████ █████       ███████████\u00AE"<< endl;
    cout << "  ░░░░░   ░░░░░ ░░░░░    ░░░░░ ░░░░░░░░░░ ░░░░░       ░░░░░   ░░░░░    ░░░░░    ░░░░░   ░░░░░ ░░░░░       ░░░░░░░░░░░ " << endl;
    cout << endl;
    cout << "    by Enzo - Student";
    cout<<endl<< endl;
}


/**
 * @brief Ask the user to choose the size of the game board.
 *
 * This function asks the user to choose the size of the game board
 * (either 11x11 or 13x13) and returns true with the selected size
 * if the input is valid. It returns false if the input is invalid
 * or not an integer.
 *
 * @param aBoardSize - Reference to the BoardSize variable to store the chosen board size.
 * @return True if the input is valid and a size is chosen, false otherwise.
 */
bool chooseSizeBoard(BoardSize& aBoardSize)
{
        int tempsize;
        bool isValidSize = false;

        cout << "    Choose your game size (11 or 13)" << endl;
        cin >> tempsize;

        switch(tempsize)        //check that players choose their game dimensions correctly
        {
        case BIG:               //if dimensions are 11x11 or 13x13
        case LITTLE:
            isValidSize=true;   //validation of dimensions
            aBoardSize = (BoardSize) tempsize;      //typecasting of tempsize to insert to aBoardSize
            break;

        default:cout << "ERROR | Your choice don't figure in the list" << endl;break;     //if dimensions are not good,
        }
    return isValidSize; //return the result, if its correct, return true else, return false and restart the process
}


/**
 * @brief Initialize the game board based on its size.
 *
 * This function initializes the game board with the specified size. It places
 * the fortresses, king, castle, shields, and swords on the board based on the
 * chosen board size. The board is represented as a 2D array of cells.
 *
 * @param aBoard A 2D array representing the game board.
 * @param aBoardSize The size of the game board (either LITTLE or BIG).
 */
void initializeBoard(Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize)
{
    int i,j;

    for(i=0; i<aBoardSize; i++)     //for i row and j column
    {
        for(j=0; j<aBoardSize; j++)
        {
            aBoard[i][j].itsPieceType=NONE;          //fill the array with NORMAL and NONE cases (empty cases)
            aBoard[i][j].itsCellType=NORMAL;
        }
    }



    switch(aBoardSize)      //Fill the board with corrects pieces
    {
    case BIG :              //with BIG part
        for(i=0; i<BIG; i++)
        {                                           //Initializes the array with pieces
            for(j=0; j<BIG; j++)
            {
                if((i==1 && j== (BIG-1)/2) || (i==(BIG-2) && j== (BIG-1)/2) || (i==(BIG-1)/2 && j==1) || (i==(BIG-1)/2 && j==(BIG-2)))      //SWORD for i=1 j=6 | i=11 j=6 | i=6 j=1 | i=6 j=11
                {
                    aBoard[i][j].itsPieceType=SWORD;
                }

                if(i== (BIG-1)/2 && j<= (BIG-4) && j>= 3)               //SHIELD for i=4 between j=4 and j=8
                {
                    aBoard[i][j].itsPieceType=SHIELD;
                }

                if(j== (BIG-1)/2 && i<= (BIG-4) && i>= 3)               //SHIELD for j=4 between i=4 and i=8
                {
                    aBoard[i][j].itsPieceType=SHIELD;
                }
            }
            }break;

    case LITTLE: //with LITTLE part
        for(i=0; i<LITTLE; i++)
        {
            for(j=0; j<LITTLE; j++)
            {
                if((i==1 && j== (LITTLE-1)/2) || (i==(LITTLE-2) && j== (LITTLE-1)/2) || (i==(LITTLE-1)/2 && j==1) || (i==(LITTLE-1)/2 && j==(LITTLE-2)))      //SWORD for i=1 j=6 | i=11 j=6 | i=6 j=1 | i=6 j=11
                {
                    aBoard[i][j].itsPieceType=SWORD;
                }

                if((i>=((LITTLE/2)-1) && i <= ((LITTLE/2)+1)) &&  (j>=((LITTLE/2)-1) && j <= ((LITTLE/2)+1)))               //SHIELD for i=4 between j=4 & j=8
                {
                    aBoard[i][j].itsPieceType=SHIELD;
                }

                if((i==(LITTLE/2)-2 && j==(LITTLE/2)) || (i==(LITTLE/2)+2 && j==(LITTLE/2)) || (j==(LITTLE/2)-2 && i==(LITTLE/2)) || (j==(LITTLE/2)+2 && i==(LITTLE/2)))             //SHIELD in the diamond, in the middle
                {
                    aBoard[i][j].itsPieceType=SHIELD;
                }
            }
        }break;

    default : cout << "ERROR | Initialize the Board (InitializeBoard)" << endl;
    }

    for (i=0; i<aBoardSize; i++)                              //for the common part
    {
        for (j=0; j<aBoardSize; j++)
        {
            if(i== (aBoardSize-1)/2 && j==i)
            {
                aBoard[i][j].itsPieceType=KING;              //king and castle in the middle of the array
                aBoard[i][j].itsCellType=CASTLE;
            }

            if((i==0 && j== 0) || (i==(aBoardSize-1) && j== (aBoardSize-1)) || (i==0 && j== (aBoardSize-1)) || (i== (aBoardSize-1) && j==0))    //fortress on the corner
            {
                aBoard[i][j].itsCellType=FORTRESS;
            }

            if((i>=(aBoardSize-1)/3 && i<=(2*(aBoardSize)/3)) && (j==0 || j==(aBoardSize-1)))        //SWORD for j=0 & j=13 between i=4 and i=8
            {
                aBoard[i][j].itsPieceType=SWORD;
            }

            if((j>=(aBoardSize-1)/3 && j<=(2*(aBoardSize)/3)) && (i==0 || i==(aBoardSize-1)))        //SWORD for j=0 & j=13 between i=4 and i=8
            {
                aBoard[i][j].itsPieceType=SWORD;
            }
        }
    }
}

/**
 * @brief Save your party
 * @param aBoard A 2D array representing the game board.
 * @param aBoardSize The size of the game board (either LITTLE or BIG).
 * @param filename, the name than you give to the file to save it
 */
void saveBoard(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize, const string &filename) {

    ofstream file(filename);// written mode

    if (file.is_open())     // check if the file is open
    {
        file << aBoardSize << endl;    // write the position of piece and case in file
        for (int i = 0; i < aBoardSize; ++i)
        {
            for (int j = 0; j < aBoardSize; ++j)
            {
                file << aBoard[i][j].itsPieceType << " " << aBoard[i][j].itsCellType << " ";
            }
            file << endl;
        }
        file.close();       // close the file
        cout << file.is_open();
        cout << "SUCCESS | saved game" << filename << endl;
    }
    else
    {
        cout << "ERROR | open file " << filename << endl;
    }
}

/**
 * @brief Load your party
 * @param aBoard A 2D array representing the game board.
 * @param aBoardSize The size of the game board (either LITTLE or BIG).
 * @param filename, the name than you give to the file to save it
 */
void loadBoard(Cell aBoard[][BOARD_SIZE_MAX], BoardSize& aBoardSize, const string& filename) {
    ifstream file(filename);

    if (file.is_open())
    {
        int tempBoardSize;
        file >> tempBoardSize;

        aBoardSize = static_cast<BoardSize>(tempBoardSize);     //transtypage of tempPieceType in PieceType

        for (int i = 0; i < aBoardSize; ++i)
        {
            for (int j = 0; j < aBoardSize; ++j)
            {
                int tempPieceType, tempCellType;
                file >> tempPieceType >> tempCellType;

                aBoard[i][j].itsPieceType = static_cast<PieceType>(tempPieceType);      //transtypage of tempPieceType in PieceType
                aBoard[i][j].itsCellType = static_cast<CellType>(tempCellType);         //transtypage of tempCellType in CellType
            }
        }
        file.close();

        cout << "Board loaded successfully from " << filename << endl;
    }
    else
    {
        // Afficher un message d'erreur sur la sortie d'erreur standard si le fichier ne peut pas être ouvert
        cout << "Unable to open file: " << filename << endl;
    }
}



/**
 * @brief Display the game board with pieces.
 *
 * This function displays the game board with the positions of pieces such as shields,
 * swords, the king, castle, and exits. It also labels rows with letters and columns
 * with numbers for easier player reference.
 *
 * @param aBoard A 2D array representing the game board.
 * @param aBoardSize The size of the game board (either LITTLE or BIG).
 */
void displayBoard(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize)
{
    int i,j;
    
    cout << "          " ;
    for(i=1; i<=aBoardSize;i++)     //indication for column line
    {
        if(i<10)
        {
            cout << i << ' ' << ' ' << ' ';
        }
        else
        {
            cout << i << ' ' << ' ';
        }
    }
    cout <<endl << endl<< "        " << '+';

    for (i=0; i<aBoardSize; i++)              //first row of the grid
    {
        cout <<"---+";
    }

    cout<<endl;

    char ind='A';
    for(i=0; i<aBoardSize; i++)                                                //display pieces
    {
        cout << "    " << ind++ << "   " << '|' << ' ';                   //indication for row line

        for(j=0; j<aBoardSize; j++)
        {
            if (aBoard[i][j].itsCellType==FORTRESS && aBoard[i][j].itsPieceType != KING)    //if the case is an fortress and KING is not this case, display X
            {
                cout << 'X' << ' ' << '|' << ' ';
            }

            else if (aBoard[i][j].itsCellType==CASTLE && aBoard[i][j].itsPieceType != KING)     //if the case is an castle and KING is not this case, display C
            {
                cout << 'C' << ' ' << '|' << ' ';
            }

            switch(aBoard[i][j].itsPieceType)       //for the board of piece, display good emote to right case
            {
            case SHIELD :cout << "♥" << ' ' << '|' << ' '; break;        //if a case equal SHIELD, display ♥

            case SWORD : cout << "♠" << ' ' << '|' << ' '; break;        //if a case equal SWORD, display ♠

            case KING : cout << "☻" << ' ' << '|' << ' '; break;         //if a case equal KING, display ☻

            case NONE : if(aBoard[i][j].itsCellType != FORTRESS && aBoard[i][j].itsCellType != CASTLE)           //if a case equal 0, display empty
                {
                    cout << ' ' << ' ' << '|' << ' ';
                }break;
            default : cout << "ERROR | initialization of the Board (displayBoard)"; return;        //else return error
            }
        }
        cout << endl << "        " << '+';

        for (int k=0; k<aBoardSize ; k++)         //grid table
        {
            cout<<"---+";
        }

        cout << endl;
    }
    cout << endl << " ☻ = King \n ♥ = Shield \n ♠ = Sword \n X = Fortress \n C = Castle" << endl << endl;  // indication of pieces and cases
}

/**
 * @brief Retrieve a position entered by the user.
 *
 * This function reads user input, validates it as a position in the format of a letter
 * followed by a number (e.g., "A1" or "B2"). If the input is valid, it returns the
 * corresponding Position structure; otherwise, it returns {-1, -1} to indicate an
 * invalid position.
 *
 * This function can save the game, you can only save with attacker, else there is a role probleme
 * when you reload the game.
 *
 * @param aPlayer, the actual role of player
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aBoardSize The size of the game board (either LITTLE or BIG).
 *
 *
 * @return The Position structure representing the user's input position, or {-1, -1} if invalid.
 */
Position getPositionFromInput(const PlayerRole& aPlayer, const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize)
{
    Position cellPosition;
    Position error= {-1, -1};       //error if the position is not good
    Position save = {100,100};
    string tempPos, gamefile;

    cin >> tempPos;

    if (aPlayer == ATTACK)
    {
        if(tempPos == "s" || tempPos == "S")
        {
            cout << "How do you want to call your game ? (ex: file.txt)" << endl;
            cin >> gamefile;
            saveBoard(aBoard, aBoardSize, gamefile);
            clearConsole();
            cout << "Your game is saved !" << endl;
            return save ;
        }
    }



    if(tempPos.length() != 2 && tempPos.length() !=3 )            //if lenght of tempPos is not 2 or 3, return error
    {
        cout << " ERROR | Your pawn don't do 2 or 3 char ! (getPositionFromInput)" << endl;
        return error;
    }
    else
    {
        if(isalpha(tempPos[0]))     //check if the char is in the alphabet
        {
            cellPosition.itsRow = toupper(tempPos[0]) - 'A';  //if char is in lowercase, switch to uppercase | is uppercase, nothing change

            if(tempPos.length() == 2 && isdigit(tempPos[1]))    //if second case of the board is a number
            {
                cellPosition.itsCol = (tempPos[1] - '0') - 1;  // -'0' => string (initialised to 0) | -1, temPos[1] == 2nd case of the board (gap)
            }
            else if (tempPos.length() == 3 && isdigit(tempPos[1]) && isdigit(tempPos[2])) //if there is 2 number in a case, declare a 3rd case for the board
            {
                cellPosition.itsCol = ((tempPos[1] - '0')*10 + (tempPos[2] - '0')) -1; //-'0' => string (initialised to 0) | -1, temPos[1] == 2nd case of the board (gap) + *10 else, the number is not declared
            }
            else
            {
                cout << "ERROR | chose pawn (getPositionFromInput)" << endl;
                return error;
            }
        }
        else
        {
            cout << "ERROR | char is not in the Alphabet (getPositionFromInput)" << endl;
            return error;
        }
    }
    cout << "SUCCESS | choice the pawn (getPositionFromInput)" << endl;
    return cellPosition;
}


/**
 * @brief Check if a position is valid within the given board size.
 *
 * This function verifies whether a provided Position structure is valid within the
 * dimensions of the game board, as specified by the given BoardSize. It returns true
 * if the position is valid, meaning it falls within the board's bounds, and false
 * otherwise.
 *
 * @param aPos The Position structure to check for validity.
 * @param aBoardSize The size of the game board.
 * @return True if the position is valid, false otherwise.
 */
bool isValidPosition(const Position& aPos, const BoardSize& aBoardSize)
{
    if(aPos.itsRow >= 0 && aPos.itsRow < aBoardSize)        //if the row is correct (between A and boardSize)
    {
        if(aPos.itsCol >= 0 && aPos.itsCol < aBoardSize)        //if the column is correct (between 0 and boardSize)
        {
            cout << "SUCCESS | This is a Valid Position (isValidPosition)" << endl;
            return true;
        }

        else
        {
            cout<<"FAIL ! | This is not a valid Column (isValidPosition)" << endl;
            return false;
        }
    }
    else
    {
        cout << "FAIL ! | This is not a valid Row (isValidPosition)" << endl;
        return false;
    }
}


/**
 * @brief Check if a specific cell on the game board is empty.
 *
 * This function determines whether a particular cell on the game board, as specified
 * by the given Position, is empty. A cell is considered empty if it does not contain
 * any game pieces.
 *
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aPos The Position of the cell to check for emptiness.
 * @return True if the cell is empty, false if it contains a game piece.
 */
bool isEmptyCell(const Cell aBoard[][BOARD_SIZE_MAX], const Position& aPos)
{
    if(aBoard[aPos.itsRow][aPos.itsCol].itsPieceType == NONE)       //if there is no pieces on case choosen
    {
        cout << "SUCCESS | empty case (isEmptyCell)" << endl;
        return true;
    }
    else
    {
        cout << "FAIL    | There is something here (isEmptyCell)" << endl;
        return false;
    }
}



/**
 * @brief Check if a selected move is valid for the current player.
 *
 * This function verifies if a selected move, from the starting position to the ending position,
 * is valid for the current player. It checks various conditions such as whether the starting position
 * contains a piece of the active player, if the move is along the same row or column, and if there are any obstacles
 * in the path.
 *
 * @param aPlayer The role of the current player (ATTACK or DEFENSE).
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aStartPos The starting position of the move.
 * @param aEndPos The ending position of the move.
 * @return True if the move is valid, false otherwise.
 */
bool isValidMovement(const PlayerRole& aPlayer, const Cell aBoard[][BOARD_SIZE_MAX],const Position& aStartPos,const Position& aEndPos)
{
    int ind, i;
    if(aPlayer == ATTACK)               //if its ATTACKER turn
    {
        if(aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType == SWORD)        //if chooses pawn is a Sword
        {
            if(aStartPos.itsRow == aEndPos.itsRow)          //if the begin row equal the end row
            {
                ind= aEndPos.itsCol - aStartPos.itsCol;     //calcul the difference between start column and end column

                if(ind > 0)             // if ind is positive
                {
                    for(i=1; i<=ind; i++)        //check each case to endPos with addition (to the right)
                    {
                        if(!(isEmptyCell(aBoard, {aStartPos.itsRow, aStartPos.itsCol+i})) || (aBoard[aStartPos.itsRow][aStartPos.itsCol+i].itsCellType == FORTRESS) || (aBoard[aStartPos.itsRow][aStartPos.itsCol+i].itsCellType == CASTLE) ) // if a case is differente of NONE or if pawn passed on a FORTRESS or the CASTLE
                        {
                            cout << "FAIL     | There is something between the start position and the end position (isValidMovement)" << endl;
                            return false;
                        }
                    }
                cout << "SUCCESS | Movement is valid (isValidMovement)" << endl;
                return true;
                }
                if(ind < 0)            //if ind is negative
                {
                    for (i = -1; i >= ind; i--)   //check each case to endPos with addition (to the left)
                    {
                        if(!(isEmptyCell(aBoard, {aStartPos.itsRow, aStartPos.itsCol+i})) || (aBoard[aStartPos.itsRow][aStartPos.itsCol+i].itsCellType == FORTRESS) || (aBoard[aStartPos.itsRow][aStartPos.itsCol+i].itsCellType == CASTLE) )
                        {
                                cout << "FAIL    | There is something between the start position and the end position (isValidMovement)" << endl;
                                return false;
                        }
                    }
                cout << "SUCCESS | Movement is valid (isValidMovement)" << endl;
                return true;
                }
            }
            else if (aStartPos.itsCol == aEndPos.itsCol)       //checking if the start column equal the end column
            {
                ind= aEndPos.itsRow - aStartPos.itsRow;     //calcul the difference between start row and end row

                if(ind > 0)         // if ind is positiv
                {
                    for(i=1; i <= ind; i++)        //check each case to endPos with addition (to the top)
                    {
                        if(!(isEmptyCell(aBoard, {aStartPos.itsRow+i, aStartPos.itsCol}) ) || (aBoard[aStartPos.itsRow+i][aStartPos.itsCol].itsCellType == FORTRESS) || (aBoard[aStartPos.itsRow+i][aStartPos.itsCol].itsCellType == CASTLE) )
                        {
                            cout << "FAIL    | There is something between the start position and the end position (isValidMovement)" << endl;
                            return false;
                        }
                    }
                    cout << "SUCCESS | Movement is valid (isValidMovement)" << endl;
                    return true;
                }
                else if(ind < 0)//if ind is negative
                {
                    for (i = -1; i >= ind; i--)   //check each case to endPos with addition (to the bottom)
                    {
                        if((!isEmptyCell(aBoard, {aStartPos.itsRow+i, aStartPos.itsCol})) || (aBoard[aStartPos.itsRow+i][aStartPos.itsCol].itsCellType == FORTRESS) || (aBoard[aStartPos.itsRow+i][aStartPos.itsCol].itsCellType == CASTLE) )
                        {
                            cout << "FAIL    | There is something between the start position and the end position (isValidMovement)" << endl;
                            return false;
                        }
                    }
                cout << "SUCCESS | Movement is valid (isValidMovement)" << endl;
                return true;
                }
            }
            else        //if chosen pawn and wanted movment is not on the same lane
            {
                cout << "FAIL ! | You are not in the same lane (isValidMovment)" << endl;
                return false;
            }
        }
        else        //if the chosen pawn is not a sword
        {
            cout << "FAIL   | Your pawn is not a SWORD" << endl;
            return false;
        }
    }
    else if (aPlayer == DEFENSE)//if its DEFENDER turn
    {
        if(aStartPos.itsRow == aEndPos.itsRow)      //checking if the start row equal the end row
        {
            ind= aEndPos.itsCol - aStartPos.itsCol;     //calcul the difference between start column and end column

            if(ind > 0) //if ind is positif
            {
                for(i=1; i <= ind; i++)        //check each case to endPos with addition (to the right)
                {
                    if(aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType == SHIELD)   //Shields can't go on castle or fortress
                    {
                        if((!isEmptyCell(aBoard, {aStartPos.itsRow, aStartPos.itsCol+i})) || (aBoard[aStartPos.itsRow][aStartPos.itsCol+i].itsCellType == FORTRESS) || (aBoard[aStartPos.itsRow][aStartPos.itsCol+i].itsCellType == CASTLE) )
                        {
                            cout << "FAIL    | There is something between the start position and the end position (isValidMovement)" << endl;
                            return false;
                        }
                    }
                    else if(aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType == KING)   //King can go where he want on the board
                    {
                        if(!(isEmptyCell(aBoard, {aStartPos.itsRow, aStartPos.itsCol+i})) || (aBoard[aStartPos.itsRow][aStartPos.itsCol+i].itsPieceType == SWORD)) // check if the place is empty
                        {
                            cout << "FAIL    | There is something between the start position and the end position (isValidMovement)" << endl;
                            return false;
                        }
                    }
                    else
                    {
                        cout << "FAIL    | You don't choose a SHIELD or KING !" << endl;
                        return false;
                    }
                }
            cout << "SUCCESS | Movement is valid (isValidMovement)" << endl;     //if the checking is valide, return true
            return true;
            }
            else if(ind < 0)        //if ind is negative
            {
                for (i = -1; i >= ind; i--)   //check each case to endPos with addition (to the left)
                {
                    if(aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType == SHIELD)   //Shields can't go on castle or fortress
                    {
                        if((!isEmptyCell(aBoard, {aStartPos.itsRow, aStartPos.itsCol+i})) || (aBoard[aStartPos.itsRow][aStartPos.itsCol+i].itsCellType == FORTRESS) || (aBoard[aStartPos.itsRow][aStartPos.itsCol+i].itsCellType == CASTLE) )
                        {
                            cout << "FAIL    | There is something between the start position and the end position (isValidMovement)" << endl;
                            return false;
                        }
                    }
                    else if(aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType == KING)   //King can go where he want on the board
                    {
                        if(!(isEmptyCell(aBoard, {aStartPos.itsRow, aStartPos.itsCol+i})) || (aBoard[aStartPos.itsRow][aStartPos.itsCol+i].itsPieceType == SWORD)) // check if the place is empty
                        {
                            cout << "FAIL    | There is something between the start position and the end position (isValidMovement)" << endl;
                            return false;
                        }
                    }
                    else
                    {
                        cout << "FAIL    | You don't choose a SHIELD or KING !" << endl;
                        return false;
                    }
                }
            cout << "SUCCESS | Movement is valid (isValidMovement)" << endl;
            return true;
            }
        }
        else if(aStartPos.itsCol == aEndPos.itsCol)      //checking if the start column equal the end column
        {
            ind= aEndPos.itsRow - aStartPos.itsRow;     //calcul the difference between start row and end row

            if(ind > 0) //if ind is positiv
            {
                for(i=1; i <= ind; i++)        //check each case to endPos with addition (to the top)
                {
                    if(aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType == SHIELD)   //Shields can't go on castle or fortress
                    {
                       if(!(isEmptyCell(aBoard, {aStartPos.itsRow+i, aStartPos.itsCol})) || (aBoard[aStartPos.itsRow+i][aStartPos.itsCol].itsCellType == FORTRESS) || (aBoard[aStartPos.itsRow+i][aStartPos.itsCol].itsCellType == CASTLE) )
                       {
                        cout << "FAIL    | There is something between the start position and the end position (isValidMovement)" << endl;
                        return false;
                        }
                    }
                    else if(aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType == KING)   //King can go where he want on the board
                    {
                        if(!(isEmptyCell(aBoard, {aStartPos.itsRow+i, aStartPos.itsCol})) || (aBoard[aStartPos.itsRow+i][aStartPos.itsCol].itsPieceType == SWORD)) // check if the place is empty
                        {
                            cout << "FAIL    | There is something between the start position and the end position (isValidMovement)" << endl;
                            return false;
                        }
                    }
                    else    //if chosen pawn is not a shield or king
                    {
                        cout << "FAIL    | You don't choose a SHIELD or KING !" << endl;
                        return false;
                    }
                }
            cout << "SUCCESS | Movement is valid (isValidMovement)" << endl;     //if the checking is valide, return true
            return true;
            }

            if(ind < 0)        //if ind is negative
            {
                for (i = -1; i >= ind; i--)   //check each case to endPos with addition (to the bottom)
                {
                    if(aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType == SHIELD)   //Shields can't go on castle or fortress
                    {
                        if(!(isEmptyCell(aBoard, {aStartPos.itsRow+i, aStartPos.itsCol})) || (aBoard[aStartPos.itsRow+i][aStartPos.itsCol].itsCellType == FORTRESS) || (aBoard[aStartPos.itsRow+i][aStartPos.itsCol].itsCellType == CASTLE) )
                        {
                            cout << "FAIL    | There is something between the start position and the end position (isValidMovement)" << endl;
                            return false;
                        }
                    }
                    else if(aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType == KING)
                    {
                        if(!(isEmptyCell(aBoard, {aStartPos.itsRow+i, aStartPos.itsCol})) || (aBoard[aStartPos.itsRow+i][aStartPos.itsCol].itsPieceType == SWORD))
                        {
                            cout << "FAIL    | There is something between the start position and the end position (isValidMovement)" << endl;
                            return false;
                        }
                    }
                    else
                    {
                        cout << "FAIL    | You don't choose a SHIELD or KING !" << endl;
                        return false;
                    }
                }
                cout << "SUCCESS | Movement is valid (isValidMovement)" << endl;
                return true;
            }
        }
        else
        {
            cout << "FAIL ! | You are not in the same lane (isValidMovment)" << endl;
            return false;
        }
    }
    return false;
}



/**
 * @brief Move a game piece on the game board.
 *
 * This function moves a game piece from the starting position to the ending position
 * on the game board. It updates the ending position to contain the piece and clears
 * the starting position.
 *
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aStartPos The starting position of the move.
 * @param aEndPos The ending position of the move.
 */
void movePiece(Cell aBoard[][BOARD_SIZE_MAX], const Position& aStartPos, const Position& aEndPos)
{
    aBoard[aEndPos.itsRow][aEndPos.itsCol].itsPieceType = aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType;      //case wanted become started pawn
    aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType = NONE;   //started case become null
    cout << "SUCCESS | Piece placement changed (movePiece)" << endl;
}



/**
 * @brief Remove captured pieces from the game board.
 *
 * This function checks for captured pieces in the four adjacent directions
 * to the ending position and removes them based on the game rules.
 *
 * @param aPlayer The current player's role (ATTACK or DEFENSE).
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aBoardSize The size of the game board.
 * @param aEndPos The ending position of the move.
 */
void capturePieces(const PlayerRole& aPlayer, Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize, const Position& aEndPos)
{
    if (aPlayer == ATTACK)  //if its ATTACKER turn
    {
        if(aBoard[aEndPos.itsRow][aEndPos.itsCol].itsPieceType == SWORD)      //if player pawn is SWORD
        {
            if(aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType == SHIELD)     //if the pawn to the left is SHIELD
            {
                if(aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == SWORD)  //if the pawn to the left of the SHIELD is a SWORD
                {
                    cout << "Un SHIELD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType = NONE;   //the SHIELD pawn become empty
                }
                else if(aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == CASTLE))   //if the case to the left of the SWORD is a FORTRESS or CASTLE
                {
                    cout << "Un SHIELD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType = NONE;   //the SHIELD pawn become empty
                }
            }

            if(aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType == SHIELD)     //if the pawn to the right is SHIELD
            {
                if(aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == SWORD)  //if the pawn to the right of the SHIELD is a SWORD
                {
                    cout << "Un SHIELD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType = NONE;
                }
                else if (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == FORTRESS || aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == CASTLE)    //if the case to the right of the SWORD is a FORTRESS or CASTLE
                {
                    cout << "Un SHIELD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType = NONE;
                }
            }

            if(aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType == SHIELD) //if the pawn to the top is SHIELD
            {
                if(aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == SWORD)  //if the pawn to the top of the SHIELD is a SWORD
                {
                    cout << "Un SHIELD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType = NONE;
                }
                else if (aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsCellType == FORTRESS || aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsCellType == CASTLE)    //if the case to the top of the SWORD is a FORTRESS or CASTLE
                {
                    cout << "Un SHIELD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType = NONE;
                }
            }

            if(aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType == SHIELD) //if the pawn to the bottom is SHIELD
            {
                if(aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == SWORD)  //if the pawn to the bottom of the SHIELD is a SWORD
                {
                    cout << "Un SHIELD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType = NONE;
                }
                else if (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == FORTRESS || aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == CASTLE)    //if the case to the bottom of the SHIELD is a FORTRESS or CASTLE
                {
                    cout << "Un SHIELD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType = NONE;
                }
            }
        }
    }
    else if (aPlayer == DEFENSE)    //if its DEFENDER turn
    {
        if(aBoard[aEndPos.itsRow][aEndPos.itsCol].itsPieceType == SHIELD)   //if player pawn is SHIELD
        {
            if(aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType == SWORD)  //if the pawn to the left is SWORD
            {
                if(aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == SHIELD || aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == KING)    //if the pawn to the left of the SWORD is a SHIELD or KING
                {
                    cout << "Un SWORD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType = NONE;   //the SWORD pawn become empty
                }
                else if (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == FORTRESS ||aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == CASTLE)     //if the case to the left of the SWORD is a FORTRESS or CASTLE
                {
                    cout << "Un SWORD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType = NONE;
                }
            }

            if(aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType == SWORD)  //if the pawn to the right is SWORD
            {
                if(aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == SHIELD || aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == KING)    //if the pawn to the right of the SWORD is a SHIELD or KING
                {
                    cout << "Un SWORD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType = NONE;
                }
                else if (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == FORTRESS || aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == CASTLE)    //if the case to the right of the SWORD is a FORTRESS or CASTLE
                {
                    cout << "Un SWORD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType = NONE;
                }
            }

            if(aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType == SWORD)     //if the pawn to the top is SWORD
            {
                if(aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == SHIELD || aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == KING)    //if the pawn to the top of the SWORD is a SHIELD or KING
                {
                    cout << "Un SWORD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType = NONE;
                }
                else if (aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsCellType == FORTRESS || aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsCellType == CASTLE)    //if the case to the top of the SWORD is a FORTRESS or CASTLE
                {
                    cout << "Un SWORD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType = NONE;
                }
            }

            if(aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType == SWORD)      //if the pawn to the bottom is SWORD
            {
                if(aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == SHIELD || aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == KING)    //if the pawn to the bottom of the SWORD is a SHIELD or KING
                {
                    cout << "Un SWORD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType = NONE;
                }
                else if (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == FORTRESS || aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == CASTLE)    //if the case to the bottom of the SWORD is a FORTRESS or CASTLE
                {
                    cout << "Un SWORD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType = NONE;
                }
            }
        }
        else if (aBoard[aEndPos.itsRow][aEndPos.itsCol].itsPieceType == KING)     //if player pawn is KING
        {
            if(aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType == SWORD)  //if the pawn to the left is SWORD
            {
                if(aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == SHIELD) //if the pawn to the left of the SWORD is a SHIELD
                {
                    cout << "Un SWORD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType = NONE;
                }
                else if (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == FORTRESS ||aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == CASTLE) //if the case to the left of the SWORD is a FORTRESS or CASTLE
                {
                    cout << "Un SWORD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType = NONE;
                    }
                }

            if(aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType == SWORD)      //if the pawn to the right is SWORD
            {
                if(aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == SHIELD) //if the pawn to the right of the SWORD is a SHIELD
                {
                    cout << "Un SWORD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType = NONE;
                }
                else if (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == FORTRESS || aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == CASTLE)    //if the case to the right of the SWORD is a FORTRESS or CASTLE
                {
                    cout << "Un SWORD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType = NONE;
                }
            }

            if(aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType == SWORD)      //if the pawn to the top is SWORD
            {
                if(aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == SHIELD) //if the pawn to the top of the SWORD is a SHIELD
                {
                    cout << "Un SWORD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType = NONE;
                }
                else if (aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsCellType == FORTRESS || aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsCellType == CASTLE)    //if the case to the top of the SWORD is a FORTRESS or CASTLE
                {
                    cout << "Un SWORD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType = NONE;
                }
            }

            if(aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType == SWORD)      //if the pawn to the bottom is SWORD
            {
                if(aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == SHIELD) //if the pawn to the bottom of the SWORD is a SHIELD
                {
                    cout << "Un SWORD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType = NONE;
                }
                else if (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == FORTRESS || aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == CASTLE)    //if the case to the bottom of the SWORD is a FORTRESS or CASTLE
                {
                    cout << "Un SWORD a été capturé !" << endl;
                    aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType = NONE;
                }
            }
        }
    }
}






/**
 * @brief Check if there are any attackers (swords) left on the game board.
 *
 * This function iterates through the game board to determine if there are any
 * attacker (sword) pieces remaining.
 *
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aBoardSize The size of the game board.
 * @return True if there are attackers left, false otherwise.
 */
bool isSwordLeft(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize)
{
    int i,j;

    for (i=0; i<aBoardSize; i++)
    {
        for(j=0; j< aBoardSize; j++)
        {
            if(aBoard[i][j].itsPieceType == SWORD)  //if there is one SWORD or more, return true
            {
                return true;
            }
        }
    }
    return false;
}






/**
 * @brief Get the position of the king on the game board.
 *
 * This function iterates through the game board to find and return the position
 * of the king piece. If the king is not found, it returns the default position {-1, -1}.
 *
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aBoardSize The size of the game board.
 * @return The position of the king or {-1, -1} if the king is not found.
 */
Position getKingPosition(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize)
{
    int i,j;

    Position NoKing = {-1 , -1};

    for (i=0; i<aBoardSize; i++)
    {
        for(j=0; j< aBoardSize; j++)
        {
            if(aBoard[i][j].itsPieceType == KING)   //if there is a KING, return king position
            {
                return {i,j};
            }
        }
    }
    return NoKing;
}




/**
 * @brief Check if the king has escaped to a fortress.
 *
 * This function first obtains the position of the king using the getKingPosition function.
 * It then checks if the cell at the king's position is of type FORTRESS, indicating that
 * the king has successfully escaped to a fortress.
 *
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aBoardSize The size of the game board.
 * @return True if the king has escaped to a fortress, false otherwise.
 */
bool isKingEscaped(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize)
{
    if(aBoard[0][0].itsPieceType == KING || aBoard[0][aBoardSize - 1].itsPieceType == KING || aBoard[aBoardSize - 1][0].itsPieceType == KING || aBoard[aBoardSize - 1][aBoardSize - 1].itsPieceType == KING ) //if KING is in a corner
    {
        return true;
    }
    else
    {
        return false;
    }
}






/**
 * @brief Check if the king is captured by 4 elements (attackers, border, or fortress).
 *
 * This function first obtains the position of the king using the getKingPosition function.
 * It then checks the four neighboring positions around the king to determine if any of them
 * contain enemy pieces (attackers), border cells, fortress cells, or castle cells. If all
 * four neighboring positions meet one of these conditions, the king is considered captured.
 *
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aBoardSize The size of the game board.
 * @return True if the king is captured by 4 elements, false otherwise.
 */
bool isKingCaptured(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize)
{
    Position error {-1, -1};
    Position KingPos = getKingPosition(aBoard, aBoardSize);

    if(KingPos.itsRow == error.itsRow && KingPos.itsCol == error.itsCol)    //if there is no king in the Board
    {
        return true;
    }
    else
    {
        if(((aBoard[KingPos.itsRow-1][KingPos.itsCol].itsPieceType != SWORD) && (aBoard[KingPos.itsRow-1][KingPos.itsCol].itsCellType == NORMAL)) || ((aBoard[KingPos.itsRow+1][KingPos.itsCol].itsPieceType != SWORD) && (aBoard[KingPos.itsRow+1][KingPos.itsCol].itsCellType == NORMAL)))   //if there is another pawn than SWORD on the same row of the KING
        {
            return false;
        }

        if(((aBoard[KingPos.itsRow][KingPos.itsCol-1].itsPieceType != SWORD) && (aBoard[KingPos.itsRow][KingPos.itsCol-1].itsCellType == NORMAL)) || ((aBoard[KingPos.itsRow][KingPos.itsCol+1].itsPieceType != SWORD) && (aBoard[KingPos.itsRow][KingPos.itsCol+1].itsCellType == NORMAL)))    //if there is another pawn than SWORD on the same column of the KING
        {
            return false;
        }
        return true;
    }
}








/**
 * @brief Recursively check if the king is blocked.
 *
 * This function recursively checks if the king is blocked from all sides. It starts
 * with the actual king's position and explores neighboring cells in all directions.
 * If the king can move to any neighboring cell, it's not considered blocked.
 *
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aBoardSize The size of the game board.
 * @param aKingPos The position of the king (defaults to {-1, -1} to use the actual king's position).
 * @return True if the king is blocked from all sides, false if it can move to at least one neighboring cell.
 */
bool isKingCapturedV2(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize, Position aKingPos = {-1, -1});








#endif // FUNCTIONS_H
