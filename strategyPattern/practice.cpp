#include<iostream>
#include<memory>

using namespace std;

class NavigationStrategy{
public:
    virtual double calculateRoutes(double source, double destination) const = 0;
    virtual ~NavigationStrategy() = default;
};

class Car: public NavigationStrategy{
    double calculateRoutes(double source, double destination) const override{
        cout<<"Car \n";
        return (destination - source ) * 30;
    }
};
class Walking: public NavigationStrategy{
    double calculateRoutes(double source, double destination) const override{
        cout<<"Walking \n";
        return (destination - source ) * 0;
    }
};
class Bicycle: public NavigationStrategy{
    double calculateRoutes(double source, double destination) const override{
        cout<<"Bicycle \n";
        return (destination - source ) * 10;
    }
};

class Navigation{
private:
    unique_ptr<NavigationStrategy> strategy;
public:
    // Navigation(unique_ptr<NavigationStrategy> strategy): strategy(move(strategy)){}

    void setStrategy(unique_ptr<NavigationStrategy> strategy){
        this->strategy = move(strategy);
    }

    double calculateRoutes(double source, double destination){
        return strategy->calculateRoutes(source, destination);
    }
};

int main(){
    Navigation navigation;

    navigation.setStrategy(make_unique<Car>());
    cout<< navigation.calculateRoutes(200,500)<< endl;
    
    navigation.setStrategy(make_unique<Walking>());
    cout<< navigation.calculateRoutes(200,500)<<endl;

    navigation.setStrategy(make_unique<Bicycle>());
    cout<< navigation.calculateRoutes(200,500)<<endl;

    return 0;
}

