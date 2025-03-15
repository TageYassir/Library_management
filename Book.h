#include <iostream>
#include <string>
#include <fstream> 
#include <limits>
#ifndef BOOK_H
#define BOOK_H


using namespace std;


class Book{
	private :
		string bookname;
		string bookauthor;
		string realeaseday;
		string price;
		string ISBN;
		int copies;
    public :
		Book(){}
		Book(string const bookname,string const bookauthor,string const realeaseday,string price,string const ISBN,int copies)
        :bookname(bookname),bookauthor(bookauthor),realeaseday(realeaseday),price(price),ISBN(ISBN),copies(copies){};
    
    //gets
    public :
string getbookname() const{return bookname;};
string getbookauthor() const{return bookauthor;};
string getrealeaseday() const{return realeaseday;};
string getprice() const{return price;};
string getISBN() const{return ISBN;};
int getcopies() const{return copies;};

    //sets
    public :
string setbookname(const string& newbookname){bookname=newbookname;};
string setbookauthor(const string& newbookauthor){bookauthor=newbookauthor;};
string setrealeaseday(const string& newrealeaseday){realeaseday=newrealeaseday;};
string setprice(const string& newprice){price=newprice;};
int setcopies(const int& newcopies){copies=newcopies;};

};


#endif // BOOK_H
