#include "Customer.h"

int Customer::counter = 0;

// adds 1 to medicationID when an object of class Medication is created
// expiry_date initialised using member initializer list to use copy constructor instead of default constructor then copy
Customer::Customer(string name, Address address) : address(address)
{
	// used setters in the constructor to not write the validation code twice
	setName(name);
	counter += 1;
	id = counter;
}

// object parameter using reference, it is passed with const to make sure nothing changes
Customer::Customer(const Customer& obj) 
	: name(obj.name), address(obj.address) { counter += 1; id = counter; }

Customer::~Customer() { counter -= 1; }

void Customer::setName(string name) 
{ 
	// checks if every character in the string is either a letter or a space
	for (int i = 0; i < name.length(); i++) {
		if ((name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z') && (name[i] != ' ')) {
			// if invalid input, sets name to 'No name'
			cout << "Name can only contain letters.\nDefaulted to 'No name'.\n";
			this->name = "No name";
			return;
		}
	}
	this->name = name; 
}

void Customer::setAddress(Address address) 
{
	this->address = address;
}

string Customer::getName() const { return name; }

int Customer::getID() const { return id; }

Address Customer::getAddress() const { return address; }

int Customer::getCounter() { return counter; }

void Customer::display() const
{
	cout << "Customer name: " << name << endl;
	cout << "Customer ID: " << id << endl;
	cout << "Customer address: ";
	address.printAddress(); // print Address object using printAddress() method in its class
}
