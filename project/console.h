// Console Input Output Library - C++ Module
// console.h
//
// Jose Ramirez
// Oct 09 2013
// Version 1.0

#ifndef __JR_CONSOLE_H__
#define __JR_CONSOLE_H__
#include "bconsole.h"
namespace cio{
  class Console: public bio::BConsole{
    static bool _insertMode;
  public:
    static unsigned int _tabsize;
    void display(const char* str, int row, int col, 
      int fieldLen=0, int curpos = -1);
    int  edit(char *str, int row, int col, int fieldLength, int maxStrLength, 
        int* strOffset=(int*)0, int* curPosition=(int*)0,  
         bool InTextEditor = false, bool ReadOnly = false, bool& insertMode=_insertMode );
  };
  Console& operator<<(Console& cn,const char* ch);
  Console& operator<<(Console& cn, char ch);
  Console& operator>>(Console& cn, int& ch);
  extern Console console;
}
#endif
