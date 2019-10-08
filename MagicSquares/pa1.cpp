/*
May Song
Date: 2/22/18
Section: 3513
*/
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <limits>
#include "pa1.h"
using namespace std;

CMagicSquare::CMagicSquare() {
    for(int n = 0; n<15;n++){
        for(int m= 0;m< 15; m++){
            m_magicSquare[n][m]=0;
        }
    }
}

CMagicSquare::~CMagicSquare() {
}
int CMagicSquare::printSquare(int i, int row, int col) {//method to print out two-dimensional array to create the magic square
    cout << setw(3) << left << m_magicSquare[row][col] << "  ";
    return 0;
}
int CMagicSquare::calculateSquare(int i, int row, int col){ // method uses Siamese method algorithm to calculate
// each value in the square
    m_magicSquare[row][col] = i * (((row + 1) + (col + 1) - 1 + (int) floor(i / 2)) % i) +
                              (((row + 1) + 2 * (col + 1) - 2) % i) + 1;
    return 0;
}
int CMagicSquare:: calculateSums(int i) { //method to check the sums of every row, column, and diagonal and print them out
    int rowSum[i];
    int colSum[i];
    int diagSum[i];
    for(int n =0;n<i;n++){
        rowSum[n]=0;
        colSum[n]=0;
        diagSum[n]=0;
    }
    int row= 0, col = 0;
    for (row = 0; row < i; row++) { //check sum of rows
        for (col = 0; col < i; col++) {
            rowSum[row] += m_magicSquare[row][col];
        }
    }
    for (col = 0; col < i; col++) { //check sum of columns
        for (row = 0; row < i; row++) {
            colSum[col] += m_magicSquare[row][col];
        }
    }
    for (row=0, col = 0; row < i; row++, col++) { //check sum of first diagonal
            diagSum[0] += m_magicSquare[row][col];
        }
    for (row=0, col = i-1; row < i; row++, col--) { //check sum of second diagonal
        diagSum[1] += m_magicSquare[row][col];
    }
    cout << "Checking the sums of every row: ";
    for (int n = 0; n<i; n++){  //prints out sums of each row
        cout << rowSum[n] << " ";
    }
    cout << endl;
    cout << "Checking the sums of every column: " ;
    for (int n = 0; n<i; n++){ //prints out sums of each column
        cout << colSum[n]<< " ";
    }
    cout << endl;
    cout << "Checking the sums of every diagonal: ";
    for (int n = 0; n<2; n++){ //prints out sums of each diagonal
        cout << diagSum[n]<< " ";
    }
    cout << endl;
    return 0;
}
int CMagicSquare:: createSquare(int i) { // i = squareSize (user input). method contains 10 different ways to create 10 magic squares
    int row = 0;
    int col = 0;
    cout << "Magic Square #1 is: " << endl;
    cout << endl;
    for (row = 0; row < i; row++) { // Magic square 1, original magic square using the Siamese method
        for (col = 0; col < i; col++) {
            calculateSquare(i, row, col); //calls method calculateSquare
            printSquare(i, row, col); //calls method printSquare
        }
        cout << endl;
    }
    cout << endl;
    calculateSums(i); //calls method calculateSums
    cout << endl;
    cout << "Magic Square #2 is: " << endl;
    cout << endl;
    for (row = i - 1; row >= 0; row--) { // Magic square 2, flips square 1
        for (col = i - 1; col >= 0; col--) {
            calculateSquare(i, row, col);
            printSquare(i, row, col);
        }
        cout << endl;
    }
    cout << endl;
    calculateSums(i);
    cout << endl;
    cout << "Magic Square #3 is: " << endl;
    cout << endl;
    for (col = 0; col < i; col++) { // Magic square 3, rows and columns of square 1 are switched
        for (row = 0; row < i; row++) {
            calculateSquare(i, row, col);
            printSquare(i, row, col);
        }
        cout << endl;
    }
    cout << endl;
    calculateSums(i);
    cout << endl;
    cout << "Magic Square #4 is: " << endl;
    cout << endl;
    for (col = i - 1; col >= 0; col--) { // Magic square 4, square 3 is rotated twice, clockwise
        for (row = i - 1; row >= 0; row--) {
            calculateSquare(i, row, col);
            printSquare(i, row, col);
        }
        cout << endl;
    }
    cout << endl;
    calculateSums(i);
    cout << endl;
    cout << "Magic Square #5 is: " << endl;
    cout << endl;
    for (row = i - 1; row >= 0; row--) { // Magic square 5, square 4 is rotated once, clockwise
        for (col = 0; col < i; col++) {
            calculateSquare(i, row, col);
            printSquare(i, row, col);
        }
        cout << endl;
    }
    cout << endl;
    calculateSums(i);
    cout << endl;
    cout << "Magic Square #6 is: " << endl;
    cout << endl;
    for (row = 0; row < i; row++) { // Magic square 6, square 1 is flipped/reflected across middle column
        for (col = i - 1; col >= 0; col--) {
            calculateSquare(i, row, col);
            printSquare(i, row, col);
        }
        cout << endl;
    }
    cout << endl;
    calculateSums(i);
    cout << endl;
    cout << "Magic Square #7 is: " << endl;
    cout << endl;
    for (col = i - 1; col >= 0; col--) { // Magic square 7, rows and columns are switched from square 6
        for (row = 0; row < i; row++) {
            calculateSquare(i, row, col);
            printSquare(i, row, col);
        }
        cout << endl;
    }
    cout << endl;
    calculateSums(i);
    cout << endl;
    cout << "Magic Square #8 is: " << endl;
    cout << endl;
    for (col = 0; col < i; col++) { // Magic square 8, square 7 is rotated twice, counter-clockwise
        for (row = i - 1; row >= 0; row--) {
            calculateSquare(i, row, col);
            printSquare(i, row, col);
        }
        cout << endl;
    }
    if (i == 3) { // for squares of size 3, there are only 8 possible magic squares
        cout << endl;
        cout << "There are no more possible magic squares";
        return 0;
    }
    cout << endl;
    calculateSums(i);
    cout << endl;
    cout << "Magic Square #9 is: " << endl;
    cout << endl;
    int temp = 0; // Magic square 9, swaps 2nd and 2nd to last column of square 1
    int temp2 = 0;
    for (row = 0; row < i; row++) {
        for (col = 0; col < i; col++) {
            calculateSquare(i, row, col);
            if (col == 1) {
                temp = m_magicSquare[row][1];
            } else if (col == (i - 2)) {
                temp2 = m_magicSquare[row][i - 2];
            }
        }
        m_magicSquare[row][1] = temp2;
        m_magicSquare[row][i - 2] = temp;
        for (col = 0; col < i; col++) {
            printSquare(i, row, col);
        }
        cout << endl;
    }
    cout << endl;
    calculateSums(i);
    cout << endl;
    cout << "Magic Square #10 is: " << endl;
    cout << endl;
    int temp3 = 0;
    int temp4 = 0;
    for (col = 0; col < i; col++) { // Magic square 10, swaps 2nd and 2nd to last row of square 1
        for (row = 0; row < i; row++) {
            calculateSquare(i, row, col);
            if (row == 1) {
                temp3 = m_magicSquare[1][col];
            } else if (row == (i - 2)) {
                temp4 = m_magicSquare[i - 2][col];
            }
        }
        m_magicSquare[1][col] = temp4;
        m_magicSquare[i - 2][col] = temp3;
    }
    for (row = 0; row < i; row++) {
        for (col = 0; col < i; col++) {
            printSquare(i, row, col);
        }
        cout << endl;
    }
    cout << endl;
    calculateSums(i);
    cout << endl;
    return 0;
}

int main() {
    int squareSize=0;
    double squareSizecin=0.0;
    bool quit =false;
    bool isDecimal= false;
    CMagicSquare square; //square is an object of the class
   while (quit == false) {
        cout << "Enter the size of a magic square: ";
            cin >> squareSizecin;  // accepts user input
       if ( (int)squareSizecin != squareSizecin){ //checks if user input is a noninteger
           isDecimal = true;
       }
       else{
           squareSize= (int)squareSizecin;
           isDecimal= false;
       }
            if ((squareSize >= 3) && (squareSize <= 15) && ((squareSize % 2) != 0)&& (isDecimal == false)) { //input must be
                // between 3 and 15 and be odd
                square.createSquare(squareSize); //calls method createSquare, taking squareSize as a parameter
                quit = true;
            }
            else{
                cout << "Invalid input. Integer must be odd and be between 3 and 15. Try again. " << endl; //exception, checks
                // invalid input
                cin.clear();
                cin.ignore();
            }
        }
    return 0;
}