// Console UI Core Classes
// clineedit.h
//
// Jose Ramirez
// Nov 22 2013
// Version 1.1
#pragma once
#ifndef _JM_CLINEEDIT_H
#define _JM_CLINEEDIT_H
#include "cfield.h"
#include "console.h"
using namespace cio;
namespace cio{
  class CLineEdit:public CField{
    bool _dyn;
    int _maxdatalen;
    bool* _insertmode;
    int _curpos;
    int _offset;
  public:
    CLineEdit(char* Str, int Row, int Col, int Width,
      int Maxdatalen, bool* Insertmode, 
      bool Bordered = false,
            const char* Border=C_BORDER_CHARS);
    CLineEdit(int Row, int Col, int Width,
      int Maxdatalen, bool* Insertmode, 
      bool Bordered = false,
            const char* Border=C_BORDER_CHARS);
    ~CLineEdit();
    void draw(int Refresh = C_FULL_FRAME);
 
    int edit();
    bool editable()const;
 
    void  set(const void* Str);
  };
}
#endif