#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "Hello There! Please select an option below:\n"; //Main Menu
    cout << "Production Line Tracker\n\n";
    cout << "1. Add Employee Account\n" << "2. Add Music Player\n" << "3. Add Movie Player\n"
         << "4. Display Production Statistics\n" << "5. Exit\n";

    cout << "Please enter your username: \n"; //Username for employers to log in (incomplete)
    string user;
    getline(cin, user);

    cout << "Please enter your password: \n"; //Password for employers to log in
    string pass;
    getline(cin, pass);

    return 0;
}

