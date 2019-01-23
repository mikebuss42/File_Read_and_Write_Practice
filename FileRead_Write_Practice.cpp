/*
 Created by: Michael Busslinger
 Using: Xcode
 Written in: C++ Language
*/


#include <iostream>
#include <fstream>
#include <string>

using namespace std;


/*
        The function of this code is to ask the user for input
        to be added to the file which will be saved to writeFile.txt
        before closing the file.
 
        The file is then openned and the contents read before closing
        the file for the last time.
 */

int writeNames(int num)
{
    ofstream outputFile;
    string name[10];

    // Open (Create) the output file
    outputFile.open("writeFile.txt");
    
    cout << "----------------------------" << endl;
    cout << "  Writing data to the file  " << endl;
    cout << "----------------------------" << endl;

    // Ask the user to input the names of the people
    cout << "Enter the names of the " << num << " people. " << endl;
    for (int i = 0; i < num; i++)
    {
        cout << "Name: ";
        cin >> name[i];
    }

    // Now write the names into the file
    for (int j = 0; j < num; j++)
    {
        outputFile << name[j] << endl;
    }

    // Close the file
    outputFile.close();

    cout << "----------------------------------" << endl;
    cout << " The names were saved to the file " << endl;
    cout << "----------------------------------" << endl;

    return -1;
}

int readNames(int num)
{
    ifstream inputFile;
    string name[10];
    
    // Open the input file
    inputFile.open("writeFile.txt");
    cout << endl;
    cout << "------------------------------" << endl;
    cout << "  Reading data from the file  " << endl;
    cout << "------------------------------" << endl;

    for (int k = 0; k < num; k++)
    {
        inputFile >> name[k];
        cout << name[k] << endl;
    }
    
    // ALWAYS remember to close the file
    inputFile.close();
    
    cout << "----------------------------" << endl;
    cout << "      Closing the file.     " << endl;
    cout << "----------------------------" << endl;

    return -1;
}

int main()
{
    int num;
    cout << "----------------------------------------------------" << endl;
    cout << " ***** This is a simple READ and WRITE program *****" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << endl;
    cout << "How many people do you want to enter: ";
    cin >> num;
    cout << endl;
    cout << writeNames(num);
    cout << readNames(num);
}
