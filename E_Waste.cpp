#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class User
{
private:
    int userID;
    string name;
    string contact;
    string location;

public:
    User()
    {
        userID = 0;
        name = "Unknown";
        contact = "Unknown";
        location = "Unknown";
    }

    User(int id, string n, string c, string l)
    {
        userID = id;
        name = n;
        contact = c;
        location = l;
    }

    void display()
    {
        cout << "\nUser ID       : " << userID;
        cout << "\nName          : " << name;
        cout << "\nContact       : " << contact;
        cout << "\nLocation      : " << location << "\n";
    }

    string getName()
    {
        return name;
    }

    string getLocation()
    {
        return location;
    }
};

class Component
{
protected:
    int componentID;
    string componentName;
    double weight;
    double condition;
    int quantity;
    bool hazardous;
    double recoveryValuePerKg;

public:
    Component()
    {
        componentID = 0;
        componentName = "Unknown";
        weight = 0;
        condition = 0;
        quantity = 1;
        hazardous = false;
        recoveryValuePerKg = 0;
    }

    Component(int id, string name, double w, double c, int q,
              bool h, double value)
    {
        componentID = id;
        componentName = name;
        weight = w;
        condition = c;
        quantity = q;
        hazardous = h;
        recoveryValuePerKg = value;
    }

    virtual string getComponentType() = 0;

    virtual string getRecoveryMethod()
    {
        if (condition >= 70)
            return "Reuse";

        if (condition >= 40)
            return "Repair/Reuse";

        return "Material Recovery";
    }

    virtual double calculateRecoveryValue()
    {
        double efficiency = (100 - condition) / 100.0;

        if (efficiency < 0)
            efficiency = 0;

        return weight * quantity * recoveryValuePerKg * efficiency;
    }

    double calculateRecoveryValue(double efficiency)
    {
        return weight * quantity * recoveryValuePerKg * efficiency;
    }

    virtual void display()
    {
        cout << "\nComponent ID      : " << componentID;
        cout << "\nComponent Type    : " << getComponentType();
        cout << "\nComponent Name    : " << componentName;
        cout << "\nWeight            : " << weight << " kg";
        cout << "\nCondition         : " << condition << "%";
        cout << "\nQuantity          : " << quantity;
        cout << "\nHazardous         : ";

        if (hazardous)
            cout << "Yes";
        else
            cout << "No";

        cout << "\nRecovery Method   : " << getRecoveryMethod();
        cout << "\nRecovery Value    : Rs. "
             << calculateRecoveryValue() << "\n";
    }

    int getComponentID()
    {
        return componentID;
    }

    string getComponentName()
    {
        return componentName;
    }

    double getWeight()
    {
        return weight;
    }

    double getCondition()
    {
        return condition;
    }w

    int getQuantity()
    {
        return quantity;
    }

    bool isHazardous()
    {
        return hazardous;
    }

    virtual ~Component()
    {
    }
};

class RAM : public Component
{
public:
    RAM(int id, double w, double c, int q)
        : Component(id, "RAM", w, c, q, false, 500)
    {
    }

    string getComponentType() override
    {
        return "RAM";
    }
};

class ROM : public Component
{
public:
    ROM(int id, double w, double c, int q)
        : Component(id, "ROM", w, c, q, false, 400)
    {
    }

    string getComponentType() override
    {
        return "ROM";
    }
};

class Battery : public Component
{
public:
    Battery(int id, double w, double c, int q)
        : Component(id, "Battery", w, c, q, true, 150)
    {
    }

    string getComponentType() override
    {
        return "Battery";
    }

    string getRecoveryMethod() override
    {
        return "Specialized Battery Recycling";
    }
};

class Charger : public Component
{
public:
    Charger(int id, double w, double c, int q)
        : Component(id, "Charger", w, c, q, false, 250)
    {
    }

    string getComponentType() override
    {
        return "Charger";
    }
};

class Glass : public Component
{
public:
    Glass(int id, double w, double c, int q)
        : Component(id, "Glass", w, c, q, false, 30)
    {
    }

    string getComponentType() override
    {
        return "Glass";
    }
};

class Copper : public Component
{
public:
    Copper(int id, double w, double c, int q)
        : Component(id, "Copper", w, c, q, false, 700)
    {
    }

    string getComponentType() override
    {
        return "Copper";
    }
};

class Plastic : public Component
{
public:
    Plastic(int id, double w, double c, int q)
        : Component(id, "Plastic", w, c, q, false, 30)
    {
    }

