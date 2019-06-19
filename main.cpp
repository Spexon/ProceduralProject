/** @file main.cpp
 *  @brief Integrates knowledge I learned in COP 2001.
 *
 *  Menu for user to select between the given options
 *
 *  @author Vladimir Hardy
 *  @bug no known bugs
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
};

struct Counters {
    int counter = 0;
    int curLineMM = 0;
    int curLineVI = 0;
    int curLineAM = 0;
    int curLineVM = 0;
};

#include "Prototypes.h"

//Ctrl + alt +  L for code formatter
//Ctrl + shift + alt + click for breakpoints

/**
 * @brief Main function that calls other functions in a switch case statement
 */
int main() {
    Counters newCounter;
    std::vector<std::string> productionLog;
    std::vector<std::string> productLineName;
    loadVectors(productionLog, productLineName,
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
                produceItems(productLineName, productionLog);
                break;
            case 2:
                createAccount();
                break;
            case 3:
                addItems(productLineName);
                break;
            case 4:
                employeeAccount();
                break;
            case 5:
                productionStatistics(productionLog, productLineName);
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

/** @brief Prints a selection menu to console
 *
 */
void showMenu() {
    std::cout
            << "======================================================\nHello There! Please select an option below:\n"
               "======================================================" << std::endl;
    std::cout << "Production Line Tracker\n";
    std::cout << "1. Produce Items\n" << "2. Add Employee Account\n" << "3. Add Items\n"
              << "4. Log In\n" << "5. Display Production Statistics\n" << "6. Exit\n";
}

/**
 * @brief Allows the user to catalog their produced items
 * @param productLineName Vector with items that can be produced
 * @param productionLog Vector with saved products that have already been produced
 */
void produceItems(std::vector<std::string> &productLineName,
                  std::vector<std::string> &productionLog) {
    bool reTry = true;
    while (reTry) {
        std::ifstream myInputFile;
        myInputFile.open("ProductLine.csv");
        if (isEmpty(myInputFile)) {
            std::cout << "Please add to the product line before producing" << std::endl;
            break;
        }
        myInputFile.close();
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
                firstThreeLetters = lineToChange.substr(0, 3);
                itemTypeCode = lineToChange.substr(lineToChange.length() - 2, 2);
            }
            counter2++;
        }
        myInputFile.close();
        int serialNumIndex;
        std::ofstream outputToFile;
        std::ifstream inputFromFile;
        Counters newCounter;
        inputFromFile.open("CounterVM.csv");
        while (getline(inputFromFile, lineToChange)) {  //if not at end of file, continue reading numbers
            inputFromFile >> lineToChange;
            newCounter.curLineVM = stoi(lineToChange);
        }
        inputFromFile.close();
        inputFromFile.open("CounterAM.csv");
        while (getline(inputFromFile, lineToChange)) {  //if not at end of file, continue reading numbers
            inputFromFile >> lineToChange;
            newCounter.curLineAM = stoi(lineToChange);
        }

        inputFromFile.close();
        inputFromFile.open("CounterMM.csv");
        while (getline(inputFromFile, lineToChange)) {  //if not at end of file, continue reading numbers
            inputFromFile >> lineToChange;
            newCounter.curLineMM = stoi(lineToChange);
        }
        inputFromFile.close();
        inputFromFile.open("CounterVI.csv");
        while (getline(inputFromFile, lineToChange)) {  //if not at end of file, continue reading numbers
            inputFromFile >> lineToChange;
            newCounter.curLineVI = stoi(lineToChange);
        }
        inputFromFile.close();
        myOutputFile.open("ProductionLog.csv", std::ios_base::app);

        for (serialNumIndex = 0;
             serialNumIndex < numProduced; serialNumIndex++) { //This loop records the production of the product
            std::ostringstream serialNumStream;
            newCounter.counter = 1;
            if (productLineName[produceItemNum - 1].substr(productLineName[produceItemNum - 1].length() - 2, 2) ==
                "MM") { //Looks for MM in a line like this: 22. AmaMM 00001
                outputToFile.open("CounterMM.csv"); //Cannot have multiple files open at the same time
                serialNumStream << counter << ". " << firstThreeLetters << itemTypeCode << serialNumStream.fill('0')
                                << std::setw(5) << newCounter.curLineMM;
                serialNumVector.push_back(serialNumStream.str());
                newCounter.curLineMM++;
                outputToFile << "\n" << newCounter.curLineMM;
                outputToFile.close();
            } else if (productLineName[produceItemNum - 1].substr(productLineName[produceItemNum - 1].length() - 2,
                                                                  2) == "VI") {
                outputToFile.open("CounterVI.csv");
                serialNumStream << counter << ". " << firstThreeLetters << itemTypeCode << serialNumStream.fill('0')
                                << std::setw(5) << newCounter.curLineVI;
                serialNumVector.push_back(serialNumStream.str());
                newCounter.curLineVI++;
                outputToFile << "\n" << newCounter.curLineVI;
                outputToFile.close();
            } else if (productLineName[produceItemNum - 1].substr(productLineName[produceItemNum - 1].length() - 2,
                                                                  2) == "AM") {
                outputToFile.open("CounterAM.csv");
                serialNumStream << counter << ". " << firstThreeLetters << itemTypeCode << serialNumStream.fill('0')
                                << std::setw(5) << newCounter.curLineAM;
                serialNumVector.push_back(serialNumStream.str());
                newCounter.curLineAM++;
                outputToFile << "\n" << newCounter.curLineAM;
                outputToFile.close();
            } else if (productLineName[produceItemNum - 1].substr(productLineName[produceItemNum - 1].length() - 2,
                                                                  2) == "VM") {
                outputToFile.open("CounterVM.csv");
                serialNumStream << counter << ". " << firstThreeLetters << itemTypeCode << serialNumStream.fill('0')
                                << std::setw(5) << newCounter.curLineVM;
                serialNumVector.push_back(serialNumStream.str());
                newCounter.curLineVM++;
                outputToFile << "\n" << newCounter.curLineVM;
                outputToFile.close();
            } else
                std::cout << "N/A\n";

            std::cout << serialNumVector[serialNumIndex] << std::endl;
            myOutputFile << serialNumVector[serialNumIndex] << std::endl;
            counter++;
        }
        myOutputFile.close();
        reTry = false;
    }
}

