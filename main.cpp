#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

struct Car
{
    string model;
    string category;
    int maxPassengers;
    double hourlyRate;
    double dailyRate;
    bool available;
};

// Ethiopian banks
string banks[7] = {
    "Commercial Bank of Ethiopia",
    "Dashen Bank",
    "Awash Bank",
    "Abyssinia Bank",
    "NIB International Bank",
    "Wegagen Bank",
    "United Bank"};

// Ethiopian cities
string ethiopianCities[10] = {
    "Addis Ababa",
    "Dire Dawa",
    "Hawassa",
    "Mekelle",
    "Bahir Dar",
    "Jimma",
    "Adama (Nazret)",
    "Dessie",
    "Adwa",
    "Gondar"};

// Validate 16-digit FAN (spaces allowed)
bool isValidFAN(string id)
{
    // Remove spaces
    id.erase(remove(id.begin(), id.end(), ' '), id.end());
    if (id.length() != 16)
        return false;
    for (int i = 0; i < 16; i++)
    {
        if (!isdigit(id[i]))
            return false;
    }
    return true;
}

// Mask FAN: show only last 4 digits
string maskFAN(string fan)
{
    // Remove spaces first
    fan.erase(remove(fan.begin(), fan.end(), ' '), fan.end());
    if (fan.length() != 16)
        return "INVALID";
    return "************" + fan.substr(12, 4);
}

bool isValidEmail(string email)
{
    size_t at = email.find('@');
    size_t dot = email.rfind('.');
    return at != string::npos && dot != string::npos && at < dot && at > 0 && dot > at + 1;
}

string toLower(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}

