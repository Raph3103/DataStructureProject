//
// Created by ayele on 30/05/2022.
//

#ifndef SPRING2022WET2DATASTRUCTURES_DEFINITIONS_H
#define SPRING2022WET2DATASTRUCTURES_DEFINITIONS_H

#include "AvlTreeWithRankAndSums.h"
#include "HashTable.h"

struct groupCompanyInfo;

//node for the hashTable
struct employeeHashNode{

    int employee_id;
    int companyID;
    int salary;
    long int grade;
    employeeHashNode* next;
    groupCompanyInfo* infoOftheCompany;  //pointer to the metaer akvoutsa of his group
    
};


//node for the AVLTree
struct nodeInAVL{
    int salary;
    int employee_id;
    long int grade;
    int num_of_employees_in_subtree;
    long int sum_of_grades_of_employees_in_subtree;
    int nosaf;


  nodeInAVL()
  {
      salary=0;
      employee_id=0;
      grade=0;
      num_of_employees_in_subtree=0;
      sum_of_grades_of_employees_in_subtree=0;
      nosaf=0;

  }

    nodeInAVL(int salary, int employee_id, int grade)
    {
        this->employee_id=employee_id;
        this->salary=salary;
        this->grade=grade;
        this->num_of_employees_in_subtree=0;
        this->sum_of_grades_of_employees_in_subtree=0;
        this->nosaf=0;
    }

    nodeInAVL(const nodeInAVL& node)=default;

    bool isEqual(int salary_to_check, int id) const
    {
        if(this->salary==salary_to_check && this->employee_id==id)
        {
            return true;
        }
        return false;
    }

    bool isGreatherThan(int salary_to_check, int id) const
    {
        if(this->salary>salary_to_check)
        {
            return true;
        }
        else if(this->salary==salary_to_check && this->employee_id>id)
        {
            return true;
        }
        return false;
    }

    bool isLessThan(int salary_to_check, int id) const
    {
        return !(isGreatherThan(salary_to_check, id));
    }

    bool operator>(const nodeInAVL& other) const
    {
        if(this->salary>other.salary)
        {
            return true;
        }
        else if(this->salary==other.salary && this->employee_id>other.employee_id)
        {
            return true;
        }
        return false;
    }

    bool operator<(const nodeInAVL& other) const
    {
        return !(operator>(other));
    }

    bool operator==(const nodeInAVL& other) const
    {
        if(this->salary==other.salary && this->employee_id== other.employee_id)
        {
            return true;
        }
        return false;
    }
};

//node for the trees in the UnionFind
struct companyNode{
    int companyID;
    double r_value;  //difference with the value of his father
    companyNode* father;
    groupCompanyInfo* companyInfo;
};


//gros big box de toute la maarehet
struct bigBox{

public:
    int numOfEmployeesWithSalary0;
    long int sumOfGradesOfEmployeesWithSalary0;
    int numOfEmployees;
    AVLtree<nodeInAVL>* treeOfAllGrades;



};
#endif //SPRING2022WET2DATASTRUCTURES_DEFINITIONS_H
