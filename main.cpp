#include <iostream>
#include <string>
#include <fstream>

//Ctrl + alt +  L for code formatter
//prototype (gives the compiler a heads up about the upcoming function)
//These prototypes can be put inside a header file
void showMenu();

void employeeAccount();

std::string createAccount();

void musicPlayer();

void moviePlayer();

void productionStatistics();

void exit();

int main() {

    bool reRun = true;
    while (reRun) {
        showMenu(); //Call to the function showMenu
        int number;
        std::cin >> number;
        std::string ans;
        switch (number) {
            case 1:
                std::cout << "Would you like to create a new account? (yes or no)\n";

                if (ans == "yes" || ans == "Yes" || ans == "y") {
                    createAccount(); //Call to createAccount which will create a new username and password
                    employeeAccount();
                } else {
                    employeeAccount(); //Call to employeeAccount which will prompt the user to log in
                }
                break;
            case 2:
                musicPlayer(); //STUB function
                break;
            case 3:
                moviePlayer(); //STUB function
                break;
            case 4:
                productionStatistics(); //STUB function
                break;
            case 5:
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
    std::cout << "Hello There! Please select an option below:\n" << std::endl;
    std::cout << "Production Line Tracker\n";
    std::cout << "1. Add Employee Account\n" << "2. Add Music Player\n" << "3. Add Movie Player\n"
              << "4. Display Production Statistics\n" << "5. Exit\n";
}

std::string createAccount() {
    std::cout << "Please enter your full name";
    std::string name;
    std::cin >> name;
    std::ofstream myOutputFile;
    myOutputFile.open("loginCreds.txt", std::ios_base::app);
    myOutputFile << "User's full name: " << name << std::endl; //adding name to the file loginCreds
    myOutputFile.close();

    std::cout << "Please enter a username: \n";
    std::string username;
    std::cin >> username;
    myOutputFile.open("loginCreds.txt", std::ios_base::app);
    myOutputFile << "User's username: " << username << std::endl; //adding username to the file loginCreds
    myOutputFile.close();

    std::cout << "Please enter a password: \n";
    std::string password;
    std::cin >> password;
    myOutputFile.close();
    myOutputFile.open("loginCreds.txt", std::ios_base::app); //Appending password to the file loginCreds
    myOutputFile << "User's password: " << password << std::endl;
    return (username, password);
}

void employeeAccount() {
    std::string line;
    std::ifstream myInputFile("loginCreds.txt");
    if (myInputFile.is_open()) {
        while (getline(myInputFile, line)) //Stores a line into a file called line, then uses that to output to console
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
        }
        myInputFile.close();
    } else std::cout << "Unable to open file";

    if (myInputFile.is_open()) {
        while (getline(myInputFile, line)) //Stores a line into a file called line, then uses that to output to console
        {


        }
        myInputFile.close();
    } else std::cout << "Unable to open file\n";
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