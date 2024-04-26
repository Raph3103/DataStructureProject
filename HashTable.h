//
// Created by ayele on 28/05/2022.
//

#ifndef SPRING2022WET2DATASTRUCTURES_HASHTABLE_H
#define SPRING2022WET2DATASTRUCTURES_HASHTABLE_H



#include "definitions.h"

struct employeeHashNode;

class hashTable
{

public:

    int array_size;  //taille du maarah
    int number_of_employees;
    employeeHashNode** employees;   //le maarah en lui meme



    hashTable();
    ~hashTable();
    void insert(employeeHashNode& employee);
    void insertForRealloc(employeeHashNode& employee);
    void remove (employeeHashNode* employee);
    void removeForRealloc(employeeHashNode* employee);
    employeeHashNode* find  (int employee_id);
    void reallocateArray(double proportion);
    void enlargeArray ();
    void reduceArray();
    int hashFunction (int employee_id);
    int getSize();

};


#endif //SPRING2022WET2DATASTRUCTURES_HASHTABLE_H
