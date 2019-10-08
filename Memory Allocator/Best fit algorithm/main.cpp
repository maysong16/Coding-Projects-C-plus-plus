/*
May Song
Date: 3/13/18
Section: 3513
*/
#include <iostream>
#include <iomanip>
#include "pa2diff.h"
#include <cstring>
#include <cmath>

using namespace std;

CList::CList() {
    m_addOption= 0;
}

CList::~CList() {
}

void CList::addUsedPage(Node *pNode, char *szName) {
    strcpy(pNode->programName, szName);
    //add to the tail
    if (usedHead == NULL) {
        usedHead = pNode;
        usedHead->usedNext = NULL;
        return;
    }
    Node *pTemp = usedHead;
    for (; pTemp != NULL; pTemp = pTemp->usedNext) {
        if (pTemp->usedNext == NULL) {//found tail
            pTemp->usedNext = pNode;
            pNode->usedNext = NULL;
            break;
        }
    }
}

void CList:: addFreePage(Node *pNode) {
    strcpy(pNode->programName, "FREE");
    if (freeHead == NULL) {
        freeHead = pNode;
        freeHead->freeNext = NULL;
        return;
    }
    if (pNode->pageNum < freeHead->pageNum) {
        pNode->freeNext = freeHead;
        freeHead = pNode;
        return;
    }
    //find the next page number and add the pNode before it.
    Node *pNextNode = NULL;
    Node *pPreNode = NULL;
    int nFound = 0;
    //check if program name exist
    pPreNode = freeHead;
    for (pNextNode = freeHead; pNextNode != NULL; pNextNode = pNextNode->freeNext) {
        if (pNode->pageNum < pNextNode->pageNum) {
            if (pNextNode == freeHead) {
                pNode->freeNext = pNextNode;
                freeHead = pNode;
                break;
            }
            pPreNode->freeNext = pNode;
            pNode->freeNext = pNextNode;
            nFound = 1;
            break;
        }
        pPreNode = pNextNode;
    }
    if (nFound == 0) {
        Node *pTemp = freeHead;
        for (; pTemp != NULL; pTemp = pTemp->freeNext) {
            if (pTemp->freeNext == NULL) {//found tail
                pTemp->freeNext = pNode;
                pNode->freeNext = NULL;
                break;
            }
        }
    }
}
void CList::addProgram(char *szName, int numPages) {
    if (m_addOption==0){
        addBestFit(szName,numPages);
    }
    else{
        addWorstFit(szName,numPages);
    }
}

Node* CList:: getPreNodefromFreeList(Node *pNode){
    Node *tempNode = freeHead;
    Node *prevNode = freeHead;
    for (tempNode = freeHead; tempNode != NULL; tempNode = tempNode->freeNext){
        if (tempNode == pNode) {
            break;
        }
        prevNode = tempNode;
    }
    return prevNode;
}

void CList::addBestFit(char *szName, int numPages) {
    int nFound = 0;
    Node *pNode = NULL;
    //check if program name exist
    for (pNode = usedHead; pNode != NULL; pNode = pNode->usedNext) {
        if (strcmp(pNode->programName, szName) == 0) {
            nFound = 1;
            break;
        }
    }
    if (nFound == 1) {
        //print warning
        cout << "Error, Program " << szName << " already running" << endl;
        return;
    }

    Node *pFreeNode = NULL;
    Node *pCurNode = NULL;
    Node *pPreNode = freeHead;
    //Node *pPreNode = memoryHead;
    Node *pNextNode = NULL;

    nFound = 0;
    int j = 0;

    Node *minNode= NULL;
    int min = 100;
    int nCount = 0;
    for (pNode = memoryHead; j <32; j++) {
        pCurNode = pNode;
        //int nCount = 0;
        nCount=0;

        while (strcmp(pNode->programName, "FREE") == 0) { //check if continuous free pages enough for numPages
            if (strcmp(pNode->programName, "FREE") != 0) {
                break;

            }
            nCount++;
            pNode++;
        }
        if (nCount > 0) {
            if (nCount == numPages) {
                nFound = 1;
                minNode = pCurNode;
                break;
            } else if (nCount > numPages) {
                if (nCount < min) {
                    min = nCount;
                    minNode = pCurNode;
                    nFound = 1;
                }
            }
        }
        pPreNode = pCurNode;
        pNode++;
    }
    if(nFound==1) {
        pPreNode = getPreNodefromFreeList(minNode);
        nCount = 0;
        // pFreeNode = pCurNode;
        pFreeNode=minNode;
        while(pFreeNode) {
            if (nCount == numPages) {
                break;
            }

            //remove it from freelist
            pPreNode->freeNext = pFreeNode->freeNext;
            pNextNode = pFreeNode->freeNext;
            if (pFreeNode == freeHead) {
                freeHead = pNextNode;
            }
            pFreeNode->freeNext = NULL;
            addUsedPage(pFreeNode, szName);
            pFreeNode = pNextNode;
            nCount++;
        }
    }
    cout << "Program " << szName << " added successfully: " << numPages << " page(s) used." << endl;
}

