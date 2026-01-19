#include <iostream>
#include <string>

using namespace std;

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

    const int pricePerHour = 800;
    const int lateFeePerHour = 300;

    // Car models categorized by seating capacity
    string carModels[3][3] = {
        {"Toyota Yaris", "Honda Civic", "Hyundai Accent"},    // 1–3 people
        {"Toyota Corolla", "Honda City", "Nissan Sentra"},    // 4 people
        {"Toyota Hiace", "Ford Transit", "Mercedes Sprinter"} // 5+ people
    };

    cout << "========================================\n";
    cout << "   WELCOME TO CAR RENTAL BOOKING SYSTEM  \n";
    cout << "========================================\n\n";

    // -------------------- Input Section --------------------

    // Number of people
    cout << "Enter number of people: ";
    cin >> numPeople;
    while (numPeople <= 0)
    {
        cout << "Invalid! Enter a positive number: ";
        cin >> numPeople;
    }

    cin.ignore();
    cout << "Enter your full name: ";
    getline(cin, name);

    // Fayda ID validation
    cout << "Enter your 15-digit Fayda ID: ";
    cin >> faydaID;
    while (faydaID.length() != 15)
    {
        cout << "Invalid! Fayda ID must be exactly 15 digits: ";
        cin >> faydaID;
    }

    // Payment method validation
    cout << "Choose payment method (1 = Cash, 2 = Bank): ";
    cin >> paymentMethod;
    while (paymentMethod != 1 && paymentMethod != 2)
    {
        cout << "Invalid! Choose 1 (Cash) or 2 (Bank): ";
        cin >> paymentMethod;
    }

    if (paymentMethod == 2)
    {
        cout << "Bank Account Number: 10005676848\n";
    }

    // Rental hours
    cout << "Enter number of rental hours: ";
    cin >> rentalHours;
    while (rentalHours <= 0)
    {
        cout << "Invalid! Hours must be positive: ";
        cin >> rentalHours;
    }

    // -------------------- Car Selection --------------------
    cout << "\nAvailable Cars:\n";

    int category;
    if (numPeople <= 3)
    {
        category = 0;
    }
    else if (numPeople == 4)
    {
        category = 1;
    }
    else
    {
        category = 2;
    }

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
    cin >> lateHours;
    while (lateHours < 0)
    {
        cout << "Invalid! Late hours cannot be negative: ";
        cin >> lateHours;
    }

    totalAmount += lateHours * lateFeePerHour;

    // -------------------- Output Section --------------------
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