/* @file Prototypes
*  @brief Header file with prototypes
*  @Author Vladimir Hardy
*/

#ifndef PROCEDURALPROJECT_PROTOTYPES_H
//prototype (gives the compiler a heads up about the upcoming function)
//@brief Welcomes the user and shows a list
void showMenu();

//@brief Allows the user to produce and track items they've created
void produceItems();

//@brief Creates a new account for the user and saves info into loginCreds.txt
//@return Username, password
std::string createAccount();

//@brief Allows the user to login to their existing account
void employeeAccount();

//@brief Music player stub
void musicPlayer();

//@brief Movie Player stub
void moviePlayer();

//@brief Production statistics stub
void productionStatistics();

//@brief Exits the program by setting the while loop condition to false
void exit();

#endif //PROCEDURALPROJECT_PROTOTYPES_H
