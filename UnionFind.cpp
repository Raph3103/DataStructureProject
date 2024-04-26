//
// Created by ayele on 28/05/2022.
//

#include "UnionFind.h"
#include "definitions.h"
#include "companyInfo.h"





UnionFind::UnionFind(int k) : numOfCompanies(k),companyTable(new companyNode*[k+1]),bigBoxOfTheSystem(new bigBox)
{
    for (int i=1; i<k+1; i++)
    {
        companyTable[i] = new companyNode;
        companyTable[i]->father= nullptr;
        companyTable[i]->companyID = i;
        companyTable[i]->r_value=i;
        companyTable[i]->companyInfo=new groupCompanyInfo;
        companyTable[i]->companyInfo->valueOfTheUnion=i;
        companyTable[i]->companyInfo->groupRoot=companyTable[i];

    }

    bigBoxOfTheSystem->numOfEmployees=0;
    bigBoxOfTheSystem->numOfEmployeesWithSalary0=0;
    bigBoxOfTheSystem->sumOfGradesOfEmployeesWithSalary0=0;
    bigBoxOfTheSystem->treeOfAllGrades= new AVLtree<nodeInAVL>;
}

UnionFind::~UnionFind()
{
    for (int i=1; i<numOfCompanies+1; i++)
    {
        if(companyTable[i]->companyInfo != nullptr)
        {
            delete companyTable[i]->companyInfo;
        }
        delete companyTable[i];
    }

    delete[] companyTable;
    delete bigBoxOfTheSystem->treeOfAllGrades;
    delete bigBoxOfTheSystem;
}

groupCompanyInfo* UnionFind::find(int companyId) const
{
     double total_sum=0;
     double to_substract=0;

    companyNode* currentNode = companyTable[companyId];
    companyNode* base = currentNode;

    companyNode* prev = currentNode;
    currentNode = currentNode->father;
    while (currentNode != nullptr)
    {
        total_sum+=prev->r_value;
        prev = prev->father;
        currentNode = currentNode->father;
    }


    companyNode* root = prev;
    companyNode* next = base->father;
    groupCompanyInfo* structToReturn = root->companyInfo;

    //kivouts masloulim dans le find
    while (next != nullptr)
    {
        base->father = root;           //la ligne qui fait le kivouts masloulim
        double temp=base->r_value;
        base->r_value=total_sum-to_substract;
        to_substract+=temp;
        base = next;
        next = next->father;
    }
    return structToReturn;
}


