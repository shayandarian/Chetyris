#ifndef WELL_INCLUDED
#define WELL_INCLUDED

class Screen;

class Well
{
  public:
    Well(int rows, int cols);
    void display(Screen& screen, int x, int y);
private:
    int m_width;
    int m_height;
};

#endif // WELL_INCLUDED