int main()
{
    cout << "===============================\n";
    cout << "WELCOME TO ADWA CAR RENTAL SYSTEM\n";
    cout << "===============================\n\n";

    const int CAR_COUNT = 6;
    Car cars[CAR_COUNT] = {
        {"Toyota Yaris", "Hatchback", 5, 120, 900, true},
        {"Toyota Corolla", "Sedan", 5, 180, 1200, true},
        {"Hyundai Tucson", "SUV", 7, 250, 1800, true},
        {"Mitsubishi Pajero", "SUV", 7, 350, 2500, true},
        {"Toyota Hiace", "Van", 14, 500, 3500, true},
        {"Toyota Hilux", "Pickup", 5, 300, 2000, true}};

    int passengers;
    cout << "How many passengers (including driver)? ";
    cin >> passengers;
    cin.ignore();
    while (passengers <= 0)
    {
        cout << "Invalid! Enter again: ";
        cin >> passengers;
    }
    cin.ignore();
    int choices[CAR_COUNT];
    int choiceCount = 0;
    cout << "\nAvailable cars for " << passengers << " people:\n";
    cout << "----------------------------------------\n";
    for (int i = 0; i < CAR_COUNT; i++)
    {
        if (cars[i].available && cars[i].maxPassengers >= passengers)
        {
            cout << (choiceCount + 1) << ". " << cars[i].category
                 << " - " << cars[i].model
                 << " (" << cars[i].maxPassengers << " seats)\n";
            choices[choiceCount] = i;
            choiceCount++;
        }
    }
    if (choiceCount == 0)
    {
        cout << "No cars available.\n";
        return 0;
    }
    int userChoice;
    cout << "\nChoose a car (1-" << choiceCount << "): ";
    cin >> userChoice;
    cin.ignore();
    while (userChoice < 1 || userChoice > choiceCount)
    {
        cout << "Invalid! Choose again: ";
        cin >> userChoice;
    }
    cin.ignore();
    Car *chosenCar = &cars[choices[userChoice - 1]];

    cout << "\n--- RENTAL OPTIONS ---\n";
    cout << "1. Hourly Rental (min 4 hours)\n";
    cout << "2. Daily Rental (min 1 day)\n";
    cout << "Choose (1 or 2): ";
    int rentalType;
    cin >> rentalType;
    cin.ignore();
    while (rentalType != 1 && rentalType != 2)
    {
        cout << "Invalid choice! Enter 1 or 2: ";
        cin >> rentalType;
    }
    cin.ignore();

    int quantity;
    double baseCost = 0;
    string unit;
    if (rentalType == 1)
    {
        cout << "Enter rental duration in hours (min 4): ";
        cin >> quantity;
        cin.ignore();
        while (quantity < 4)
        {
            cout << "Minimum 4 hours required. Enter again: ";
            cin >> quantity;
        }
        cin.ignore();
        baseCost = chosenCar->hourlyRate * quantity;
        unit = "hour(s)";
    }
    else
    {
        cout << "Enter rental duration in days (min 1): ";
        cin >> quantity;
        cin.ignore();
        while (quantity < 1)
        {
            cout << "Minimum 1 day required. Enter again: ";
            cin >> quantity;
        }
        cin.ignore();
        baseCost = chosenCar->dailyRate * quantity;
        unit = "day(s)";
    }

    cout << "\n--- LATE RETURN POLICY ---\n";
    if (rentalType == 1)
    {
        cout << "• 20% extra per additional hour\n";
    }
    else
    {
        cout << "• 50% extra per additional day\n";
    }
    cout << "• Full damage protection available for 10% extra fee\n";
    cout << "Add damage protection? (Yes or No): ";
    string damageInput;
    getline(cin, damageInput);
    bool addInsurance = (toLower(damageInput) == "yes");
    double insuranceCost = addInsurance ? baseCost * 0.10 : 0;
    double totalBeforeDiscount = baseCost + insuranceCost;

    double discount = 0;
    if (rentalType == 2)
    {
        if (quantity >= 30)
        {
            discount = baseCost * 0.20;
            cout << "\n 20% monthly discount applied!\n";
        }
        else if (quantity >= 7)
        {
            discount = baseCost * 0.10;
            cout << "\n 10% weekly discount applied!\n";
        }
    }
    double finalTotal = totalBeforeDiscount - discount;

    // FAN INPUT WITH HINT & SPACE TOLERANCE
    string name, fan, email;
    cout << "\n--- CUSTOMER INFORMATION ---\n";
    cout << "Full name: ";
    getline(cin, name);

    cout << "National ID (FAN - 16 digits)\n";
    cout << "Enter as: XXXX XXXX XXXX XXXX\n"; // Helpful hint
    getline(cin, fan);

    // Validate FAN (allow spaces)
    string fanClean = fan;
    fanClean.erase(remove(fanClean.begin(), fanClean.end(), ' '), fanClean.end());
    while (!isValidFAN(fan))
    {
        cout << "Invalid FAN! Please enter 16 digits (spaces allowed): ";
        getline(cin, fan);
        fanClean = fan;
        fanClean.erase(remove(fanClean.begin(), fanClean.end(), ' '), fanClean.end());
    }

    cout << "Email address: ";
    getline(cin, email);
    while (!isValidEmail(email))
    {
        cout << "Valid email: ";
        getline(cin, email);
    }

    string phoneDigits;

    while (true)
    {
        cout << "Enter phone number\n";
        cout << "+251";
        getline(cin, phoneDigits);

        phoneDigits.erase(remove_if(phoneDigits.begin(), phoneDigits.end(), ::isspace), phoneDigits.end());

        bool valid = true;

        if (phoneDigits.length() != 9)
        {
            cout << "\nInvalid phone number! Must be 9 digits.\n";
            valid = false;
        }
        else if (phoneDigits[0] != '9' && phoneDigits[0] != '7')
        {
            cout << "\nPhone number must start with 9 or 7.\n";
            valid = false;
        }
        else
        {
            for (char c : phoneDigits)
            {
                if (!isdigit(c))
                {
                    cout << "\nDigits only!\n";
                    valid = false;
                    break;
                }
            }
        }

        if (valid)
            break;
    }

    string fullPhone = "+251" + phoneDigits;
    string provider = (phoneDigits[0] == '9') ? "tele" : "bank";

    cout << "\n--- SELECT YOUR CITY ---\n";
    for (int i = 0; i < 10; i++)
    {
        cout << (i + 1) << ". " << ethiopianCities[i] << "\n";
    }
    cout << "Choose (1-10): ";
    int cityChoice;
    cin >> cityChoice;
    cin.ignore();
    while (cityChoice < 1 || cityChoice > 10)
    {
        cout << "Invalid city! Choose again: ";
        cin >> cityChoice;
    }
    cin.ignore();
    string selectedCity = ethiopianCities[cityChoice - 1];
    cout << "\n--- PAYMENT OPTIONS ---\n";
    if (provider == "tele")
    {
        cout << "1. TeleBirr\n";
        for (int i = 0; i < 7; i++)
            cout << (i + 2) << ". " << banks[i] << "\n";
        cout << "Choose (1-8): ";
    }
    else
    {
        for (int i = 0; i < 7; i++)
            cout << (i + 1) << ". " << banks[i] << "\n";
        cout << "Choose (1-7): ";
    }
    int payChoice;
    cin >> payChoice;
    cin.ignore();
    string payment;
    if (provider == "tele")
    {
        if (payChoice == 1)
            payment = "TeleBirr";
        else if (payChoice >= 2 && payChoice <= 8)
            payment = banks[payChoice - 2];
        while (payChoice < 1 || payChoice > 8)
        {
            cout << "Invalid! Choose again: ";
            cin >> payChoice;
        }
        cin.ignore();
    }
    else
    {
        while (payChoice < 1 || payChoice > 7)
        {
            cout << "Invalid! Choose again: ";
            cin >> payChoice;
        }
        cin.ignore();
    }

    cout << "\nTOTAL COST: " << finalTotal << " ETB\n";
    cout << "Confirm rental? (Yes or No): ";
    string confirm;
    getline(cin, confirm);
    while (toLower(confirm) != "yes" && toLower(confirm) != "no")
    {
        cout << "Please enter Yes or No: ";
        getline(cin, confirm);
    }

    if (toLower(confirm) == "no")
    {
        cout << "Rental cancelled.\n";
        return 0;
    }
    // MASKED FAN IN RECEIPT
    string maskedFAN = maskFAN(fan);

    cout << "\n===============================\n";
    cout << "   BOOKING CONFIRMED\n";
    cout << "   Adwa Car Rental System\n";
    cout << "===============================\n";
    cout << "Name: " << name << "\n";
    cout << "FAN: " << maskedFAN << "\n"; //  Only last 4 digits shown
    cout << "Email: " << email << "\n";
    cout << "Phone: " << fullPhone << "\n";
    cout << "City: " << selectedCity << "\n";
    cout << "Car: " << chosenCar->model << "\n";
    cout << "Rental: " << quantity << " " << unit << "\n";
    cout << "Damage Protection: " << (addInsurance ? "Yes" : "No") << "\n";
    cout << "Payment: " << payment << "\n";
    cout << "Total: " << finalTotal << " ETB\n";
    cout << "\n You'll be contacted via email for vehicle delivery details.\n";
    cout << " Late returns incur extra fees as per policy.\n";
    cout << "Thank you! Drive safely in Ethiopia!\n";

    chosenCar->available = false;
    return 0;
}
