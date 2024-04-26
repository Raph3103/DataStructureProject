//
// Created by ayele on 29/05/2022.
//

#ifndef SPRING2022WET2DATASTRUCTURES_COMPANYMANAGERWET2_H
#define SPRING2022WET2DATASTRUCTURES_COMPANYMANAGERWET2_H



#include "library2.h"
#include "HashTable.h"
#include "AvlTreeWithRankAndSums.h"
#include "UnionFind.h"
#include "definitions.h"

class CompanyManager {

    hashTable* employeesHash;
    UnionFind* companies;



public:
    explicit CompanyManager(int k);
    ~CompanyManager();
    CompanyManager(const CompanyManager& companyManagerToCopy)=delete;
    CompanyManager& operator= (CompanyManager)=delete;
    StatusType addEmployee( int EmployeeID, int CompanyID, int Grade);
    StatusType removeEmployee( int EmployeeID);
    StatusType acquireCompany( int AcquirerID, int TargetID, double Factor);
    StatusType employeeSalaryIncrease( int EmployeeID, int SalaryIncrease);
    StatusType promoteEmployee( int EmployeeID, int BumpGrade);
    StatusType sumOfBumpGradeBetweenTopWorkersByGroup ( int CompanyID, int m);
    StatusType averageBumpGradeBetweenSalaryByGroup ( int CompanyID, int lowerSalary, int higherSalary);
    StatusType companyValue( int CompanyID);
    StatusType bumpGradeToEmployees( int lowerSalary, int higherSalary, int BumpGrade);


};

#endif //SPRING2022WET2DATASTRUCTURES_COMPANYMANAGERWET2_H
