#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <limits>

using namespace std;
bool isValidName(string &name)
{
    if (name.empty())
        return false;
    for (char c : name)
    {
        unsigned char uc = static_cast<unsigned char>(c);
        if (!isalpha(uc) && !isspace(uc))
        {
            return false;
        }
    }
    return true;
}
/*
    Function Name : carRental
    Type          : void function
    Purpose       : Simulates a car rental booking system
*/
void carRental()
{

    // -------------------- Variable Declaration --------------------
    int numPeople;
    int paymentMethod;
    int rentalHours;
    int carChoice;
    int lateHours;
    double totalAmount;

    string name;
    string faydaID;
    string paymentMethodStr;

    const int pricePerHour = 800;
    const int lateFeePerHour = 300;

    // Car models categorized by seating capacity
    string carModels[3][3] = {
        {"Toyota Yaris", "suzuki", "vitz"},             // 1–3 people
        {"Toyota Corolla", "atoz", "Nissan Sentra"},    // 4 people
        {"jetour", "Ford Transit", "Mercedes Sprinter"} // 5+ people
    };

    cout << "========================================\n";
    cout << "   WELCOME TO ADWA CAR RENTAL BOOKING SYSTEM  \n";
    cout << "========================================\n\n";

    // -------------------- Input Section --------------------

    // Number of people
    cout << "Enter number of people: ";
    while (!(cin >> numPeople) || numPeople <= 0)
    {
        cout << "Invalid input! Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
                                                         // name validation
    cout << "Enter your full name: ";
    getline(cin, name);
    while (!isValidName(name))
    {
        cout << "invaild! the name must only contain letters and spaces: ";
        getline(cin, name);
    }

    // Fayda ID validation
    cout << "Enter your 16-digit Fayda ID: ";
    cin >> faydaID;
    while (
        faydaID.length() != 16 ||

        !all_of(faydaID.begin(), faydaID.end(),
                [](char c)
                { return isdigit(static_cast<unsigned char>(c)); }))
    {

        cout << "Invalid! Fayda ID must be exactly 16 digits (numbers only): ";
        cin >> faydaID;
    }

    // Payment method validation
    const string banks[7] = {
        "Commercial Bank of Ethiopia",
        "Dashen Bank",
        "Awash Bank",
        "Abyssinia Bank",
        "NIB International Bank",
        "Wegagen Bank",
        "United Bank"};

    cout << "\n--- PAYMENT OPTIONS ---\n";
    if (true)
    {
        cout << "1. TeleBirr\n";
        for (int i = 0; i < 7; i++)
        {
            cout << (i + 2) << ". " << banks[i] << "\n";
        }
        cout << "Choose (1-8): ";
    }
    else
    {
        for (int i = 0; i < 7; i++)
        {
            cout << (i + 1) << ". " << banks[i] << "\n";
        }
        cout << "Choose (1-7): ";
    }

    int payChoice;
    cin >> payChoice;

    if (true)
    {
        if (payChoice == 1)
        {
            paymentMethodStr = "TeleBirr";
        }
        else if (payChoice >= 2 && payChoice <= 8)
        {
            paymentMethodStr = banks[payChoice - 2];
        }
        else
        {
            cout << "Invalid choice! Using TeleBirr.\n";
            paymentMethodStr = "TeleBirr";
        }
    }
    else
    {
        if (payChoice >= 1 && payChoice <= 7)
        {
            paymentMethodStr = banks[payChoice - 1];
        }
        else
        {
            cout << "Invalid choice! Using Commercial Bank of Ethiopia.\n";
            paymentMethodStr = banks[0];
        }
    }

    // Rental hours
    cout << "Enter number of rental hours: ";
    while (!(cin >> rentalHours) || rentalHours <= 0)
    {
        cout << "Invalid! Hours must be positive: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Car selection
    cout << "\nAvailable Cars:\n";
    int category = (numPeople <= 3) ? 0 : (numPeople == 4 ? 1 : 2);
    for (int i = 0; i < 3; i++)
    {
        cout << i + 1 << ". " << carModels[category][i] << endl;
    }

    cout << "Choose a car (1-3): ";
    while (!(cin >> carChoice) || carChoice < 1 || carChoice > 3)
    {
        cout << "Invalid choice! Choose 1-3: ";
        cin.clear();

        // -------------------- Car Selection --------------------
        cout << "\nAvailable Cars:\n";

        int category;
        if (numPeople <= 3)
            category = 0;
        else if (numPeople == 4)
            category = 1;
        else
            category = 2;

        for (int i = 0; i < 3; i++)
        {
            cout << i + 1 << ". " << carModels[category][i] << endl;
        }

        cout << "Choose a car (1-3): ";
        cin >> carChoice;
        while (carChoice < 1 || carChoice > 3)
        {
            cout << "Invalid choice! Choose 1-3: ";
            cin >> carChoice;
        }

        // -------------------- Payment Calculation --------------------
        totalAmount = rentalHours * pricePerHour;
        cout << "\nDid you return the car late? (Enter late hours, 0 if none): ";
        while (!(cin >> lateHours) || lateHours < 0)
        {
            cout << "Invalid! Late hours cannot be negative: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        totalAmount += lateHours * lateFeePerHour;

        // Output
        cout << "\n========= RENTAL SUMMARY =========\n";
        cout << "Renter Name      : " << name << endl;
        cout << "Fayda ID         : " << faydaID << endl;
        cout << "People           : " << numPeople << endl;
        cout << "Selected Car     : " << carModels[category][carChoice - 1] << endl;
        cout << "Rental Hours     : " << rentalHours << endl;
        cout << "Rate per Hour    : " << pricePerHour << " birr\n";
        cout << "Late Fee         : " << lateHours * lateFeePerHour << " birr\n";
        cout << "TOTAL PAYMENT    : " << totalAmount << " birr\n";

        cout << "\nPolicies:\n";
        cout << "- Damage cost is paid by renter\n";
        cout << "- Late return fee: " << lateFeePerHour << " birr per hour\n";
        cout << "- Bring Fayda ID and receipt if paid via bank\n";

        cout << "\nThank you for using our service!\n";
    }

    // -------------------- Main Function --------------------
    int main()
    {
        carRental();
        return 0;
    }
}