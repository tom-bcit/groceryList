#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <stdio.h>
using namespace std;

class gradebook {
    map<string, string> data;
    public:void displayMenu() {
        cout << "\n\nGrocery List Main Menu" << endl;
        cout << "\n1) Add Item" << endl;
        cout << "2) Delete Item" << endl;
        cout << "3) Find Item" << endl;
        cout << "4) Display All" << endl;
        cout << "5) Save List" << endl;        
        cout << "6) Exit Application" << endl;
    }

    public:int getChoice() {
        int choice = 0;
        bool done = false;
        while (!done) {
            cout << "Enter selection: " << endl;
            cin >> choice;
            if (cin.fail()) {
                cout << "Wrong input, please enter a number" <<endl;
            } else {
                if (7 > choice > 0) {
                    done = true;
                } else {
                    cout << "Invalid number" << endl;
                }
            }
        }
        return choice;
    }

    public:void addGrocery() {
        string groceryName = "";
        string quantity = "";
        cout << "Enter grocery name: ";
        cin.ignore();
        getline (cin, groceryName);
        cout << "Enter quantity: ";
        getline (cin, quantity);
        data[groceryName] = quantity;
    }

    public:void deleteGrocery() {
        string groceryName = "";        
        cout << "Enter grocery name: " << endl;
        cin >> groceryName;
        if (data.find(groceryName) == data.end()) {
            cout << "Could not delete. Grocery does not exist." << endl;
        } else {
            data.erase(groceryName);
            cout << "\"";
            cout << groceryName;
            cout << "\" deleted successfully." << endl;
        }
    }

    public:void findGrocery() {
        string groceryName = "";
        cout << "Enter grocery name: " << endl;
        cin >> groceryName;
        map<string, string>::iterator counter = data.find(groceryName);
        if (counter == data.end()) {
            cout << "Could not find. Grocery does not exist." << endl;
        } else {
            string grocery = counter -> first;
            string quantity = counter -> second;
            cout << "\n\n\nGroceries           Amount" << endl;
            printf("%-20s%s\n", grocery.c_str(), quantity.c_str());
        }
    }

    public:void displayAll() {
        cout << "\n\n\nGroceries           Amount" << endl;
        map<string, string>::iterator iter;
        for (iter = data.begin(); iter != data.end(); ++iter) {
            string grocery = iter -> first;
            string quantity = iter -> second;
            printf("%-20s%s\n", grocery.c_str(), quantity.c_str());
        }
    }

    public:void save() {
        string selection = "";
        string tempSave = "";
        cout << "Save all current data? (y/n)" << endl;
        cin.ignore();
        getline (cin, selection);
        if (selection == "y") {
            tempSave += "{\n";
            map<string, string>::iterator iter;
            for (iter = data.begin(); iter != data.end(); ++iter) {
                tempSave += "\"" + iter -> first + "\": \"" + iter-> second + "\"";
                tempSave += ",\n";
            }
            if (!data.empty()) {
                tempSave.erase(tempSave.end()-2, tempSave.end());
            }
            tempSave += "\n}";
            ofstream MyFile("saved.txt");
            MyFile << tempSave;
            MyFile.close();
            cout << "List saved succesfully." << endl;
        }
    }    

    void parseJSON(string str) {
        str.erase(str.begin(), str.begin()+1);
        str.erase(str.end()-1);
        if (str != "") {
            string delimiter = ",";
            data = split(str, delimiter);
        }
    }

    map<string, string> split(string trimmed, string delimiter) {
        map<string, string> temp;
        vector<string> vec;
        size_t start = 0;
        size_t end = delimiter.length();
        size_t delimiter_length = delimiter.length();
        string token;
        while ((end = trimmed.find(delimiter, start)) != string::npos) {
            token = trimmed.substr(start, end - start);
            // "abc": "def"
            token.erase(token.begin());
            token.erase(token.end()-1);
            // abc": "def
            vec = splitSmall(token, "\": \"");
            
            start = end + delimiter_length;
            temp[vec.at(0)] = vec.at(1);
        }
        token = trimmed.substr(start);
        token.erase(token.begin());
        token.erase(token.end()-1);
        vec = splitSmall(token, "\": \"");
        temp[vec.at(0)] = vec.at(1);
        
        
        return temp;
    }

    vector<string> splitSmall(string pair, string delimiter) {
        vector<string> temp;
        size_t start = 0;
        size_t end = delimiter.length();
        size_t delimiter_length = delimiter.length();
        string token;
        while ((end = pair.find(delimiter, start)) != string::npos) {
            token = pair.substr(start, end - start);
            start = end + delimiter_length;
            temp.push_back(token);
        }
        token = pair.substr(start);
        temp.push_back(token);
        return temp;
    }

    int run() {
        string myText;
        string fullText;
        ifstream MyReadFile("saved.txt");
        while (getline (MyReadFile, myText)) {
            fullText += myText;
        }
        parseJSON(fullText);
        map<string ,string> :: iterator it;
        int choice = 0;
        do {
            displayMenu();
            choice = getChoice();
            switch(choice){
            case 1:
                addGrocery();
                break;
            case 2:
                deleteGrocery();
                break;
            case 3:
                findGrocery();
                break;
            case 4:
                displayAll();
                break;
            case 5:
                save();   
                break;             
        }
        } while (choice != 6);
        return 0;
    }
};

int main () {
    gradebook mygradebook;
    mygradebook.run();
}
