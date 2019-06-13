/** @file Prototypes.cpp
 *  @brief Header file with prototypes
 *
 *  @author Vladimir Hardy
 *  @bug No known bugs
 */

#ifndef PROCEDURALPROJECT_PROTOTYPES_H

//prototype (gives the compiler a heads up about the upcoming function)
//@brief Welcomes the user and shows a list
void showMenu();

//@brief Allows the user to produce and track items they've created
void produceItems(std::vector<std::string> &, std::vector<std::string> &, std::vector<std::string> &,
                  std::vector<std::string> &);

//@brief adds new product items to their vectors

bool checkWord(std::string, std::string);

void outputSortedProductNames(std::vector<std::string>);

void findManufacturerOfProduct(std::vector<std::string>, std::vector<std::string>);

//@brief Creates a new account for the user and saves info into loginCreds.txt
//@return Username, password
void createAccount();

std::string encryptString(std::string);

//@brief Allows the user to login to their existing account
void employeeAccount();

void addItems(std::vector<Products> &);

void
loadVectors(std::vector<Products> &, std::vector<std::string> &, std::vector<std::string> &, std::vector<std::string> &,
            std::vector<std::string> &,
            std::vector<int> &, std::vector<int> &, std::vector<int> &, std::vector<int> &);

std::pair<bool, int > findInVector(const std::vector<std::string>  &, std::string &);

//@brief Production statistics stub
void productionStatistics();

void exit();


#endif //PROCEDURALPROJECT_PROTOTYPES_H