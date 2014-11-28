#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNIGS

#include "cio.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>

using namespace std;
using namespace cio;

struct Book
{
	char _name[71];
	char _author[71];
	char _publisher[71];
	char _releaseDate[11];
	unsigned long _isbn;
	unsigned long _rating;

	Book(char* name, char* author, char* publisher, char* releaseDate, long isbn,
		long rating){
		strcpy(_name, name);
		strcpy(_author,author);
		strcpy(_publisher, publisher);
		strcpy(_releaseDate, releaseDate);
		_isbn = isbn;
		_rating = rating;
	}

	Book(){
		_name[0] = '\0';
		_author[0] = '\0';
		_publisher[0] = '\0';
		_releaseDate[0] = '\0';
		_isbn = 0;
		_rating = 0;
	}

	const char* cas(long num){
		string s = to_string(num);
		 return  s.c_str();
	}

	void operator<<(CDialog& C){
		strcpy(_name, (char*)C[1].data());
		strcpy(_author, (char*)C[3].data());
		strcpy(_publisher, (char*)C[5].data());
		strcpy(_releaseDate, (char*)C[7].data());
		_isbn = atoi((char*)C[9].data());
		_rating = atoi((char*)C[11].data());
	}
};

bool Yes(const char* message, CDialog* owner){
	int key;
	bool res = false;
	bool done = false;
	CButton bt_yes("Yes", 4, 4, true, "+-+|+-+|");
	CButton bt_no("No", 4, 15, true, "+-+|+-+|");
	CDialog YesNo(owner, (console.getRows() - 10) / 2, (console.getCols() - 40) / 2, 40, 10, true, "+-+|+-+|");
	YesNo << new CLabel(2, 2, 36) << bt_yes << bt_no;
	YesNo[0].set(message);
	YesNo.draw(C_FULL_FRAME);
	while (!done){
		key = YesNo.edit();
		if (key == C_BUTTON_HIT){
			res = &YesNo.curField() == &bt_yes;
			done = true;
		}
		else if (key == F(6)){
			YesNo.move();
		}
	}
	YesNo.hide();
	return res;
}

void Help(CDialog* owner, CDialog* helping){
	CDialog help(owner, 5, (console.getCols() - 40) / 2, 42, 21, true);

	help << new CLabel("Command Help", 2, 1)
		<< new CLabel("F9 key: Go to the first register.", 4, 3)
		<< new CLabel("F10 Key: Go to the last register.", 6, 3)
		<< new CLabel("PGUP: Move to the Next register.", 8, 3)
		<< new CLabel("PGDN: Move to the Previous register.", 10, 3)
		<< new CLabel("Escape Key: Exit the test program.", 12, 3)
		<< new CLabel("F4 key: Add new register.", 14, 3)
		<< new CLabel("F3 key: Save Changes.", 16, 3)
		<< new CLabel("F1 Key: Open this window.", 18, 3);
	while (help.edit(C_FULL_FRAME) == F(6)){
		help.move();
	}
	help.hide();
}


