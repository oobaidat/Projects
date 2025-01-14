#include "Address.h"
using namespace std;

Address::Address() {
	email_ = "no email provided";
	city_ = "no city provided";
	mobileNo_ = 0;
	streetName_ = "no street name provided";
}

Address::Address(string email, string city, int mobileNo, string streetName) {
	email_ = email;
	city_ = city;
	mobileNo_ = mobileNo;
	streetName_ = streetName;
}

Address::Address(const Address& a)
{
	email_ = a.email_;
	city_ = a.city_;
	mobileNo_ = a.mobileNo_;
	streetName_ = a.streetName_;
}

Address::~Address() {}

void Address::setEmail(string email) {
	email_ = email;
}

string Address::getEmail() const {
	return email_;
}

void Address::setCity(string city) {
	city_ = city;
}

string Address::getCity() const {
	return city_;
}

void Address::setMobileNo(int mobileNo) {
	mobileNo_ = mobileNo;
}

int Address::getMobileNo() const {
	return mobileNo_;
}

void Address::setStreetName(string streetName) {
	streetName_ = streetName;
}

string Address::getStreetName() const {
	return streetName_;
}

void Address::printAddress() const {
	cout << "Email: " << email_ << "\n" << "City: " << city_ << "\n" << "Phone number: " << mobileNo_ << "\n" << "Street name: " << streetName_ << endl;
}
