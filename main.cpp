#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <algorithm>
using namespace std;

bool isValidName(const string &name)
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

void carRental()
{
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

    string carModels[3][3] = {
        {"Toyota Yaris", "Honda Civic", "Hyundai Accent"},
        {"Toyota Corolla", "Honda City", "Nissan Sentra"},
        {"Toyota Hiace", "Ford Transit", "Mercedes Sprinter"}};

    cout << "========================================\n";
    cout << "   WELCOME TO ADWA CAR RENTAL BOOKING SYSTEM  \n";
    cout << "========================================\n\n";

    // Number of people
    cout << "Enter number of people: ";
    while (!(cin >> numPeople) || numPeople <= 0)
    {
        cout << "Invalid input! Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer

    // Name validation
    cout << "Enter your full name: ";
    getline(cin, name);
    while (!isValidName(name))
    {
        cout << "Invalid! Name must contain only letters and spaces: ";
        getline(cin, name);
    }

    // Fayda ID validation
    cout << "Enter your 15-digit Fayda ID: ";
    cin >> faydaID;
    while (faydaID.length() != 15 ||
           !all_of(faydaID.begin(), faydaID.end(), ::isdigit))
    {
        cout << "Invalid! Fayda ID must be exactly 15 digits (numbers only): ";
        cin >> faydaID;
    }

    // Payment method
    cout << "Choose payment method (1 = Cash, 2 = Bank): ";
    while (!(cin >> paymentMethod) || (paymentMethod != 1 && paymentMethod != 2))
    {
        cout << "Invalid! Choose 1 (Cash) or 2 (Bank): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (paymentMethod == 2)
    {
        cout << "Bank Account Number: 10005676848\n";
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Payment calculation
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

int main()
{
    carRental();
    return 0;
}