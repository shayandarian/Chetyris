#include "Well.h"
#include "UserInterface.h"

Well::Well(int rows, int cols)
{
    m_width = cols + 2;
    m_height = rows + 1;
}

void Well::display(Screen& screen, int xOffset, int yOffset)
{
    for(int y = 0; y < m_height; y++)
    {
        screen.gotoXY(0+xOffset, y+yOffset);
        screen.printChar('@');
        screen.gotoXY(m_width-1+xOffset, y+yOffset);
        screen.printChar('@');
    }
    for(int x = 0; x < m_width; x++)
    {
        screen.gotoXY(x+xOffset, m_height-1+yOffset);
        screen.printChar('@');
    }
}
