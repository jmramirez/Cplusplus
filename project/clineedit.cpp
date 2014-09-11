// Console UI Core Classes
// clineedit.cpp
//
// Jose Ramirez
// Nov 22 2013
// Version 1.1

#include "clineedit.h"
using namespace cio;
using namespace bio;

namespace cio{
  CLineEdit::CLineEdit(char* Str, int Row, int Col, int Width,int Maxdatalen, bool* Insertmode, 
      bool Bordered,const char* Border):CField(Row,Col,Width,(Bordered)?3:1,Str,Bordered,Border){
    _data=Str;
	_dyn=false;
	_maxdatalen=Maxdatalen;
	_insertmode=Insertmode;
	_curpos=0;
	_offset=0;
  }
  CLineEdit::CLineEdit(int Row, int Col, int Width,int Maxdatalen, bool* Insertmode, 
      bool Bordered,const char* Border):CField(Row,Col,Width,(Bordered)?3:1,0,Bordered,Border){
    char* temp=new char[Maxdatalen+1];
	temp[0]=0;
	_data=temp;
	_dyn=true;
	_maxdatalen=Maxdatalen;
	_insertmode=Insertmode;
	_curpos=0;
	_offset=0;
  }
  CLineEdit::~CLineEdit(){
    if(_dyn){
	  delete [] _data;
	}
  }

  void CLineEdit::draw(int Refresh){
    CFrame::draw(Refresh);
	console.display((char*)_data+_offset,(visible())?absRow()+1:absRow(),(visible())?absCol()+1:absCol(),(visible())?width()-2:width());
  }
  int CLineEdit::edit(){
    return console.edit((char*)_data,(visible())?absRow()+1:absRow(),(visible())?absCol()+1:absCol(),(visible())?width()-2:width(),_maxdatalen,&_offset,&_curpos);
  }
  bool CLineEdit::editable()const{
    return true;
  }
  void CLineEdit::set(const void* Str){
    bio::strncpy(_data,Str,_maxdatalen);
  }

}