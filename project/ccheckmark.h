// Console UI Core Classes
// ccheckmark.h
//
// Jose Ramirez
// Nov 22 2013
// Version 1.0

#pragma once
#ifndef _JM_CCHECKMARK_H_
#define _JM_CCHECKMARK_H_
#include "cfield.h"
#include "clabel.h"
namespace cio{
  class CCheckMark : public CField{
    bool _flag;
    bool _radio;
    char _format[4];
    CLabel _Label;
  public:
    CCheckMark(bool Checked,const char* Format, const char* Text,
               int Row, int Col, int Width, bool IsRadio = false);
    CCheckMark(const CCheckMark& C);
    void draw(int fn = C_NO_FRAME) ;
    int edit();
    bool editable()const;
    void set(const void* flag);
    bool checked()const;
    void checked(bool val);
    bool radio(); 
    void radio(bool isRadio);
    operator bool(); 
    operator char*();  
    bool operator=(bool flag);
  };
}
#endif