#pragma once
#include <iostream>
#include <string>
#include "Address.h"
using namespace std;

class Customer
{
	static int counter;
	string name;
	int id;
	Address address;

public:
	// defaulted constructor for Customer class
	Customer(string name = "No name", Address address = Address("no email provided", "no city provided", 0, "no street name provided"));
	Customer(const Customer& obj);
	~Customer();
	
	void setName(string name);
	void setAddress(Address address);

	// getters are const methods since they don't change anything in the object attributes
	string getName() const;
	Address getAddress() const;
	int getID() const;

	// static methods can't be declared as const as they do not belong to an object in the class
	static int getCounter();

	void display() const;
};
