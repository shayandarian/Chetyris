#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};

PieceType chooseRandomPieceType();

const int PIECE_WIDTH = 4;
const int PIECE_HEIGHT = 4;

class Piece
{
public:
    Piece();
    virtual void rotateClockwise();
    virtual void rotateCounterClockwise();
    int* xcoords;
    int* ycoords;
protected:
    int currentOrientation = 0; // determines what rotation offset to use
    int* CWRotationShiftsX;
    int* CWRotationShiftsY;
};

class IPiece : public Piece
{
public:
    IPiece();
};

class LPiece : public Piece
{
public:
    LPiece();
};

class JPiece : public Piece
{
public:
    JPiece();
};

class TPiece : public Piece
{
public:
    TPiece();
};

class OPiece : public Piece
{
public:
    OPiece();
};

class SPiece : public Piece
{
public:
    SPiece();
};

class ZPiece : public Piece
{
public:
    ZPiece();
};

class VaporBomb : public Piece
{
public:
    VaporBomb();
    virtual void rotateClockwise();
    virtual void rotateCounterClockwise();
};

class FoamBomb : public Piece
{
public:
    FoamBomb();
};

class CrazyShape : public Piece
{
public:
    CrazyShape();
};

#endif // PIECE_INCLUDED
