#include "OffTheShelf.h"

OffTheShelf::OffTheShelf(Medication m, bool BOGOF) : Medication(m)
{
    setBOGOF(BOGOF);
    if (BOGOF_)
        offerEnds_ = Date(9 / 4 / 2024);
    else
        offerEnds_ = Date(9 / 1 / 2026);
    // no increase in counter as it's done in the parent
}

OffTheShelf::OffTheShelf(const OffTheShelf& obj)
    : Medication(obj.name, obj.description, obj.price, obj.stock, obj.expiry_date, obj.barcode),
    BOGOF_(obj.BOGOF_), offerEnds_(obj.offerEnds_) { }

void OffTheShelf::setBOGOF(int BOGOF) {
    if (BOGOF == 1 || BOGOF == 0)
        BOGOF_ = (BOGOF == 1);
    else {
        cout << "Input needs to be 0 or 1.\nDefaulted to false.\n";
        BOGOF_ = false;
    }
}

bool OffTheShelf::getBOGOF() const { return BOGOF_; }

Date OffTheShelf::getOfferEnds() const { return offerEnds_; }

string OffTheShelf::getType() const { return "OffTheShelf"; }

void OffTheShelf::display() const {
    Medication::display();
    cout << "BOGOF: " << BOGOF_ << endl;
    offerEnds_.print_d(); // prints the details of the date object
}

OffTheShelf::~OffTheShelf() {

}
