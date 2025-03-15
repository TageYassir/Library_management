#include <iostream>
#include <string>
#include <fstream> 
#include <limits>


// I tried in my simple code to avoid any problems with strings because I allow the user to enter any character in the ISBN ("v"). 
// Additionally, the price can be in any currency the user wishes, and the release date can be in any format the user prefers (-_-).
// It is a code friendly to user and flexible +('U')+.


using namespace std;


class Book1{
	protected :
		string bookname;
		string bookauthor;
		string realeaseday;
		string price;
		string ISBN;
		int copies;
    public :
		Book1(){}
		Book1(string bookname,string  bookauthor,string realeaseday,string price,string ISBN,int copies)
        :bookname(bookname),bookauthor(bookauthor),realeaseday(realeaseday),price(price),ISBN(ISBN),copies(copies){};
        Book1(const Book1 &B) : bookname(B.bookname),bookauthor(B.bookauthor),realeaseday(B.realeaseday),price(B.price),ISBN(B.ISBN),copies(B.copies){};
        Book1& operator=(const Book1& B) {      /* I had a problem when I was working on the old Dev++ that's why I add it    /\_/\  
                                                                                                                             ( o.o ) 
                                                                                                                              > ^ <
*/
    if (this != &B) {     // Just for more security and to be shure that's everything is ok.
        ISBN = B.ISBN;    // I used references to ensure the copy of the object.
        copies = B.copies;
        realeaseday = B.realeaseday;
        bookauthor = B.bookauthor;
        bookname = B.bookname;
    }
    return *this;};
    
    

};


class Book_file : protected Book1{
private:
    string filename;

public:
	
    Book_file(const string& filename) : filename(filename) {}
    Book_file(string bookname,string  bookauthor,string realeaseday,string price,string ISBN,int copies) : Book1(bookauthor,bookauthor,realeaseday,price,ISBN,copies){};
    

    void Addbook(string ISBN,string bookname,string bookauthor,string realeaseday,int copies ,string price) {
        if (ISBN.length() != 6) {
            cerr << "|Error: ISBN must be exactly 6 digits." << "\n------------------------------------------------------------" << endl;
            return;
    }	 // I add it to ensure that the isbn is 6 digits it's my own method to handle the errors of the stings you will find it all along the code with some other methodes.
    /*
 /\_/\  
( o.o ) 
 > ^ <
*/
    	ifstream checkFile(filename.c_str());  // I used the c.str() in order to work in the old version of the compiler.
        string line;
        
        // It is used to check if a isbn already exists it is one of my methods to avoid any problem of overwrithing.
        
        while (getline(checkFile, line)) {
            size_t pos = line.find("ISBN : " + ISBN);
            if (pos != string::npos) {
                cout << "|Error: A book with the same ISBN already exists.If you want to modify a bookrecord already existing try 4!!\n" << "------------------------------------------------------------------------------------------------------------------------" << endl;
                checkFile.close();
                return;
        }
    }
    checkFile.close();
        ofstream outFile(filename.c_str(), ios::app);
        if (!outFile.is_open()) {
            cerr << "|Error: Could not open the file." << "\n------------------------------------------------------------" << endl;  // cerr is use for output especialy in error handling.
            return;
        }
        outFile << "ISBN : " << ISBN<< "\nTitle : " << bookname << "\nAuthor : " << bookauthor << "\nDate : " << realeaseday << "\nPrice : " << price << "\nCopies : " << copies << "\n------------------------------------------------------------" << endl;
        outFile.close();
        cout << "|Book record added successfully!\n" << "------------------------------------------------------------"<< endl;
    }
    
    void list_of_Book() {
        ifstream inFile(filename.c_str());
        string line;
        cout << "|This all the books we have :\n";
        while (getline(inFile,line)) {
            cout << line << endl;
        }
        cout << "(|'_'|)" << endl;
        inFile.close();
    }
    
    void checkAvailability(string ISBN) {
        ifstream inFile(filename.c_str());
        string line;
        bool found = false;
        while (getline(inFile, line)) {
            size_t pos = line.find(ISBN); // size_t is a type of integers.
  /*          
 /\_/\  
( o.o ) 
 > ^ <
*/
            if (pos != string::npos) {
                found = true;  // The use of it is just to remember the isbn if found or not in case I need it to modify the function.
                cout << "|Book available!\n" ;
				cout << "------------------------------------------------------------" << endl;
				
				// I used the loop to output the demanded atributs using the positions
				
				for (int i=pos+1;i<=pos+6;++i){
					if (!getline(inFile,line)){
						break;
					}
					if (i==pos+1 || i==pos+2 || i==pos+5 || i==pos+6){
						cout << line << endl;
					}
				}
				break;
				}
			}
        if (!found) {
            cout << "|Book not available, see if the ISBN you entered is correct and retry!!!" << "\n------------------------------------------------------------"<< endl;
        }
        inFile.close();
    }
 
