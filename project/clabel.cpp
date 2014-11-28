// Console UI Core Classes
// clabel.cpp
//
// Jose Ramirez
// Nov 22 2013
// Version 1.1

#include "clabel.h"
using namespace cio;
using namespace bio;


  CLabel::CLabel(const char *Str, int Row, int Col, int Len):CField(Row,Col){
    if(Len==0){
	  char* temp=new char[strlen(Str)+1];
	  strcpy(temp,Str);
	  _data=temp;
	  CFrame::width(strlen(Str)+1);
	}
	else if(Len>0){
	  char* temp=new char[Len+1];
	  strncpy(temp,Str,Len);
	  temp[Len]='\0';
	  _data=temp;
	  CFrame::width(Len);
	}
  }
  CLabel::CLabel(int Row,int Col,int Len):CField(Row,Col){
    char* temp=new char[Len+1];
	temp[0]='\0';
	_data=temp;
	CFrame:width(Len);
  }
  CLabel::CLabel(const CLabel& L){
    *this=L;
  }
  
  void CLabel::draw(int fn){
    console.display((char*)_data,absRow(),absCol(),width()); 
  }

  int CLabel::edit(){
    draw();
	return 0;
  }

  bool CLabel::editable() const{
    return false;
  }

  void CLabel::set(const void* str){
    if(width()>0){
	  strncpy(_data,str,width());
	}
	else if(width()==0){
	  delete [] _data;
	  _data=new char[strlen(str)+1];
	  strcpy(_data,str);
	}
  }

  CLabel::~CLabel(){
    delete [] _data;
  }