int main(int argc, char* argv[]){
	bool done = false;
	int key = 0;
	int i = 0;
	bool insert = true;
	CDialog Screen;
	string fname = "";
	Book book;
	string option = "";
	int lenght = 0;
	int books = 0;
	string s;
	string b;
	char const *pchar;
	char const *bo;
	bool adding = true;

	

	Screen << new CLabel("[Book DataBase Application]", 1, ((console.getCols() - 27) / 2));
	Screen.draw();

	CLineEdit name(2, 15,27,50, &insert, true, "+-+|+-+|");
	CLineEdit author(5, 15, 27, 25, &insert, true, "+-+|+-+|");
	CLineEdit publisher(8, 15, 27, 25, &insert, true, "+-+|+-+|");
	CLineEdit release(11, 15, 27, 25, &insert, true, "+-+|+-+|");
	CLineEdit isbn(14, 15, 27, 25, &insert, true, "+-+|+-+|");
	CLineEdit rating(17, 15, 27, 25, &insert, true, "+-+|+-+|");
	CLineEdit file_n(3, 2,35,15, &insert, true, "+-+|+-+|");
	CLabel first_last(20, 15, 30);

	CDialog file(&Screen, 3, 5, 40, 10,  true, "+-+|+-+|");
	file << new CLabel("Enter FileName:", 2, 2) << file_n;
	file.draw();

	file_n.set("book.db");
	
	while (!done)
	{
		key = file_n.edit();
		fname = (char*)file_n.data();
		if (key == ENTER && fname.length()>0){
			done = true;
		}
		else{
			console.alarm();
		}
	}
	file.hide();
	fstream data(fname, ios::in|ios::out|ios::binary|ios::ate);
	

	CDialog main_d(&Screen, 3, 5, 70, 23, true, "+-+|+-+|");
	main_d << new CLabel("Name:", 3, 9) << name
		<< new CLabel("Author:", 6, 7) << author
		<< new CLabel("Publisher:", 9, 4) << publisher
		<< new CLabel("ReleaseDate:", 12, 2) << release
		<< new CLabel("ISBN:", 15, 9) << isbn
		<< new CLabel("Rating:", 18, 7) << rating
		<< new CLabel("Register #:", 1, 43);

	data.seekg(0, ios::end);
	lenght = (data.tellg()/sizeof(book));
	books = lenght + 1;
	s = to_string(lenght);
	b = to_string(books);
	pchar = s.c_str();
	bo = b.c_str();
	main_d << new CLabel(bo, 2, 43, 20) ;
	main_d << first_last;
	
	Screen << new CLabel("----------------------------------------------------------------------------", 26, 2) <<
			new CLabel("[F1 : Help] [F9 : First] [F10 : Last] [PGUP : Next] [PGDN : Prev]", 27, 8) <<
			new CLabel("[ESCAPE : Exit] [F4 : Add New] [F3 : Save Changes]", 28, ((console.getCols() - 52) / 2) + 4);
	Screen.draw();
	main_d.draw();
	
	done = false;
	while (!done){
		key = main_d.edit();
		switch (key){
		case F(1):
			Help(&Screen, &main_d);
			break;
		case F(9):
			adding = false;
			first_last.set("");
			data.clear();
			data.seekg(0, ios::beg);
			data.read((char*)&book, sizeof(Book));
			lenght = data.tellg();
			books = lenght / sizeof(Book);
			s = to_string(lenght);
			b = to_string(books);
			pchar = s.c_str();
			bo = b.c_str();
			main_d[13].set(bo);
			main_d[1].set(book._name);
			main_d[3].set(book._publisher);
			main_d[5].set(book._releaseDate);
			main_d[7].set(to_string(book._isbn).c_str());
			main_d[9].set(to_string(book._rating).c_str());
			break;
		case F(10):
			adding = false;
			first_last.set("");
			data.clear();
			data.seekg(-(ios::off_type)sizeof(Book), ios::end);
			data.read((char*)&book, sizeof(Book));
			lenght = data.tellg();
			books = lenght / sizeof(Book);
			s = to_string(lenght);
			b = to_string(books);
			pchar = s.c_str();
			bo = b.c_str();
			main_d[13].set(bo);
			main_d[1].set(book._name);
			main_d[3].set(book._publisher);
			main_d[5].set(book._releaseDate);
			main_d[7].set(to_string(book._isbn).c_str());
			main_d[9].set(to_string(book._rating).c_str());
			break;
		case PGUP:
			adding = false;
			data.clear();
			s = to_string(lenght);
			b = to_string(books);
			pchar = s.c_str();
			bo = b.c_str();
			if (books == 1){
				first_last.set("Firts Element of the File");
			}
			else if (books > lenght){
				first_last.set("");
				main_d[13].set(bo);
				data.seekg(-(ios::off_type)(sizeof(Book)), ios::cur);
				data.read((char*)&book, sizeof(Book));
				lenght = data.tellg();
				books = lenght / sizeof(Book);
				s = to_string(lenght);
				b = to_string(books);
				pchar = s.c_str();
				bo = b.c_str();
				main_d[13].set(bo);
				main_d[1].set(book._name);
				main_d[3].set(book._publisher);
				main_d[5].set(book._releaseDate);
				main_d[7].set(to_string(book._isbn).c_str());
				main_d[9].set(to_string(book._rating).c_str());
			}
			else{
				first_last.set("");
				main_d[13].set(bo);
				data.seekg(-(ios::off_type)(2 * sizeof(Book)), ios::cur);
				data.read((char*)&book, sizeof(Book));
				lenght = data.tellg();
				books = lenght / sizeof(Book);
				s = to_string(lenght);
				b = to_string(books);
				pchar = s.c_str();
				bo = b.c_str();
				main_d[13].set(bo);
				main_d[1].set(book._name);
				main_d[3].set(book._publisher);
				main_d[5].set(book._releaseDate);
				main_d[7].set(to_string(book._isbn).c_str());
				main_d[9].set(to_string(book._rating).c_str());
			}
			break;
		case PGDN:
			adding = false;
			first_last.set("");
			data.clear();
			//data.seekg((ios::off_type)(sizeof(Book)), ios::cur);
			data.read((char*)&book, sizeof(Book));
			lenght = data.tellg();
			if (lenght == -1){
				first_last.set("Last Element of the File");
				data.clear();
				data.seekg(0, ios::end);
				lenght = (data.tellg() / sizeof(book));
				books = lenght + 1;
				s = to_string(lenght);
				b = to_string(books);
				pchar = s.c_str();
				bo = b.c_str();
				main_d[13].set(bo);
				main_d[1].set("");
				main_d[3].set("");
				main_d[5].set("");
				main_d[7].set("");
				main_d[9].set("");
			}
			else{
				first_last.set("");
				books = lenght / sizeof(Book);
				s = to_string(lenght);
				b = to_string(books);
				pchar = s.c_str();
				bo = b.c_str();
				main_d[13].set(bo);
				main_d[1].set(book._name);
				main_d[3].set(book._publisher);
				main_d[5].set(book._releaseDate);
				main_d[7].set(to_string(book._isbn).c_str());
				main_d[9].set(to_string(book._rating).c_str());
			}
			break;
		case ESCAPE:
			if (Yes("Do you really want to quit?", &Screen)){
				done = true;
			}
			break;
		case F(4):
			adding = true;
		
		case F(3):
			lenght = data.tellg();
			books = (lenght / sizeof(Book))-1;
			if (adding&&(Yes("Add New Book?", &main_d))){
				book << main_d;
				data.clear();
				data.seekp((ios::pos_type)(sizeof(Book) * books));
				data.write((const char*)&book, sizeof(Book));
				data.clear();
				data.seekg((ios::off_type)(sizeof(Book)), ios::cur);
				lenght = data.tellg();
				books = lenght / sizeof(Book);
				s = to_string(lenght);
				b = to_string(books);
				pchar = s.c_str();
				bo = b.c_str();
				main_d[13].set(bo);
				main_d[1].set("");
				main_d[3].set("");
				main_d[5].set("");
				main_d[7].set("");
				main_d[9].set("");
				main_d[11].set("");
				main_d.draw();
				
			}
			else if(Yes("Save Changes?", &main_d)){
				book << main_d;
				data.seekg(-(ios::off_type)(sizeof(Book)), ios::cur);
				lenght = data.tellg();
				data.write((const char*)&book, sizeof(Book));
				lenght = data.tellg();
				lenght = data.tellg();
				books = lenght / sizeof(Book);
				s = to_string(lenght);
				b = to_string(books);
				pchar = s.c_str();
				bo = b.c_str();
				main_d[13].set(bo);
				main_d[1].set(book._name);
				main_d[3].set(book._publisher);
				main_d[5].set(book._releaseDate);
				main_d[7].set(to_string(book._isbn).c_str());
				main_d[9].set(to_string(book._rating).c_str());
			}
			break;
			
		}
	}
	data.close();
	return 0;
}

#endif