    void modifyBook(string ISBN,string newbookname,string newbookauthor,string newrealeaseday,int newcopies,string newprice) {	
	if (ISBN.length() != 6) {
        cout << "|Error: ISBN must have exactly 6 characters.\n------------------------------------------------------------" << endl;
        return;
    }   // I add it to ensure that the isbn is 6 digits it's my own method to handle the errors of the stings you will find it all along the code with some other methodes.
  /*
 /\_/\  
( o.o ) 
 > ^ <
*/
	ifstream inFile(filename.c_str());
    ofstream outFile("temp.txt");
    string line;
    bool found = false;
    while (getline(inFile, line)) {
        size_t pos = line.find("ISBN : " + ISBN);
        if (pos != string::npos) {
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "|Book not found in the records!\n" << "------------------------------------------------------------" << endl;
        inFile.close();
        outFile.close();
        return; 
    }
    inFile.seekg(0, ios::beg);  // I used it to set the position.
    while (getline(inFile, line)) {
        size_t pos = line.find(ISBN);
        if (pos != string::npos) {
            for (int i = 0; i < 6; ++i) {
                if (!getline(inFile, line)) {
                    break;
                }
            }
            outFile << "ISBN: " << ISBN << "\nTitle: " << newbookname << "\nAuthor: " << newbookauthor << "\nDate: " << newrealeaseday << "\nPrice: " << newprice << "\nCopies: " << newcopies << "\n------------------------------------------------------------" << endl;
        } 
		else {
            outFile << line << endl;
        }
    }
    inFile.close();
    outFile.close();
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());   // It is file handling to avoid any overwriting.
    if (found) {
        cout << "|Book record modified successfully!\n" << "------------------------------------------------------------" << endl;;
   }
}
    
    void deleteBook(string ISBN) {
    if (ISBN.length() != 6) {
        cout << "|Error: ISBN must have exactly 6 characters.\n------------------------------------------------------------" << endl;
        return;
    }

    ifstream inFile(filename.c_str());
    ofstream outFile("temp.txt");
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        if (line.find("ISBN : " + ISBN) != string::npos) {
            found = true;
            cout << "|Book found. Are you sure you want to delete? (Y/N): ";
            char choice;
            cin >> choice;
            if (toupper(choice) == 'Y' || choice == 'y') {
                cout << "|Book deleted successfully!\n------------------------------------------------------------" << endl;
                for (int i = 0; i < 6; ++i) {
                    if (!getline(inFile, line)) {
                        break;
                    }
                }
                continue; 
            } else {
                cout << "|You cancelled deletion.\n------------------------------------------------------------" << endl;
            }
        }
        outFile << line << endl; 
    }

    inFile.close();
    outFile.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (!found) {
        cout << "|Book not found in the records!\n------------------------------------------------------------" << endl;
    }
}

void modifycopies(string ISBN, int newcopies) {
    if (ISBN.length() != 6) {
        cout << "|Error: ISBN must have exactly 6 characters.\n------------------------------------------------------------" << endl;
        return;
    }

    ifstream inFile(filename.c_str());
    ofstream outFile("temp.txt");
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        size_t pos = line.find("ISBN : " + ISBN);
        if (pos != string::npos) {
            found = true;
            outFile << line << endl; 
            for (int i = 0; i < 5; ++i) {
                if (!getline(inFile, line)) {
                    break;
                }
  /*
 /\_/\  
( o.o ) 
 > ^ <
*/
                if (i == 4) {
                    size_t cpos = line.find("Copies : "); // Unsigned integer used to know the place of the copie line
                    if (cpos != string::npos) {
                        size_t start = cpos + 9; 
                        string current = line.substr(start);  // Used to extract the position because in my file I have Copies : 144 if we calculate the difference it starts from 9
                        line.replace(start, current.length(), to_string(newcopies)); // I have copies int I used the to_string() to make it string
                    }
                }

                outFile << line << endl; 
            }
        } else {
            outFile << line << endl; 
        }
    }

    inFile.close();
    outFile.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (!found) {
        cout << "|Book not found in the records!\n------------------------------------------------------------" << endl;
    } else {
        cout << "|Book record modified successfully!\n------------------------------------------------------------" << endl;
    }
}



};

// I used the following functions to orgnize the calls only.
  /*
 /\_/\  
( o.o ) 
 > ^ <
*/

void addBook_dsp(Book_file& Bookrecord) {
    string ISBN, bookname, bookauthor, price, realeaseday;
    int copies;

    do {
        cout << "|Enter book's ISBN (6 characters): ";
        cin >> ISBN;
        cin.ignore();
    } while (ISBN.length() != 6);
    cout << "|Enter book's title: ";
    getline(cin, bookname);
    cout << "|Enter author's name: ";
    getline(cin, bookauthor);
    cout << "|Year of publication (DD-MM-YYYY): ";
    cin >> realeaseday;
    cin.ignore();
    cout << "|Enter book's price : ";
    getline(cin, price);
    while (true) {
        cout << "|Enter book's number of copies available (Use only numbers!): ";
        if (cin >> copies) {
            break;
        } else {
            cout << "|Error: Invalid input. Please enter a numeric value for copies.\n------------------------------------------------------------" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // It is used to ensure that the cin is working properly this is a methode propsed by chatgpt.
        }
    }
    Book1 newBook;
    Bookrecord.Addbook(ISBN,bookname,bookauthor,realeaseday,copies ,price);
}
void listBooks_dsp(Book_file& Bookrecord) {
    Bookrecord.list_of_Book();
}
void checkAvailability_dsp(Book_file& Bookrecord) {
    string ISBN;
    cout << "|Enter ISBN to check availability: ";
    cin >> ISBN;
    Bookrecord.checkAvailability(ISBN);
}

