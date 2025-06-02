#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"
#include <string>

const int WIDTH = 10;
const int HEIGHT = 18;

class Game
{
  public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
    void displayGrid();
    void displayPiece(Piece piece, int x, int y);
    bool checkCollision(Piece piece, int pieceX, int pieceY);
    void removeRow(int row);
    int removeFullRows();
    void clearBoard();
    void solidifyPiece(Piece piece, int x, int y);
    Piece* getNewPiece();
  private:
    Well    m_well;
    Screen  m_screen;
    int     m_level;
    int     m_rowsCleared;
    int     m_score;
    int     m_interval;
    char m_grid[WIDTH][HEIGHT];
};

#endif // GAME_INCLUDED
