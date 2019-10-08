//
// Created by mayso on 2/17/2018.
//

#ifndef PA1_PA1_H
#define PA1_PA1_H

class CMagicSquare
{
public:
    CMagicSquare(); //constructor
    ~CMagicSquare(); //deconstructor

    int m_magicSquare[15][15]; //member variable

    //class methods
    int createSquare(int i);
    int printSquare(int i, int row, int col);
    int calculateSquare(int i, int row, int col);
    int calculateSums(int i);
};



#endif //PA1_PA1_H
