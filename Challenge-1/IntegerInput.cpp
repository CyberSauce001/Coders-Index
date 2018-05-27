#include <iostream>
#include <cmath>

using namespace std;

int main() {
    char choice;
    int n1,n2;
    
    cout << "Enter a number: ";
    cin >> n1;
    cout << "\nEnter a number: ";
    cin >> n2;
    
    do{
        cout << endl << endl;
        cout << "a - Display all odd\n";
        cout << "b - Display all prime\n";
        cout << "c - Sum of numbers between 1 and 10\n";
        cout << "q - Quit\n\n";
        cin >> choice;

        switch(choice) {
            case 'a': cout <<"test";
                    break;
            case 'b': cout << "test";
                    break;
            case 'c': cout << "test";
                    break;
            case 'q': break;
            default: cout << "<Unknown Command>\n\n";
                     break;
        }
    }while(choice!='q');

    return 0;
}
