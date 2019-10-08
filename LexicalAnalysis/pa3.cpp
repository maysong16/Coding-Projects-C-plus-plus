/*
May Song
Date: 3/23/18
Section: 3513
*/
#include <iostream>
#include <iomanip>
#include "pa3.h"
#include <cstring>

using namespace std;
CStack::CStack() {
    for (int i = 0; i<1000;i++){
        keywordStack[i]= NULL;
    }
    counter = 0;
}

CStack::~CStack() {
}

void CStack:: push(char *keyword){ //push method for stack
    keywordStack[counter]= keyword;
    counter++;

}

char* CStack::pop() { //pop method for stack
    char *keyword = keywordStack[--counter];
    keywordStack[counter]=NULL;
    return keyword;
}


CLexAnalysis::CLexAnalysis() {
    for (int i = 0; i<100;i++){
        syntaxErrors[i]= NULL;
    }
    errorNum = 0;
    numKeyword=0;
}

CLexAnalysis::~CLexAnalysis() {
    for (int i = 0; i < errorNum; i++) {
        delete (syntaxErrors[i]);
    }
    for (int i = 0; i < numKeyword; i++) {
        delete (keywordList[i]);
    }
}

int CLexAnalysis::findIdentifiers(FILE* pFile) { //method to find identifiers
    fseek(pFile, 0, SEEK_SET);
    char *token;
    char *identifierList[100] = {NULL};
    char buffer[500];
    while (fgets(buffer, 1000, pFile)) {
        token = strtok(buffer,"(), =;\n " );
        while (token != NULL) {
            if (token[0] >= 'a' && token[0]<= 'z') {   //check existing identifiers
                addElement(identifierList,token);
            }
            token = strtok(NULL, "(), =;\n ");
        }
    }
    cout << "Identifiers: ";
    int i = 0;
    while (identifierList[i]!=NULL){
        cout << identifierList[i] << " ";
        delete(identifierList[i]);
        identifierList[i]= NULL;
        i++;
    }
    cout << endl;
    return 0;
}

int CLexAnalysis::findConstants(FILE* pFile) { //method to find constants
    fseek(pFile, 0, SEEK_SET);
    char *token;
    char *constantList[100] = {NULL};
    char buffer[500];
    while (fgets(buffer, 1000, pFile)) {
        token = strtok(buffer,"(), =;\n " );
        while (token != NULL) {
            if (token[0] >= '0' && token[0]<= '9') {   //check existing constants
                addElement(constantList,token);
            }
            token = strtok(NULL, "(), =;\n ");
        }
    }
    cout << "Constants: ";
    int i = 0;
    while (constantList[i]!=NULL){
        cout << constantList[i] << " ";
        delete(constantList[i]);
        constantList[i]= NULL;
        i++;
    }
    cout << endl;
    return 0;
}

int CLexAnalysis::findOperators(FILE* pFile) { //method to find operators
    fseek(pFile, 0, SEEK_SET);
    char *operatorList[100] = {NULL};
    char buffer[500];
    char *opera = NULL;
    while (fgets(buffer, 1000, pFile)) {
        int unsigned x = 0;
        while (x < strlen(buffer)) {
            if (buffer[x] == '*' || buffer[x] == '/' || buffer[x] == '+' || buffer[x] == '=' || buffer[x] == '-') {
                opera = new char[3];
                opera[0] = buffer[x];
                opera[1]='\0'; //end string
                if (buffer[x] == buffer[x + 1]) {
                    opera[1] = opera[0];
                    opera[2]= '\0';
                    x++;
                }
                addElement(operatorList,opera);
                delete opera;
            }
            x++;
        }
    }
    cout << "Operators: ";
    int i = 0;
    while (operatorList[i]!=NULL){
        cout << operatorList[i] << " ";
        delete(operatorList[i]);
        operatorList[i]= NULL;
        i++;
    }
    cout << endl;
    return 0;
}

int CLexAnalysis::findDelimiters(FILE* pFile) { //method to find delimiters
    bool semicolFound = false;
    bool commaFound = false;
    fseek(pFile, 0, SEEK_SET);
    char buffer[500];
    while (fgets(buffer, 1000, pFile)) {
        int unsigned x = 0;
        while (x < strlen(buffer)) {
            if (buffer[x] == ';'){  //if a semicolon is found
                semicolFound = true;
            }
            if (buffer[x] == ','){ //if a comma is found
                commaFound = true;
            }
            x++;
        }
    }
    cout << "Delimiters: ";
    if (semicolFound == true){
        cout << "; ";
    }
    if (commaFound== true){
        cout << ",";
    }
    cout << endl;
    return 0;
}

