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
    if (this->stocks[it] >= qty){
        int supplierCost = getEmployeeSalary(getEmployeeThatProduces(it));

        this->stocks[it] -= qty;
        this->money += supplierCost * qty; // Not sure if the money needs to be increased
        this->nbSupplied += qty;

        return supplierCost * qty;
    }
    return 0;
}

void Supplier::run() {
    interface->consoleAppendText(uniqueId, "[START] Supplier routine");

    while (this->money >= 10){ /*Maybe not right, but it is safe*/
        ItemType resourceSupplied = getRandomItemFromStock();
        int supplierCost = getEmployeeSalary(getEmployeeThatProduces(resourceSupplied));
        this->stocks[resourceSupplied]++;
        this->money -= supplierCost;

        /* Temps aléatoire borné qui simule l'attente du travail fini*/
        interface->simulateWork();
        //TODO
        //I don't know what to implement after this TODO
        nbSupplied++;

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
