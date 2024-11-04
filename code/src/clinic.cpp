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
    if (stocks[what] >= qty){
        stocks[what] -= qty;
        //Not sure if the price should be updated
        int price = getCostPerUnit(ItemType::PatientHealed) * qty;
        this->money += price;
        return price;
    }
    return 0;
}

void Clinic::treatPatient() {
    for(ItemType item : resourcesNeeded){
        this->stocks[item]--;
    }
    //Temps simulant un traitement 
    interface->simulateWork();

    this->money -= getEmployeeSalary(getEmployeeThatProduces(ItemType::PatientHealed));
    this->nbTreated++;
    this->stocks[ItemType::PatientHealed]++;
    interface->consoleAppendText(uniqueId, "Clinic have healed a new patient");
}

void Clinic::orderResources() {
    //Request a sick patient from hospital
    int nbOfPatient;
    Seller* hospital = Seller::chooseRandomSeller(this->hospitals); // Not sure if the static call is the right one
    nbOfPatient = hospital->request(ItemType::PatientSick, 2); // TODO WORK with the return
    if(nbOfPatient == 0) interface->consoleAppendText(uniqueId, "Clinic has found no sickPatient"); // TO REMOVE DEBUG MESSAGE
    else stocks[ItemType::PatientSick]+= nbOfPatient;


    //Something might be wrong, and a function already exists
    std::map<ItemType, int> tempItems;
    for (auto item : resourcesNeeded) {
        if(item != ItemType::PatientSick){
            tempItems[item] = 1;
        }
    }
    //Request a new resource from supplier
    ItemType item = Seller::chooseRandomItem(tempItems);
    Seller* supplier = Seller::chooseRandomSeller(this->suppliers); // Not sure if the static call is the right one
    int amountToPay = 0;
    amountToPay = supplier->request(item, 1);
    this->money -= amountToPay;

    stocks[item]++;

}

void Clinic::run() {
    if (hospitals.empty() || suppliers.empty()) {
        std::cerr << "You have to give to hospitals and suppliers to run a clinic" << std::endl;
        return;
    }
    interface->consoleAppendText(uniqueId, "[START] Factory routine");

    while (this->nbTreated <= 900 /*Idk what to put*/) {
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
