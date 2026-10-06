#include <iostream>
#include <string>
using namespace std;

class PaymentProcessor {
public:

    void pay(string paymentMethod, double amount) {

        if (paymentMethod == "UPI") {

            cout << "Connecting to UPI...\n";
            cout << "Validating UPI ID...\n";
            cout << "Processing UPI payment of ₹" << amount << "\n";

        }
        else if (paymentMethod == "CREDIT_CARD") {

            cout << "Connecting to bank...\n";
            cout << "Validating card...\n";
            cout << "Checking CVV...\n";
            cout << "Processing card payment of ₹" << amount << "\n";

        }
        else if (paymentMethod == "PAYPAL") {

            cout << "Connecting to PayPal...\n";
            cout << "Authenticating PayPal account...\n";
            cout << "Processing PayPal payment of ₹" << amount << "\n";

        }
        else {

            cout << "Invalid payment method\n";
        }
    }
};