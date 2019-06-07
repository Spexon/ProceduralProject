/** @file main.cpp
 *  @brief Integrates knowledge I learned in COP 2001.
 *
 *  Menu for user to select between the given options
 *
 *  @author Vladimir Hardy
 *  @bug Inputting numbers with spaces jumps through multiple cin statements. Create account doesnt work yet.
 */
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <iomanip>
#include <cctype>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "Prototypes.h"
#include <vector>


//Ctrl + alt +  L for code formatter
//Ctrl + shift + alt + click for breakpoints
int curLineMM = 0, curLineVI = 0, curLineAM = 0, curLineVM = 0;

int main() {

    std::vector<std::string> productLineName;
    std::vector<std::string> productLineManufacturer;
    std::vector<std::string> productLineItemType;
    bool reRun = true;
    while (reRun) {
        showMenu(); //Call to the function showMenu
        int number;
        std::cin >> number;
        std::string ans;
        switch (number) {
            case 1: //Catalog of products being produced
                produceItems(productLineName, productLineManufacturer, productLineItemType);
                break;
            case 2:
                createAccount();
                break;
            case 3:
                addItems(productLineName, productLineManufacturer, productLineItemType);
                break;
            case 4:
                employeeAccount();
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
    std::cout << "1. Produce Items\n" << "2. Add Employee Account\n" << "3. Add Items\n"
              << "4. Log In\n" << "5. Display Production Statistics\n" << "6. Exit\n";
}

void produceItems(std::vector<std::string> &productLineManufacturer, std::vector<std::string> &productLineName,
                  std::vector<std::string> &productLineItemType) {

    std::cout << "The products in the Product Line are:\n";
    outputSortedProductNames(productLineName);
    std::cout << "Which product would you like to record?" << std::endl;
    int produceItemNum;
    std::cin >> produceItemNum;
    std::cout << "Enter the number of items that were produced\n";
    int numProduced;
    std::cin >> numProduced;
    int counter = 1;
    std::ifstream myInputFile;
    myInputFile.open("production.txt", std::ios_base::app);
    std::string lineToChange;
    while (getline(myInputFile, lineToChange)) {  //if not at end of file, continue reading numbers
        std::istringstream(lineToChange, counter);
        counter++;
    }
    myInputFile.close();

    std::vector<std::string> serialNumVector;
    std::ofstream myOutputFile;
    myInputFile.open("catalog.txt", std::ios_base::app);
    std::string firstThreeLetters;
    std::string itemTypeCode;
    int counter2 = 1;
    while (getline(myInputFile, lineToChange)) {
        if (counter2 == produceItemNum) {
            std::istringstream iss(lineToChange);
            firstThreeLetters = lineToChange.substr(3, 3);
            itemTypeCode = lineToChange.substr(lineToChange.length() - 2, 2);
        }
        counter2++;
    }
    int serialNumIndex;
    myOutputFile.open("production.txt", std::ios_base::app);
    for (serialNumIndex = 0;
         serialNumIndex < numProduced; serialNumIndex++) { //This loop records the production of the product
        std::ostringstream serialNumStream;
        /*if (checkWord("production.txt", "MM")) {

                curLineMM++;
                std::cout << curLineMM << std::endl;
                if ((itemTypeCode.find(itemTypeCode, 0)) != std::string::npos) {
                    serialNumStream << counter << ". " << firstThreeLetters << itemTypeCode << serialNumStream.fill('0')
                                    << std::setw(5) << curLineMM;
                    serialNumVector.push_back(serialNumStream.str());
                    std::cout << serialNumVector[curLineMM] << std::endl;
                    myOutputFile << serialNumVector[curLineMM] << std::endl;
                    counter++;
                }

        } else if (checkWord("production.txt", "VI")) {

                if ((itemTypeCode.find(itemTypeCode, 0)) != std::string::npos) {
                    serialNumStream << counter << ". " << firstThreeLetters << itemTypeCode << serialNumStream.fill('0')
                                    << std::setw(5) << curLineVI;
                    serialNumVector.push_back(serialNumStream.str());
                    std::cout << serialNumVector[curLineVI] << std::endl;
                    myOutputFile << serialNumVector[curLineVI] << std::endl;
                    counter++;
                    curLineVI++;
                }

        } else if (checkWord("production.txt", "AM")) {

                curLineAM++;
                if ((itemTypeCode.find(itemTypeCode, 0)) != std::string::npos) {
                    serialNumStream << counter << ". " << firstThreeLetters << itemTypeCode
                                    << serialNumStream.fill('0')
                                    << std::setw(5) << curLineAM;
                    serialNumVector.push_back(serialNumStream.str());
                    std::cout << serialNumVector[curLineAM] << std::endl;
                    myOutputFile << serialNumVector[curLineAM] << std::endl;
                    counter++;
                }

        } else if (checkWord("production.txt", "VM")) {

                curLineVM++;
                if ((itemTypeCode.find(itemTypeCode, 0)) != std::string::npos) {
                    serialNumStream << counter << ". " << firstThreeLetters << itemTypeCode
                                    << serialNumStream.fill('0')
                                    << std::setw(5) << curLineVM;
                    serialNumVector.push_back(serialNumStream.str());
                    std::cout << serialNumVector[curLineVM] << std::endl;
                    myOutputFile << serialNumVector[curLineVM] << std::endl;
                    counter++;
                }

        } else {
            serialNumStream << counter << ". " << firstThreeLetters << itemTypeCode << serialNumStream.fill('0')
                            << std::setw(5) << serialNumIndex;
            serialNumVector.push_back(serialNumStream.str());
            std::cout << serialNumVector[serialNumIndex] << std::endl;
            myOutputFile << serialNumVector[serialNumIndex] << std::endl;
            counter++;
        }*/

        serialNumStream << counter << ". " << firstThreeLetters << itemTypeCode << serialNumStream.fill('0')
                        << std::setw(5) << serialNumIndex;
        serialNumVector.push_back(serialNumStream.str());
        std::cout << serialNumVector[serialNumIndex] << std::endl;
        myOutputFile << serialNumVector[serialNumIndex] << std::endl;
        counter++;
    }
    myOutputFile.close();

}

void outputSortedProductNames(std::vector<std::string> productLineNames) {
    std::ifstream myInputFile;
    myInputFile.open("catalog.txt", std::ios_base::app);
    std::string lineToChange;
    while (getline(myInputFile, lineToChange)) {  //if not at end of file, continue reading numbers
        std::istringstream iss(lineToChange);
        std::cout << lineToChange << std::endl;
    }
    myInputFile.close();
    sort(productLineNames.begin(), productLineNames.end());
    for (auto inc: productLineNames) {
        std::cout << inc << std::endl;
    }
}

void findManufacturerOfProduct(std::vector<std::string> productLineManufacturers,
                               std::vector<std::string> productLineNames) {

    std::cout << "Enter a product name to find the manufacturer\n";
    std::string prodNameToFind;
    std::cin >> prodNameToFind;
    bool product_found;
    int inc; //Unless there is another way to retain the increment from the loop, a global increment is used
    for (inc = 0; inc < productLineNames.size(); inc++) {
        if (productLineNames[inc] == prodNameToFind) {
            product_found = true;
            break;
        } else {
            product_found = false;
        }
    }
    if (product_found) {
        std::cout << "The manufacturer of that product is " << productLineManufacturers[inc] << std::endl;
    } else {
        std::cout << "That product name was not found." << std::endl;
    }
}

void addItems(std::vector<std::string> &productLineManufacturer, std::vector<std::string> &productLineName,
              std::vector<std::string> &productLineItemType) {
    // Add three new products to the product line
    std::cout << "Adding a new product to the product line\n";

    std::cout << "Enter the Manufacturer\n";
    std::cin.ignore();
    std::string manufacturer;
    getline(std::cin, manufacturer);
    std::string firstThreeLetters = manufacturer.substr(0, 3);
    // manufacturer = "MicrosoftApple";
    // add manufacturer to the vector here
    productLineManufacturer.push_back(manufacturer);
    std::cout << "Enter the Product Name\n";
    std::string prodName;
    getline(std::cin, prodName);
    // add prodName to the vector
    productLineName.push_back(prodName);
    std::cout << "Enter the item type\n";
    std::cout << "1. Audio\n" <<
              "2. Visual\n" <<
              "3. AudioMobile\n" <<
              "4. VisualMobile\n";
    int itemTypeChoice;
    std::cin >> itemTypeChoice;
    std::string itemTypeCode;
    std::ofstream myOutputFile;
    myOutputFile.open("counters.txt",std::ios_base::app);
    myOutputFile << "test1" << curLineMM << std::endl;
    if (itemTypeChoice == 1) {
        itemTypeCode = "MM";
        curLineMM++;

    } else if (itemTypeChoice == 2) {
        itemTypeCode = "VI";

        curLineVI++;
    } else if (itemTypeChoice == 3) {
        itemTypeCode = "AM";
        curLineAM++;
    } else if (itemTypeChoice == 4) {
        itemTypeCode = "VM";
        curLineVM++;
    } else {
        std::cout << "Invalid Choice\n";
        itemTypeCode = "N/A";
    }
    productLineItemType.push_back(itemTypeCode);

    // Audio "MM", Visual "VI", AudioMobile "AM", or VisualMobile "VM".

    int counter;
    counter = 1;
    std::ifstream myInputFile;

    std::string lineToChange;
    myInputFile.open("catalog.txt", std::ios_base::app);
    while (getline(myInputFile, lineToChange)) {  //if not at end of file, continue reading numbers
        std::istringstream(lineToChange, counter);
        counter++;
    }
    myInputFile.close();
    myOutputFile.open("catalog.txt", std::ios_base::app);
    myOutputFile << counter << ". " << manufacturer << ", " << prodName << ", " << itemTypeCode << std::endl;
    myOutputFile.close();
    std::cout << "Saved to file" << std::endl;
}

bool checkWord(std::string fileName, std::string search) {
    std::string line;
    std::ifstream myFile;
    myFile.open(fileName);
    if (myFile.is_open()) {
        while (!myFile.eof()) {
            getline(myFile, line);
            if ((line.find(search, 0)) != std::string::npos) {
                //std::cout << "found '" << search << " \n"<< line  <<std::endl;
                return true;
            } else {
                //std::cout << "Not found \n";
            }
        }
        myFile.close();
    } else
        std::cout << "Unable to open this file." << std::endl;
    return false;
}

void createAccount() {
    std::cout << "Please enter your first and last name\n";
    std::string firstName;
    std::cin >> firstName;
    std::string lastName;
    std::cin >> lastName;
    std::string userName;
    userName = firstName[0] + lastName.substr(0, lastName.length());
    std::transform(userName.begin(), userName.end(), userName.begin(), ::tolower);
    std::cout << "Your username is: " << userName << std::endl;
    userName = encryptString(userName);

    std::cout << "Please enter a password, it must contain at least: one digit, one lowercase letter, "
                 "and one uppercase letter.\nThe password cannot contain a space or any other symbols: \n";
    std::string password;
    std::cin >> password;
    password = encryptString(password);
    bool valid = false;
    for (int i = 0; i < password.length(); i++) {
        if (isupper(password[i])) {
            for (int i = 0; i < password.length(); i++) {
                if (islower(password[i])) {
                    for (int i = 0; i < password.length(); i++) {
                        if (!isspace(password[i])) {
                            for (int i = 0; i < password.length(); i++) {
                                if (isdigit(password[i])) {
                                    for (int i = 0; i < password.length(); i++) {
                                        if (isalnum(password[i])) {
                                            valid = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (valid) {
        std::ofstream myOutputFile;
        myOutputFile.open("loginCreds.txt", std::ios_base::app);
        myOutputFile << userName << " " << password << std::endl; //adding name to the file loginCreds
        myOutputFile.close();
    } else {
        std::cout << "Invalid password" << std::endl;
    }
}

std::string encryptString(std::string str) {
    if (str.length() == 1) {
        return str;
    } else {
        return char((int) str[0] + 3) + encryptString(str.substr(1, str.length() - 1));
    }
}

void employeeAccount() {
    std::ifstream myInputFile("loginCreds.txt");
    if (myInputFile.is_open()) {
        std::cout << "Enter your username below:" << std::endl;
        std::string username;
        std::cin >> username;
        if (checkWord("loginCreds.txt", encryptString(username))) {
            std::cout << "Enter your password below:" << std::endl;
            std::string password;
            std::cin >> password;
            if (checkWord("loginCreds.txt", encryptString(username))) {
                std::cout << "Login Successful!" << std::endl;
            } else {
                std::cout << "Login Failed!" << std::endl;
            }
        } else {
            std::cout << "Login Failed!" << std::endl;
        }

    } else std::cout << "Unable to open file" << std::endl;


    myInputFile.close();
}

void productionStatistics() {
    std::cout << "FIXME" << std::endl;
}

void exit() {
    std::cout << "Have a nice day!" << std::endl;
}