#include <iostream>
#include <string>
#include "Customer.h"
#include "Medication.h"
#include "Date.h"
#include "Address.h"
#include "Pharmacy.h"
#include "Prescription.h"
#include "OffTheShelf.h"
using namespace std;

// function to resize pharmacy array returning the new size
int resizePharmacy(Pharmacy* phar_arr, int size)
{
    int resize;
    cout << "What new size of pharmacies do you want: ";
    cin >> resize;
    Pharmacy* temp = new Pharmacy[resize];

    if (resize > size) {
        for (int i = 0; i < size; i++) {
            temp[i] = phar_arr[i];
        }

        for (int i = size; i < resize; i++) {
            string name;
            cout << "Enter name for pharmacy " << i + 1 << ": ";
            cin.ignore();
            getline(cin, name);
            temp[i].setName(name);
        }
    }
    else {
        int* remove_arr = new int[size - resize];

        cout << "Which ID(s) would you like to remove: ";
        for (int i = 0; i < size - resize; i++) {
            cin >> remove_arr[i];
        }

        // three indicies, one for the new array, one for the original, one for the array of IDs we want to remove
        // where we skip one for the new index when we reach an index we want to remove from the orignial array and add one to the index of array of IDs we want to remove
        int j = 0, n = 0;
        for (int i = 0; i < size; i++) {
            if (i == remove_arr[n]) {
                n++;
                continue;
            }
            temp[j] = phar_arr[i];
            j++;
        }

        delete[] remove_arr;
    }
    delete[] phar_arr;
    phar_arr = temp;

    return resize;
}

// function to choose pharmacy
int choosePharmacy(int max)
{
    // variable to store pharmacy id from user
    int id;
    cin >> id;

    // check if a pharmacy with the inputted id exists
    if (id < 1 || id > max) {
        cout << "Please choose a valid pharmacy ID\n\n" << endl;
        return -1;
    }

    return id;
}

// function to add medications
void addMedications(Pharmacy& phar)
{
    // variables to store medical stuff for medicine
    string name, description;
    double price;
    int stock;
    int day, month, year;
    string barcode;

    // variable for loop
    char ch = 'y';

    cout << "What medication(s) would you like to add: " << endl;
    while (ch == 'y') {
        Medication m;

        cout << "Enter medication name: ";
        cin.ignore();
        getline(cin, name);
        m.setName(name);

        cout << "Enter medication description: ";
        cin.ignore();
        getline(cin, description);
        m.setDescription(description);

        cout << "Enter medication price: ";
        cin >> price;
        m.setPrice(price);

        cout << "Enter medication stock: ";
        cin >> stock;
        m.setStock(stock);

        cout << "Enter medication expiry date (day month year): ";
        cin >> day >> month >> year;
        m.setExpiryDate(Date(day, month, year));

        cout << "Enter medication barcode: ";
        cin.ignore();
        getline(cin, barcode);
        m.setBarcode(barcode);

        char type = ' ';
        cout << "Is the medication a prescription or off the shelf ('p'/'o'): ";
        cin >> type;
        while (type != 'p' && type != 'o') {
            cout << "Please input a valid option: ";
            cin >> type;
        }

        if (type == 'p') {
            Prescription p(m);
            int FDANumber;

            cout << "Enter prescription FDA number: ";
            cin >> FDANumber;
            p.setFdaNumber(FDANumber);

            cout << "Enter prescription approval date (day month year): ";
            cin >> day >> month >> year;
            p.setApprovalDate(Date(day, month, year));

            phar.addMedication(p);
        }
        else {
            OffTheShelf o(m);
            int BOGOF;

            cout << "Enter if it has the offer of buy one get one free (1 if true/0 if false): ";
            cin >> BOGOF;
            o.setBOGOF(BOGOF);

            phar.addMedication(o);
        }

        cout << "\n";

        cout << "Would you like to add more? (enter 'y' for yes) ";
        cin >> ch;
    }
}

// function to add customers
void addCustomers(Pharmacy& phar)
{
    // variables to store medical stuff for medicine
    string name, email, city, street;
    int phone;

    // variable for loop
    char ch = 'y';

    cout << "Which customers would you like to add: " << endl;
    while (ch == 'y') {
        Customer c;
        Address a;

        cout << "Enter customer name: ";
        cin.ignore();
        getline(cin, name);
        c.setName(name);

        cout << "Enter customer email: ";
        cin.ignore();
        getline(cin, email);
        a.setEmail(email);

        cout << "Enter customer city: ";
        cin.ignore();
        getline(cin, city);
        a.setCity(city);

        cout << "Enter customer phone number: ";
        cin >> phone;
        a.setMobileNo(phone);

        cout << "Enter customer street name: ";
        cin.ignore();
        getline(cin, street);
        a.setStreetName(street);

        c.setAddress(a);
        cout << "\n";

        phar.addCustomer(c);

        cout << "Would you like to add more? (enter 'y' for yes) ";
        cin >> ch;
    }
}