    string getComponentType() override
    {
        return "Plastic";
    }
};

class GenericComponent : public Component
{
public:
    GenericComponent(int id, string name, double w, double c,
                     int q, bool h, double value)
        : Component(id, name, w, c, q, h, value)
    {
    }

    string getComponentType() override
    {
        return "Other";
    }
};

class EWaste
{
protected:
    int productID;
    string productName;
    string company;
    double weight;
    int quantity;
    double damagePercentage;

    Component* components[20];
    int componentCount;

public:
    EWaste()
    {
        productID = 0;
        productName = "Unknown";
        company = "Unknown";
        weight = 0;
        quantity = 1;
        damagePercentage = 0;
        componentCount = 0;
    }

    EWaste(int id, string name, string comp, double w,
           int q, double damage)
    {
        productID = id;
        productName = name;
        company = comp;
        weight = w;
        quantity = q;
        damagePercentage = damage;
        componentCount = 0;
    }

    virtual string getProductType() = 0;

    void addComponent(Component* component)
    {
        if (componentCount < 20)
        {
            components[componentCount] = component;
            componentCount++;
        }
    }

    Component** getComponents()
    {
        return components;
    }

    int getComponentCount()
    {
        return componentCount;
    }

    virtual void display()
    {
        cout << "\n========================================";
        cout << "\nProduct ID       : " << productID;
        cout << "\nProduct Type     : " << getProductType();
        cout << "\nProduct Name     : " << productName;
        cout << "\nCompany          : " << company;
        cout << "\nWeight           : " << weight << " kg";
        cout << "\nQuantity         : " << quantity;
        cout << "\nDamage           : " << damagePercentage << "%";
        cout << "\n========================================";

        cout << "\n\nComponents:\n";

        if (componentCount == 0)
        {
            cout << "No components added.\n";
        }
        else
        {
            for (int i = 0; i < componentCount; i++)
            {
                components[i]->display();
            }
        }
    }

    int getProductID()
    {
        return productID;
    }

    string getProductName()
    {
        return productName;
    }

    string getCompany()
    {
        return company;
    }

    double getWeight()
    {
        return weight;
    }

    int getQuantity()
    {
        return quantity;
    }

    double getDamage()
    {
        return damagePercentage;
    }

    virtual ~EWaste()
    {
        for (int i = 0; i < componentCount; i++)
        {
            delete components[i];
        }
    }
};

class Laptop : public EWaste
{
public:
    Laptop(int id, string name, string company,
           double weight, int quantity, double damage)
        : EWaste(id, name, company, weight, quantity, damage)
    {
    }

    string getProductType() override
    {
        return "Laptop";
    }
};

class Mobile : public EWaste
{
public:
    Mobile(int id, string name, string company,
           double weight, int quantity, double damage)
        : EWaste(id, name, company, weight, quantity, damage)
    {
    }

    string getProductType() override
    {
        return "Mobile";
    }
};

class TV : public EWaste
{
public:
    TV(int id, string name, string company,
       double weight, int quantity, double damage)
        : EWaste(id, name, company, weight, quantity, damage)
    {
    }

    string getProductType() override
    {
        return "TV";
    }
};

class AC : public EWaste
{
public:
    AC(int id, string name, string company,
       double weight, int quantity, double damage)
        : EWaste(id, name, company, weight, quantity, damage)
    {
    }

    string getProductType() override
    {
        return "AC";
    }
};

class Refrigerator : public EWaste
{
public:
    Refrigerator(int id, string name, string company,
                 double weight, int quantity, double damage)
        : EWaste(id, name, company, weight, quantity, damage)
    {
    }

    string getProductType() override
    {
        return "Refrigerator";
    }
};

class WashingMachine : public EWaste
{
public:
    WashingMachine(int id, string name, string company,
                    double weight, int quantity, double damage)
        : EWaste(id, name, company, weight, quantity, damage)
    {
    }

    string getProductType() override
    {
        return "Washing Machine";
    }
};

class GenericProduct : public EWaste
{
public:
    GenericProduct(int id, string name, string company,
                   double weight, int quantity, double damage)
        : EWaste(id, name, company, weight, quantity, damage)
    {
    }

    string getProductType() override
    {
        return "Other";
    }
};

class WasteClassifier
{
public:
    string classify(double damage)
    {
        if (damage < 30)
            return "Reusable";

        if (damage < 50)
            return "Repairable";

        if (damage < 70)
            return "Recoverable";

        if (damage < 90)
            return "Recyclable";

        return "Recyclable";
    }

