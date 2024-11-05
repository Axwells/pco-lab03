/**
 * @authors : Gruber Adam, Pittet Axel
 */
#include "hospital.h"
#include "costs.h"
#include "clinic.h"
#include <iostream>
#include <pcosynchro/pcothread.h>

IWindowInterface* Hospital::interface = nullptr;

Hospital::Hospital(int uniqueId, int fund, int maxBeds)
    : Seller(fund, uniqueId), maxBeds(maxBeds), currentBeds(0), nbHospitalised(0), nbFree(0)
{
    interface->updateFund(uniqueId, fund);
    interface->consoleAppendText(uniqueId, "Hospital Created with " + QString::number(maxBeds) + " beds");

    std::vector<ItemType> initialStocks = { ItemType::PatientHealed, ItemType::PatientSick };

    for(const auto& item : initialStocks) {
        stocks[item] = 0;
    }
}

int Hospital::request(ItemType what, int qty){
    if (what == ItemType::PatientSick) {
        mutex.lock();

        if (stocks[what] >= qty) {
            const int bill = getCostPerUnit(ItemType::PatientSick) * qty;
            stocks[what] -= qty;
            currentBeds -= qty;
            money += bill;

            mutex.unlock();
            return bill;
        }
        mutex.unlock();
    }
    return 0;
}

void Hospital::freeHealedPatient() {

    const int healedCount = recoveryQueue.size();

    for (int i = 0; i < healedCount; ++i) {
        int recoveryTime = recoveryQueue.front();
        recoveryQueue.pop();

        if (--recoveryTime == 0) {
            // Patient is healed
            --stocks[ItemType::PatientHealed];
            --currentBeds;
            ++nbFree;
        } else {
            //Patient did not recover enough yet
            recoveryQueue.push(recoveryTime);
        }
    }
}

void Hospital::transferPatientsFromClinic() {

    const auto clinic =  static_cast<Clinic*>(chooseRandomSeller(this->clinics));
    const int qty = clinic->getNumberPatients() - clinic->getWaitingPatients();
    const int bill = getCostPerUnit(ItemType::PatientHealed) * qty;
    const int salary = getEmployeeSalary(EmployeeType::Nurse) * qty;

    mutex.lock();

    if (money >= bill + salary && currentBeds + qty <= maxBeds) {
        if (clinic->request(ItemType::PatientHealed, qty) == bill) {
            stocks[ItemType::PatientHealed] += qty;
            currentBeds += qty;
            nbHospitalised += qty;
            for (int i = 0; i< qty; ++i){
                recoveryQueue.push(RECOVERY_TIME);
            }
            money -= bill;
            money -= salary;
        }
    }
    mutex.unlock();
}

int Hospital::send(ItemType it, int qty, int bill) {
    const int salary = getEmployeeSalary(EmployeeType::Nurse) * qty;
    mutex.lock();

    if(currentBeds + qty > maxBeds || money < bill + salary) {
        mutex.unlock();
        return 0;
    }
    stocks[ItemType::PatientSick] += qty;
    currentBeds += qty;
    nbHospitalised += qty;
    money -= bill;
    money -= salary;

    mutex.unlock();
    return 1;
}

void Hospital::run()
{
    if (clinics.empty()) {
        std::cerr << "You have to give clinics to a hospital before launching is routine" << std::endl;
        return;
    }

    interface->consoleAppendText(uniqueId, "[START] Hospital routine");

    while (!PcoThread::thisThread()->stopRequested()) {
        transferPatientsFromClinic();

        freeHealedPatient();

        interface->updateFund(uniqueId, money);
        interface->updateStock(uniqueId, &stocks);
        interface->simulateWork(); // Temps d'attente
    }

    interface->consoleAppendText(uniqueId, "[STOP] Hospital routine");
}

int Hospital::getAmountPaidToWorkers() {
    return nbHospitalised * getEmployeeSalary(EmployeeType::Nurse);
}

int Hospital::getNumberPatients(){
    return stocks[ItemType::PatientSick] + stocks[ItemType::PatientHealed] + nbFree;
}

std::map<ItemType, int> Hospital::getItemsForSale()
{
    return stocks;
}

void Hospital::setClinics(std::vector<Seller*> clinics){
    this->clinics = clinics;

    for (Seller* clinic : clinics) {
        interface->setLink(uniqueId, clinic->getUniqueId());
    }
}

void Hospital::setInterface(IWindowInterface* windowInterface){
    interface = windowInterface;
}
