#include "Prescription.h"

Prescription::Prescription(Medication m, int FDANumber, Date approvalDate) : Medication(m)
{
    setFdaNumber(FDANumber);
    setApprovalDate(approvalDate);
    // no increase in counter as it's done in the parent
}

Prescription::Prescription(const Prescription& obj)
    : Medication(obj.name, obj.description, obj.price, obj.stock, obj.expiry_date, obj.barcode),
    FDANumber_(obj.FDANumber_), approvalDate_(obj.approvalDate_) { }

void Prescription::setFdaNumber(int FdaNumber) {
    if (FDANumber_ >= 0) {
        this->FDANumber_ = FdaNumber;
    }
    else {
        cout << "Error FDA number can only be a positive integer" << endl;
        this->FDANumber_ = 1;
    }
}
void Prescription::setApprovalDate(Date approvalDate) {

    if (approvalDate_.getYear() < 2024) {
        cout << "Approval year can only be after 2023.\nDefaulted to 1/1/2024" << endl;
        this->approvalDate_ = Date(1, 1, 2024);
    }
    else {
        this->approvalDate_ = approvalDate;
    }
}

int Prescription::getFdaNumber() const { return FDANumber_; }

Date Prescription::getApprovalDate() const { return approvalDate_; }

string Prescription::getType() const { return "Prescription"; }

void Prescription::display() const {
    Medication::display();
    cout << "FDA number: " << FDANumber_ << endl;
    approvalDate_.print_d(); // prints the details of the date object
}
Prescription::~Prescription() {

}
