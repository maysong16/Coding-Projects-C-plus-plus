//
// Created by mayso on 3/23/2018.
//
#include <iostream>
class CStack{ //stack class
public:
    char *keywordStack[1000];
    CStack(); //constructor
    ~CStack(); //deconstructor
    void push(char *keyword);
    char* pop();
    int counter;
};

class CLexAnalysis{
public:
    char *syntaxErrors[100];
    char* keywordList[3];
    int errorNum;
    int numKeyword;

    CLexAnalysis();  //constructor
    ~CLexAnalysis(); //deconstructor

    int findIdentifiers(FILE *pFile);
    int findConstants(FILE *pFile);
    int findOperators(FILE *pFile);
    int findDelimiters(FILE *pFile);
    int findKeywords(FILE *pFile);
    int findLoopDepth(CStack &keywordStack);
    bool findSyntaxErrors(char *buffer, char* token);
    int printSyntaxErrors();
    int addKeyword(char *keyword);
    int addElement(char* elementList[], char* element);



};

#ifndef PA3_PA3_H
#define PA3_PA3_H

#endif //PA3_PA3_H



