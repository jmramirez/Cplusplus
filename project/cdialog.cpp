// Console UI Core Classes
// cdialog.cpp
//
// Jose Ramirez
// Nov 22 2013
// Version 1.1

#include "cdialog.h"
#include "cfield.h"
using namespace cio;

namespace cio{
  CDialog::CDialog(CFrame *Container,int Row, int Col,int Width, int Height, 
             bool Bordered,const char* Border):CFrame(Row,Col,Width,Height,true,Border,Container){
    _fnum=0;
	_fldSize=C_INITIAL_NO_FIELDS;
	_fld=new CField*[C_INITIAL_NO_FIELDS];
	_dyn=new bool[C_INITIAL_NO_FIELDS];
	_editable=false;
	_curidx=0;

	int idx;
	for(idx=0;idx<=_fldSize;idx++){
	  _fld[idx]=0;
	}
	for(idx=0;idx<=_fldSize;idx++){
	  _dyn[idx]=false;
	}
  }
  CDialog::~CDialog(){
    int idx;
	for(idx=0;idx<_fnum&&_fld[idx];idx++){
	  if(_dyn[idx]){
	    delete  _fld[idx];
	  }
	}
  }

  void CDialog::draw(int fn){
    int idx;
    if(fn==C_FULL_FRAME){
      CFrame::draw();
	  for(idx=0;idx<_fnum&&_fld[idx];idx++){
	    _fld[idx]->draw(fn);
	  } 
	}
	else if(fn==0){
	  for(idx=0;idx<=_fnum&&_fld[idx];idx++){
	    _fld[idx]->draw(fn);
	  }
	}
	else if(fn>0){
		_fld[fn]->draw(fn);
	}
  }

  int CDialog::edit(int fn){
    int key;
	int idx;
	bool flag;
	bool done=false;
	if (!(_editable)){
	    this->draw(fn);
	    key=console.getKey();
	    done=true;
	}
	else if(fn<=0){
	    this->draw(fn);
	    while(!_fld[_curidx]->editable()){
	      _curidx++;
	    }
	}
	else if(fn>0){
	    _curidx=fn-1;
		while(!_fld[_curidx]->editable()){
		  _curidx++;
		  if(_curidx==_fnum){
		    _curidx=0;
		  }
		}	
	}
	while(!done){
	  key=_fld[_curidx]->edit();
	  switch(key){
	  case ENTER:
	  case TAB:
	  case DOWN:
		flag=false;
        while(!flag){
		  _curidx++;
		  if(_curidx==_fnum){
		    _curidx=0;
		  }
		  if(_fld[_curidx]->editable()){
		  flag=true;
		  }
		}
		break;
	  case UP:
		  if(_curidx !=0){
           _curidx--; 
		  }
		  else{
			  _curidx=_fnum-1;
		  }
        while(!_fld[_curidx]->editable()){
		  _curidx--;
		  if(_curidx<0){
		    _curidx=_fnum-1;
		  }
		}
		break;
	  default:
	    done=true;
		break;
	  }
    }
	return key;
  }

  int CDialog::add(CField* field,bool dynamic){
    int idx;
    if(_fnum==_fldSize){
	  CField** temp=new CField*[_fldSize+C_DIALOG_EXPANSION_SIZE];
	  bool* temp1=new bool[_fldSize+C_DIALOG_EXPANSION_SIZE];
	  for(idx=0;idx<=_fldSize;idx++){
	    temp[idx]=_fld[idx];
		temp1[idx]=_dyn[idx];
	  }
	  _fld=temp;
	  _dyn=temp1;
	  _fldSize +=C_DIALOG_EXPANSION_SIZE;
	}
	field->container(this);
	_fld[_fnum]=field;
	_dyn[_fnum]=dynamic;
	_fnum++;
	if(field->editable()){
	  _editable=true;
	}
	return(_fnum-1);
  }

  int CDialog::add(CField& field, bool dynamic){
	  return add(&field,dynamic);
    
  }

  CDialog& CDialog::operator<<(CField* field){
    add(field);
	return *this;
  }

  CDialog& CDialog::operator<<(CField& field){
    add(field);
	return *this;
  }
  
  bool CDialog::editable(){
   return _editable;
  }

  int CDialog::fieldNum()const{
    return _fnum;
  }

  int CDialog::curIndex()const{
    return _curidx;
  }

  CField& CDialog::operator[](unsigned int index){
    return *_fld[index];
  }

  CField& CDialog::curField(){
    return *_fld[_curidx];
  }
}