    string classify(double damage, bool hazardous)
    {
        if (hazardous)
            return "Hazardous";

        return classify(damage);
    }
};

class CollectionCenter
{
private:
    int centerID;
    string centerName;
    string location;
    double capacity;
    double currentLoad;

public:
    CollectionCenter(int id, string name, string loc, double cap)
    {
        centerID = id;
        centerName = name;
        location = loc;
        capacity = cap;
        currentLoad = 0;
    }

    bool canAccept(double amount)
    {
        return currentLoad + amount <= capacity;
    }

    bool addWaste(double amount)
    {
        if (amount <= 0)
            return false;

        if (canAccept(amount))
        {
            currentLoad += amount;
            return true;
        }

        return false;
    }

    int getID()
    {
        return centerID;
    }

    string getName()
    {
        return centerName;
    }

    string getLocation()
    {
        return location;
    }

    double getCapacity()
    {
        return capacity;
    }

    double getCurrentLoad()
    {
        return currentLoad;
    }

    double getAvailableCapacity()
    {
        return capacity - currentLoad;
    }

    void display()
    {
        cout << "\n========================================";
        cout << "\nCenter ID          : " << centerID;
        cout << "\nCenter Name        : " << centerName;
        cout << "\nLocation           : " << location;
        cout << "\nCapacity           : " << capacity << " kg";
        cout << "\nCurrent Load       : " << currentLoad << " kg";
        cout << "\nAvailable Capacity : "
             << getAvailableCapacity() << " kg";
        cout << "\n========================================\n";
    }
};

class RecoveryPlanner
{
public:
    void generateRecoveryPlan(EWaste* product)
    {
        WasteClassifier classifier;

        cout << "\n========================================";
        cout << "\n          RECOVERY PLAN";
        cout << "\n========================================";

        cout << "\nProduct: " << product->getProductName();

        string decision =
            classifier.classify(product->getDamage());

        cout << "\nCategory: " << decision;

        if (decision == "Reusable")
        {
            cout << "\nAction: Reuse the product directly.";
        }
        else if (decision == "Repairable")
        {
            cout << "\nAction: Send product for repair.";
        }
        else if (decision == "Recoverable")
        {
            cout << "\nAction: Recover usable components.";
        }
        else
        {
            cout << "\nAction: Send product for recycling.";
        }

        cout << "\n\nComponent Recovery Analysis:\n";

        double totalValue = 0;

        Component** componentList =
            product->getComponents();

        int componentCount =
            product->getComponentCount();

        for (int i = 0; i < componentCount; i++)
        {
            Component* c = componentList[i];

            cout << "\n----------------------------------------";
            cout << "\nComponent       : "
                 << c->getComponentName();

            cout << "\nType            : "
                 << c->getComponentType();

            cout << "\nCondition       : "
                 << c->getCondition() << "%";

            cout << "\nRecovery Method : "
                 << c->getRecoveryMethod();

            double value =
                c->calculateRecoveryValue();

            cout << "\nRecovery Value  : Rs. "
                 << value;

            totalValue += value;

            if (c->isHazardous())
            {
                cout << "\nStatus          : HAZARDOUS";
            }
        }

        cout << "\n\nTotal Recovery Value: Rs. "
             << totalValue << "\n";
    }
};

class CSVManager
{
public:
    void saveProduct(EWaste* product)
    {
        ofstream file("products.csv", ios::app);

        if (!file)
        {
            cout << "\nError opening products.csv";
            return;
        }

        WasteClassifier classifier;

        file << product->getProductID() << ","
             << product->getProductType() << ","
             << product->getProductName() << ","
             << product->getCompany() << ","
             << product->getWeight() << ","
             << product->getQuantity() << ","
             << product->getDamage() << ","
             << classifier.classify(product->getDamage())
             << "\n";

        file.close();
    }

    void saveComponents(EWaste* product)
    {
        ofstream file("components.csv", ios::app);

        if (!file)
        {
            cout << "\nError opening components.csv";
            return;
        }

        Component** componentList =
            product->getComponents();

        int componentCount =
            product->getComponentCount();

        for (int i = 0; i < componentCount; i++)
        {
            Component* c = componentList[i];

            file << c->getComponentID() << ","
                 << product->getProductID() << ","
                 << c->getComponentName() << ","
                 << c->getWeight() << ","
                 << c->getQuantity() << ","
                 << c->getCondition() << ","
                 << (c->isHazardous() ? "Yes" : "No") << ","
                 << c->getRecoveryMethod() << ","
                 << c->calculateRecoveryValue()
                 << "\n";
        }

        file.close();
    }

