#pragma once
#include <iostream>
#include <string>
#include "Date.h"
using namespace std;

class Medication
{
	static int counter;
// to be accessed easily by the child
protected:
	int id;
	string name, description;
	double price;
	int stock;
	Date expiry_date;
	string barcode;

public:
	// defaulted constructor for Medication class
	Medication(string name = "No name", string description = "No description", double price = 1,
		int stock = 1, Date expiry_date = Date(1, 1, 2024), string barcode = "0000");
	Medication(const Medication& obj);
	~Medication();

	void setName(string name);
	void setDescription(string description);
	void setPrice(double price);
	void setStock(int stock);
	void setExpiryDate(Date expiry_date);
	void setBarcode(string barcode);

	// static methods can't be declared as const as they do not belong to an object in the class
	static int getCounter();

	// getters are const methods since they don't change anything in the object attributes
	int getID() const;
	string getName() const;
	string getDescription() const;
	double getPrice() const;
	int getStock() const;
	Date getExpiryDate() const;
	string getBarcode() const;

	void display() const;
};
