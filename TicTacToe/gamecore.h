#pragma once

class GameCore {
public:
    struct Grid {
        int size[9];

        void Reset() {
            for (int i = 0; i < static_cast<int>(sizeof (size) / sizeof (*size)); i++) {
                size[i] = 0;
            }
        }
    };

    static void DrawGrid(Grid grid);
    static bool CheckWin(Grid grid, int currentPlayer);
    static bool CheckTie(Grid grid);
    static void RestartGame();
    static void RunGame();
};
