/** @file main.cpp
 *  @brief Integrates knowledge I learned in COP 2001.
 *
 *  Menu for user to select between the given options
 *
 *  @author Vladimir Hardy
 *  @bug Inputting numbers with spaces jumps through multiple cin statements. Create account doesnt work yet.
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "Prototypes.h"
#include <vector>

//Ctrl + alt +  L for code formatter

int main() {

    bool reRun = true;
    while (reRun) {
        showMenu(); //Call to the function showMenu
        int number;
        std::cin >> number;
        std::string ans;
        switch (number) {
            case 1: //Catalog of products being produced
                produceItems();
                break;
            case 2:
                std::cout << "Do you have an account? (yes or no)\n";
                std::cin >> ans;
                if (ans == "yes" || ans == "Yes" || ans == "y") {
                    employeeAccount();
                } else {
                    createAccount(); //Call to createAccount which will create a new username and password
                    employeeAccount(); //Call to employeeAccount which will prompt the user to log in
                }
                break;
            case 3:
                musicPlayer(); //STUB function
                break;
            case 4:
                moviePlayer(); //STUB function
                break;
            case 5:
                productionStatistics(); //STUB function
                break;
            case 6:
                exit(); //Exit the switch statement
                reRun = false; //breaks out of the while loop
                break;
            default: //Default statement if the user gives bad input
                std::cout << "Invalid selection, please type a number within the given range" << std::endl;
                break;
        }
    }
    return 0;
}

void showMenu() {
    std::cout
            << "======================================================\nHello There! Please select an option below:\n"
               "======================================================" << std::endl;
    std::cout << "Production Line Tracker\n";
    std::cout << "1. Produce Items\n" << "2. Add Employee Account\n" << "3. Add Music Player\n"
              << "4. Add Movie Player\n" << "5. Display Production Statistics\n" << "6. Exit\n";
}

void produceItems() {
    // Eventually the user will be able to choose the item to produce.
    // For now, just have them input the information.
    std::cout << "Enter the Manufacturer\n";
    std::string manufacturer;
    std::cin >> manufacturer;
    //manufacturer = "Apple";
    std::cout << "Enter the Product Name\n";
    std::string prodName;
    std::cin >> prodName;
    //prodName = "iPod";
    std::string firstThreeLetters = manufacturer.substr(0, 3);

    std::cout << "Enter the item type\n";
    std::cout << "1. Audio\n" <<
              "2. Visual\n" <<
              "3. AudioMobile\n" <<
              "4. VisualMobile\n";
    int itemTypeChoice;
    std::cin >> itemTypeChoice;
    std::string itemTypeCode;
    if (itemTypeChoice == 1) {
        itemTypeCode = "MM";
    } else if (itemTypeChoice == 2) {
        itemTypeCode = "VI";
    } else if (itemTypeChoice == 3) {
        itemTypeCode = "AM";
    } else if (itemTypeChoice == 4) {
        itemTypeCode = "VM";
    } else {
        std::cout << "Invalid Choice\n";
    }
    // Audio "MM", Visual "VI", AudioMobile "AM", or VisualMobile "VM".
    std::cout << "Enter the number of items that were produced\n";
    int numProduced;
    std::cin >> numProduced;
    std::string serialNum;
    for (int i = 1; i <= numProduced; i++) { //This loop records the production of the product
        std::ostringstream  serialNumStream;
        serialNumStream.width(10);
        serialNumStream.fill('0');
        serialNumStream << "Production Number: " << i << " Serial Number: " <<
        firstThreeLetters  << itemTypeCode << i;
        std::string serialNum = serialNumStream.str();
        std::cout << serialNum << std::endl;
        std::ofstream myOutputFile;
        myOutputFile.open("production.txt", std::ios_base::app);
        myOutputFile << serialNum << std::endl;
        myOutputFile.close();
    }
}

std::string createAccount() {
    std::cout << "Please enter your full name\n";
    std::string name;
    std::cin >> name;
    std::ofstream myOutputFile;
    myOutputFile.open("loginCreds.txt", std::ios_base::app);
    myOutputFile << name << std::endl; //adding name to the file loginCreds
    myOutputFile.close();

    std::cout << "Please enter a username: \n";
    std::string username;
    std::cin >> username;
    myOutputFile.open("loginCreds.txt", std::ios_base::app);
    myOutputFile << username << std::endl; //adding username to the file loginCreds
    myOutputFile.close();

    std::cout << "Please enter a password: \n";
    std::string password;
    std::cin >> password;
    myOutputFile.close();
    myOutputFile.open("loginCreds.txt", std::ios_base::app); //Appending password to the file loginCreds
    myOutputFile << password << std::endl;
    return (username, password);
}

void employeeAccount() {
    std::string line;
    std::ifstream myInputFile("loginCreds.txt");
    if (myInputFile.is_open()) {
        /*while (getline(myInputFile, line)) //Stores a line into a file called line, then uses that to output to console
         {
             if (line == username) { //change username to something that reads info from the loginCreds file
                 std::cout << "Access Granted" << std::endl;
             } else {
                 std::cout << "The username you entered is incorrect" << std::endl;
                 break;
             }
             if (line == password) {
                 std::cout << "Access Granted" << std::endl;
                 break;
             } else {
                 std::cout << "The password you entered is incorrect" << std::endl;
                 break;
             }
         }*/
        myInputFile.close();
    } else std::cout << "Unable to open file" << std::endl;
}

void musicPlayer() {
    std::cout << "FIXME" << std::endl;
}

void moviePlayer() {
    std::cout << "FIXME" << std::endl;
}

void productionStatistics() {
    std::cout << "FIXME" << std::endl;
}

void exit() {
    std::cout << "Have a nice day!" << std::endl;
}