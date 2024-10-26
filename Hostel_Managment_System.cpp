#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const string RESET_COLOR = "\033[0m";   // Reset color to default
const string RED_TEXT = "\033[1;31m";   // Red text color
const string GREEN_TEXT = "\033[1;32m"; // Green text color
const string YELLOW_TEXT = "\033[33m";  // Yellow background color
const string WHITE_BG = "\033[47m";     // White background color
const string CYAN_TEXT = "\033[36m";    // Cyan background color
const string BLUE_TEXT = "\033[34m";    // Blue background color.
const string RED_BG = "\033[41m";       // Blue background color604
const string WHITE_TEXT = "\033[97m";   // white text color

const string USERNAME = "admin";
const string PASSWORD = "123456";

// Structure to represent a room records
struct RoomRecord
{
    string roomNumber;
    string name;
    string address;
    string phoneNumber;
    string nationality;
    string arrivalDate;
};

// Function to display the main menu
void displayMenu()
{
    cout << RED_TEXT << "--------- Room Booking System ---------" << RESET_COLOR << endl
         << endl;
    cout << CYAN_TEXT << "1. Book a Room" << endl;
    cout << "2. View Records" << endl;
    cout << "3. Delete a Record" << endl;
    cout << "4. Search a Record" << endl;
    cout << "5. Edit a Record" << endl;
    cout << "6. Exit" << RESET_COLOR << endl
         << endl;
    cout << RED_TEXT << "---------------------------------------" << RESET_COLOR << endl
         << endl;
}

// Function to book a room and save the record
void bookRoom(RoomRecord &record)
{
    cout << YELLOW_TEXT << "Enter Room Number: " << RESET_COLOR;
    cin.ignore();
    getline(cin, record.roomNumber);
    cout << YELLOW_TEXT << "Enter Name: " << RESET_COLOR;
    cin.ignore(); // add this line
    getline(cin, record.name);
    cout << YELLOW_TEXT << "Enter Address: " << RESET_COLOR;
    cin.ignore(); // add this line
    getline(cin, record.address);
    string enteredPhoneNumber;
    cout << YELLOW_TEXT << "Enter Phone Number: " << RESET_COLOR;
    cin >> enteredPhoneNumber;

    while (enteredPhoneNumber.length() != 10)
    {
        cout << GREEN_TEXT<< "Invalid phone number."<<RESET_COLOR<<"\n"<<YELLOW_TEXT<< "Please enter a 10-digit phone number:" <<RESET_COLOR;
        cin >> enteredPhoneNumber;
    }
    record.phoneNumber = enteredPhoneNumber;
    cout << YELLOW_TEXT << "Enter Nationality: " << RESET_COLOR;
    cin.ignore(); // add this line
    getline(cin, record.nationality);
    cout << YELLOW_TEXT << "Enter Arrival Date (dd/mm/yyyy): " << RESET_COLOR;
    cin.ignore(); // add this line

    
    getline(cin, record.arrivalDate);
}

// Function to save a record to a file
void saveRecord(const RoomRecord &record)
{
    ofstream file("room_records.txt", ios::app);
    if (file.is_open())
    {
        file << record.roomNumber << "," << record.name << "," << record.address << ","
             << record.phoneNumber << "," << record.nationality << ", " << record.arrivalDate << endl;
        file.close();
        cout << GREEN_TEXT << endl
             << "Record has been saved." << endl
             << endl;
    }
    else
    {
        cout << "Error: Unable to open the file." << RESET_COLOR << endl;
    }
}

// Function to display records in tabular form
void viewRecords()
{
    ifstream file("room_records.txt");
    if (file.is_open())
    {
        cout << RED_TEXT << "---------------------------------------------------------------------------------------" << RESET_COLOR << endl;

        cout << CYAN_TEXT << left << setw(12) << "Room No." << setw(15) << "Name" << setw(15) << "Address"
             << setw(15) << "Phone No." << setw(15) << "Nationality"
             << setw(15) << "Arrival Date" << RESET_COLOR << endl;
        cout << RED_TEXT << "---------------------------------------------------------------------------------------" << RESET_COLOR << endl
             << endl;

        RoomRecord record;
        while (getline(file, record.roomNumber, ','))
        {
            getline(file, record.name, ',');
            getline(file, record.address, ',');
            getline(file, record.phoneNumber, ',');
            getline(file, record.nationality, ',');
            file.ignore();
            getline(file, record.arrivalDate);

            cout << RED_BG << WHITE_TEXT << left << setw(12) << record.roomNumber << setw(15) << record.name << setw(15) << record.address << setw(15) << record.phoneNumber << setw(15) << record.nationality << setw(15) << record.arrivalDate << RESET_COLOR << endl
                 << endl;
        }

        file.close();
    }
    else
    {
        cout << "Error: Unable to open the file." << endl;
    }
}

