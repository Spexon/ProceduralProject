# ProceduralProject
//Nothing that I try seems to work or get on Github, so I will leave this here temporarily

#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "Hello There! Please select an option below:\n";
    cout << "Production Line Tracker\n\n";
    cout << "1. Add Employee Account\n" << "2. Add Music Player\n" << "3. Add Movie Player\n"
         << "4. Display Production Statistics\n" << "5. Exit\n";

    cout << "Please enter your username: \n";
    string user;
    getline(cin, user);

    cout << "Please enter your password: \n";
    string pass;
    getline(cin, pass);
    return 0;

}
