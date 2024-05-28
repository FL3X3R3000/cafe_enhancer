#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Cafe {

public:

    struct Dish {

        string name;

        int price;

    };

    vector<Dish> dishes;

    vector<Dish> order;

};


class People {

public:

    string name;

    string surname;

    string secondName;

    string phone;

    string salary;

};


class Customers : People, Cafe {
public:
    vector<string> data;
    string name;
    string surname;
    string phone;
    int totalPrice = 0;
    Customers() {

        dishes.push_back({ "Burger", 200 });
        dishes.push_back({ "French Fries", 80 });
        dishes.push_back({ "Wings", 180 });
        dishes.push_back({ "Cola", 100 });
        dishes.push_back({ "Ice cream", 50 });

    }

    void login() {
        cout << "Fill in: " << endl;
        cout << "Name: " << endl;
        cin >> name;
        this->name = name;
        cout << "Surname: " << endl;
        cin >> surname;
        this->surname = surname;;
    enter:;
        cout << "Phone number: " << endl;
        cin >> phone;
        string p1 = phone.substr(0, 3);
        if (p1 != "+79") {
            cout << "Incorrect format." << endl;
            goto enter;
        }
        this->phone = phone;
        system("cls");
    }

    void menu() {
        system("cls");

        cout << "Menu:\n";

        for (int i = 0; i < dishes.size(); i++) {

            cout << i + 1 << ". " << dishes[i].name << " - " << dishes[i].price << " rub\n";

        }

    }


    void addToOrder(int dishIndex) {
        

        if (dishIndex >= 1 && dishIndex <= dishes.size()) {

            order.push_back(dishes[dishIndex - 1]);
            data.push_back(order[dishIndex - 1].name);
            cout << "Dish was added to your order.\n";
        }

        else {

            cout << "Incorrect dish number.\n";

        }

    }


    void printOrder() {

        cout << "Your order:\n";


        for (int i = 0; i < order.size(); i++) {

            cout << i + 1 << ". " << order[i].name << " - " << order[i].price << " rub\n";

            this->totalPrice += order[i].price;

        }
        cout << "Total order price: " << this->totalPrice << " rub\n";



    }

    bool saveOrder() {
        ofstream out;
        out.open("buffer.txt", std::ios::out | std::ios::app);

        if (!out.is_open()) {
            cout << "Error: file not opened.";
            return false;
        }

        out << this->name + " " + this->surname + " " << this->phone << endl;
        for (int i = 0; i < this->data.size(); i++) {
            out << this->data[i] << endl;
        }
        out << "Total price: " << this->totalPrice << "\n";
        out << "~" << endl;
        out.close();
        return true;
    }
};