// Function to delete a record by room number
void deleteRecord()
{
    string roomToDelete;
    cout << YELLOW_TEXT << "Enter the Room Number to delete: " << RESET_COLOR;
    cin.ignore();
    getline(cin, roomToDelete);

    ifstream file("room_records.txt");
    if (!file.is_open())
    {
        cout << "Error: Unable to open the file." << endl;
        return;
    }

    ofstream tempFile("temp.txt");
    bool found = false;
    string line;

    while (getline(file, line))
    {
        string roomNumber = line.substr(0, line.find(","));
        if (roomNumber != roomToDelete)
        {
            tempFile << line << endl;
        }
        else
        {
            found = true;
        }
    }

    file.close();
    tempFile.close();

    if (found)
    {
        remove("room_records.txt");
        rename("temp.txt", "room_records.txt");
        cout << GREEN_TEXT << endl
             << "Record deleted successfully." << RESET_COLOR << endl
             << endl;
    }
    else
    {
        cout << GREEN_TEXT << endl
             << "Record not found." << RESET_COLOR << endl
             << endl;
    }
}

// Function to search a record by room number
void searchRecord()
{
    string roomToSearch;
    cout << YELLOW_TEXT << "Enter the Room Number to search: " << RESET_COLOR;
    cin.ignore();
    getline(cin, roomToSearch);

    ifstream file("room_records.txt");
    if (!file.is_open())
    {
        cout << "Error: Unable to open the file." << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line))
    {
        string roomNumber = line.substr(0, line.find(","));
        if (roomNumber == roomToSearch)
        {
            cout << GREEN_TEXT << endl
                 << "Record found." << RESET_COLOR << endl
                 << endl;

            cout << RED_BG << line << RESET_COLOR << endl
                 << endl;
            found = true;
        }
    }

    file.close();

    if (!found)
    {
        cout << GREEN_TEXT << endl
             << "Record not found." << RESET_COLOR << endl
             << endl;
    }
}

// Function to edit a record by room number
void editRecord()
{
    string roomToEdit;
    cout << YELLOW_TEXT << "Enter the Room Number to edit: " << RESET_COLOR;
    cin.ignore();
    getline(cin, roomToEdit);

    cout << endl;

    ifstream file("room_records.txt");
    if (!file.is_open())
    {
        cout << "Error: Unable to open the file." << endl;
        return;
    }

    ofstream tempFile("temp.txt");
    string line;
    bool found = false;

    while (getline(file, line))
    {
        string roomNumber = line.substr(0, line.find(","));
        if (roomNumber == roomToEdit)
        {
            RoomRecord record;
            record.roomNumber = roomToEdit;
            bookRoom(record);   // Prompt for updated data
            saveRecord(record); // Save the updated data
            found = true;
        }
        else
        {
            tempFile << line << endl;
        }
    }

    file.close();
    tempFile.close();

    if (found)
    {
        remove("room_records.txt");
        rename("temp.txt", "room_records.txt");
        cout << GREEN_TEXT << "Record edited successfully." << RESET_COLOR << endl
             << endl;
    }
    else
    {
        cout << GREEN_TEXT << "Record not found." << RESET_COLOR << endl
             << endl;
    }
}

int main()
{
    string username, password;

    cout << RED_TEXT << "Welcome to the Hostel Management System" << RESET_COLOR << endl
         << endl;

    // Prompt for username and password
    cout << YELLOW_TEXT << "Username: " << RESET_COLOR;
    cin >> username;
    cout << YELLOW_TEXT << "Password: " << RESET_COLOR;
    cin >> password;

    // Check if the entered username and password are correct
    if (username == USERNAME && password == PASSWORD)
    {
        cout << GREEN_TEXT << endl
             << "Login successful. You have access to the menu." << RESET_COLOR << endl
             << endl;

        int choice;
        RoomRecord record;

        while (true)
        {
            displayMenu();
            cout << YELLOW_TEXT << "Enter your choice: " << RESET_COLOR;
            cin >> choice;
            cout << endl;

            switch (choice)
            {
            case 1:
                bookRoom(record);
                saveRecord(record);
                break;
            case 2:
                viewRecords();
                break;
            case 3:
                deleteRecord();
                break;
            case 4:
                searchRecord();
                break;
            case 5:
                editRecord();
                break;
            case 6:
                cout << WHITE_BG << "Goodbye!" << RESET_COLOR << endl
                     << endl;
                return 0;
            default:
                cout << GREEN_TEXT << "Invalid choice. Try again." << RESET_COLOR << endl
                     << endl;
            }
        }

        return 0;
    }
    else
    {
        cout << GREEN_TEXT << endl
             << "Login failed. Access denied." << RESET_COLOR << endl
             << endl;
    }

    return 0;
}