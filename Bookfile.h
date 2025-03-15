#include <iostream>
#include <string>
#include <fstream> 
#include <limits>
#include "Book.h"


using namespace std;


class Bookfile {
private:
    string filename;

public:
    Bookfile(const string& filename) : filename(filename) {}
    

    void Addbook(const Book& book) {
        if (book.getISBN().length() != 6) {
            cerr << "|Error: ISBN must be exactly 6 digits." << "\n------------------------------------------------------------" << endl;
            return;
    }	
    	ifstream checkFile(filename.c_str());
        string line;
        while (getline(checkFile, line)) {
            size_t pos = line.find("ISBN : " + book.getISBN());
            if (pos != string::npos) {
                cout << "|Error: A book with the same ISBN already exists.If you want to modify a bookrecord alreadi existing try 4!!\n" << "------------------------------------------------------------------------------------------------------------------------" << endl;
                checkFile.close();
                return;
        }
    }
    checkFile.close();
        ofstream outFile(filename.c_str(), ios::app);
        if (!outFile.is_open()) {
            cerr << "|Error: Could not open the file." << "\n------------------------------------------------------------" << endl;
            return;
        }
        outFile << "ISBN : " << book.getISBN() << "\nTitle : " << book.getbookname() << "\nAuthor : " << book.getbookauthor() << "\nDate : " << book.getrealeaseday() << "\nPrice : " << book.getprice() << "\nCopies : " << book.getcopies() << "\n------------------------------------------------------------" << endl;
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
    
    void checkAvailability(const string& ISBN) {
        ifstream inFile(filename.c_str());
        string line;
        bool found = false;
        while (getline(inFile, line)) {
            size_t pos = line.find(ISBN);
            if (pos != string::npos) {
                found = true;
                cout << "|Book available!\n" ;
				cout << "------------------------------------------------------------" << endl;
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
 
    void modifyBook(const string& ISBN, const string& newbookname, const string& newbookauthor, const string& newrealeaseday, const int& newcopies, const string& newprice) {	
	if (ISBN.length() != 6) {
        cout << "|Error: ISBN must have exactly 6 characters.\n------------------------------------------------------------" << endl;
        return;
    }
	ifstream inFile(filename.c_str());
    ofstream outFile("temp.txt");
    string line;
    bool found = false;
    while (getline(inFile, line)) {
        size_t pos = line.find(ISBN);
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
    inFile.seekg(0, ios::beg);
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
    rename("temp.txt", filename.c_str());
    if (found) {
        cout << "|Book record modified successfully!\n" << "------------------------------------------------------------" << endl;;
   }
}
    
    void deleteBook(const string& ISBN) {
    if (ISBN.length() != 6) {
        cout << "|Error: ISBN must have exactly 6 characters.\n------------------------------------------------------------" << endl;
        return;
    }	
    ifstream inFile(filename.c_str());
    ofstream outFile("temp.txt");
    string line;
    bool found = false;
    while (getline(inFile, line)) {
        size_t pos = line.find(ISBN);
        if (pos != string::npos) {
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "|Book not found in the records!\n------------------------------------------------------------" << endl;
        inFile.close();
        outFile.close();
        return;
    }
    inFile.seekg(0, ios::beg);
    while (getline(inFile, line)) {
        size_t pos = line.find(ISBN);
        if (pos != string::npos) {
            cout << "|Book found. Are you sure you want to delete? (Y/N): ";
            char choice;
            cin >> choice;
            if (toupper(choice) == 'Y' || choice == 'y') {
                cout << "|Book deleted successfully!\n------------------------------------------------------------" << endl;
            } else {
                cout << "|You cancelled deletion.\n------------------------------------------------------------" << endl;
            }
            for (int i = 0; i < 6; ++i) {
                if (!getline(inFile, line)) {
                    break;
                }
            }
        } else {
            outFile << line << endl;
        }
    }
    inFile.close();
    outFile.close();
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
}

};
