/**
 * @authors : Gruber Adam, Pittet Axel
 */
#include "clinic.h"
#include "costs.h"
#include <pcosynchro/pcothread.h>
#include <iostream>

IWindowInterface* Clinic::interface = nullptr;

Clinic::Clinic(int uniqueId, int fund, std::vector<ItemType> resourcesNeeded)
    : Seller(fund, uniqueId), nbTreated(0), resourcesNeeded(resourcesNeeded)
{
    interface->updateFund(uniqueId, fund);
    interface->consoleAppendText(uniqueId, "Factory created");

    for(const auto& item : resourcesNeeded) {
        stocks[item] = 0;
    }
}

bool Clinic::verifyResources() {
    for (auto item : resourcesNeeded) {
        if (stocks[item] == 0) {
            return false;
        }
    }
    return true;
}

int Clinic::request(ItemType what, int qty){
    if (what != ItemType::PatientHealed) return 0;

    const int bill = getCostPerUnit(what) * qty;

    mutex.lock();

    if (stocks[what] >= qty){
        stocks[what] -= qty;
        money += bill;

        mutex.unlock();
        return bill;
    }
    mutex.unlock();
    return 0;
}

void Clinic::treatPatient() {
    //Temps simulant un traitement 
    interface->simulateWork();
    const int salary = getEmployeeSalary(getEmployeeThatProduces(ItemType::PatientHealed));

    mutex.lock();

    for(ItemType item : resourcesNeeded){
        this->stocks[item]--;
    }
    if(money >= salary) {
        money -= salary;
        ++nbTreated;
        ++stocks[ItemType::PatientHealed];

        interface->consoleAppendText(uniqueId, "Clinic have healed a new patient");
    }
    mutex.unlock();
}

void Clinic::orderResources() {
    //Find missing resource
    const int qtyOfResource = 1;
    for (auto item : resourcesNeeded) {
        if (stocks[item] == 0) {
            //Check if enough money
            if (money < getCostPerUnit(item) * qtyOfResource) return;

            int bill = 0;
            if (item == ItemType::PatientSick) {
                bill = Seller::chooseRandomSeller(this->hospitals)->request(ItemType::PatientSick, qtyOfResource);
            } else {
                bill = Seller::chooseRandomSeller(this->suppliers)->request(item, qtyOfResource);
            }
            if (bill) {
                mutex.lock();

                money -= bill;
                stocks[item]+= qtyOfResource;

                mutex.unlock();
            }
        }
    }
}

void Clinic::run() {
    if (hospitals.empty() || suppliers.empty()) {
        std::cerr << "You have to give to hospitals and suppliers to run a clinic" << std::endl;
        return;
    }
    interface->consoleAppendText(uniqueId, "[START] Factory routine");

    while (!PcoThread::thisThread()->stopRequested()) {
        if (verifyResources()) {
            treatPatient();
        } else {
            orderResources();
        }
       
        interface->simulateWork();

        interface->updateFund(uniqueId, money);
        interface->updateStock(uniqueId, &stocks);
    }
    interface->consoleAppendText(uniqueId, "[STOP] Factory routine");
}


void Clinic::setHospitalsAndSuppliers(std::vector<Seller*> hospitals, std::vector<Seller*> suppliers) {
    this->hospitals = hospitals;
    this->suppliers = suppliers;

    for (Seller* hospital : hospitals) {
        interface->setLink(uniqueId, hospital->getUniqueId());
    }
    for (Seller* supplier : suppliers) {
        interface->setLink(uniqueId, supplier->getUniqueId());
    }
}

int Clinic::getTreatmentCost() {
    return 0;
}

int Clinic::getWaitingPatients() {
    return stocks[ItemType::PatientSick];
}

int Clinic::getNumberPatients(){
    return stocks[ItemType::PatientSick] + stocks[ItemType::PatientHealed];
}

int Clinic::send(ItemType it, int qty, int bill){
    return 0;
}

int Clinic::getAmountPaidToWorkers() {
    return nbTreated * getEmployeeSalary(getEmployeeThatProduces(ItemType::PatientHealed));
}

void Clinic::setInterface(IWindowInterface *windowInterface) {
    interface = windowInterface;
}

std::map<ItemType, int> Clinic::getItemsForSale() {
    return stocks;
}


Pulmonology::Pulmonology(int uniqueId, int fund) :
    Clinic::Clinic(uniqueId, fund, {ItemType::PatientSick, ItemType::Pill, ItemType::Thermometer}) {}

Cardiology::Cardiology(int uniqueId, int fund) :
    Clinic::Clinic(uniqueId, fund, {ItemType::PatientSick, ItemType::Syringe, ItemType::Stethoscope}) {}

Neurology::Neurology(int uniqueId, int fund) :
    Clinic::Clinic(uniqueId, fund, {ItemType::PatientSick, ItemType::Pill, ItemType::Scalpel}) {}
