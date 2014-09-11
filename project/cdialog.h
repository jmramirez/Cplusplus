// Console UI Core Classes
// cdialog.h
//
// Jose Ramirez
// Nov 22 2013
// Version 1.1

#pragma once
#ifndef __JM_CDialog_H__
#define __JM_CDialog_H__
#include "ciogh.h"
#include "cframe.h"
namespace cio{
  class CField;
  class CDialog: public CFrame{
    private:
    int _fnum;
    int _curidx;
    CField** _fld;
    bool* _dyn;
    bool _editable;
    unsigned int _fldSize;
    public:
    CDialog(CFrame *Container = (CFrame*)0,
             int Row = -1, int Col = -1, 
             int Width = -1, int Height = -1, 
             bool Bordered = false,
             const char* Border=C_BORDER_CHARS);
    virtual ~CDialog();
    void draw(int fn = C_FULL_FRAME);
    int edit(int fn = C_FULL_FRAME);
 
    int add(CField* field, bool dynamic = true);
    int add(CField& field, bool dynamic = false);
    CDialog& operator<<(CField* field);
    CDialog& operator<<(CField& field);
 
    bool editable();
    int fieldNum()const;
    int curIndex()const;
 
    CField& operator[](unsigned int index);
    CField& curField();
  };
}
#endif