void CList::addWorstFit(char *szName, int numPages) {
    int nFound = 0;
    Node *pNode = NULL;
    //check if program name exist
    for (pNode = usedHead; pNode != NULL; pNode = pNode->usedNext) {
        if (strcmp(pNode->programName, szName) == 0) {
            nFound = 1;
            break;
        }
    }
    if (nFound == 1) {
        //print warning
        cout << "Error, Program " << szName << " already running" << endl;
        return;
    }

    Node *pFreeNode = NULL;
    Node *pCurNode = NULL;
    Node *pPreNode = freeHead;
    Node *pNextNode = NULL;

    nFound = 0;

    int j = 0;

    Node *maxNode= NULL;
    int max = 0;
    int nCount = 0;
    for (pNode = memoryHead; j <32; j++) {
        pCurNode = pNode;
        //int nCount = 0;
        nCount=0;

        while (strcmp(pNode->programName, "FREE") == 0) { //check if continuous free pages enough for numPages
            nCount++;
            if (strcmp(pNode->programName, "FREE") != 0) {
                break;

            }
            pNode++;
        }
        if (nCount == numPages) {
            nFound = 1;
            maxNode = pCurNode;
            break;
        } else if (nCount > numPages) {

            if (nCount > max) {
                max = nCount;
                maxNode = pCurNode;
                nFound = 1;
            }
        }
        pPreNode = pCurNode;
        pNode++;
    }
    if(nFound==1) {
        pPreNode = getPreNodefromFreeList(maxNode);
        nCount = 0;
        // pFreeNode = pCurNode;
        pFreeNode=maxNode;
        while(pFreeNode) {
            if (nCount == numPages) {
                break;
            }

            //remove it from freelist
            pPreNode->freeNext = pFreeNode->freeNext;
            pNextNode = pFreeNode->freeNext;
            if (pFreeNode == freeHead) {
                freeHead = pNextNode;
            }
            pFreeNode->freeNext = NULL;
            addUsedPage(pFreeNode, szName);
            pFreeNode = pNextNode;
            nCount++;
        }
    }
    cout << "Program " << szName << " added successfully: " << numPages << " page(s) used." << endl;
}

void CList:: deleteProgram(char *szName) {
    int pagesReclaimed=0;
    int nFound = 0;
    Node *pNode = NULL;
    Node *pPreNode = usedHead;
    //check if program name exist
    for (pNode = usedHead; pNode != NULL; pNode = pNode->usedNext) {
        if (strcmp(pNode->programName, szName) == 0) { //found the beginning of the program
            nFound = 1;
            break;
        }
        pPreNode = pNode;
    }
    if (nFound == 0) {
        cout << "Program does not exist" << endl;//print warning
        return;
    }

    Node *pNextNode = NULL;

    //remove from the usedlist
    while(pNode) {
        if (strcmp(pNode->programName, szName) != 0) {
            break;
        }
        pPreNode->usedNext = pNode->usedNext;

        pNextNode = pNode->usedNext;
        if (usedHead == pNode) {
            usedHead = pNextNode;
        }
        pNode->usedNext = NULL;
        //add back to the freelist in the original location
        addFreePage(pNode);
        pNode = pNextNode;
        pagesReclaimed++;
    }
    cout << "Program " << szName << " successfully killed, " << pagesReclaimed << " page(s) reclaimed." << endl;
}
int CList:: printMemory() {
    Node *pTempNode = memoryHead;
    for (int i = 0; i < 4; i++) {
        for (int n = 0; n < 8; n++) {
            cout << setw(5) << left << pTempNode->programName;
            pTempNode++;
        }
        cout << endl;
    }
}
int CList:: findFragments(){
    int numFragments = 0;
    bool isAllFree = false;
    for (int n = 0; n < 31; n++){
        if (strcmp(memoryHead[n].programName, "FREE")!=0 && (strcmp(memoryHead[n+1].programName, "FREE")==0 )){
            numFragments++;
        }
        if (strcmp(memoryHead[n].programName, "FREE")==0){
            isAllFree = true;
        }
        /*if (strcmp(memoryHead[n].programName, "FREE")==0 && (strcmp(memoryHead[n+1].programName, "FREE")!=0 )){
            numFragments++;
        }*/
    }
    if (numFragments==0 && isAllFree==true){
        numFragments=1;
    }
    cout << "There are " << numFragments << " fragment(s)." << endl;
}


int main(int argc, char *argv[]) {
    memoryHead = NULL;
    usedHead = NULL;
    freeHead = NULL;
    memoryHead = (Node*)malloc(sizeof(Node) * 32); //allocate size of memory
    for (int n = 0; n < 32; n++)
    {
        memoryHead[n].pageNum = n;
        strcpy(memoryHead[n].programName, "FREE");
        memoryHead[n].freeNext = &memoryHead[n + 1];
    }
    memoryHead[31].freeNext = NULL;

    freeHead = memoryHead;

    CList list1;
    int menuOption = 0;
    char progName[30];
    int progSize = 0;
    int numPages = 0;

    if (strcmp(argv[1], "worst")==0){
        list1.m_addOption = 1;
        cout << "Using worst fit algorithm" << endl;
        cout << endl;
    }
    else{
        list1.m_addOption = 0;
        cout << "Using best fit algorithm" << endl;
        cout << endl;
    }

    cout << "1. Add program" << endl;
    cout << "2. Kill program" << endl;
    cout << "3. Fragmentation" << endl;
    cout << "4. Print memory" << endl;
    cout << "5. Exit" << endl;
    while (menuOption != 5) {
        cout << endl;
        cout << "choice - ";
        cin >> menuOption;
        if (menuOption == 5) {
            free(memoryHead);
            return 0;
        }

        switch(menuOption){
            case 1: cout << "Program name - "; //add program
                cin >> progName;
                cout << "Program size (KB) - ";
                cin >> progSize;
                numPages = ceil(progSize/4.0);
                list1.addProgram(progName,numPages);
                break;

            case 2: cout << "Program name - "; //kill program
                cin >> progName;
                list1.deleteProgram(progName);
                break;
            case 3: list1.findFragments(); //print out number of fragments in memory
                break;
            case 4: list1.printMemory();  //print out memory
                break;
        }

    }
    return 0;
}
