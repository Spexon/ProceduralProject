/** @file Prototypes.cpp
 *  @brief Header file with prototypes
 *
 *  @author Vladimir Hardy
 *  @bug No known bugs
 */
#include <vector>

#ifndef PROCEDURALPROJECT_PROTOTYPES_H

//prototype (gives the compiler a heads up about the upcoming function)
//@brief Welcomes the user and shows a list
void showMenu();

//@brief Allows the user to produce and track items they've created
void produceItems(std::vector<std::string>&productLineManufacturer, std::vector<std::string>&productLineName,
                  std::vector<std::string>&productLineItemType);

//@brief adds new product items to their vectors

bool checkWord(std::string fileName, std::string search);

void outputSortedProductNames(std::vector<std::string>);

void findManufacturerOfProduct(std::vector<std::string>, std::vector<std::string>);

//@brief Creates a new account for the user and saves info into loginCreds.txt
//@return Username, password
void createAccount();

std::string encryptString(std::string);

//@brief Allows the user to login to their existing account
void employeeAccount();

void addItems(std::vector<std::string>&, std::vector<std::string>&,
              std::vector<std::string>&);

//@brief Production statistics stub
void productionStatistics();

void exit();


#endif //PROCEDURALPROJECT_PROTOTYPES_H