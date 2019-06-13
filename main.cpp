/** @file main.cpp
 *  @brief Integrates knowledge I learned in COP 2001.
 *
 *  Menu for user to select between the given options
 *
 *  @author Vladimir Hardy
 *  @bug Switch cases break when a non-numeric value is used. Cannot use minGW compiler without code breaking.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <exception>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>

struct Products {
    std::string manufacturer;
    std::string prodName;
    std::string itemTypeCode;
    std::string comma;
    std::string period;

};

struct Counters {
    int counter;
    std::vector<int> curLineMM;
    std::vector<int> curLineVI;
    std::vector<int> curLineAM;
    std::vector<int> curLineVM;
};

#include "Prototypes.h"

//Ctrl + alt +  L for code formatter
//Ctrl + shift + alt + click for breakpoints

int main() {
    Counters newCounter;
    std::vector<std::string> productionLog;
    std::vector<Products> catalogVectorStruct;
    std::vector<std::string> productLineManufacturer;
    std::vector<std::string> productLineName;
    std::vector<std::string> productLineItemType;
    loadVectors(catalogVectorStruct, productLineManufacturer, productionLog, productLineName, productLineItemType,
                newCounter.curLineMM, newCounter.curLineVI, newCounter.curLineAM, newCounter.curLineVM);
    bool reRun = true;
    while (reRun) {
        showMenu(); //Call to the function showMenu
        int number;
        try {
            std::string badInput;
            std::cin >> badInput;
            number = std::stoi(badInput);
        }
        catch (std::invalid_argument &ex) {
            std::cout << "Invalid selection, please type a number\n";
            continue;
        }
        switch (number) {
            case 1: //Catalog of products being produced
                produceItems(productLineManufacturer, productLineName, productLineItemType, productionLog);
                break;
            case 2:
                createAccount();
                break;
            case 3:
                addItems(catalogVectorStruct);
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
                  std::vector<std::string> &productLineItemType, std::vector<std::string> &productionLog) {
    bool reTry = true;
    while (reTry) {
        std::cout << "The products in the Product Line are:\n";
        outputSortedProductNames(productLineName);
        int produceItemNum;
        int numProduced;
        try {
            std::cout << "Which product would you like to record?" << std::endl;
            std::string badInput;
            std::cin >> badInput;
            produceItemNum = std::stoi(badInput);
            std::cout << "Enter the number of items that were produced\n";
            std::cin >> badInput;
            numProduced = std::stoi(badInput);
        }
        catch (std::invalid_argument &ex) {
            std::cout << "Invalid selection, please type a number\n";
            continue;
        }

        int counter = 1;
        std::ifstream myInputFile;
        myInputFile.open("ProductionLog.csv", std::ios_base::app);
        std::string lineToChange;
        while (getline(myInputFile, lineToChange)) {  //if not at end of file, continue reading numbers
            counter++;
        }
        myInputFile.close();

        std::vector<std::string> serialNumVector;
        std::ofstream myOutputFile;
        myInputFile.open("ProductLine.csv", std::ios_base::app);
        std::string firstThreeLetters;
        std::string itemTypeCode;
        int counter2 = 1;
        while (getline(myInputFile, lineToChange)) { //gets stuff between counter and serial num
            if (counter2 == produceItemNum) {
                std::istringstream iss(lineToChange);
                firstThreeLetters = lineToChange.substr(2, 3);
                itemTypeCode = lineToChange.substr(lineToChange.length() - 2, 2);
            }
            counter2++;
        }
        myInputFile.close();
        int serialNumIndex;
        myOutputFile.open("ProductionLog.csv", std::ios_base::app);
        for (serialNumIndex = 0;
             serialNumIndex < numProduced; serialNumIndex++) { //This loop records the production of the product
            std::ostringstream serialNumStream;
            Counters newCounter;
            newCounter.counter = 1;
            if (produceItemNum == std::stoi(productLineName[produceItemNum - 1].substr(0, 1))) {
                newCounter.counter += serialNumIndex;
                if (productLineName[produceItemNum - 1].substr(productLineName[produceItemNum - 1].length() - 2, 2) ==
                    "MM") {
                    auto it = std::find(productionLog.begin(), productionLog.end(), "MM");
                    int result;
                    if (it != productionLog.end()) { //Does not recognize MM
                        result = distance(productionLog.begin(), it);
                        std::cout << result << std::endl;
                    } else {
                        result = -1;
                    }
                    newCounter.curLineMM.emplace_back(newCounter.counter);
                    //findInVector(newCounter.curLineMM,"MM");
                } else if (productLineName[produceItemNum - 1].substr(productLineName[produceItemNum - 1].length() - 2,
                                                                      2) == "VI") {
                    newCounter.curLineVI.emplace_back(newCounter.counter);
                } else if (productLineName[produceItemNum - 1].substr(productLineName[produceItemNum - 1].length() - 2,
                                                                      2) == "AM") {
                    newCounter.curLineMM.emplace_back(newCounter.counter);
                } else if (productLineName[produceItemNum - 1].substr(productLineName[produceItemNum - 1].length() - 2,
                                                                      2) == "VM") {
                    newCounter.curLineMM.emplace_back(newCounter.counter);
                } else
                    std::cout << "N/A\n";
            }
            serialNumStream << counter << ". " << firstThreeLetters << itemTypeCode << serialNumStream.fill('0')
                            << std::setw(5) << newCounter.counter;
            serialNumVector.push_back(serialNumStream.str());
            std::cout << serialNumVector[serialNumIndex] << std::endl;
            myOutputFile << serialNumVector[serialNumIndex] << std::endl;
            counter++;
        }
        myOutputFile.close();
        reTry = false;
    }
}

void outputSortedProductNames(std::vector<std::string> productLineName) {
    sort(productLineName.begin(), productLineName.end());
    for (auto inc: productLineName) {
        std::cout << inc << std::endl;
    }
}

void findManufacturerOfProduct(std::vector<std::string> productLineManufacturers,
                               std::vector<std::string> productLineName) {

    std::cout << "Enter a product name to find the manufacturer\n";
    std::string prodNameToFind;
    std::cin >> prodNameToFind;
    bool product_found;
    int inc; //Unless there is another way to retain the increment from the loop, a global increment is used
    for (inc = 0; inc < productLineName.size(); inc++) {
        if (productLineName[inc] == prodNameToFind) {
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

void addItems(std::vector<Products> &catalogVectorStruct) {
    // Add three new products to the product line
    std::cout << "Adding a new product to the product line\nEnter the Manufacturer\n";
    std::cin.ignore();
    Products newItem;
    getline(std::cin, newItem.manufacturer);

    // manufacturer = "MicrosoftApple";
    // add manufacturer to the vector here

    std::cout << "Enter the Product Name\n";
    std::string prodName;
    getline(std::cin, newItem.prodName);
    // add prodName to the vector

    bool reTry = true;
    while (reTry) {
        std::cout << "Enter the item type\n";
        std::cout << "1. Audio\n" <<
                  "2. Visual\n" <<
                  "3. AudioMobile\n" <<
                  "4. VisualMobile\n";
        int itemTypeChoice = 0;
        try {
            std::string badInput;
            std::cin >> badInput;
            itemTypeChoice = std::stoi(badInput);
        }
        catch (std::invalid_argument &ex) {
            std::cout << "Invalid selection, please type a number\n";
            continue;
        }
        if (itemTypeChoice == 1) {
            newItem.itemTypeCode = "MM";
        } else if (itemTypeChoice == 2) {
            newItem.itemTypeCode = "VI";
        } else if (itemTypeChoice == 3) {
            newItem.itemTypeCode = "AM";
        } else if (itemTypeChoice == 4) {
            newItem.itemTypeCode = "VM";
        } else {
            std::cout << "Invalid Choice\n";
            newItem.itemTypeCode = "N/A";
        }

        // Audio "MM", Visual "VI", AudioMobile "AM", or VisualMobile "VM".
        Counters newCounter;
        newCounter.counter = 1;
        std::ifstream myInputFile;
        myInputFile.open("ProductLine.csv", std::ios_base::app);
        std::string lineToChange;
        while (getline(myInputFile, lineToChange)) {  //if not at end of file, continue reading numbers
            newCounter.counter++;
        }
        myInputFile.close();
        newItem.comma = ",";
        newItem.period = ".";
        std::ofstream myOutputFile;
        myOutputFile.open("ProductLine.csv", std::ios_base::app);
        std::stringstream catalogStream;
        catalogStream << newCounter.counter << newItem.period << newItem.manufacturer <<
                      newItem.comma << newItem.prodName << newItem.comma << newItem.itemTypeCode;
        catalogVectorStruct.emplace_back(newItem);
        myOutputFile << catalogStream.str() << std::endl;
        myOutputFile.close();
        std::cout << "Saved to file" << std::endl;
        reTry = false;
    }
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

    bool tryAgain = true;
    while (tryAgain) {
        std::cout << "Please enter a password, it must contain at least: one digit, one lowercase letter, "
                     "and one uppercase letter.\nThe password cannot contain a space or any other symbols: \n";
        std::string password;
        std::cin >> password;
        password = encryptString(password);
        bool upper = false, lower = false, digit = false, space = false;
        for (int i = 0; i < password.length(); i++) {
            if (isupper(password[i]))
                upper = true;
            if (islower(password[i]))
                lower = true;
            if (isspace(password[i]))
                space = true;
            if (isdigit(password[i]))
                digit = true;
        }
        if (upper && lower && !space && digit) {
            std::ofstream myOutputFile;
            myOutputFile.open("loginCreds.txt", std::ios_base::app);
            myOutputFile << userName << " " << password << std::endl; //adding name to the file loginCreds
            myOutputFile.close();
            tryAgain = false;
        } else {
            std::cout << "Invalid password" << std::endl;
        }
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

void loadVectors(std::vector<Products> &catalogVectorStruct, std::vector<std::string> &productLineManufacturer,
                 std::vector<std::string> &productionLog, std::vector<std::string> &productLineName,
                 std::vector<std::string> &productLineItemType, std::vector<int> &curLineMM,
                 std::vector<int> &curLineVI,
                 std::vector<int> &curLineAM, std::vector<int> &curLineVM) { //Call at beginning of the program
    std::ifstream myInputFile;
    myInputFile.open("ProductLine.csv");
    std::string lineToChange;
    int inc = 0;
    while (getline(myInputFile, lineToChange)) { //Loads ProductLineName
        productLineName.emplace_back(lineToChange);
        inc++;
    }
    myInputFile.close();
    myInputFile.open("ProductionLog.csv");
    inc = 0;
    while (getline(myInputFile, lineToChange)) { //Loads ProductionLog
        productionLog.emplace_back(lineToChange);
        inc++;
    }

}

std::pair<bool, int> findInVector(const std::vector<std::string> &productionLog, std::string &element) {
    std::pair<bool, int> result;
    // Find given element in vector
    auto it = std::find(productionLog.begin(), productionLog.end(), element);

    if (it != productionLog.end()) {
        result.second = distance(productionLog.begin(), it);
        result.first = true;
    } else {
        result.first = false;
        result.second = -1;
    }

    return result;
}

void productionStatistics() {
    std::cout << "FIXME" << std::endl;
}

void exit() {
    std::cout << "Have a nice day!" << std::endl;
}