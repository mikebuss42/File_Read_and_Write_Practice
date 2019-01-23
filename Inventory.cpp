/*
 Created by: Michael Busslinger
 Using: Xcode
 Written in: C++ Language
*/

/*
            This program is an Inventory program that creates an
            inventory.txt file from scratch which you can add items
            and edit their information.
*/

/*
 CURRENT PROBLEMS:
            1) Program creates inventory.txt file which you use but
            deletes the file upon quitting.
            2) Program can only use "New Item" once. If used again,
            it erases all information of the other inventory items.
*/

#include <iostream>
#include <fstream>

using namespace std;

const int DESC_SIZE = 31;
int NUM_RECORDS = 0;

// -------------------------------------------------------------------------------------//

struct Inventory
{
    char desc[DESC_SIZE];
    int quantity;
    double price;
    
};
// -------------------------------------------------------------------------------------//
void printWelcome()
{
    cout << "**************************************" << endl;
    cout << "   Welcome to the Inventory Program   " << endl;
    cout << "**************************************" << endl;
}


// -------------------------------------------------------------------------------------//

void printMenu()
{
    cout << "------------" << endl;
    cout << "*** Menu ***" << endl;
    cout << "------------" << endl;
    cout << "N: New Item" << endl;
    cout << "D: Display Inventory" << endl;
    cout << "E: Edit Existing Item" << endl;
    cout << "Q: Quit" << endl;
    cout << "-> ";
}

// -------------------------------------------------------------------------------------//

int inventoryAdd(int num, int current)
{
    Inventory record = { "", 0, 0.0 };
    //  Create file object and open file
    fstream inventory("inventory.dat", ios::out | ios::binary);
    if (!inventory)
    {
        cout << "Error opening file." << endl;
        return 0;
    }
    
    //  Now write the blank records
    for (int count = current; count < NUM_RECORDS; count++)
    {
        cout << endl << "Item(s) added. " << endl << endl;
        inventory.seekp(count * sizeof(record), ios::beg);
        cout << "Description: ";
        cin.ignore();
        cin.getline(record.desc, DESC_SIZE);
        
        cout << "Quantity: ";
        cin >> record.quantity;
        
        cout << "Price: $";
        cin  >> record.price;
        inventory.seekp(count * sizeof(record), ios::beg);
        inventory.write(reinterpret_cast<char *>(&record), sizeof(record));

    }
    
    //  Close the file
    inventory.close();
    return -1;
}

// -------------------------------------------------------------------------------------//
int inventoryDisplay()
{
    Inventory record;
    
    //  Create and open the file for reading
    fstream inventory("inventory.dat", ios::in | ios::binary);
    if (!inventory)
    {
        cout << "Error in opening the file. File is empty or doesn't exist." << endl;
        return 0;
    }
    
    if (NUM_RECORDS == 0)
    {
        cout << endl;
        cout <<"----------------------" << endl;
        cout <<"*** File is empty! ***" << endl;
        cout <<"----------------------" << endl << endl;
        return 0;
    }

    //  Now read and display the records
    inventory.read(reinterpret_cast<char *>(&record), sizeof(record));
    
    while (!inventory.eof())
    {
        cout << "---------------------------" << endl;
        cout << "********  RECORDS  ********" << endl;
        cout << "---------------------------" << endl;
        
        for (int i = 0; i < NUM_RECORDS; i++)
        {
            cout << "--------------" << endl;
            cout << "Item " << i << endl;
            cout << "Description: ";
            cout << record.desc << endl;

            cout << "Quantity: ";
            cout << record.quantity << endl;
    
            cout << "Price: $";
            cout << record.price << endl;
            cout << "--------------" << endl;
            inventory.read(reinterpret_cast<char *>(&record), sizeof(record));
        }
        
        cout << "---------------------------" << endl;
        cout << "*****  END OF RECORD  *****" << endl;
        cout << "---------------------------" << endl;
    }
    
    //  Close the file
    inventory.close();
    return -1;
}
// -------------------------------------------------------------------------------------//

int inventoryEdit()
{
    Inventory record;
    long recNum;
    
    //  Open the file
    fstream inventory("inventory.dat", ios::in | ios::out | ios::binary);
    
    if (!inventory)
    {
        cout << "Error opening file." << endl;
        return 0;
    }
    
    //  Move to the desired record and read it into record
    cout << "Which item do you want to edit?" << endl;
    cout << "-> ";
    cin >> recNum;
    inventory.seekg(recNum * sizeof(record), ios::beg);
    inventory.read(reinterpret_cast<char *>(&record), sizeof(record));
    
    //  Get new data from user and edit in-memory record
    cout << "Description: ";
    cout << record.desc << endl;
    
    cout << "Quantity: ";
    cout << record.quantity << endl;
    
    cout << "Price: $";
    cout << record.price << endl;
    
    cout << "Enter the new data: " << endl;
    cout << "Description: ";
    cin.ignore();
    cin.getline(record.desc, DESC_SIZE);
    
    cout << "Quantity: ";
    cin >> record.quantity;
    
    cout << "Price: $";
    cin  >> record.price;
    
    //  Move to the right place in the file and write the record
    inventory.seekp(recNum * sizeof(record), ios::beg);
    inventory.write(reinterpret_cast<char *>(&record), sizeof(record));
    
    //  Close the file
    inventory.close();
    
    return -1;
}

// -------------------------------------------------------------------------------------//

int main()
{
    int num;
    int current;
    char input;
    printWelcome();
    printMenu();
    cin >> input;
    while (input != 'Q' && input != 'q')
    {
        switch(input)
        {
            case 'n':
            case 'N':
                cout << "Enter number of items: ";
                cin >> num;
                current = NUM_RECORDS;
                NUM_RECORDS+=num;
                inventoryAdd(num, current);
                
                break;
            case 'd':
            case 'D':
                inventoryDisplay();
                break;
            case 'e':
            case 'E':
                inventoryEdit();
                break;
                
            default:
                cout << "Error. Try Again." << endl;
        }
        printMenu();
        cin >> input;
    }
    cout << endl;
    cout << "*********************************" << endl;
    cout << "             Goodbye.            " << endl;
    cout << "*********************************" << endl;
    
    return 0;
}