int main()
{
    // 1 - Object in static memory with attributes in static memory
    // Customer cStatic("Ahmad", Address("Ahmad@gmail.com", "Amman", 962, "University"));

    // 2 - Object in static memory with attributes in dynamic memory
    // Address* aDynamic = new Address("Osama@gmail.com", "Amman", 962, "Garden");
    // Customer cStatic("Osama", *aDynamic);
    // delete aDynamic;

    // 3 - Object in dynamic memory with attributes in static memory
    // Customer* cDynamic = new Customer("Amr", Address("Amr@gmail.com", "Amman", 962, "Jordan"));
    // delete cDynamic;

    // 4 - Object in dynamic memory with attributes in dynamic memory
    // Address* aDynamic = new Address("Zuheir@gmail.com", "Amman", 962, "Rainbow");
    // Customer* cDynamic = new Customer("Osama", *aDynamic);
    // delete aDynamic, cDynamic;

    cout << "Welcome to our pharmacy!" << endl;

    // size of pharmacies we have
    int t_phar;

    // take pharmacy size and the pharmacies from the user as soon as the program starts
    cout << "How many pharmacies do you want: ";
    cin >> t_phar;
    Pharmacy* phar_arr = new Pharmacy[t_phar];

    for (int i = 0; i < t_phar; i++) {
        string name;
        cout << "Enter name for pharmacy " << i + 1 << ": ";
        cin.ignore(); // this allows us to ignore any whitespaces left from previous outputs
        getline(cin, name); // this way we can take spaces as input
        phar_arr[i].setName(name);
    }

    // choice: saves the user choice to execute different interactions
    int choice = 0;

    // keep repeating loop till user chooses to exit
    while (choice != -1) {
        cout << "Please choose one of the following options:" << endl;
        cout << "1. Change amount of pharmacies\n";
        cout << "2. Add medication for a pharmacy\n";
        cout << "3. Add customer for a pharmacy\n";
        cout << "4. Display available medications for a pharmacy\n";
        cout << "5. Remove medication from pharmacy\n";
        cout << "6. Display list of customers for a pharmacy\n";
        cout << "7. Make purchase from a pharmacy\n";
        cout << "8. Calculate total sales and profit for a pharmacy\n";
        cout << "9. Compare medications (stock) between pharmacies\n";
        cout << "10. Compare customers between pharmacies\n";
        cout << "11. Compare profit between pharmacies\n";
        cout << "12. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "\n";

        if (choice == 1) {
            cout << "----Selected option 1: Change amount of pharmacies----" << endl;

            t_phar = resizePharmacy(phar_arr, t_phar);

            cout << "\nTo add a medication: choose option 2\nTo add a customer: choose option 3\n\n" << endl;
        }
        else if (choice == 2) {
            cout << "----Selected option 2: Add medication for a pharmacy----" << endl;

            cout << "Which pharmacy would you like to add medication(s) to (ID): ";
            int phar_id = choosePharmacy(t_phar);

            // choosePharmacy() returns -1 if input from user was invalid
            if (phar_id == -1)
                continue;

            // add medication to array of medicines in the pharmacy
            addMedications(phar_arr[phar_id - 1]);

            cout << "\n\n";
        }
        else if (choice == 3) {
            cout << "----Selected option 3: Add customer for a pharmacy----" << endl;

            cout << "Which pharmacy would you like to add customer(s) to (ID): ";
            int phar_id = choosePharmacy(t_phar);

            // choosePharmacy() returns -1 if input from user was invalid
            if (phar_id == -1)
                continue;

            // add customer to array of customers in pharmacy
            addCustomers(phar_arr[phar_id - 1]);

            cout << "\n\n";
        }
        else if (choice == 4) {
            cout << "----Selected option 4: Display available medications for a pharmacy----" << endl;

            cout << "Which pharmacy would you like to see medications for (ID): ";
            int phar_id = choosePharmacy(t_phar);

            // choosePharmacy() returns -1 if input from user was invalid
            if (phar_id == -1)
                continue;

            cout << "Medications in " << phar_arr[phar_id - 1].getName() << ":\n";

            phar_arr[phar_id - 1].displayMedications();

            cout << "\n\n";
        }
        else if (choice == 5) {
            cout << "----Selected option 5: Remove medication from pharmacy----" << endl;

            cout << "Which pharmacy would you like to remove a medication from (ID): ";
            int phar_id = choosePharmacy(t_phar);

            // choosePharmacy() returns -1 if input from user was invalid
            if (phar_id == -1)
                continue;

            int med_id;
            cout << "Write the ID of the medication you want to remove: " << endl;
            cin >> med_id;

            phar_arr[phar_id - 1].removeMedication(med_id);

            cout << "\n\n";
        }
        else if (choice == 6) {
            cout << "----Selected option 6: Display list of customers for a pharmacy----" << endl;

            cout << "Which pharmacy would you like to see customers for (ID): ";
            int phar_id = choosePharmacy(t_phar);

            // choosePharmacy() returns -1 if input from user was invalid
            if (phar_id == -1)
                continue;

            cout << "Customers in " << phar_arr[phar_id - 1].getName() << ":\n";

            phar_arr[phar_id - 1].displayCustomers();

            cout << "\n\n";
        }
        else if (choice == 7) {
            cout << "----Selected option 7: Make purchase from a pharmacy----" << endl;

            cout << "Which pharmacy would you like to buy from (ID): ";
            int phar_id = choosePharmacy(t_phar);

            // choosePharmacy() returns -1 if input from user was invalid
            if (phar_id == -1)
                continue;

            string name;
            cout << "What is the name of the medicine you want to buy: ";
            cin.ignore();
            getline(cin, name);

            phar_arr[phar_id - 1].makePurchase(name);

            cout << "\n\n";
        }
        else if (choice == 8) {
            cout << "----Selected option 8: Calculate total sales and profit for a pharmacy----" << endl;

            cout << "Which pharmacy would you like to get sales and profit for (ID): ";
            int phar_id = choosePharmacy(t_phar);

            // choosePharmacy() returns -1 if input from user was invalid
            if (phar_id == -1)
                continue;

            cout << phar_arr[phar_id].getName() << " has:" << endl;
            cout << "Medicines sold: " << phar_arr[phar_id].getSold() << endl;
            cout << "Profit made: " << phar_arr[phar_id].getProfit() << endl;
            cout << "\n";

            cout << "\n\n";
        }
        else if (choice == 9) {
            cout << "----Selected option 9: Compare medications (stock) between pharmacies----" << endl;

            cout << "First pharmacy (ID): ";
            int phar_id1 = choosePharmacy(t_phar);

            // choosePharmacy() returns -1 if input from user was invalid
            if (phar_id1 == -1)
                continue;

            cout << "Second pharmacy (ID): ";
            int phar_id2 = choosePharmacy(t_phar);

            // choosePharmacy() returns -1 if input from user was invalid
            if (phar_id2 == -1)
                continue;

            string comp = phar_arr[phar_id1].compareMedications(phar_arr[phar_id2]);

            if (comp == "error")
                continue;

            cout << phar_arr[phar_id1].getName() << " has " << comp << " medications than " << phar_arr[phar_id2].getName() << endl;

            cout << "\n\n";
        }
        else if (choice == 10) {
            cout << "----Selected option 10: Compare customers between pharmacies----" << endl;

            cout << "First pharmacy (ID): ";
            int phar_id1 = choosePharmacy(t_phar);

            // choosePharmacy() returns -1 if input from user was invalid
            if (phar_id1 == -1)
                continue;

            cout << "Second pharmacy (ID): ";
            int phar_id2 = choosePharmacy(t_phar);

            // choosePharmacy() returns -1 if input from user was invalid
            if (phar_id2 == -1)
                continue;

            string comp = phar_arr[phar_id1].compareCustomers(phar_arr[phar_id2]);

            if (comp == "error")
                continue;

            cout << phar_arr[phar_id1].getName() << " has " << comp << " customers than " << phar_arr[phar_id2].getName() << endl;

            cout << "\n\n";
        }
        else if (choice == 11) {
            cout << "----Selected option 11: Compare profit between pharmacies----" << endl;

            cout << "First pharmacy (ID): ";
            int phar_id1 = choosePharmacy(t_phar);

            // choosePharmacy() returns -1 if input from user was invalid
            if (phar_id1 == -1)
                continue;

            cout << "Second pharmacy (ID): ";
            int phar_id2 = choosePharmacy(t_phar);

            // choosePharmacy() returns -1 if input from user was invalid
            if (phar_id2 == -1)
                continue;

            string comp;
            if (phar_arr[phar_id1].getProfit() > phar_arr[phar_id2].getProfit())
                comp = "more";
            else if (phar_arr[phar_id1].getProfit() == phar_arr[phar_id2].getProfit())
                comp = "equal";
            else
                comp = "less";

            cout << phar_arr[phar_id1].getName() << " has " << comp << " profit than " << phar_arr[phar_id2].getName() << endl;

            cout << "\n\n";
        }
        else if (choice == 12) {
            cout << "----Selected option 12: Exit----" << endl;
            cout << "Goodbye! Thank you for visiting!" << endl;
            choice = -1;
        }
        else {
            cout << "Please enter a number between 1 and 12.\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cout << "\n";
        }
    }

    // deallocate memory when done
    delete[] phar_arr;

    system("pause");
    return 0;
}
