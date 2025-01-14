#include "Pharmacy.h"

// set static variable at the start of the implementation
int Pharmacy::counter = 1;

// adds 1 to medicationID when an object of class Medication is created
// pharmacyID needs to be initialised in member list since it is const
Pharmacy::Pharmacy() : pharmacyID(counter), pharmacyName("No name"), size_M_(0), size_C_(0), sold(0), profit(0)
{ 
    medication_ = new Medication[size_M_];
    customer_ = new Customer[size_C_];
    counter += 1;
}

Pharmacy::Pharmacy(string name) : pharmacyID(counter), size_M_(0), size_C_(0), sold(0), profit(0)
{
    // used setters in the constructor to not write the validation code twice
    setName(name);
    medication_ = new Medication[size_M_];
    customer_ = new Customer[size_C_];
    counter += 1;
}

// object parameter using reference, it is passed with const to make sure nothing changes
Pharmacy::Pharmacy(const Pharmacy& p) : pharmacyID(counter), pharmacyName(p.pharmacyName), size_M_(p.size_M_), size_C_(p.size_C_), sold(p.sold), profit(p.profit)
{
    medication_ = new Medication[size_M_];

    for (int i = 0; i < size_M_; i++) {
        medication_[i] = p.medication_[i];
    }

    customer_ = new Customer[size_C_];

    for (int i = 0; i < size_C_; i++) {
        customer_[i] = p.customer_[i];
    }

    counter += 1;
}

// removes 1 from medicationID when an object of class Medication is deleted
Pharmacy::~Pharmacy()
{
    counter -= 1;

    if (medication_ != NULL) { //checks if the array points to anything other than null if yes it deletes the array it points to
        delete[] medication_;
    }

    if (customer_ != NULL) {  //checks if the array points to anything other than null if yes it deletes the array it points to
        delete[] customer_;
    }
}


void Pharmacy::setName(string name)
{
    // checks if every character in the string is either a letter, a space, or a '
    for (int i = 0; i < name.length(); i++) {
        if ((name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z') && (name[i] != ' ') && (name[i] != '\'')) {
            // if invalid input, sets name to 'No name'
            cout << "Name can only contain letters.\nDefaulted to 'No name'.\n";
            this->pharmacyName = "No name";
            return;
        }
    }
    this->pharmacyName = name;
}

// -1 since for the counter to work with const we had to start the counter from 1 not 0
int Pharmacy::getCounter() { return counter - 1; }

int Pharmacy::getID() const { return pharmacyID; }

string Pharmacy::getName() const { return pharmacyName; }

int Pharmacy::getSizeM() const { return size_M_; }

int Pharmacy::getSizeC() const { return size_C_; }

int Pharmacy::getSold() const { return sold; }

int Pharmacy::getProfit() const { return profit; }

// addMedication function adds a medication to the pharmacy
void Pharmacy::addMedication(const Medication& medication) {
    size_M_ = size_M_ + 1;

    Medication* newMedication = new Medication[size_M_];

    for (int i = 0; i < size_M_ - 1; i++) {
        newMedication[i] = medication_[i];
    }

    newMedication[size_M_ - 1] = medication;

    delete[] medication_;
    medication_ = newMedication;
}

// removeMedication function using index of med, iterates through medications,
// makes a copy of the array but without the chosen index as the new array
void Pharmacy::removeMedication(int index) {
    if (index < 0 || index >= size_M_) {
        cout << "Invalid index" << endl;
        return;
    }

    size_M_ = size_M_ - 1;

    Medication* newMedication = new Medication[size_M_];

    // two indicies, one for the new array, one for the original
    // where we skip one for the new index when we reach the index we want to remove from the orignial array
    int j = 0;
    for (int i = 0; i < size_M_; i++) {
        if (i == index)
            continue;
        newMedication[j] = medication_[i];
        j++;
    }

    delete[] medication_;
    medication_ = newMedication;
}

// addCustomer function adds a customer to the pharmacy
void Pharmacy::addCustomer(const Customer& customer) {
    size_C_ = size_C_ + 1;
    Customer* newCustomer = new Customer[size_C_];

    for (int i = 0; i < size_C_ - 1; i++) {
        newCustomer[i] = customer_[i];
    }
    newCustomer[size_C_ - 1] = customer;

    delete[] customer_;
    customer_ = newCustomer;
}

// displayMedications and displayCustomers functions simply iterate through the respective arrays and display
// the medications and customers stored in the pharmacy using their own functions.
void Pharmacy::displayMedications() const {

    if (medication_ != NULL) {
        for (int i = 0; i < size_M_; i++) {
            medication_[i].display();
        }
    }
    else { cout << "ERORR there is no medication" << endl; }
}

void Pharmacy::displayCustomers() const {

    if (customer_ != NULL) {
        for (int i = 0; i < size_C_; i++) {
            customer_[i].display();
        }
    }
    else { cout << "ERORR there is no customer" << endl; }
}

// returns more, equal, or less depending on number of medications*stock for comparing two pharmacies
string Pharmacy::compareMedications(const Pharmacy& p) const
{
    if (medication_ == NULL || p.medication_ == NULL) {
        cout << "ERORR there is no medication to compare" << endl;
        return "error";
    }

    int count1 = 0, count2 = 0;

    for (int i = 0; i < size_M_; i++) {
        count1 += medication_[i].getStock();
    }
    for (int i = 0; i < p.size_M_; i++) {
        count2 += p.medication_[i].getStock();
    }

    if (count1 > count2)
        return "more";
    else if (count1 == count2)
        return "equal";
    else
        return "less";
}

// returns more, equal, or less depending on number of customers comparing two pharmacies
string Pharmacy::compareCustomers(const Pharmacy& p) const
{
    if (customer_ == NULL || p.customer_ == NULL) {
        cout << "ERORR there are no customers to compare" << endl;
        return "error";
    }

    if (size_C_ > p.size_C_)
        return "more";
    else if (size_C_ == p.size_C_)
        return "equal";
    else
        return "less";
}

// checks whether the medicine exists in the pharmacy, then asks the user for how much they want to buy, how much was bought and profit made
void Pharmacy::makePurchase(string name)
{
    for (int i = 0; i < size_M_; i++) {
        if (medication_[i].getName() == name) {

            int buy;
            int stock = medication_[i].getStock();

            cout << "We have " << stock << "in stock." << endl;
            cout << "How many would you like to buy: ";
            cin >> buy;

            if (buy > stock) {
                cout << "Sorry we don't have that much.\nYou have bought "
                    << stock << " of " << name << ", thank you for your purchase!" << endl;
                sold += stock;
                profit += stock * medication_[i].getPrice();
                medication_[i].setStock(0);
            }
            else {
                cout << "You have bought " << buy << " of " << name << ", thank you for your purchase!" << endl;
                sold += buy;
                profit += buy * medication_[i].getPrice();
                medication_[i].setStock(stock - buy);
            }
            break;

        }
        // end of medicine list reached without finding the medicine
        else if (i == size_M_ - 1)
            cout << "We don't have that medicine" << endl;
    }
    cout << "\n";
}