    void saveCollectionCenter(CollectionCenter* center)
    {
        ofstream file("collection_centers.csv", ios::app);

        if (!file)
        {
            cout << "\nError opening collection_centers.csv";
            return;
        }

        file << center->getID() << ","
             << center->getName() << ","
             << center->getLocation() << ","
             << center->getCapacity() << ","
             << center->getCurrentLoad() << ","
             << center->getAvailableCapacity()
             << "\n";

        file.close();
    }
};

class ReportGenerator
{
public:
    void generateReport(
        EWaste* products[],
        int productCount,
        CollectionCenter* centers[],
        int centerCount)
    {
        ofstream file("ewaste_report.txt");

        if (!file)
        {
            cout << "\nUnable to create report.";
            return;
        }

        WasteClassifier classifier;

        int reusable = 0;
        int repairable = 0;
        int recoverable = 0;
        int recyclable = 0;
        int hazardousCount = 0;

        double totalWeight = 0;
        double totalRecoveryValue = 0;

        for (int i = 0; i < productCount; i++)
        {
            EWaste* product = products[i];

            string category =
                classifier.classify(
                    product->getDamage()
                );

            if (category == "Reusable")
                reusable++;

            else if (category == "Repairable")
                repairable++;

            else if (category == "Recoverable")
                recoverable++;

            else
                recyclable++;

            totalWeight +=
                product->getWeight() *
                product->getQuantity();

            Component** componentList =
                product->getComponents();

            int componentCount =
                product->getComponentCount();

            for (int j = 0; j < componentCount; j++)
            {
                Component* c =
                    componentList[j];

                totalRecoveryValue +=
                    c->calculateRecoveryValue();

                if (c->isHazardous())
                    hazardousCount++;
            }
        }

        file << "========================================\n";
        file << "       E-WASTE MANAGEMENT REPORT\n";
        file << "========================================\n\n";

        file << "Total Products       : "
             << productCount << "\n";

        file << "Total E-Waste Weight : "
             << totalWeight << " kg\n\n";

        file << "----------------------------------------\n";
        file << "WASTE CLASSIFICATION\n";
        file << "----------------------------------------\n";

        file << "Reusable             : "
             << reusable << "\n";

        file << "Repairable           : "
             << repairable << "\n";

        file << "Recoverable          : "
             << recoverable << "\n";

        file << "Recyclable           : "
             << recyclable << "\n\n";

        file << "----------------------------------------\n";
        file << "RECOVERY INFORMATION\n";
        file << "----------------------------------------\n";

        file << "Estimated Recovery Value : Rs. "
             << totalRecoveryValue << "\n";

        file << "Hazardous Components    : "
             << hazardousCount << "\n\n";

        file << "----------------------------------------\n";
        file << "COLLECTION CENTERS\n";
        file << "----------------------------------------\n";

        for (int i = 0; i < centerCount; i++)
        {
            CollectionCenter* center =
                centers[i];

            file << "\nCenter ID       : "
                 << center->getID();

            file << "\nCenter Name     : "
                 << center->getName();

            file << "\nLocation        : "
                 << center->getLocation();

            file << "\nCapacity        : "
                 << center->getCapacity()
                 << " kg";

            file << "\nCurrent Load    : "
                 << center->getCurrentLoad()
                 << " kg";

            file << "\nAvailable       : "
                 << center->getAvailableCapacity()
                 << " kg\n";
        }

        file << "\n========================================\n";

        file.close();

        cout << "\nReport generated successfully.";
        cout << "\nFile: ewaste_report.txt\n";
    }
};

