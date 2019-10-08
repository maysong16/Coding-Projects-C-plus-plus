//
// Created by mayso on 3/14/2018.
//

#ifndef PA2DIFF_PA2DIFF_H
#define PA2DIFF_PA2DIFF_H

struct Node {
    int pageNum;
    char programName[30];
    Node *freeNext;
    Node *usedNext;
};

static Node *memoryHead = NULL; // the head of a linked list of memory.
static Node *usedHead = NULL; // the head of a linked list of used space.
static Node *freeHead = NULL; // the head of a linked list of used space.

class CList
{
public:
    CList(); // constructor
    ~CList(); // deconstructor

    int m_addOption; //member variable

    //class methods
    void addUsedPage(Node *pNode, char *szName);
    void addFreePage(Node *pNode);
    void addProgram(char *szName, int numPages);
    void addBestFit(char *szName, int numPages);
    Node* getPreNodefromFreeList(Node *pNode);
    void addWorstFit(char *szName, int numPages);
    void deleteProgram(char *szName);
    int printMemory();
    int findFragments();



};
/*
 Lab- Stack
private:
    int[]array;
public
    void push(int);
    int pop( );
*/





#endif //PA2DIFF_PA2DIFF_H
