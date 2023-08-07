#include <iostream>
#include <string>
#include <vector>
using namespace std;

// A class to represent an ice cream type
class IceCreamType {
    private:
        string name; // the name of the ice cream type
        double price; // the price per scoop of the ice cream type
    public:
        // A constructor to initialize the name and price
        IceCreamType(string n, double p) {
            name = n;
            price = p;
        }

        // A getter method to return the name
        string getName() {
            return name;
        }

        // A getter method to return the price
        double getPrice() {
            return price;
        }
};

// A class to represent an ice cream flavor
class IceCreamFlavor {
    private:
        string name; // the name of the ice cream flavor
        IceCreamType* type; // a pointer to the ice cream type object
    public:
        // A constructor to initialize the name and type
        IceCreamFlavor(string n, IceCreamType* t) {
            name = n;
            type = t;
        }

        // A getter method to return the name
        string getName() {
            return name;
        }

        // A getter method to return the type
        IceCreamType* getType() {
            return type;
        }
};

// A class to represent an ice cream order
class IceCreamOrder {
    private:
        IceCreamFlavor* flavor; // a pointer to the ice cream flavor object
        int quantity; // the number of scoops ordered
    public:
        // A constructor to initialize the flavor and quantity
        IceCreamOrder(IceCreamFlavor* f, int q) {
            flavor = f;
            quantity = q;
        }

        // A getter method to return the flavor
        IceCreamFlavor* getFlavor() {
            return flavor;
        }

        // A getter method to return the quantity
        int getQuantity() {
            return quantity;
        }

        // A method to calculate and return the cost of the order
        double getCost() {
            return flavor->getType()->getPrice() * quantity;
        }
};

// A class to represent a customer
class Customer {
    private:
        string name; // the name of the customer
        vector<IceCreamOrder*> orders; // a vector of pointers to the ice cream order objects
    public:
        // A constructor to initialize the name and orders
        Customer(string n) {
            name = n;
            orders.clear();
        }

        // A destructor to delete the orders from memory
        ~Customer() {
            for (int i = 0; i < orders.size(); i++) {
                delete orders[i];
            }
            orders.clear();
        }

        // A getter method to return the name
        string getName() {
            return name;
        }

        // A method to add an order to the customer's orders vector
        void addOrder(IceCreamOrder* o) {
            orders.push_back(o);
        }

        // A method to print the customer's details and orders
        void printDetails() {
            cout << "Customer name: " << name << endl;
            cout << "Orders: " << endl;
            double total = 0.0; // a variable to store the total cost of all orders
            for (int i = 0; i < orders.size(); i++) {
                cout << i+1 << ". " << orders[i]->getFlavor()->getName() << " (" << orders[i]->getFlavor()->getType()->getName() << ") - " << orders[i]->getQuantity() << " scoop(s) - tk " << orders[i]->getCost() << endl;
                total += orders[i]->getCost();
            }
            cout << "Total: tk " << total << endl;
            cout << endl;



        }
};

// A friend function to create and return a pointer to a new ice cream order object
IceCreamOrder* createOrder(IceCreamFlavor* f, int q) {
    IceCreamOrder* o = new IceCreamOrder(f, q); // dynamically allocate memory for the order object
    return o; // return the pointer to the order object
}

// A main function to test the program
int main() {
    // Create some ice cream type objects
    IceCreamType regular("Regular", 30);
    IceCreamType premium("Premium", 70);
    IceCreamType vegan("Vegan", 40);

    // Create some ice cream flavor objects
    IceCreamFlavor vanilla("Vanilla", &regular);
    IceCreamFlavor chocolate("Chocolate", &premium);
    IceCreamFlavor strawberry("Strawberry", &regular);
    IceCreamFlavor mango("Mango", &vegan);
    IceCreamFlavor pistachio("Pistachio", &premium);

    // Create a vector of pointers to the ice cream flavor objects
    vector<IceCreamFlavor*> flavors;
    flavors.push_back(&vanilla);
    flavors.push_back(&chocolate);
    flavors.push_back(&strawberry);
    flavors.push_back(&mango);
    flavors.push_back(&pistachio);

    // Ask the user for their name
    cout << "Enter your name: ";
    string name;
    cin >> name;

    // Create a customer object with the given name
    Customer customer(name);

    // A variable to store the total expenses of the customer
    double total = 0.0;

    // A loop to take orders from the user until they say no
    while (true) {
        // Show the available flavors and their prices to the user
        cout << "Available flavors and prices: " << endl;
        for (int j = 0; j < flavors.size(); j++) {
            cout << j+1 << ". " << flavors[j]->getName() << " (" << flavors[j]->getType()->getName() << ") - tk " << flavors[j]->getType()->getPrice() << endl;
        }

        // Ask the user to choose a flavor by entering its number
        cout << "Choose a flavor by entering its number: ";
        int f;
        cin >> f;

        // Check if the input is valid
        if (f < 1 || f > flavors.size()) {
            cout << "Invalid input. Please try again." << endl;
            continue; // skip the rest of the loop
        }

        // Ask the user to enter the quantity of scoops they want
        cout << "Enter the quantity of scoops you want: ";
        int q;
        cin >> q;

        // Check if the input is positive
        if (q < 1) {
            cout << "Invalid input. Please try again." << endl;
            continue; // skip the rest of the loop
        }

        // Add an order to the customer's orders vector with the chosen flavor and quantity
        customer.addOrder(createOrder(flavors[f-1], q));

        // Update the total expenses of the customer by adding the cost of the order
        total += flavors[f-1]->getType()->getPrice() * q;

        // Show the current total expenses of the customer to the user
        cout << "Your current total expenses are: tk " << total << endl;

        // Ask the user if they want to order more
        cout << "Do you want to order more? (yes/no) ";
        string answer;
        cin >> answer;

        // Check if the answer is no
        if (answer == "no") {
            break; // exit the loop
        }
    }

    // Print the customer's details and orders
    customer.printDetails();

    return 0;
}

