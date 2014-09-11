// Console UI Core Classes
// cmenuitem.cpp
//
// Jose Ramirez
// Nov 22 2013
// Version 1.0

#include "cmenuitem.h"
using namespace cio;
using namespace bio;
namespace cio{

	CMenuItem::CMenuItem(bool Selected,const char* Format, const char* Text, int Row, int Col, int Width):CField(Row,Col,Width,1),
	Label(Text,0,1,Width-2){
	  _selected=Selected;
	   strcpy(_format,Format);
	  CField::_data=(void*)&_format;
	 Label.frame(this);
	}

	CMenuItem::CMenuItem(const CMenuItem &CM):CField(CM),Label(CM.Label){
	  _selected=CM._selected;
	   strcpy(_format,CM._format);
	  CField::_data=(void*)&CM._format;
	  Label.frame(this);
	}

	void CMenuItem::draw(int fn){
	  Label.draw(fn);
	  if(_selected){
	    console.display(_format,absRow(),absCol(),1);
		console.display(_format+1,absRow(),absCol()+Label.width());
		
	  }
	  else{
	    console.display(" ",absRow(),absCol());
		console.display(" ",absRow(),absCol()+Label.width());
	  }
	  console.setPos(absRow(),absCol()+1);
	}

	int CMenuItem::edit(){
	  int key;
	  bool valid=false;
	  draw();
	  while(!valid){
	    key=console.getKey();
	    if(key==ENTER||key==TAB||key==UP||key==DOWN||key==SPACE||key==ESCAPE){
	      valid=true;
	    }
	  }
	  if(key==SPACE){
	    _selected=true;
	  }
	  draw();
      return key;
	}

	bool CMenuItem::editable()const{
	  return true;
	}
	void CMenuItem::set(const void* Selected){
	  _selected=Selected;
	}

	bool CMenuItem::selected()const{
	  return _selected;
	}

	void CMenuItem::selected(bool val){
	  _selected=val;
	}

	const char* CMenuItem::Text()const{
	  return (char*)Label.data();
	}
}