Component* createComponent(int componentID)
{
    int choice;
    double weight;
    double condition;
    int quantity;

    cout << "\n========== COMPONENT ==========";
    cout << "\n1. RAM";
    cout << "\n2. ROM";
    cout << "\n3. Battery";
    cout << "\n4. Charger";
    cout << "\n5. Glass";
    cout << "\n6. Copper";
    cout << "\n7. Plastic";
    cout << "\n8. Other";

    cout << "\nEnter component type: ";
    cin >> choice;

    cout << "Enter weight of ONE component (kg): ";
    cin >> weight;

    cout << "Enter condition (0-100%): ";
    cin >> condition;

    cout << "Enter quantity: ";
    cin >> quantity;

    if (choice == 1)
        return new RAM(
            componentID,
            weight,
            condition,
            quantity
        );

    if (choice == 2)
        return new ROM(
            componentID,
            weight,
            condition,
            quantity
        );

    if (choice == 3)
        return new Battery(
            componentID,
            weight,
            condition,
            quantity
        );

    if (choice == 4)
        return new Charger(
            componentID,
            weight,
            condition,
            quantity
        );

    if (choice == 5)
        return new Glass(
            componentID,
            weight,
            condition,
            quantity
        );

    if (choice == 6)
        return new Copper(
            componentID,
            weight,
            condition,
            quantity
        );

    if (choice == 7)
        return new Plastic(
            componentID,
            weight,
            condition,
            quantity
        );

    string name;
    double value;
    char h;

    cout << "Enter component name: ";
    cin >> name;

    cout << "Is it hazardous? (Y/N): ";
    cin >> h;

    cout << "Enter recovery value per kg: ";
    cin >> value;

    bool hazardous =
        (h == 'Y' || h == 'y');

    return new GenericComponent(
        componentID,
        name,
        weight,
        condition,
        quantity,
        hazardous,
        value
    );
}

EWaste* createProduct()
{
    int type;
    int id;
    string name;
    string company;
    double weight;
    int quantity;
    double damage;

    cout << "\n========================================";
    cout << "\n          ADD E-WASTE PRODUCT";
    cout << "\n========================================";

    cout << "\n1. Laptop";
    cout << "\n2. Mobile";
    cout << "\n3. TV";
    cout << "\n4. AC";
    cout << "\n5. Refrigerator";
    cout << "\n6. Washing Machine";
    cout << "\n7. Other";

    cout << "\nEnter product type: ";
    cin >> type;

    cout << "Enter Product ID: ";
    cin >> id;

    cout << "Enter Product Name: ";
    cin >> name;

    cout << "Enter Company: ";
    cin >> company;

    cout << "Enter Weight (kg): ";
    cin >> weight;

    cout << "Enter Quantity: ";
    cin >> quantity;

    cout << "Enter Damage Percentage (0-100): ";
    cin >> damage;

    EWaste* product = nullptr;

    if (type == 1)
    {
        product = new Laptop(
            id,
            name,
            company,
            weight,
            quantity,
            damage
        );
    }
    else if (type == 2)
    {
        product = new Mobile(
            id,
            name,
            company,
            weight,
            quantity,
            damage
        );
    }
    else if (type == 3)
    {
        product = new TV(
            id,
            name,
            company,
            weight,
            quantity,
            damage
        );
    }
    else if (type == 4)
    {
        product = new AC(
            id,
            name,
            company,
            weight,
            quantity,
            damage
        );
    }
    else if (type == 5)
    {
        product = new Refrigerator(
            id,
            name,
            company,
            weight,
            quantity,
            damage
        );
    }
    else if (type == 6)
    {
        product = new WashingMachine(
            id,
            name,
            company,
            weight,
            quantity,
            damage
        );
    }
    else
    {
        product = new GenericProduct(
            id,
            name,
            company,
            weight,
            quantity,
            damage
        );
    }

    int numberOfComponents;

    cout << "\nHow many components does this product have? ";
    cin >> numberOfComponents;

    for (int i = 1; i <= numberOfComponents; i++)
    {
        Component* component =
            createComponent(i);

        product->addComponent(component);
    }

    return product;
}

void displayAllProducts(
    EWaste* products[],
    int productCount)
{
    if (productCount == 0)
    {
        cout << "\nNo products available.";
        return;
    }

    for (int i = 0; i < productCount; i++)
    {
        products[i]->display();
    }
}

void generateRecoveryPlan(
    EWaste* products[],
    int productCount)
{
    if (productCount == 0)
    {
        cout << "\nNo products available.";
        return;
    }

    int id;

    cout << "\nEnter Product ID: ";
    cin >> id;

    for (int i = 0; i < productCount; i++)
    {
        if (products[i]->getProductID() == id)
        {
            RecoveryPlanner planner;

            planner.generateRecoveryPlan(
                products[i]
            );

            return;
        }
    }

    cout << "\nProduct not found.";
}

