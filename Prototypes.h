/** @file Prototypes.cpp
 *  @brief Header file with prototypes
 *
 *  @author Vladimir Hardy
 *  @bug No known bugs
 */

#ifndef PROCEDURALPROJECT_PROTOTYPES_H

//prototype (gives the compiler a heads up about the upcoming function)

void showMenu();

void produceItems(std::vector<std::string> &, std::vector<std::string> &);

bool checkWord(std::string, std::string);

void outputSortedProductNames(std::vector<std::string>);


void createAccount();

std::string encryptString(std::string);

void employeeAccount();

void addItems(std::vector<std::string> &);

void
loadVectors(std::vector<std::string> &productionLog, std::vector<std::string> &productLineName,
            int &curLineMM, int &curLineVI, int &curLineAM,
            int &curLineVM);

bool isEmpty(std::ifstream &pFile);

void productionStatistics(std::vector<std::string> &, std::vector<std::string> &);

void exit();

#endif //PROCEDURALPROJECT_PROTOTYPES_H