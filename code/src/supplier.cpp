/**
 * @authors : Gruber Adam, Pittet Axel
 */
#include "supplier.h"
#include "costs.h"
#include <pcosynchro/pcothread.h>

IWindowInterface* Supplier::interface = nullptr;

Supplier::Supplier(int uniqueId, int fund, std::vector<ItemType> resourcesSupplied)
    : Seller(fund, uniqueId), resourcesSupplied(resourcesSupplied), nbSupplied(0) 
{
    for (const auto& item : resourcesSupplied) {    
        stocks[item] = 0;    
    }

    interface->consoleAppendText(uniqueId, QString("Supplier Created"));
    interface->updateFund(uniqueId, fund);
}

int Supplier::request(ItemType it, int qty) {
    const int bill = getCostPerUnit(it) * qty;
    mutex.lock();

    if (stocks[it] >= qty){
        stocks[it] -= qty;
        money += bill;

        mutex.unlock();
        return bill;
    }
    mutex.unlock();
    return 0;
}

void Supplier::run() {
    interface->consoleAppendText(uniqueId, "[START] Supplier routine");

    while (!PcoThread::thisThread()->stopRequested()){
        ItemType resourceSupplied = getRandomItemFromStock();
        const int supplierCost = getEmployeeSalary(getEmployeeThatProduces(resourceSupplied));

        /* Temps aléatoire borné qui simule l'attente du travail fini*/
        interface->simulateWork();

        mutex.lock();
        if (money >= supplierCost) {
            money -= supplierCost;
            ++stocks[resourceSupplied];
            ++nbSupplied;
        }
        mutex.unlock();

        interface->updateFund(uniqueId, money);
        interface->updateStock(uniqueId, &stocks);
    }
    interface->consoleAppendText(uniqueId, "[STOP] Supplier routine");
}

std::map<ItemType, int> Supplier::getItemsForSale() {
    return stocks;
}

int Supplier::getMaterialCost() {
    int totalCost = 0;
    for (const auto& item : resourcesSupplied) {
        totalCost += getCostPerUnit(item);
    }
    return totalCost;
}

int Supplier::getAmountPaidToWorkers() {
    return nbSupplied * getEmployeeSalary(EmployeeType::Supplier);
}

void Supplier::setInterface(IWindowInterface *windowInterface) {
    interface = windowInterface;
}

std::vector<ItemType> Supplier::getResourcesSupplied() const
{
    return resourcesSupplied;
}

int Supplier::send(ItemType it, int qty, int bill){
    return 0;
}