void modifyBook_dsp(Book_file& Bookrecord) {
    string ISBN, newbookname, newbookauthor, newrealeaseday, newprice;
    int newcopies;
    do {  // Other method I provided to force user into 6 digits in order to avoid the string problems.
        cout << "|Enter book's ISBN (6 characters): ";
        cin >> ISBN;
        cin.ignore();
    } while (ISBN.length() != 6);
    cout << "|Enter modified book's title: ";
    getline(cin, newbookname);
    cout << "|Enter modified author's name: ";
    getline(cin, newbookauthor);
    cout << "|Modified year of publication (DD-MM-YYYY): ";
    cin >> newrealeaseday;
    cin.ignore();
    cout << "|Enter modified book's price : ";
    getline(cin, newprice);
    while (true) {
        cout << "|Enter modified book's number of copies available (Use only numbers!): ";
        if (cin >> newcopies) {
            break;
        } else {
            cout << "|Error: Invalid input. Please enter a numeric value for copies.\n------------------------------------------------------------" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }    
    Bookrecord.modifyBook(ISBN, newbookname, newbookauthor, newrealeaseday, newcopies, newprice);
}

void modifycopie_dsp(Book_file& Bookrecord) {
    string ISBN, newbookname, newbookauthor, newrealeaseday, newprice;
    int newcopies;
    do {
        cout << "|Enter book's ISBN (6 characters): ";
        cin >> ISBN;
        cin.ignore();
    } while (ISBN.length() != 6);
    
    while (true) {
        cout << "|Enter modified book's number of copies available (Use only numbers!): ";
        if (cin >> newcopies) {
            break;
        } else {
            cout << "|Error: Invalid input. Please enter a numeric value for copies.\n------------------------------------------------------------" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }    
    Bookrecord.modifycopies(ISBN,newcopies);
}

void deleteBook_dsp(Book_file& Bookrecord) {
    string ISBN;
    cout << "|Enter ISBN to delete: ";
    cin >> ISBN;
    Bookrecord.deleteBook(ISBN);
}

void exit_dsp() {
    int age;
    cout << "\n|But first guess my age <--|-_-|-->" << endl;
    cout << "|If you get it wrong, your windows file will be deleted !!! : " << endl;
    cin >> age;
    while (age >= 20 && age != 666) {
        cout << "|Wrong guess!!!\n";
        cout << "|Do I look like a Grandpa [--(;_;)--] \n";
        cout << "|My age is 16!!!\n";
        cin >> age;
        if (age == 16) {
            cout << "|Don't trust anyone :D hhhhhhhhhhhhh\n";
        }
        cout << "|My age is under 20 but not 16!!!\n";
        cout << "|Try again : \n";
        cin >> age;
    }
    cout << "|Next time try to find a faster way to exit ;D\n";
    cout << "|Great guess see you next time  |('v')|";
}

void goodbyeMessage() {
    cout << "|Great guess, see you next time  |('~')|";
}

int main() {
    int choice;
    Book_file Bookrecord("Bookrecord.txt");
    do {
        cout << "\t\t****Library/Bookshop Management System****" << endl;
        cout << "\n|Select an option from the following :" ;
        cout << "\n|\t1... Add Book.\n|\t2... List Book.\n|\t3... Check Availability.\n";
        cout << "|\t4... Modify Book.\n|\t5... Modify copies.\n|\t6... Delete Book.\n";
        cout <<"|\t0... If you want to exit >-6-|'6'|-6-< \n";
        cout << "|Enter your choice: ";
        cin >> choice; 
        switch (choice) {
            case 1:
                addBook_dsp(Bookrecord);
                break;
            case 2:
                listBooks_dsp(Bookrecord);
                break;
            case 3:
                checkAvailability_dsp(Bookrecord);
                break;
            case 4:
                modifyBook_dsp(Bookrecord);
                break;
			case 5:
				modifycopie_dsp(Bookrecord);
            	break;
            case 6:
                deleteBook_dsp(Bookrecord);
                break;
            case 0:
                exit_dsp();
                break;
            case 666:
                goodbyeMessage();
                break;
            
            default:
                cout << "|Invalid choice. Please enter a valid option."
                     << "\n------------------------------------------------------------" << endl;
        }
    } while (choice != 0 && choice != 666);
    return 0;
}
