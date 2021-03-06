#include "cvaledit.h"
using namespace cio;
using namespace bio;

namespace cio{
  CValEdit::CValEdit(char* Str, int Row, int Col, int Width,
      int Maxdatalen, bool* Insertmode,
      bool (*Validate)(const char* , CDialog&), 
      void (*Help)(MessageStatus, CDialog&),
      bool Bordered,
      const char* Border):CLineEdit(Str,Row,Col,Width,Maxdatalen,Insertmode,Bordered,Border){
    _help=Help;
	_validate=Validate;
  
  }

  CValEdit::CValEdit(int Row, int Col, int Width,
      int Maxdatalen, bool* Insertmode,
      bool (*Validate)(const char* , CDialog&), 
      void (*Help)(MessageStatus, CDialog&),
      bool Bordered,const char* Border):CLineEdit(Row,Col,Width,Maxdatalen,Insertmode,Bordered,Border){
    _help=Help;
	_validate=Validate;
  }

  int CValEdit::edit(){
	  int key;
	  bool valid=false;
    if(container()){
      if(_help){
		_help(MessageStatus::SetMessage,*(container()));
	  }
	  key=CLineEdit::edit();
	  if ((key == UP || key == DOWN || key == TAB || key == ENTER)&&_validate){
		  
		  valid=_validate((char*)_data,*(container()));
		  while ((key == UP || key == DOWN || key == TAB || key == ENTER)&&!valid){
            key=CLineEdit::edit();
		    valid=_validate((char*)_data,*(container()));
		  }
		  	  
	  }
	  if(_help){
		_help(MessageStatus::ClearMessage,*(container()));
	  }
	}else{
	  key:CLineEdit::edit();
	}
	return key;
	}
  
}