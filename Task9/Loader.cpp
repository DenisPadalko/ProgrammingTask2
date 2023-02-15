#include "Loader.h"
#include <fstream>
#include "Exceptions.h"

const vector<string>& ConsoleLoader::Load() const
{
    cout << "Enter data. Empty line will stop reading." << endl;
    vector<string>* Vec = new vector<string>();
    string Temp;
    while (true)
    {
        getline(cin, Temp);
        if(Temp.empty()) break;
        Vec->push_back(Temp);
        Temp.clear();
    }
    return *Vec;
}

const vector<string>& FileLoader::Load() const
{
    ifstream Input;
    Input.open("Input.txt", ios::in);
    if(!Input)
    {
        throw CannotOpenTheFileException("Error. File is not opened");
    }
    vector<string>* Vec = new vector<string>();
    string Temp;
    while(!Input.eof())
    {
        getline(Input, Temp);
        Vec->push_back(Temp);
        Temp.clear();
    }
    Input.close();
    return *Vec;
}
