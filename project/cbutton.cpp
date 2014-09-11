// Console UI Core Classes
// cbutton.cpp
//
// Jose Ramirez
// Nov 22 2013
// Version 1.0


#include "cbutton.h"
using namespace cio;
using namespace bio;

namespace cio{
  CButton::CButton(const char *Str, int Row, int Col, 
             bool Bordered,const char* Border):CField(Row,Col,
			 (Bordered)?strlen(Str)+4:strlen(Str)+2,(Bordered)?3:1,(void*)0,Bordered,Border){
    char* temp=new char[strlen(Str)+1];
	_data=temp;
	strcpy(_data,Str);

  }
  CButton::~CButton(){
    delete [] _data;
  }

  void CButton::draw(int fn){
    CFrame::draw(fn);
	console.display(" ",(visible())?absRow()+1:absRow(),(visible())?absCol()+1:absCol()-1,1,0);
	console.display((char*)_data,(visible())?absRow()+1:absRow(),(visible())?absCol()+2:absCol(),strlen((char*)_data),0);
  }

  int CButton::edit(){
	  int key;
	  draw();
	  if (visible()){
		  console.display("]", absRow() + 1, absCol() + strlen((char*)_data) + 2);
		  console.display("[", absRow() + 1, absCol() + 1, 1);
	  }
	  else{
		  console.display("]", absRow(), absCol() + strlen((char*)_data));
		  console.display("[", absRow(), absCol() - 1, 1);
	  }
	  key = console.getKey();
	  switch (key) {
	  case ENTER:
	  case SPACE:
		  key = C_BUTTON_HIT;
		  break;
	  default:
		  break;
	  }
	  if (visible()){
		  console.display(" ", absRow() + 1, absCol() + strlen((char*)_data) + 2);
		  console.display(" ", absRow() + 1, absCol() + 1, 1);
	  }
	  else{
		  console.display(" ", absRow(), absCol() + strlen((char*)_data));
		  console.display(" ", absRow(), absCol() - 1, 1);
	  }
	  return key;
  }

  void CButton::set(const void* Str){
    delete _data;
	char* temp=new char[strlen(Str)+1];
	_data=temp;
	strcpy(_data,Str);
	delete temp;
  }

  bool CButton::editable()const{
    return true;
  }

}