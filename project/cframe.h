// Console UI Core Classes
// cframe.h
//
// Fardad Soleimanloo, Chris Szalwinski
// Oct 04 2013
// Version 1.1

/* 
Add your names under fardad's name:
Reviewed by: (Team member names and date of review)
Full Name, Github id,  date
Fardad Soleimanloo, fardad, Oct 03 2013 - 22:34
Jose Ramirez, jmramirez, Oct 20 2013 -20:48
Yuri Valverde, Yurv25, Oct 20 2013 -21:47
Bernard Casenas, bpcasenas, Oct 20 2013 - 23:02
Victor Obregon, Man31, Oct 20 2013 -23:12
*/

#ifndef __CIO_CFRAME_H__
#define __CIO_CFRAME_H__
#include "ciogh.h"
#include "console.h"
namespace cio{
  class CFrame{
    int _row;
    int _col;
    int _height;
    int _width;
    char _border[9];
    bool _visible;
    CFrame* _frame;
    char* _covered;
    void setLine(char* line, char left, char fill, char right)const;
    void capture();
    void free();
  protected:
    int absRow()const;
    int absCol()const;
  public:
    CFrame(int Row=-1, int Col=-1, int Width=-1,int Height=-1,
      bool Visible = false,
      const char* Border=C_BORDER_CHARS,
      CFrame* Frame = (CFrame*)0);
  
    virtual void draw(int fn=C_FULL_FRAME);
    virtual void move(CDirection dir);
    virtual void move();
    virtual void hide();

    virtual ~CFrame();
  
    /* setters and getters: */

    bool fullscreen()const;

    void visible(bool val);
    bool visible()const;

    void frame(CFrame* theContainer);
    CFrame* frame();
  
    void row(int val);
    int row()const;

    void col(int val);
    int col()const;

    void height(int val);
    int height()const;

    void width(int val);
    int width()const;

    void refresh();
  };

}

#endif
