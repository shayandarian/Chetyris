#include "Piece.h"
#include <iostream>


Piece::Piece()
{
}

void Piece::rotateClockwise()
{
    for(int i = 0; i < 4; i++)
    {
        // -90 degree rotation around (0,0)
        // see rotation matrix wikipedia for derivation
        int oldX = xcoords[i];
        int oldY = ycoords[i];
        int newX = (0 * oldX) + (-1 * oldY);
        int newY = (1 * oldX) + (0 * oldY);
        xcoords[i] = newX + CWRotationShiftsX[currentOrientation];
        ycoords[i] = newY + CWRotationShiftsY[currentOrientation];
    }
    currentOrientation++;
    currentOrientation %= 4;
}

void Piece::rotateCounterClockwise()
{
    // basically do everything in rotateClockwise() but in reverse
    currentOrientation--;
    currentOrientation = (currentOrientation+4) % 4;
    
    for(int i = 0; i < 4; i++)
    {
        int oldX = xcoords[i] - CWRotationShiftsX[currentOrientation];
        int oldY = ycoords[i] - CWRotationShiftsY[currentOrientation];
        int newX = (0 * oldX) + (1 * oldY);
        int newY = (-1 * oldX) + (0 * oldY);
        xcoords[i] = newX;
        ycoords[i] = newY;
    }
}

IPiece::IPiece()
{
    xcoords = new int[4]{0, 1, 2, 3};
    ycoords = new int[4]{1, 1, 1, 1};
    CWRotationShiftsX = new int[4]{2, 3, 2, 3};
    CWRotationShiftsY = new int[4]{0, 0, 0, 0};
}

LPiece::LPiece()
{
    xcoords = new int[4]{0, 0, 1, 2};
    ycoords = new int[4]{1, 2, 1, 1};
    CWRotationShiftsX = new int[4]{3, 2, 3, 3};
    CWRotationShiftsY = new int[4]{0, 0, 1, 0};
}

JPiece::JPiece()
{
    xcoords = new int[4]{1, 2, 3, 3};
    ycoords = new int[4]{1, 1, 1, 2};
    CWRotationShiftsX = new int[4]{3, 4, 3, 3};
    CWRotationShiftsY = new int[4]{0, 0, -1, 0};
}

TPiece::TPiece()
{
    xcoords = new int[4]{0, 1, 1, 2};
    ycoords = new int[4]{1, 0, 1, 1};
    CWRotationShiftsX = new int[4]{2, 2, 2, 2};
    CWRotationShiftsY = new int[4]{0, 0, 0, 0};
}

OPiece::OPiece()
{
    xcoords = new int[4]{0, 1, 0, 1};
    ycoords = new int[4]{0, 0, 1, 1};
    CWRotationShiftsX = new int[4]{1, 1, 1, 1};
    CWRotationShiftsY = new int[4]{0, 0, 0, 0};
}

SPiece::SPiece()
{
    xcoords = new int[4]{0, 1, 1, 2};
    ycoords = new int[4]{2, 1, 2, 1};
    CWRotationShiftsX = new int[4]{3, 2, 3, 2};
    CWRotationShiftsY = new int[4]{0, 0, 0, 0};
}

ZPiece::ZPiece()
{
    xcoords = new int[4]{0, 1, 1, 2};
    ycoords = new int[4]{1, 1, 2, 2};
    CWRotationShiftsX = new int[4]{3, 2, 3, 2};
    CWRotationShiftsY = new int[4]{0, 0, 0, 0};
}

VaporBomb::VaporBomb()
{
    xcoords = new int[4]{1, 1, 2, 2};
    ycoords = new int[4]{0, 0, 0, 0};
    CWRotationShiftsX = new int[4]{1, 1, 2, 2};
    CWRotationShiftsY = new int[4]{0, 0, 0, 0};
}

void VaporBomb::rotateClockwise()
{}

void VaporBomb::rotateCounterClockwise()
{}

FoamBomb::FoamBomb()
{
    xcoords = new int[4]{1, 1, 1, 1};
    ycoords = new int[4]{1, 1, 1, 1};
    CWRotationShiftsX = new int[4]{2, 2, 2, 2};
    CWRotationShiftsY = new int[4]{0, 0, 0, 0};
}

CrazyShape::CrazyShape()
{
    xcoords = new int[4]{0, 1, 2, 3};
    ycoords = new int[4]{0, 1, 1, 0};
    CWRotationShiftsX = new int[4]{3, 3, 3, 3};
    CWRotationShiftsY = new int[4]{0, 0, 0, 0};
}
