#include <iostream>
#include <fstream>
#include "Header.h"



int main() {



    Customers customer;
    customer.login();
    customer.menu();

    int dishNumber;

    cout << "Enter dish number to add it to your order (or 0 to finish your order): ";

    cin >> dishNumber;


    while (dishNumber != 0) {
        customer.menu();
        customer.addToOrder(dishNumber);

        cout << "Enter dish number to add it to your order (or 0 to finish your order): ";

        cin >> dishNumber;

    }


    customer.printOrder();

    customer.saveOrder();

    return 0;
}