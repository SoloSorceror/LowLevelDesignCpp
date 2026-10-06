#include<iostream>
#include<memory>

class PaymentStrategy{
public:
    virtual void pay(double amount) = 0;
    virtual ~PaymentStrategy() = default;
};

class UPI: public PaymentStrategy{
public:
    void pay(double amount) override{
        std::cout<<"Paid "<< amount<< " using UPI \n";
    }
};

class CreditCard : public PaymentStrategy {
public:
    void pay(double amount) override {
        std::cout << "Paid " << amount << " using Credit Card\n";
    }
};

class Payment{
private:
    std::unique_ptr<PaymentStrategy> strategy;
public:
    Payment(std::unique_ptr<PaymentStrategy> strategy): strategy(std::move(strategy)){};
    
    void makePayment(double amount){
        strategy->pay(amount);
    }
};

int main(){
    Payment payment(std::make_unique<UPI>());
    payment.makePayment(100.00);

    Payment payment2(std::make_unique<CreditCard>());
    payment2.makePayment(200.00);

    /*
    you can also do this
    Payment payment;

    payment.setStrategy(make_unique<UPI>());
    payment.makePayment(500);

    payment.setStrategy(make_unique<CreditCard>());
    payment.makePayment(1000);

    payment.setStrategy(make_unique<PayPal>());
    payment.makePayment(2000);
    
    */

    return 0;
}
