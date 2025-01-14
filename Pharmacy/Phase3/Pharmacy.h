#pragma once
#include <iostream>
#include <string>
#include "Medication.h"
#include "Customer.h"
using namespace std;

class Pharmacy {
    // made a counter to be able to update the ID sequentially
    static int counter;
    int pharmacyID;
    string pharmacyName;

    Medication* medication_;
    Customer* customer_;
    // extra attributes made to be used in the functions
    int size_M_, size_C_, sold, profit;

public:
    Pharmacy();
    Pharmacy(string name);
    Pharmacy(const Pharmacy& p);
    ~Pharmacy();

    void setName(string name);
    // no setters for size_M_, size_C_, sold, profit since they are not decided by the user

    static int getCounter();
    int getID() const;
    string getName() const;
    int getSizeM() const;
    int getSizeC() const;
    int getSold() const;
    int getProfit() const;

    void addMedication(const Medication& medication);
    void removeMedication(int index);
    void addCustomer(const Customer& customer);
    void displayMedications() const;
    void displayCustomers() const;

    string compareMedications(const Pharmacy& p) const;
    string compareCustomers(const Pharmacy& p) const;

    void makePurchase(string name);
};
