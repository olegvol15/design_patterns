#include <iostream>
using namespace std;

class Herbivore_Animal {
protected:
    int weight;
    bool life;
public:
    virtual void SetWeight();
    void SetLife(bool life) {
        this->life= life;
    };
    bool GetLife() {
        return life;
    }
    int GetWeight() {
        return weight;
    }
    void Eat_Grass() {
        weight += 10;
        cout << "Herbivore ate grass. His weight now " << weight << endl;
    }
};

class Wildebeest : public Herbivore_Animal {
public:
    void SetWeight() override {
        weight = rand() % (274-168) + 168;
    }
};

class Bison : public Herbivore_Animal {
public:
    void SetWeight() override {
        weight = rand() % (1200 - 700) + 700;
    }
};

class Elk : public Herbivore_Animal {
public:
    void SetWeight() override {
        weight = rand() % (600 - 360) + 360;
    }
};

class Carnivore_Animal {
protected:
    int power;
public:
    virtual void SetPower();
    void Eat(Herbivore_Animal* animal) {
        if (!animal->GetLife()) {
            return;
        }
        if (power > animal->GetWeight()) {
            power += 10;
            cout << "Carnivore ate herbivore. He's get stronger. Power: " << power << endl;
            animal->SetLife(false);
        } else {
            power -= 10;
            cout << "Carnivore couldn't eat herbivore. He's get weaker. Power: " << power << endl;
        }
    }
};

class Wolf : public Carnivore_Animal {
public:
    void SetPower() override {
        power = rand() % (1300 - 500) + 500;
    }
};

class Lion : public Carnivore_Animal {
public:
    void SetPower() override {
        power = rand() % (400 - 100) + 100;
    }
};

class Tiger : public Carnivore_Animal {
public:
    void SetPower() override {
        power = rand() % (800 - 300) + 300;
    }
};

class Continent {
public:
    virtual Herbivore_Animal* CreateHerbivoreAnimal();
    virtual Carnivore_Animal* CreateCarnivoreAnimal();
};

class Africa : public Continent {
public:
    Herbivore_Animal* CreateHerbivoreAnimal() {
        Herbivore_Animal* animal = new Wildebeest();
        animal->SetWeight();
        animal->SetLife(true);
        return animal;
    }
    Carnivore_Animal* CreateCarnivoreAnimal() {
        Carnivore_Animal* animal = new Lion();
        animal->SetPower();
        return animal;
    }
};

class North_America : public Continent {
public:
    Herbivore_Animal* CreateHerbivoreAnimal() {
        Herbivore_Animal* animal = new Bison();
        animal->SetWeight();
        animal->SetLife(true);
        return animal;
    }
    Carnivore_Animal* CreateCarnivoreAnimal() {
        Carnivore_Animal* animal = new Wolf();
        animal->SetPower();
        return animal;
    }
};

class Eurasia : public Continent {
public:
    Herbivore_Animal* CreateHerbivoreAnimal() {
        Herbivore_Animal* animal = new Elk();
        animal->SetWeight();
        animal->SetLife(true);
        return animal;
    }
    Carnivore_Animal* CreateCarnivoreAnimal() {
        Carnivore_Animal* animal = new Tiger();
        animal->SetPower();
        return animal;
    }
};

class Animal_World {
    Herbivore_Animal* herbivore[3];
    Carnivore_Animal* carnivore[3];
public:
    Animal_World(Continent* continent) {
        for (size_t i = 0; i < 3; i++)
        {
            herbivore[i] = continent->CreateHerbivoreAnimal();
            carnivore[i] = continent->CreateCarnivoreAnimal();
        }
    }
    void Meals_Herbivores() {
        for (size_t i = 0; i < 3; i++)
        {
            herbivore[i]->Eat_Grass();
        }
    }
    void Nutrition_Carnivores() {
        for (size_t i = 0; i < 3; i++)
        {
            for (size_t j = 0; j < 3; j++)
            {
                carnivore[i]->Eat(herbivore[j]);
            }
        }
    }
};

int main() {
    srand(time(0));

    Continent* continent = new Africa();
    
    Animal_World* world = new Animal_World(continent);

    cout << "Africa" << std::endl;
    world->Meals_Herbivores();
    world->Nutrition_Carnivores();

    delete continent;
    delete world;

    cout << "\nNorth America" << endl;
    continent = new North_America();
    world = new Animal_World(continent);

    world->Meals_Herbivores();
    world->Nutrition_Carnivores();

    delete continent;
    delete world;

    cout << "\nEurasia" << endl;
    continent = new Eurasia();
    world = new Animal_World(continent);

    world->Meals_Herbivores();
    world->Nutrition_Carnivores();

    delete continent;
    delete world;

    return 0;
}
