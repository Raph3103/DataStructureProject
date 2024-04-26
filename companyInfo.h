//
// Created by ayele on 30/05/2022.
//

#ifndef SPRING2022WET2DATASTRUCTURES_COMPANYINFO_H
#define SPRING2022WET2DATASTRUCTURES_COMPANYINFO_H

#include "AvlTreeWithRankAndSums.h"
#include "definitions.h"
#include "HashTable.h"

class groupCompanyInfo{

public:
    int numberOfEmployeesWithSalary0;
    long int sumOfGradesWithSalary0;
    int numOfEmployees;
    int numOfCompaniesInTheUnion;
    long double valueOfTheUnion=0;
    AVLtree<nodeInAVL>* treeOfGrades;
    hashTable* allEmployeesInGroup;  //hashTableOfAllTheEmployeesInTheGroup
    companyNode* groupRoot;

    groupCompanyInfo()

    {
        allEmployeesInGroup = new hashTable;
        treeOfGrades = new AVLtree<nodeInAVL>;
        numOfEmployees = 0;
        numOfCompaniesInTheUnion = 1;
        numberOfEmployeesWithSalary0 = 0;
        sumOfGradesWithSalary0 = 0;
        groupRoot = nullptr;

    }

    ~groupCompanyInfo() {

        delete allEmployeesInGroup;
        delete treeOfGrades;

    }
};




#endif //SPRING2022WET2DATASTRUCTURES_COMPANYINFO_H