void addCollectionCenter(
    CollectionCenter* centers[],
    int& centerCount,
    CSVManager& csvManager)
{
    if (centerCount >= 20)
    {
        cout << "\nMaximum collection centers reached.";
        return;
    }

    int id;
    string name;
    string location;
    double capacity;

    cout << "\n========== ADD COLLECTION CENTER ==========";

    cout << "\nEnter Center ID: ";
    cin >> id;

    cout << "Enter Center Name: ";
    cin >> name;

    cout << "Enter Location: ";
    cin >> location;

    cout << "Enter Capacity (kg): ";
    cin >> capacity;

    CollectionCenter* center =
        new CollectionCenter(
            id,
            name,
            location,
            capacity
        );

    centers[centerCount] = center;
    centerCount++;

    csvManager.saveCollectionCenter(center);

    cout << "\nCollection center added successfully.";
}

void displayCollectionCenters(
    CollectionCenter* centers[],
    int centerCount)
{
    if (centerCount == 0)
    {
        cout << "\nNo collection centers available.";
        return;
    }

    for (int i = 0; i < centerCount; i++)
    {
        centers[i]->display();
    }
}

void assignWaste(
    EWaste* products[],
    int productCount,
    CollectionCenter* centers[],
    int centerCount)
{
    if (productCount == 0)
    {
        cout << "\nNo products available.";
        return;
    }

    if (centerCount == 0)
    {
        cout << "\nNo collection centers available.";
        return;
    }

    int productID;
    double amount;

    cout << "\nEnter Product ID: ";
    cin >> productID;

    cout << "Enter Waste Weight to Assign (kg): ";
    cin >> amount;

    bool productFound = false;

    for (int i = 0; i < productCount; i++)
    {
        if (products[i]->getProductID() == productID)
        {
            productFound = true;

            for (int j = 0; j < centerCount; j++)
            {
                if (centers[j]->addWaste(amount))
                {
                    cout << "\nWaste assigned successfully.";

                    cout << "\nCollection Center: "
                         << centers[j]->getName();

                    cout << "\nLocation: "
                         << centers[j]->getLocation();

                    return;
                }
            }
        }
    }

    if (!productFound)
    {
        cout << "\nProduct not found.";
    }
    else
    {
        cout << "\nNo collection center has enough capacity.";
    }
}

int main()
{
    EWaste* products[100];
    int productCount = 0;

    CollectionCenter* centers[20];
    int centerCount = 0;

    CSVManager csvManager;
    ReportGenerator reportGenerator;

    int choice;

    do
    {
        cout << "\n\n========================================";
        cout << "\n     E-WASTE COLLECTION & RECOVERY";
        cout << "\n              PLANNER";
        cout << "\n========================================";

        cout << "\n1. Add E-Waste Product";
        cout << "\n2. Display All Products";
        cout << "\n3. Generate Recovery Plan";
        cout << "\n4. Add Collection Center";
        cout << "\n5. Assign Waste to Collection Center";
        cout << "\n6. Display Collection Centers";
        cout << "\n7. Generate Final Report";
        cout << "\n8. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            if (productCount >= 100)
            {
                cout << "\nMaximum product limit reached.";
            }
            else
            {
                EWaste* product =
                    createProduct();

                products[productCount] =
                    product;

                productCount++;

                csvManager.saveProduct(product);
                csvManager.saveComponents(product);

                cout << "\nProduct successfully added.";
                cout << "\nData saved to CSV files.";
            }
        }

        else if (choice == 2)
        {
            displayAllProducts(
                products,
                productCount
            );
        }

        else if (choice == 3)
        {
            generateRecoveryPlan(
                products,
                productCount
            );
        }

        else if (choice == 4)
        {
            addCollectionCenter(
                centers,
                centerCount,
                csvManager
            );
        }

        else if (choice == 5)
        {
            assignWaste(
                products,
                productCount,
                centers,
                centerCount
            );
        }

        else if (choice == 6)
        {
            displayCollectionCenters(
                centers,
                centerCount
            );
        }

        else if (choice == 7)
        {
            reportGenerator.generateReport(
                products,
                productCount,
                centers,
                centerCount
            );
        }

        else if (choice == 8)
        {
            cout << "\nGenerating final report...";

            reportGenerator.generateReport(
                products,
                productCount,
                centers,
                centerCount
            );

            cout << "\nProgram terminated.";
        }

        else
        {
            cout << "\nInvalid choice.";
        }

    } while (choice != 8);

    for (int i = 0; i < productCount; i++)
    {
        delete products[i];
    }

    for (int i = 0; i < centerCount; i++)
    {
        delete centers[i];
    }

    return 0;
}