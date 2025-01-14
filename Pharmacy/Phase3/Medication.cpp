#include "Medication.h"

// set static variable at the start of the implementation
int Medication:: counter = 0;

// adds 1 to medicationID when an object of class Medication is created
// expiry_date initialised using member initializer list to use copy constructor instead of default constructor then copy
Medication::Medication(string name, string description, double price, int stock, Date expiry_date, string barcode)
	: expiry_date(expiry_date.getYear() >= 2024 ? expiry_date : (cout << "Expiry date needs to be after 2023.\nDefaulted to 1/1/2024.\n", Date(1, 1, 2024)))
{
	counter += 1;
	id = counter;
	// used setters in the constructor to not write the validation code twice
	setName(name);
	setDescription(description);
	setPrice(price);
	setStock(stock);
	setBarcode(barcode);
}

// object parameter using reference, it is passed with const to make sure nothing changes
Medication::Medication(const Medication& obj) 
	: name(obj.name), description(obj.description), price(obj.price), 
	stock(obj.stock), expiry_date(obj.expiry_date), barcode(obj.barcode) { counter += 1; id = counter; }

// removes 1 from medicationID when an object of class Medication is deleted 
Medication::~Medication() { counter -= 1; }

void Medication::setName(string name)
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

void Medication::setDescription(string description)
{
	// checks if every character in the string is either a letter or a space
	for (int i = 0; i < description.length(); i++) {
		if ((description[i] < 'A' || description[i] > 'Z') && (description[i] < 'a' || description[i] > 'z') && (description[i] != ' ')) {
			// if invalid input, sets description to 'No description'
			cout << "Description can only contain letters.\nDefaulted to 'No description'.\n";
			this->description = "No description";
			return;
		}
	}
	this->description = description;
}

void Medication::setPrice(double price)
{   
	// checks if price is positive
    if (price > 0) {
        this->price = price;
    } else {
		// if invalid input, sets price to 1
        cout << "Price can only be a positive double.\nDefaulted to 1" << endl;
        this->price = 1;
    }
}

void Medication::setStock(int stock)
{
	// checks if price is positive
	if (stock >= 0) {
		this->stock = stock;
	}
	else {
		// if invalid input, sets stock to 1
		cout << "Stock can only be a more than or equal to 0.\nDefaulted to 1" << endl;
		this->stock = 1;
	}
}

void Medication::setExpiryDate(Date expiry_date)
{
	// checks if expiry date is greater than or equal 2024
	if (expiry_date.getYear() < 2024) {
		// if invalid input, sets the expiry date to 1/1/2024
		cout << "Expiry year can only be after 2023.\nDefaulted to 1/1/2024.\n";
		this->expiry_date = Date(1, 1, 2024);
		return;
	}
	this->expiry_date = expiry_date;
}

void Medication::setBarcode(string barcode)
{    
	// checks if the string only contains numbers
    for (int i = 0; i < barcode.length(); i++) {
        if (barcode[i]<'0' || barcode[i]>'9') {
			// if invalid input, sets barcode to '0000'
            cout << "Invalid barcode. Barcode can only be a series positive digits.\nDefaulted to '0000'" << endl;
            this->barcode = "0000";
            return;
        }
    }
    this->barcode = barcode;
}

int Medication::getCounter() { return counter; }

int Medication::getID() const { return id; }

string Medication::getName() const { return name; }

string Medication::getDescription() const { return description; }

double Medication::getPrice() const { return price; }

int Medication::getStock() const { return stock; }

Date Medication::getExpiryDate() const { return expiry_date; }

string Medication::getBarcode() const { return barcode; }

void Medication::display() const
{
	cout << "Medication ID: " << id << endl;
	cout << "Medication name: " << name << endl;
	cout << "Medication description: " << description << endl;
	cout << "Medication price: " << price << endl;
	cout << "Medication stock: " << stock << endl;
	cout << "Medication expiry date: ";
	expiry_date.print_d(); // print Date object using print_d() method in its class
	cout << "Medication barcode: " << barcode << endl;
}
