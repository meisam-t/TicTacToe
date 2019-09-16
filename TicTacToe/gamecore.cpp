#include <iostream>
#include "gamecore.h"

void GameCore::DrawGrid(Grid grid) {
    // the grid has three states. 0 = empty | 1 = player 1 | 2 = player 2
    int colums { 0 };

    std::cout << '\n';

    for (int y = 0; y < static_cast<int>(sizeof (grid.size) / sizeof (*grid.size)); y++) {
        std::cout << " | ";

        if (grid.size[y] == 0) {
            std::cout << y + 1;
        }
        else if (grid.size[y] == 1) {
            std::cout << 'X';
        }
        else if (grid.size[y] == 2) {
            std::cout << 'O';
        }

        if (colums < 2) {
            colums++;
        }
        else {
            std::cout << " |\n";
            colums = 0;
        }
    }
}

bool GameCore::CheckWin(Grid grid, int currentPlayer) {
    bool checkIfWin { false };

    // check if the current player has won verticallly
    for (int i = 0; i < 3; i++) {
        // this 'helperValue' exist just to reduce the i * 3 calculations
        int _helperValue = i * 3;

        if (grid.size[_helperValue] == currentPlayer &&
                grid.size[_helperValue + 1] == currentPlayer &&
                grid.size[_helperValue + 2] == currentPlayer) {
            checkIfWin = true;
        }
    }

    // check if the current player has won horizontally
    for (int i = 0; i < 3; i++) {
        if (grid.size[i] == currentPlayer && grid.size[i + 3] == currentPlayer && grid.size[i + 6] == currentPlayer) {
            checkIfWin = true;
        }
    }

    // check if the current player has won diagonally
    if (grid.size[0] == currentPlayer && grid.size[4] == currentPlayer && grid.size[8] == currentPlayer) {
        checkIfWin = true;
    }
    else if (grid.size[2] == currentPlayer && grid.size[4] == currentPlayer && grid.size[6] == currentPlayer) {
        checkIfWin = true;
    }

    return checkIfWin;
}

bool GameCore::CheckTie(Grid grid) {
    bool retVal { false };

    for (int i = 0; i < static_cast<int>(sizeof (grid.size) / sizeof (*grid.size)); i++) {
        if (grid.size[i] == 0) {
            retVal = false;
            break;
        }

        retVal = true;
    }

    return retVal;
}

void GameCore::RunGame() {
    Grid grid;
    bool playerWins { false }, gameTie { false };
    int inPlace, currentPlayer { 1 };
    char replayReply { 'y' };

    std::cout << "*****Welcome to Tic Tac Toe!*****\n\n";

    grid.Reset();

    // start the game loop
    while (true) {
        DrawGrid(grid);

        std::cout << "\nPlayer " << currentPlayer << " (1 - 9): ";
        std::cin >> inPlace;

        if (inPlace > 0 && inPlace <= 9) {
            if (grid.size[inPlace - 1] == 0) {
                grid.size[inPlace - 1] = currentPlayer;

                // check if the game is tied
                gameTie = CheckTie(grid);
                // check if any player
                playerWins = CheckWin(grid, currentPlayer);

                if (playerWins || gameTie) {
                    DrawGrid(grid);

                    if (playerWins) {
                        std::cout << "\nCongratulations Player " << currentPlayer << "\nDo you want to replay? (y / n) ";
                    }
                    else if (gameTie) {
                        std::cout << "\nThe game was tied...\nDo you want to replay? (y / n) ";
                    }

                    std::cin >> replayReply;

                    if (replayReply == 'y' || replayReply == 'Y') {
                        // start the game over again
                        std::cout << "\n*****Welcome to Tic Tac Toe!*****\n\n";

                        // reset values to prepare the game
                        playerWins = false;
                        gameTie = false;
                        grid.Reset();

                        continue;
                    }
                    else if (replayReply == 'n' || replayReply == 'N') {
                        // quit the game
                        break;
                    }
                    else {
                        std::cout << "The character " << replayReply << " is not valid!\n";
                    }
                }

                // switch the players' turn
                currentPlayer = currentPlayer == 1 ? 2 : 1;

                continue;
            }
            else {
                std::cout << "You cannot place a pin in an already occupied section.\n\n";
                continue;
            }
        }

        std::cout << "The input " << inPlace << " was not accepted...\n";
    }
}
