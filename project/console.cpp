/*
      console.cpp
	  Upgraded of the basic console input output class (BConsole) to include line-display 
	  and line-editing facilities and use of "<<" and ">>" operators for character I/O and 
	  string output. 

	  Jose Ramirez
	  Oct 09, 2013

*/

#include "console.h"
using namespace bio;

namespace cio{
  bool Console::_insertMode = true;
  unsigned int Console::_tabsize=4;
  
  //operator >>
  Console& operator>>(Console& cn, int& ch){
    ch= cn.getKey();
	return cn;
  }

  //operator <<
  Console& operator<<(Console& cn, char ch){
    cn.putChar(ch);
	return cn;
  }
  Console& operator<<(Console& cn,const char* ch){
    int i;
	for(i=0; ch[i];i++){
		cn.putChar(ch[i]);
	}
	return cn;
  }

  void Console::display(const char* str, int row, int col, int len, int curpos){
    int i = 0;
    setPos(row, col);
    if(len){ // max fieldlen cars
      for(;i<len && str[i];i++){
        putChar(str[i]);
      }
      for(;i<len;i++){
        putChar(' ');
      }
    }
    else{  // print the whole thing
      for(;str[i];i++){
        putChar(str[i]);
      }
    }
    if(curpos >=0){
      setPos(row, col + curpos);
    }
  }
  //function used to edit the string  
  int  Console::edit(char *str, int row, int col, int fieldLength, int maxStrLength, 
      int* strOffset, int* curPosition,  
        bool InTextEditor, bool ReadOnly, bool& insertMode){
    bool done = false;
    int key = 0;
    int idx = 0;
	int lcurPosition=0;
	int lOffset=0;
	int intOffset=*strOffset;
	int intCurpos=*curPosition;
	char* oStr;
	oStr=new char[maxStrLength+1];
	strcpy(oStr,str);

	if((unsigned int)*strOffset>strlen(str)){ 
	  *strOffset=strlen(str);     
	}
	else if(strOffset==(int*)0){
	  strOffset= &lOffset;
	}
	else{
	  lOffset=*strOffset;
	}
    if(*curPosition>fieldLength-1){
	  *curPosition=fieldLength-1;
	}
	else if((unsigned int)*curPosition>strlen(str)){
	  *curPosition=strlen(str);
	}
	else if(curPosition==(int*)0){
	  curPosition=&lcurPosition;
	}
    while(!done){
      // display UI
      display(str + (*strOffset), row, col, fieldLength, *curPosition);
      // get user response
      key = getKey();
      // act on it
      switch(key){
      case INSERT: //when INSERT is pressed
        insertMode = !insertMode;
        break;
      case HOME:  //when HOME is pressed
        *strOffset = *curPosition = 0;
        break;
	  case END:  //when END is pressed
        if((int)strlen(str)>=(*strOffset+fieldLength)){  
		  *strOffset=strlen(str)-fieldLength+1;
		  *curPosition=strlen(str)-*strOffset;
		}
		else if(strlen(str)==(*strOffset+fieldLength)){
		  *curPosition=strlen(str)-*strOffset-1;
		}
		else{
		  *curPosition=strlen(str)-*strOffset;  
		}
		break;
      case BACKSPACE: //when BACKSPACE is pressed
        for(idx = *curPosition+*strOffset-1;idx >=0 && str[idx];idx++){
          str[idx] = str[idx+1];
        }
        if(*curPosition){
          (*curPosition)--;
        }
        else if(*strOffset && !*curPosition){
		  *curPosition +=3;
          *strOffset-=4;
        }
        else{
          console.alarm();
        }
        break;
	  case DEL:  //when DEL is pressed
        if((unsigned int)*curPosition<strlen(str)){
			
		  for(idx=0;str[*strOffset+*curPosition+idx];idx++){
		    str[*strOffset+*curPosition+idx]=str[*strOffset+*curPosition+1+idx];
		  }
		}
		else{
		  console.alarm();
		}
	    break;
      case LEFT:
        if((*curPosition) > 0){
          (*curPosition)--;
        }
        else if((*strOffset) > 0){
          (*strOffset)--;
        }
        else{
          console.alarm();
        }

		break;
	  case RIGHT:
	    if((*curPosition<fieldLength-1)&&((unsigned int)*curPosition<strlen(str))){
		  (*curPosition)++;
		}
		else if((unsigned int)(*curPosition+*strOffset)<strlen(str)){
		  (*strOffset)++;
		}
		else{
		  cio::console.alarm();
		}
        break;
      case ENTER:
        done = true;
        break;
      case ESCAPE:
        if(InTextEditor){ //escape pressed in TextEditor mode
		  intCurpos=*curPosition;
		}
		else{ 
		  *curPosition=intCurpos;
		  strcpy(str,oStr);
		  *strOffset=intOffset;
		}
        done = true;
        break;
	  case TAB:
		if(InTextEditor){ //TAB pressed in TextEditor mode
		  if(_tabsize+strlen(str)<(unsigned int)maxStrLength){
            str[strlen(str)-1+_tabsize+1]=0;
		    for(idx=strlen(str);idx>(*strOffset+*curPosition);idx--){
			  str[idx+_tabsize-1]=str[idx-1];
			  str[idx-1]=' ';
			}
			
			if(*curPosition+_tabsize<(unsigned int)fieldLength-1){
			  (*curPosition)+=_tabsize;
			}
			else if(*curPosition<fieldLength-1){
				(*strOffset)+=_tabsize-(fieldLength-*curPosition)+1;
				(*curPosition)+=(fieldLength-1)-*curPosition;
			}
			else{
			  (*strOffset)+=_tabsize;
			}
		  }
		}
		else{ //TAB pressed in ReadOnly mode
		  done=true;
		}
	    break;
	  case F(1): //when F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12 is pressed
      case F(2):
	  case F(3):
	  case F(4):
      case F(5):
	  case F(6):
	  case F(7):
	  case F(8):
      case F(9):
      case F(10):
      case F(11):
      case F(12):
	  case UP:
	  case DOWN:
	  case PGDN:
	  case PGUP:
        done=true;
        break;
      default:
        if(!ReadOnly){ 
          if(key >= ' ' && key <= '~'){ // printable chars
            if(insertMode){ //insert mode
		      if(strlen(str)<(unsigned int)maxStrLength){
			    for(idx=strlen(str);idx>=(*strOffset+*curPosition);idx--){
			      str[idx+1]=str[idx];
			    }
			    str[*strOffset+*curPosition]=key;
			    if(*curPosition<fieldLength-1){
			      (*curPosition)++;
			    }
			    else{
				  (*strOffset)++;
				}
			  }
			  else{  
		        console.alarm();
		      }
            }
            else { // overstrike
              if(*curPosition<fieldLength-1){
			    str[*strOffset+*curPosition]=key;
			    (*curPosition)++;
			  } 
			  else{
			    if((*strOffset+fieldLength<=maxStrLength) && str[*strOffset+*curPosition] == 0){
                  str[*strOffset+*curPosition+1] = 0;
                }
			    if(*strOffset+fieldLength<=maxStrLength){
			      str[*strOffset+fieldLength-1]=key;
				  (*strOffset)++;
			    }
			  }
            }
          }
		}
        break;
      }
	  if(InTextEditor && (*strOffset) !=lOffset){ //when in TextEditor mode and the Offset is changed
	    return 0;
	  }  
	}
    return key;
  }
  Console console;
}