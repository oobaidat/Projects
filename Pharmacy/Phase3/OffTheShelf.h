#pragma once
#include "Medication.h"

class OffTheShelf : public Medication {
    bool BOGOF_;
    Date offerEnds_;

public:

    OffTheShelf(Medication m = Medication("No name", "No description", 1, 1, Date(1, 1, 2024), "0000"), bool BOGOF = false);
    OffTheShelf(const OffTheShelf& obj);

    void setBOGOF(int BOGOF);

    bool getBOGOF() const;
    Date getOfferEnds() const;
    string getType() const;

    void display() const;

    ~OffTheShelf();
};
