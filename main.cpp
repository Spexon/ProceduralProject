#include <iostream>
#include <string>
#include <fstream>
//Ctrl + alt +  L for code formatter
//prototype (gives the compiler a heads up about the upcoming function)
//These prototypes can be put inside a header file
void sayHello();

void printSum(int, int);

int calculateSum(int, int);

int main() {
    std::ofstream myOutputFile; //Use this for username/password
    myOutputFile.open("example.txt");
    myOutputFile << "Writing this to a file.\n";
    myOutputFile.close();

    myOutputFile.open("example.txt", std::ios_base::app);
    myOutputFile << "Writing more to a file.\n";
    myOutputFile.close();

    std::string line;
    std::ifstream myInputFile("example.txt");
    if (myInputFile.is_open()) {
        while (getline(myInputFile, line)) //Stores a line into a file called line, then uses that to output to console
        {
            std::cout << line << std::endl;
        }
        myInputFile.close();
    } else std::cout << "Unable to open file";

    sayHello(); //Call to the function sayHello
    std::cout << "Production Line Tracker\n\n";
    std::cout << "1. Add Employee Account\n" << "2. Add Music Player\n" << "3. Add Movie Player\n"
              << "4. Display Production Statistics\n" << "5. Exit\n";

    std::cout << "Please enter your username: \n";
    std::string user;
    getline(std::cin, user);

    std::cout << "Please enter your password: \n";
    std::string pass;
    getline(std::cin, pass);
    printSum(2, 3);
    int sum = calculateSum(5, 5);
    std::cout << sum << std::endl;
    return 0;
}

void sayHello() {
    std::cout << "Hello There! Please select an option below:" << std::endl;
}

void printSum(int num1, int num2) {
    std::cout << "The sum is " << num1 + num2 << std::endl;
}

int calculateSum(int num1, int num2) {
    return num1 + num2;
}