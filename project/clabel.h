// Console UI Core Classes
// clabel.h
//
// Jose Ramirez
// Nov 22 2013
// Version 1.1

#pragma once
#include "cfield.h"
using namespace cio;

class CLabel :  public CField{
   // for length of the field:
   //  Use void CFrame::width(int) to store length, and int CFrame::width() to retrieve the length
 
 public:
   CLabel(const CLabel& L);
   CLabel(const char *Str, int Row, int Col,
     int Len = 0);
   CLabel(int Row, int Col, int Len);
   virtual ~CLabel();
   void draw(int fn=C_NO_FRAME) ;
   int edit();
   bool editable()const;
   void set(const void* str);
};
