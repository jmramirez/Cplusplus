// Console UI Core Classes
// cbutton.h
//
// Jose Ramirez
// Nov 22 2013
// Version 1.0

#pragma once
#ifndef _JM_CButton_H_
#define _JM_CButton_H_
#include "cfield.h"

namespace cio{
  class  CButton: public CField{
  public:
    CButton(const char *Str, int Row, int Col, 
             bool Bordered = true,
             const char* Border=C_BORDER_CHARS);
    virtual ~CButton();
    void draw(int fn=C_FULL_FRAME);
    int edit();
    bool editable()const;
    void set(const void* str);
  };
}

#endif