void UnionFind::mergeGroups(int companyId1, int companyId2, double Factor)
{
    //dans cette fonction fusion de TOUT le metaer akvoutsa + les etsim afouhim
    //in the end, root of the upside down united tree should point to finalStruct

    groupCompanyInfo* groupOneStruct = find(companyId1);
    groupCompanyInfo* groupTwoStruct = find(companyId2);


    if(groupOneStruct==groupTwoStruct)
    {
        return;
    }

    //constructing finalStruct gradeTree
    AVLtree<nodeInAVL>* firstGradeTree = groupOneStruct->treeOfGrades;
    AVLtree<nodeInAVL>* secondGradeTree = groupTwoStruct->treeOfGrades;
    AVLtree<nodeInAVL>* finalGradeTree = firstGradeTree->mergeWith(secondGradeTree);


    //now we are going to merge the upside down trees
    companyNode* absoluteRoot;
    //root of smaller tree should have a NULLPTR in its structInfo field after merging,
    // so that only the absolute root of the final tree will have a pointer to the structInfo
    if (groupOneStruct->numOfCompaniesInTheUnion >= groupTwoStruct->numOfCompaniesInTheUnion)   //absolute root= premier
    {
        companyNode* groupRoot1=groupOneStruct->groupRoot;  //acquirer_root
        companyNode* groupRoot2 = groupTwoStruct->groupRoot; //target_root


        groupRoot1->r_value+=(groupTwoStruct->valueOfTheUnion*Factor);
        groupRoot2->r_value-=groupRoot1->r_value;

        groupRoot2->companyInfo= nullptr;  //is no more a root so dont have to point to any GroupcompanyInfo (=metaer akvoutsa)
        absoluteRoot = upsideDownMerge(groupOneStruct->groupRoot,groupTwoStruct->groupRoot);
        absoluteRoot->companyInfo->numOfCompaniesInTheUnion = groupOneStruct->numOfCompaniesInTheUnion + groupTwoStruct->numOfCompaniesInTheUnion;
        delete absoluteRoot->companyInfo->treeOfGrades;   //delete au premier ets
        absoluteRoot->companyInfo->treeOfGrades = finalGradeTree;

        //we will pass on all the employees in the second hash table (of target) and insert each one in the first hashtABLE (Acquire)
        hashTable* firstHash=groupOneStruct->allEmployeesInGroup;
        hashTable* secondHash=groupTwoStruct->allEmployeesInGroup;
        int sizeOfSecond= secondHash->getSize();
        for(int i=0; i<sizeOfSecond; i++)
        {
            employeeHashNode* to_insert= secondHash->employees[i];

            while(to_insert!= nullptr)
            {
                to_insert->companyID=companyId1;
                firstHash->insert(*to_insert);
                to_insert=to_insert->next;
            }
        }
        absoluteRoot->companyInfo->numOfEmployees = groupOneStruct->numOfEmployees + groupTwoStruct->numOfEmployees;
        absoluteRoot->companyInfo->groupRoot = absoluteRoot;
        absoluteRoot->companyInfo->numberOfEmployeesWithSalary0 = groupOneStruct->numberOfEmployeesWithSalary0 + groupTwoStruct->numberOfEmployeesWithSalary0;
        absoluteRoot->companyInfo->sumOfGradesWithSalary0=groupOneStruct->sumOfGradesWithSalary0+groupTwoStruct->sumOfGradesWithSalary0;
        double value_after_union=groupOneStruct->valueOfTheUnion+((groupTwoStruct->valueOfTheUnion)*Factor);
        absoluteRoot->companyInfo->valueOfTheUnion=value_after_union;
        delete groupTwoStruct;
    }
    else {
        companyNode* groupRoot1 = groupOneStruct->groupRoot;
        companyNode* groupRoot2=groupTwoStruct->groupRoot;
      //  groupTwoStruct->valueOfTheUnion=groupOneStruct->valueOfTheUnion+((groupTwoStruct->valueOfTheUnion)*Factor);


        groupRoot1->r_value+=((groupTwoStruct->valueOfTheUnion*Factor)-groupRoot2->r_value);

        groupRoot1->companyInfo= nullptr;
        absoluteRoot = upsideDownMerge(groupTwoStruct->groupRoot,groupOneStruct->groupRoot);
        absoluteRoot->companyInfo->numOfCompaniesInTheUnion = groupOneStruct->numOfCompaniesInTheUnion + groupTwoStruct->numOfCompaniesInTheUnion;
        delete absoluteRoot->companyInfo->treeOfGrades;
        absoluteRoot->companyInfo->treeOfGrades = finalGradeTree;

        //we will pass on all the employees in the first hash table (of target) and insert each one in the second hashtABLE (Acquire)
        hashTable* firstHash=groupOneStruct->allEmployeesInGroup;
        hashTable* secondHash=groupTwoStruct->allEmployeesInGroup;
        int sizeOfFirst= firstHash->getSize();
        for(int i=0; i<sizeOfFirst; i++)
        {

            employeeHashNode* to_insert= firstHash->employees[i];

            while (to_insert != nullptr) {

                to_insert->companyID = companyId2;
                secondHash->insert(*to_insert);
                to_insert = to_insert->next;

            }

        }

        absoluteRoot->companyInfo->numOfEmployees = groupOneStruct->numOfEmployees + groupTwoStruct->numOfEmployees;
        absoluteRoot->companyInfo->groupRoot = absoluteRoot;
        absoluteRoot->companyInfo->numberOfEmployeesWithSalary0 = groupOneStruct->numberOfEmployeesWithSalary0 + groupTwoStruct->numberOfEmployeesWithSalary0;
        absoluteRoot->companyInfo->sumOfGradesWithSalary0=groupOneStruct->sumOfGradesWithSalary0+groupTwoStruct->sumOfGradesWithSalary0;
        double value_after_union=groupOneStruct->valueOfTheUnion+((groupTwoStruct->valueOfTheUnion)*Factor);
        absoluteRoot->companyInfo->valueOfTheUnion=value_after_union;

        delete groupOneStruct;
    }
}

companyNode* UnionFind::upsideDownMerge(companyNode* bigGroupRoot, companyNode* smallGroupRoot)
{
    smallGroupRoot->father = bigGroupRoot;
    return bigGroupRoot;
}