int CLexAnalysis::findKeywords(FILE* pFile) { //method to find keywords
    fseek(pFile, 0, SEEK_SET);
    char *token;
    CStack keywordStack; //object of CStack class
    char buffer[500];
    char *keyword = NULL;
    bool errorFound;
    char line[500];
    while (fgets(buffer, 1000, pFile)) {
        strcpy(line,buffer);
        token = strtok(buffer,"(), =;\n\r " );
        while (token != NULL) {
            if (token[0] >= 'A' && token[0]<= 'Z') {   //check if uppercase
                errorFound = findSyntaxErrors(line, token);
                if (errorFound ==false){
                    keyword = new char[30];
                    strcpy(keyword,token);
                    keywordStack.push(keyword);// push
                }
                else if (strcmp(token,"FOR")==0){
                    addKeyword(token);
                }
            }
            token = strtok(NULL, "(), =;\n\r ");
        }
    }
    cout << endl;
    findLoopDepth(keywordStack);
    cout << "Keywords: ";
    for (int i = 0; i<numKeyword; i++){
            cout << keywordList[i] << " ";
    }
    cout << endl;
    return 0;
}

int CLexAnalysis:: findLoopDepth(CStack &keywordStack){ //method to find depth of nested loops
    int depthSize = 0;
    int index = 0;
    int count = 0; //how many pops
    char *correctLoopStack[50];
    while (keywordStack.counter>0){
        char *keyword = keywordStack.pop(); //pop
        if (strcmp(keyword,"FOR")==0 || strcmp(keyword,"BEGIN")==0 || strcmp(keyword,"END")==0){
            addKeyword(keyword);
        }
        correctLoopStack[index]=keyword;
        index++;
        if (strcmp(keyword,"END") ==0){

        }
        else{
            if (count==0){
                depthSize=0; //missing first END
                char* errorSign = new char[6]; //add END to syntax errors
                strcpy(errorSign, "END");
                syntaxErrors[errorNum]= errorSign;
                errorNum++;
                break;
            }
        }
        if (strcmp(keyword,"FOR")==0) {
            if (strcmp(correctLoopStack[0],"END")!=0){ //missing END
                for (int i = 0; i<index;i++){
                    keyword = correctLoopStack[i];
                    correctLoopStack[i]=NULL;
                    delete keyword;
                }
                char* errorSign = new char[6]; //add END to syntax errors
                strcpy(errorSign, "END");
                syntaxErrors[errorNum]= errorSign;
                errorNum++;
                continue;
            }
            if ((strcmp(correctLoopStack[index-1],"FOR")==0) &&
                    (strcmp(correctLoopStack[index-2],"BEGIN")==0)&& (strcmp(correctLoopStack[index-3],"END")==0)){
                if ((index-2)>depthSize){
                    depthSize=index-2;
                }
                keyword = correctLoopStack[--index]; //delete FOR
                correctLoopStack[index]=NULL;
                delete keyword;
                keyword = correctLoopStack[--index]; //delete BEGIN
                correctLoopStack[index]=NULL;
                delete keyword;
                keyword = correctLoopStack[--index]; //delete END
                correctLoopStack[index]=NULL;
                delete keyword;
            }
            else if ((strcmp(correctLoopStack[index-2],"END")==0)) { //missing BEGIN
                keyword = correctLoopStack[--index]; //delete FOR
                correctLoopStack[index] = NULL;
                delete keyword;
                char *errorSign = new char[6]; //add BEGIN to syntax errors
                strcpy(errorSign, "BEGIN");
                syntaxErrors[errorNum] = errorSign;
                errorNum++;
                if (index > 1) {
                keyword = correctLoopStack[--index]; //delete END
                correctLoopStack[index] = NULL;
                delete keyword;
            }
                else{
                    char *errorSign = new char[6]; //add BEGIN to syntax errors
                    strcpy(errorSign, "END");
                    syntaxErrors[errorNum] = errorSign;
                    errorNum++;
                }
            }
            else if ((index>=3)&&(strcmp(correctLoopStack[index-2],"BEGIN")==0)&&(strcmp(correctLoopStack[index-3],"END")!=0)){ //missing END
                keyword = correctLoopStack[--index]; //delete FOR
                correctLoopStack[index]=NULL;
                delete keyword;
                keyword = correctLoopStack[--index]; //delete BEGIN
                correctLoopStack[index]=NULL;
                delete keyword;
                char* errorSign = new char[6];
                if ((strcmp(correctLoopStack[index-1],"FOR")==0)||(strcmp(correctLoopStack[index-1],"BEGIN")==0)){
                    //add END to syntax errors
                    strcpy(errorSign, "END");
                }
                else{
                    //add to syntax errors
                    keyword = correctLoopStack[--index]; //delete FOR
                    correctLoopStack[index]=NULL;
                    strcpy(errorSign, keyword);
                    delete keyword;
                }
                syntaxErrors[errorNum]= errorSign;
                errorNum++;
            }
            else  if ((strcmp(correctLoopStack[index-2],"BEGIN")!=0)&& (strcmp(correctLoopStack[index-3],"END")==0)){ //BEGIN is mispelled
                keyword = correctLoopStack[--index]; //delete FOR
                correctLoopStack[index]=NULL;
                delete keyword;
                keyword = correctLoopStack[--index]; //delete BEGIN
                correctLoopStack[index]=NULL;
                char* errorSign = new char[6]; //add BEGIN to syntax errors
                strcpy(errorSign, keyword);
                syntaxErrors[errorNum]= errorSign;
                errorNum++;
                delete keyword;
                keyword = correctLoopStack[--index]; //delete END
                correctLoopStack[index]=NULL;
                delete keyword;
            }
        }
        count++;
    }
    cout << "The depth of nested loop(s) is " << depthSize << endl;
    return depthSize;
}

