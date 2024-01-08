#include <iostream>
using namespace std;

class Transport {
protected:
    double delivery_cost;
    double max_load_capacity;
    double fuel_consumption;
public:
    virtual void SetDeliveryCost() = 0;
    virtual void SetMaxLoadCapacity() = 0;
    virtual void SetFuelConsumption() = 0;
    double CalculateDeliveryCost(double distance) {
        return delivery_cost * (distance / 100);
    };
    double CalculateFuelConsumption(double distance) {
        return fuel_consumption * (distance / 100);
    }
};

class Truck : public Transport {
    void SetDeliveryCost() override {
        delivery_cost = 3000;
    }
    void SetMaxLoadCapacity() override {
        max_load_capacity = 10;
    }
    void SetFuelConsumption() override {
        fuel_consumption = 30;
    }
};

class Ship : public Transport {
    void SetDeliveryCost() override {
        delivery_cost = 1460;
    }
    void SetMaxLoadCapacity() override {
        max_load_capacity = 10000;
    }
    void SetFuelConsumption() override {
        fuel_consumption = 100;
    }
};

class Logistics {
public:
    virtual Transport* FactoryMethod() = 0;
    virtual void Deliver(Transport* transport, double distance) = 0;
};

class RoadLogistics : public Logistics {
public:
    virtual void Deliver(Transport* transport, double distance) {
        cout << "Delivered by truck:\n";
        cout << "Delivery Cost: " << transport->CalculateDeliveryCost(distance) << endl;
        cout << "Fuel was consumed: " << transport->CalculateFuelConsumption(distance) << endl;
    }

    Transport* FactoryMethod() override {
        Transport* transport = new Truck();
        transport->SetDeliveryCost();
        transport->SetMaxLoadCapacity();
        transport->SetFuelConsumption();
        return transport;
    }
};

class SeaLogistics : public Logistics {
public:
    virtual void Deliver(Transport* transport, double distance) {
        cout << "Delivered by ship:\n";
        cout << "Delivery Cost: " << transport->CalculateDeliveryCost(distance) << endl;
        cout << "Fuel was consumed: " << transport->CalculateFuelConsumption(distance) << endl;
    }

    Transport* FactoryMethod() override {
        Transport* transport = new Ship();
        transport->SetDeliveryCost();
        transport->SetMaxLoadCapacity();
        transport->SetFuelConsumption();
        return transport;
    }
};

void Factory(Logistics** logistics, int size) {
    for (int i = 0; i < size; i++)
    {
        Transport* transport = logistics[i]->FactoryMethod();
        logistics[i]->Deliver(transport, 230);
        cout << endl;
    }
}

int main() {

    Logistics* logistics[2];
    logistics[0] = new RoadLogistics();
    logistics[1] = new SeaLogistics();

    Factory(logistics, 2);

    return 0;
}