/**
 * @brief Sorts and outputs products from the ProductLine file
 * @param productLineName Vector with items that can be produced
 */
void outputSortedProductNames(std::vector<std::string> productLineName) {
    std::ofstream myOutputFile;
    myOutputFile.open("ProductLine.csv");
    sort(productLineName.begin(), productLineName.end());
    for (int inc = 0; inc < productLineName.size(); inc++) {
        myOutputFile << productLineName[inc] << std::endl;
        std::cout << inc + 1 << ". " << productLineName[inc] << std::endl;
    }
    myOutputFile.close();
}

/**
 * @brief Allows the user to add new products to the production line
 * @param productLineName Vector with items that can be produced
 */
void addItems(std::vector<std::string> &productLineName) {
    // Add three new products to the product line
    std::cout << "Adding a new product to the product line\nEnter the Manufacturer\n";
    std::cin.ignore();
    Products newItem;
    getline(std::cin, newItem.manufacturer);

    std::cout << "Enter the Product Name\n";
    std::string prodName;
    getline(std::cin, newItem.prodName);

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
        std::ofstream myOutputFile;
        myOutputFile.open("ProductLine.csv", std::ios_base::app);
        std::stringstream catalogStream;
        catalogStream << newItem.manufacturer <<
                      newItem.comma << newItem.prodName << newItem.comma << newItem.itemTypeCode;
        productLineName.emplace_back(catalogStream.str());
        myOutputFile << catalogStream.str() << std::endl;

        myOutputFile.close();
        std::cout << "Saved to file" << std::endl;
        reTry = false;
    }
}

/**
 * @brief Finds a certain word from a specified file and returns true if word is found or false if not
 * @param fileName file which you want to find a word in
 * @param search Word that you want to find in the file
 * @return true or false, depending if the word is found
 */
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

/**
 * @brief creates an account for a user, encrypts, and saves to a file. Also checks password strength
 */
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

/**
 * @brief Encrypts the string that gets passed in
 * @param str any type of string
 * @return the encrypted string
 */
std::string encryptString(std::string str) {
    if (str.length() == 1) {
        return str;
    } else {
        return char((int) str[0] + 3) + encryptString(str.substr(1, str.length() - 1));
    }
}

