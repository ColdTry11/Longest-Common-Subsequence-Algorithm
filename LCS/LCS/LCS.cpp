#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

char** b;
int** c;

void lcsLength(string X, string Y) {
    // Get length of each string
    auto m = X.length();
    auto n = Y.length();

    // Allocate memory for two 2D arrays
    b = new char* [m + 1];
    c = new int* [m + 1]; 

    // Initialize each element of the two 2D arrays
    for (int i = 0; i <= m; i++) {
        b[i] = new char[n + 1];
        c[i] = new int[n + 1];
    }

    // Set the first column of c to 0
    for (int i = 0; i <= m; i++) {
        c[i, 0] = 0;
    }

    // Set the first row of c to 0
    for (int j = 0; j <= n; j++) {
        c[0, j] = 0;
    }

    // Calculate the LCS
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            // If the two characters are equal
            if (X[i - 1] == Y[j - 1]) { 
                c[i, j] = c[i - 1, j - 1] + 1; 
                b[i][j] = '\\';
            }
            // If the LCS coming from the top is longer than the one coming from the left
            else if (c[i - 1, j] >= c[i, j - 1]) { 
                c[i, j] = c[i - 1, j]; 
                b[i][j] = '|'; 
            }
            // If the LCS coming from the left is longer than the one coming from the top
            else { 
                c[i, j] = c[i, j - 1]; 
                b[i][j] = '-';
            }
        }
    }
}



// Print LCS by following arrow path
void printLcs(string X, int i, int j) {
    if (i == 0 || j == 0) {
        return;
    }
    if (b[i][j] == '\\') {
        printLcs(X, i - 1, j - 1);
        cout << X[i - 1];
    }
    else if (b[i][j] == '|') {
        printLcs(X, i - 1, j);
    }
    else {
        printLcs(X, i, j - 1);
    }
}


int main(int argc, char** argv)
{
    //Check for command line error
    if (argc == 1) {
        cout << "You forgot the command line parameter" << endl;
        exit(0);
    }

    //Check for file
    ifstream ifs;
    ifs.open(argv[1], ios::in);
    if (!ifs) {
        cout << "could not find file " << argv[1] << endl;
        exit(0);
    }

    // Get strings X and Y
    string X, Y;
    getline(ifs, X);
    getline(ifs, Y);

    // Print results
    cout << "String X: " << X << endl << "String Y: " << Y << endl << "LCS: ";
    lcsLength(X, Y);
    printLcs(X, X.length(), Y.length());
    cout << endl;

    // Close the input file
    ifs.close();

    return 0;
}