bool CLexAnalysis::findSyntaxErrors(char* buffer, char*token) {
    int leftPar = 0;
    int rightPar = 0;
    char* errorSign = NULL;
    bool synErrorFound = false;
            if(strcmp(token, "FOR")==0 ) {
                for (int unsigned i = 0; i < strlen(buffer); i++) {
                    if (buffer[i] == '(') {
                        leftPar++;
                    } else if (buffer[i] == ')') {
                        rightPar++;
                    }
                }
                if (leftPar > rightPar) { //check if number of left parenthesis is greater than num of right parenthesis
                    for (int n = 0; n<(leftPar-rightPar);n++) {
                        errorSign = new char[3];
                        if (rightPar == 0) {
                            strcpy(errorSign, ")");
                        } else {
                            strcpy(errorSign, "(");
                        }
                        syntaxErrors[errorNum] = errorSign; //add to list of syntax errors
                        errorNum++;
                    }
                    synErrorFound = true;
                } else if (leftPar < rightPar) {
                    for (int n = 0; n<(rightPar-leftPar);n++) {
                        errorSign = new char[3];
                        if (leftPar==0){
                            strcpy(errorSign,"(");
                        }
                        else {
                            strcpy(errorSign, ")");
                        }
                        syntaxErrors[errorNum] = errorSign;
                        errorNum++;
                    }
                    synErrorFound = true;
                }
            }
    return synErrorFound;
}

int CLexAnalysis:: printSyntaxErrors(){
    cout << endl;
    cout << "Syntax Error(s): ";
    for (int i = 0; i<errorNum; i++){
        cout << syntaxErrors[i] << " ";
    }
    if (errorNum==0){
        cout << "NA";
    }
    return 0;
}

int CLexAnalysis::addKeyword(char *keyword) {
    bool keyFound = false;
    for (int i= 0; i< numKeyword; i++){
        if(strcmp(keyword,keywordList[i])==0){
            keyFound = true;
            break;
        }
    }
    if (keyFound==false){
        char* key = new char[6];
        strcpy(key,keyword);
        keywordList[numKeyword]= key;
        numKeyword++;
    }
    return 0;
}

int CLexAnalysis::addElement(char *elementList[], char* element) {
    bool isFound = false; //checks if element exists
    int i = 0;
    while (elementList[i]!=NULL){
        if(strcmp(element,elementList[i])==0){
            isFound = true;
            break;
        }
        i++;
    }
    if (isFound==false){
        char* tok = new char[50];
        strcpy(tok, element);
        elementList[i]= tok; //adds element to list
    }
    return i;
}


int main() {
    struct CLexAnalysis stack1; //object of CLexAnalysis class
    char fileName[50] = {};
    cout << "Please enter the name of the input file: " << endl;
    cin.getline(fileName,1000);
    char myBuffer[1000];
    FILE *myFile;
    myFile = fopen(fileName, "r");
    if (myFile != NULL) {
        while (fgets(myBuffer, 1000, myFile)) { //reads file line by line and stores into myBuffer
            cout << myBuffer;
        }
    }
    else{
        cout << "Error, unable to open file" << endl;
        return 0;
    }

    cout << endl;
    stack1.findKeywords(myFile);
    stack1.findIdentifiers(myFile);
    stack1.findConstants(myFile);
    stack1.findOperators(myFile);
    stack1.findDelimiters(myFile);
    stack1.printSyntaxErrors();
    cout << endl;


    return 0;
}
