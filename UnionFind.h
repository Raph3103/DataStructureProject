//
// Created by ayele on 28/05/2022.
//

#ifndef SPRING2022WET2DATASTRUCTURES_UNIONFIND_H
#define SPRING2022WET2DATASTRUCTURES_UNIONFIND_H

//
// Created by Niv on 1/5/2022.
//

#include "definitions.h"


class UnionFind
{
public:
    int numOfCompanies;
    companyNode** companyTable;
    bigBox* bigBoxOfTheSystem;



    explicit UnionFind(int k);
    ~UnionFind();
    groupCompanyInfo* find(int CompanyID) const;
    void mergeGroups(int companyId1, int companyId2, double Factor);
    companyNode* upsideDownMerge(companyNode* bigGroupRoot, companyNode* smallGroupRoot);

};



#endif //SPRING2022WET2DATASTRUCTURES_UNIONFIND_H
