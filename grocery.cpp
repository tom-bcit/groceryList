#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class gradebook {
    vector<string> data;
    public:void displayMenu() {
        cout << "\n\n1) Add" << endl;
        cout << "2) Delete" << endl;
        cout << "3) Find" << endl;
        cout << "4) Display All" << endl;
        cout << "5) Save" << endl;        
        cout << "6) Exit" << endl;
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
        cout << "Enter grocery name: ";
        cin.ignore();
        getline (cin, groceryName);
        data.push_back(groceryName);
    }

    public:void deleteGrocery() {
        string groceryName = "";        
        cout << "Enter grocery name: " << endl;
        cin >> groceryName;
        int index = search(groceryName);
        if (index == -1) {
            cout << "Could not delete. Grocery does not exist." << endl;
        } else {
            data.erase(data.begin() + index);
        }
    }

    public:void findGrocery() {
        string groceryName = "";
        cout << "Enter grocery name: " << endl;
        cin >> groceryName;
        int index = search(groceryName);
        if (index == -1) {
            cout << "Could not find. Grocery does not exist." << endl;
        } else {
            cout << "Details and options to go here" << endl;
        }
    }

    public:void displayAll() {
        cout << "Groceries: " << endl;
        for (string s: data) {
            cout << s << endl;
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
            for (string s: data) {
                tempSave += "\"" + s + "\"";
                tempSave += ",\n";
            }
            if (!data.empty()) {
                tempSave.erase(tempSave.end()-2, tempSave.end());
            }
            tempSave += "\n}";
            ofstream MyFile("filename.txt");
            MyFile << tempSave;
            MyFile.close();
            cout << "List saved succesfully." << endl;
        }
    }    

    int search(string str) {
        int counter = 0;
        for (string s : data) {
            if (s == str) {
                break;
            } else {
                counter++;
            }
        }
        if (counter == data.size()) {
            return -1;
        } else {
            return counter;
        }
    }

    void parseJSON(string str) {
        str.erase(str.begin(), str.begin()+1);
        str.erase(str.end()-1);
        string delimiter = ",";
        data = split(str, delimiter);
    }

    vector<string> split(string trimmed, string delimiter) {
        vector<string> temp;
        size_t start = 0;
        size_t end = delimiter.length();
        size_t delimiter_length = delimiter.length();
        string token;
        while ((end = trimmed.find(delimiter, start)) != string::npos) {
            token = trimmed.substr(start, end - start);
            start = end + delimiter_length;
            temp.push_back(token);
        }
        temp.push_back (trimmed.substr(start));
        for (auto i : temp) {
            cout << i;
        }
        return temp;
    }

    int run() {
        string myText;
        string fullText;
        ifstream MyReadFile("saved.dat");
        while (getline (MyReadFile, myText)) {
            fullText += myText;
        }
        cout << fullText;
        parseJSON(fullText);
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
