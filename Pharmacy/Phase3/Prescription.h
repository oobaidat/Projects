#pragma once
#include "Medication.h"

class Prescription : public Medication {
    int FDANumber_;
    Date approvalDate_;

public:
    Prescription(Medication m = Medication("No name", "No description", 1, 1, Date(1, 1, 2024), "0000"),
        int FDANumber = 0, Date approvalDate = Date(1, 1, 2024));
    Prescription(const Prescription& obj);

    void setFdaNumber(int FdaNumber);
    void setApprovalDate(Date approvalDate);

    int getFdaNumber() const;
    Date getApprovalDate() const;
    string getType() const;

    void display() const;

    ~Prescription();
};
