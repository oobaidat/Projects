#pragma once
#include <iostream>
#include <string>
using namespace std;

class Address {
private:
	string email_;
	string city_;
	int mobileNo_;
	string streetName_;
public:
	Address(); //default constructor
	Address(string email, string city, int mobileNo, string streetName);//parameterized constructor
	Address(const Address& a); //copy constructor
	~Address();//destructor

	//setters and getters
	void setEmail(string email);
	string getEmail() const;
	void setCity(string city);
	string getCity() const;
	void setMobileNo(int moblileNo);
	int getMobileNo() const;
	void setStreetName(string streetName);
	string getStreetName() const;

	void printAddress() const;//print function
};
