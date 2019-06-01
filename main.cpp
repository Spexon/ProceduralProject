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
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "Prototypes.h"
#include <vector>

//Ctrl + alt +  L for code formatter
//Ctrl + shift + alt + click for breakpoints

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
                //addToProductLine();
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
                addItems(); //STUB function
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
    std::cout << "1. Produce Items\n" << "2. Add Employee Account\n" << "3. Add Items\n"
              << "4. Add Movie Player\n" << "5. Display Production Statistics\n" << "6. Exit\n";
}

void produceItems() {
    // Eventually the user will be able to choose the item to produce.
    // For now, just have them input the information.
    // Create vectors to store product manufacturer

    // a parallel vector to store product name
    std::vector<std::string> productLineName;
    // a parallel vector to store product item type
    std::vector<std::string> productLineManufacturer;
    // create vector here
    std::vector<std::string> productLineItemType;
    // Add three new products to the product line
    addToProductLine(productLineManufacturer, productLineName, productLineItemType);
    // Output the products in the product line
    std::cout << "Saved to file" << std::endl;
    /*std::cout << "The products in the Product Line are:\n";
    for (int productLineItemNum = 0; productLineItemNum < 1; productLineItemNum++) {
        std::cout << productLineManufacturer[productLineItemNum] << ", ";
        std::cout << productLineName[productLineItemNum] << ", ";
        std::cout << productLineItemType[productLineItemNum] << "\n";
    }
    outputProductLine(productLineManufacturer, productLineName, productLineItemType);*/
    outputSortedProductNames(productLineName);
    findManufacturerOfProduct(productLineManufacturer, productLineName);
}

void outputSortedProductNames(std::vector<std::string> productLineNames) {
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

void addToProductLine(std::vector<std::string> &productLineManufacturer,
                      std::vector<std::string> &productLineName, std::vector<std::string> &productLineItemType) {

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
        itemTypeCode = "N/A";
    }
    productLineItemType.push_back(itemTypeCode);

    // Audio "MM", Visual "VI", AudioMobile "AM", or VisualMobile "VM".
    std::cout << "Enter the number of items that were produced\n";
    int numProduced;
    std::cin >> numProduced;
    int serialNumIndex;
    int counter = 1;
    std::ifstream myInputFile;
    myInputFile.open("production.txt", std::ios_base::app);
    std::string lineToChange;
    while (getline(myInputFile, lineToChange)) {  //if not at end of file, continue reading numbers
        std::istringstream(lineToChange, counter);
        counter++;
    }
    myInputFile.close();
    int curLineMM = 0, curLineVI = 0, curLineAM = 0, curLineVM = 0;
    std::vector<std::string> serialNumVector;
    std::ofstream myOutputFile;
    myOutputFile.open("production.txt", std::ios_base::app);
    for (serialNumIndex = 1;
         serialNumIndex <= numProduced; serialNumIndex++) { //This loop records the production of the product
        std::ostringstream serialNumStream;
        /*if (checkWord("production.txt", "MM")) {
            while (getline(myInputFile, itemTypeCode)) {
                curLineMM++;
                std::cout << curLineMM << std::endl;
                if ((itemTypeCode.find(itemTypeCode, 0)) != std::string::npos) {
                    serialNumStream << counter << ". " << firstThreeLetters << itemTypeCode << serialNumStream.fill('0')
                                    << std::setw(4) << curLineMM;
                    serialNumVector.push_back(serialNumStream.str());
                    std::cout << serialNumVector[curLineMM] << std::endl;
                    myOutputFile << serialNumVector[curLineMM] << std::endl;
                    counter++;
                }
            }
        } else if (checkWord("production.txt", "VI")) {
            while (getline(myInputFile, itemTypeCode)) {
                curLineVI++;
                if ((itemTypeCode.find(itemTypeCode, 0)) != std::string::npos) {
                    serialNumStream << counter << ". " << firstThreeLetters << itemTypeCode << serialNumStream.fill('0')
                                    << std::setw(4) << curLineVI;
                    serialNumVector.push_back(serialNumStream.str());
                    std::cout << serialNumVector[curLineVI] << std::endl;
                    myOutputFile << serialNumVector[curLineVI] << std::endl;
                    counter++;
                }
            }
        } else if (checkWord("production.txt", "AM")) {
            while (getline(myInputFile, itemTypeCode)) {
                curLineAM++;
                if ((itemTypeCode.find(itemTypeCode, 0)) != std::string::npos) {
                    serialNumStream << counter << ". " << firstThreeLetters << itemTypeCode
                                    << serialNumStream.fill('0')
                                    << std::setw(4) << curLineAM;
                    serialNumVector.push_back(serialNumStream.str());
                    std::cout << serialNumVector[curLineAM] << std::endl;
                    myOutputFile << serialNumVector[curLineAM] << std::endl;
                    counter++;
                }
            }
        } else if (checkWord("production.txt", "VM")) {
            while (getline(myInputFile, itemTypeCode)) {
                curLineVM++;
                if ((itemTypeCode.find(itemTypeCode, 0)) != std::string::npos) {
                    serialNumStream << counter << ". " << firstThreeLetters << itemTypeCode
                                    << serialNumStream.fill('0')
                                    << std::setw(4) << curLineVM;
                    serialNumVector.push_back(serialNumStream.str());
                    std::cout << serialNumVector[curLineVM ] << std::endl;
                    myOutputFile << serialNumVector[curLineVM] << std::endl;
                    counter++;
                }
            }
        } else {
            serialNumStream << counter << ". " << firstThreeLetters << itemTypeCode << serialNumStream.fill('0')
                            << std::setw(4) << serialNumIndex;
            serialNumVector.push_back(serialNumStream.str());
            std::cout << serialNumVector[serialNumIndex - 1] << std::endl;
            myOutputFile << serialNumVector[serialNumIndex - 1] << std::endl;
            counter++;
        }*/
        serialNumStream << counter << ". " << firstThreeLetters << itemTypeCode << serialNumStream.fill('0')
                        << std::setw(4) << serialNumIndex;
        serialNumVector.push_back(serialNumStream.str());
        std::cout << serialNumVector[serialNumIndex - 1] << std::endl;
        myOutputFile << serialNumVector[serialNumIndex - 1] << std::endl;
        counter++;
        myOutputFile.close();
    }
}

bool checkWord(std::string fileName, std::string search) {

    std::string line;
    std::ifstream myFile;
    myFile.open("production.txt");
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

void addItems() {
    std::vector<std::string> productLineManufacturer;
    std ::vector<std::string> productLineName;
    std::vector<std::string> productLineItemType;

    std::cout << "The products in the Product Line are:\n";
    outputSortedProductNames(productLineName);
    findManufacturerOfProduct(productLineManufacturer, productLineName);
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