/**
 * @breif Allows the user to log in, if their credentials are correct
 */
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
            if (checkWord("loginCreds.txt", encryptString(password))) {
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

/**
 * @brief Gets all important information from files and saves them to vectors
 * @param catalogVectorStruct A vector of type Products (struct)
 * @param productLineName Vector with items that can be produced
 * @param productionLog Vector with saved products that have already been produced
 * @param curLineMM A counter for type MM in a struct
 * @param curLineVI A counter for type VI in a struct
 * @param curLineAM A counter for type AM in a struct
 * @param curLineVM A counter for type VM in a struct
 */
void loadVectors(std::vector<std::string> &productionLog, std::vector<std::string> &productLineName,
                 int &curLineMM, int &curLineVI, int &curLineAM,
                 int &curLineVM) { //Call at beginning of the program
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

/**
 * @brief checks if a file is empty
 * @param pFile any type of file
 * @return true if the file is empty, false otherwise
 */
bool isEmpty(std::ifstream &pFile) {
    return pFile.peek() == std::ifstream::traits_type::eof();
}

/**
 * @brief Displays certain informatioin about the products produced
 * @param productionLog Vector with saved products that have already been produced
 * @param productLineName Vector with items that can be produced
 */
void productionStatistics(std::vector<std::string> &productionLog, std::vector<std::string> &productLineName) {
    bool reTry = true;
    while (reTry) {
        try {
            std::cout
                    << "Pick an option below by typing a number:\n1. Display items produced\n"
                       "2. Number of each item produced" << std::endl;
            Counters newCounter;
            std::string badInput;
            std::cin >> badInput;
            int num = stoi(badInput);
            switch (num) {
                case 1 : {
                    std::string numProduced;
                    int prodLength = productionLog.size();
                    std::cout << "Number of items produced: " << productionLog[prodLength - 1].substr(0, 2)
                              << std::endl;
                    break;
                }
                case 2: { // Audio "MM", Visual "VI", AudioMobile "AM", or VisualMobile "VM".
                    std::cout << "Choose an item type:\n1. Audio(MM)\n2. Visual(VI)\n"
                                 "3. Audio Mobile(AM)\n4. Visual Mobile(VM)\n";
                    std::cin >> badInput;
                    int innerNum = stoi(badInput);
                    switch (innerNum) {
                        case 1: {
                            std::ifstream inputFromFile;
                            inputFromFile.open("CounterMM.csv");
                            if (isEmpty(inputFromFile)) {
                                std::cout << "0 items of type audio mobile were produced." << std::endl;
                            }
                            std::string lineToChange;
                            if (isEmpty(inputFromFile)) {
                                lineToChange = "0";
                            }
                            while (getline(inputFromFile, lineToChange)) {  //if not at end of file, continue reading numbers
                                inputFromFile >> lineToChange;
                                std::cout << lineToChange << " items of type audio were produced." << std::endl;
                            }
                            inputFromFile.close();
                            break;
                        }
                        case 2: {
                            std::ifstream inputFromFile;
                            inputFromFile.open("CounterVI.csv");
                            if (isEmpty(inputFromFile)) {
                                std::cout << "0 items of type audio mobile were produced." << std::endl;
                            }
                            std::string lineToChange;
                            while (getline(inputFromFile, lineToChange)) {  //if not at end of file, continue reading numbers
                                inputFromFile >> lineToChange;
                                std::cout << lineToChange << " items of type visual were produced." << std::endl;
                            }
                            inputFromFile.close();
                            break;
                        }
                        case 3: {
                            std::ifstream inputFromFile;
                            inputFromFile.open("CounterAM.csv");

                            if (isEmpty(inputFromFile)) {
                                std::cout << "0 items of type audio mobile were produced." << std::endl;
                            }
                            std::string lineToChange;
                            while (getline(inputFromFile, lineToChange)) {  //if not at end of file, continue reading numbers
                                inputFromFile >> lineToChange;
                                std::cout << lineToChange << " items of type audio mobile were produced." << std::endl;
                            }
                            inputFromFile.close();
                            break;
                        }

                        case 4: {
                            std::ifstream inputFromFile;
                            inputFromFile.open("CounterVM.csv");
                            std::string lineToChange;
                            if (isEmpty(inputFromFile)) {
                                std::cout << "0 items of type audio mobile were produced." << std::endl;
                            }
                            while (getline(inputFromFile, lineToChange)) {  //if not at end of file, continue reading numbers
                                inputFromFile >> lineToChange;
                                std::cout << lineToChange << " items of type visual mobile were produced." << std::endl;
                            }
                            inputFromFile.close();
                            break;
                        }
                        default:
                            std::cout << "Invalid Selection\n";
                            break;
                    }
                    break;
                }
                default:
                    std::cout << "Invalid selection" << std::endl;
                    break;
            }
        }
        catch (std::invalid_argument &ex) {
            std::cout << "Please enter a number" << std::endl;
            continue;
        }
        reTry = false;
    }
}

void exit() {
    std::cout << "Have a nice day!" << std::endl;
}