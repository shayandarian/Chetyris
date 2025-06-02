#include "Game.h"
#include "Well.h"
#include "Piece.h"
#include "UserInterface.h"
#include <string>
#include <iostream>

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int GRID_X = WELL_X+1;
const int GRID_Y = WELL_Y;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

Game::Game(int width, int height)
 : m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_well(HEIGHT, WIDTH), m_score(0), m_interval(2000)
{
    for (int x = 0; x < WIDTH; x++)
    {
        for( int y = 0; y < HEIGHT; y++)
        {
            m_grid[x][y] = ' '; // initiallize grid to spaces
        }
    }
}

void Game::play()
{
    m_well.display(m_screen, WELL_X, WELL_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]

    for(;;)
    {
        m_interval = std::max(1000-(100*(m_level-1)), 100);
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_level++;
        m_rowsCleared = 0;
        displayStatus();
        m_screen.refresh();
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus()
{
    m_screen.gotoXY(SCORE_X, SCORE_Y);
    m_screen.printString("Score: " + std::to_string(m_score));
    m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
    m_screen.printString("Rows left: " + std::to_string(m_level*5 - m_rowsCleared));
    m_screen.gotoXY(LEVEL_X, LEVEL_Y);
    m_screen.printString("Level: " + std::to_string(m_level));
}

void Game::displayGrid()
{
    for(int i = 0; i < WIDTH; i++)
    {
        for(int j = 0; j < HEIGHT; j++)
        {
            m_screen.gotoXY(i+GRID_X, j+GRID_Y);
            m_screen.printChar(m_grid[i][j]);
        }
    }
}

void Game::removeRow(int row)
{
    for (int r = row; r >= 0; r--)
    {
        for (int c = 0; c < WIDTH; c++)
        {
            m_grid[c][r] = (r == 0) ? ' ' : m_grid[c][r-1];
        }
    }
}

void Game::displayPiece(Piece piece, int pieceX, int pieceY)
{
    for(int i = 0; i < 4; i++)
    {
        int x = piece.xcoords[i];
        int y = piece.ycoords[i];
        m_screen.gotoXY(x+pieceX+GRID_X, y+pieceY+GRID_Y);
        m_screen.printChar('#');
    }
}

void Game::solidifyPiece(Piece piece, int posX, int posY)
{
    for(int i = 0; i < 4; i++)
    {
        int x = piece.xcoords[i];
        int y = piece.ycoords[i];
        m_grid[x+posX][y+posY] = '$';
    }
}

bool Game::checkCollision(Piece piece, int pieceX, int pieceY)
{
    
    for(int i = 0; i < 4; i++)
    {
        int gridX = piece.xcoords[i] + pieceX;
        int gridY = piece.ycoords[i] + pieceY;
        if(gridX < 0 || gridX > 9 || gridY < 0 || gridY > 17 || m_grid[gridX][gridY] == '$')
        {
            return true;
        }
    }
    return false;
}

Piece* Game::getNewPiece()
{
    switch(chooseRandomPieceType())
    {
        case PIECE_I:
            return(new IPiece);
        case PIECE_L:
            return(new LPiece);
        case PIECE_J:
            return(new JPiece);
        case PIECE_T:
            return(new TPiece);
        case PIECE_O:
            return(new OPiece);
        case PIECE_S:
            return(new SPiece);
        case PIECE_Z:
            return(new ZPiece);
        case PIECE_VAPOR:
            return(new VaporBomb);
        case PIECE_FOAM:
            return(new FoamBomb);
        case PIECE_CRAZY:
            return(new CrazyShape);
    }
    return(new IPiece);
}

// returns the number of rows cleared
int Game::removeFullRows() {
    int rowsCleared = 0;
    for(int row = 0; row < HEIGHT; row++)
    {
        bool full = true;
        for (int col = 0; col < WIDTH; col++)
        {
            if (m_grid[col][row] != '$') full = false;
        }
        if(full)
        {
            removeRow(row);
            rowsCleared++;
        }
    }
    return rowsCleared;
}

void Game::clearBoard()
{
    for(int x = 0; x < WIDTH; x++)
    {
        for(int y = 0; y < HEIGHT; y++)
        {
            m_grid[x][y] = ' ';
        }
    }
}

bool Game::playOneLevel()
{
    clearBoard();
    m_rowsCleared = 0;
    for (int pieces = 0; pieces < 10000; pieces++)
    {
        Piece* piece = getNewPiece();
        int pieceX = 3;
        int pieceY = 0;
        if (checkCollision(*piece, pieceX, pieceY))
        {
            // immediate collision, game over
            return(false);
        }
        bool spacePressed = false;
        
        for(int index = 0; index < 10000; index++)
        {
            displayGrid();
            displayPiece(*piece, pieceX, pieceY);
            m_screen.refresh();
            
            // Start a timer
            Timer timer;
            
            // Repeat as long as 2000 milliseconds have not yet elapsed
            while (timer.elapsed() < m_interval && !spacePressed)
            {
                char ch;
                bool downKeyPressed = false;
                if (getCharIfAny(ch))
                {
                    // There was a character typed; it's now in ch
                    switch (ch)
                    {
                        case ' ':
                            spacePressed = true;
                            break;
                        case ARROW_LEFT:
                            if(!checkCollision(*piece, pieceX-1, pieceY))
                            {
                                pieceX--;
                            }
                            break;
                        case ARROW_RIGHT:
                            if(!checkCollision(*piece, pieceX+1, pieceY))
                            {
                                pieceX++;
                            }
                            break;
                        case ARROW_UP:
                            piece->rotateClockwise();
                            if (checkCollision(*piece, pieceX, pieceY))
                            {
                                piece->rotateCounterClockwise();
                            }
                            break;
                        case ARROW_DOWN:
                            downKeyPressed = true;
                            break;
                    }
                    displayGrid();
                    displayPiece(*piece, pieceX, pieceY);
                    m_screen.refresh();
                }
                if (downKeyPressed)
                {
                    break;
                }
            }
            // 2 seconds have elapsed
            if (!checkCollision(*piece, pieceX, pieceY+1))
            {
                pieceY++;
            }
            else
            {
                solidifyPiece(*piece, pieceX, pieceY);
                int simultaneousClears = removeFullRows();
                switch (simultaneousClears)
                {
                    case 1: m_score += 100;
                        break;
                    case 2: m_score += 200;
                        break;
                    case 3: m_score += 400;
                        break;
                    case 4: m_score += 800;
                        break;
                    case 5: m_score += 1600;
                        break;
                }
                m_rowsCleared += simultaneousClears;
                displayStatus();
                m_screen.refresh();
                break;
            }
        }
        displayGrid();
        m_screen.refresh();
        
        if (m_rowsCleared >= m_level*5)
        {
            m_rowsCleared = 0;
            displayStatus();
            return(true);
        }
        delete piece;
    }
    return(false);
}

