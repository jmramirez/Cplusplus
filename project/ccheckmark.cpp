// Console UI Core Classes
// ccheckmark.cpp
//
// Jose Ramirez
// Nov 22 2013
// Version 1.0

#include "ccheckmark.h"
using namespace cio;
using namespace bio;
namespace cio{
  
  CCheckMark::CCheckMark(bool Checked,const char* Format, const char* Text,
	  int Row, int Col, int Width, bool IsRadio):CField(Row,Col,Width,1),_Label(Text,0,4,(Width-4)){
	_Label.frame(this);
	_flag=Checked;
	_radio=IsRadio;
    strcpy(_format,Format);
    _data=(void*)&_flag;
  }

  CCheckMark::CCheckMark(const CCheckMark& C):CField(C),_Label(C._Label){
	_flag=C._flag;
	_radio=C._radio;
	strcpy(_format,C._format);
    _data=(void*)&(C._flag);
	_Label.frame(this);
  }

  void CCheckMark::draw(int fn){
    console.display(_format,absRow(),absCol());
	if(!_flag){
	  console.display(" ",absRow(),absCol()+1);
	}
	_Label.draw();
	 console.setPos(absRow(),absCol()+1);
  }

  int CCheckMark::edit(){
    int key;
	bool valid=false;
	draw();
	while(!valid){
	  key=console.getKey();
	  if(key==ENTER||key==TAB||key==UP||key==DOWN||key==SPACE||key==F(2)||key==F(1)||key==F(6)||key==ESCAPE){
	    valid=true;
	  }
	}
	if(key==SPACE){
	  if(_radio){
	    _flag=true;
	  }
	  else{
	    _flag=!_flag;
	  }
	}
	draw();
    return key;
  }

  bool CCheckMark::editable()const{
    return true; 
  }

  void CCheckMark::set(const void* flag){
    _flag=(bool*)flag;
  }

  bool CCheckMark::checked()const{
    return _flag;
  }

  void CCheckMark::checked(bool val){
    _flag=val;
  }

  bool CCheckMark::radio(){
    return _radio;
  }

  void CCheckMark::radio(bool isRadio){
    _radio=isRadio;
  }

  CCheckMark::operator bool(){
    return _flag;
  } 
  
  CCheckMark::operator char*(){
    return (char*)_Label.data();
  } 

  bool CCheckMark::operator=(bool flag){
    _flag=flag;
	return _flag;
  }
}