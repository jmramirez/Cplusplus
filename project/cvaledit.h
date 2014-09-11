// Console UI Core Classes
// cvaledit.h
//
// Jose Ramirez
// Nov 22 2013
// Version 1.0

#pragma once
#ifndef _JM_CVALEDIT_H_
#define _JM_CVALEDIT_H_
#include "clineedit.h"

namespace cio{
	class CLineEdit;
  class CValEdit :public CLineEdit{
	void (*_help)(MessageStatus, CDialog&);
    bool (*_validate)(const char*, CDialog&);
  public:
    CValEdit(char* Str, int Row, int Col, int Width,
          int Maxdatalen, bool* Insertmode,
          bool (*Validate)(const char* , CDialog&) = NO_VALDFUNC, 
          void (*Help)(MessageStatus, CDialog&) = NO_HELPFUNC,
          bool Bordered = false,
          const char* Border=C_BORDER_CHARS);
    CValEdit(int Row, int Col, int Width,
          int Maxdatalen, bool* Insertmode,
          bool (*Validate)(const char* , CDialog&) = NO_VALDFUNC, 
          void (*Help)(MessageStatus, CDialog&) = NO_HELPFUNC,
          bool Bordered = false,
          const char* Border=C_BORDER_CHARS);
    int edit();
  };
}

#endif