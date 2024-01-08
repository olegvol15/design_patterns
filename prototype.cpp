#include <iostream>
#include <vector>
using namespace std;

class AbstractPart
{
public:
    virtual AbstractPart* Clone() ;
};

class Engine : public AbstractPart {
    int cylinders;
    double fuelConsumption;
public:
    int GetCylinders() {
        return cylinders;
    }
    double GetFuelConsumption() {
        return fuelConsumption;
    }
    void SetCylinders(int cylinders) {
        this->cylinders = cylinders;
    }
    void SetFuelConsumption(double fuelConsumption) {
        this->fuelConsumption = fuelConsumption;
    }

    AbstractPart* Clone() override {
        Engine* engine = new Engine;
        *engine = *this;
        return engine;
    }
};

class GearBox : public AbstractPart {
    int numOfTransmissions;
public:
    int GetNumOfTransmissions() {
        return numOfTransmissions;
    }
    void SetNumOfTransmissions(int numOfTransmissions) {
        this->numOfTransmissions = numOfTransmissions;
    }

    AbstractPart* Clone() override {
        GearBox* gearbox = new GearBox;
        *gearbox = *this;
        return gearbox;
    }
};

class Body : public AbstractPart {
    string color;
    string bodyType;
public:
    string GetColor() {
        return color;
    }
    string GetBodyType() {
        return bodyType;
    }
    void SetColor(string color) {
        this->color = color;
    }
    void SetBodyType(string bodyType) {
        this->bodyType = bodyType;
    }

    AbstractPart* Clone() override {
        Body* body = new Body;
        *body = *this;
        return body;
    }
};

class Wheel : public AbstractPart {
    double radius;
    bool isStudded;
public:
    double GetRadius() {
        return radius;
    }
    bool GetIsStudded() {
        return isStudded;
    }
    void SetRadius(double radius) {
        this->radius = radius;
    }
    void SetIsStudded(bool isStudded) {
        this->isStudded = isStudded;
    }

    AbstractPart* Clone() override {
        Wheel* wheel = new Wheel;
        *wheel = *this;
        return wheel;
    }
};

class GasTank : public AbstractPart {
    double fuelVolume;
public:
    double GetFuelVolume() {
        return fuelVolume;
    }
    void SetFuelVolume(double fuelVolume) {
        this->fuelVolume = fuelVolume;
    }
    AbstractPart* Clone() override {
        GasTank* gasTank = new GasTank;
        *gasTank = *this;
        return gasTank;
    }
};

class Prototype {
public:
    virtual Prototype* Clone();
};

class Car : public Prototype {
    Engine* engine;
    GearBox* gearbox;
    Body* body;
    GasTank* gasTank;
    vector<Wheel*> wheels;
public:
    Engine* GetEngine()
    {
        return this->engine;
    }
    void SetEngine(Engine* engine)
    {
        this->engine = engine;
    }
    GearBox* GetGearBox()
    {
        return this->gearbox;
    }
    void SetGearBox(GearBox* gearbox)
    {
        this->gearbox = gearbox;
    }
    Body* GetBody()
    {
        return this->body;
    }
    void SetBody(Body* body)
    {
        this->body = body;
    }
    GasTank* GetGasTank()
    {
        return this->gasTank;
    }
    void SetGasTank(GasTank* gasTank)
    {
        this->gasTank = gasTank;
    }
    std::vector<Wheel*>& GetWheels()
    {
        return wheels;
    }
    void AddWheel(Wheel* wheel)
    {
        wheels.push_back(wheel);
    }

    Prototype* Clone() override {
        Car* car = new Car;
        car->engine = this->engine != nullptr ? (Engine*)this->engine->Clone() : nullptr;
        car->gearbox = this->gearbox != nullptr ? (GearBox*)this->gearbox->Clone() : nullptr;
        car->body = this->body != nullptr ? (Body*)this->body->Clone() : nullptr;
        car->gasTank = this->gasTank != nullptr ? (GasTank*)this->gasTank->Clone() : nullptr;
        for (Wheel* wheel : this->wheels)
        {
            if (wheel != nullptr)
            {
                car->AddWheel((Wheel*)wheel->Clone());
            }
        }
        return car;
    }
};

void PrintCar(Car* car) {
    cout << "Car: " << std::endl;
    cout << "Body: " << car->GetBody()->GetColor() << endl;
    cout << "Engine: \n\tCylinders: " << car->GetEngine()->GetCylinders() << "\n\tFuel Consumption: " << car->GetEngine()->GetFuelConsumption() << endl;
    cout << "Gear Box: \n\tNumber of Transmissions: " << car->GetGearBox()->GetNumOfTransmissions() << std::endl;
    cout << "Gas Tank: \n\tFuel Volume: " << car->GetGasTank()->GetFuelVolume() << endl;
    cout << "Wheels: ";
    for (Wheel* wheel : car->GetWheels())
    {
        cout << "\n\tRadius: " << wheel->GetRadius() << "\tIs Studded: " << wheel->GetIsStudded();
    }
    cout << endl;
}

int main() {

    Car* car = new Car();

    Body* body = new Body();
    body->SetColor("Black");
    car->SetBody(body);

    Engine* engine = new Engine();
    engine->SetCylinders(4);
    engine->SetFuelConsumption(2.3);
    car->SetEngine(engine);

    GearBox* gearbox = new GearBox();
    gearbox->SetNumOfTransmissions(5);
    car->SetGearBox(gearbox);

    GasTank* gasTank = new GasTank();
    gasTank->SetFuelVolume(50);
    car->SetGasTank(gasTank);

    Wheel* wheel = new Wheel();
    wheel->SetRadius(7);
    wheel->SetIsStudded(false);
    for (size_t i = 0; i < 4; i++)
    {
        car->AddWheel(wheel);
    }

    Car* myNewCar = dynamic_cast<Car*>(car->Clone());

    delete car;

    PrintCar(myNewCar);

    return 0;
}
