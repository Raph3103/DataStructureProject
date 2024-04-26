

#include "HashTable.h"



hashTable::hashTable()
{
    array_size=2;
    number_of_employees = 0;
    employees = new employeeHashNode*[array_size];
    for(int i=0; i<array_size; i++)
    {
        employees[i]= nullptr;
    }
}


hashTable::~hashTable()
{
    for (int i=0;i<array_size;i++)
    {
        employeeHashNode* temp = employees[i];
        while(temp!= nullptr)
        {
            employees[i] = employees[i]->next;
            delete temp;
            temp = employees[i];
        }
        // maybe delete metaer ? already delete in unionfind ?
    }
    delete[] employees;
}

void hashTable::insertForRealloc(employeeHashNode& employee)
{
    int index= hashFunction(employee.employee_id);

    employeeHashNode* to_insert= new employeeHashNode;
    to_insert->employee_id=employee.employee_id;
    to_insert->salary=employee.salary;
    to_insert->companyID=employee.companyID;
    to_insert->grade=employee.grade;
    to_insert->next= nullptr;
    to_insert->infoOftheCompany = employee.infoOftheCompany;

    if(employees[index]== nullptr)
    {
        employees[index]=to_insert;
    }

    else
    {
        to_insert->next=employees[index];
        employees[index]=to_insert;
    }

    number_of_employees++;
}
void hashTable::insert(employeeHashNode& employee)
{
    int index= hashFunction(employee.employee_id);

    employeeHashNode* to_insert= new employeeHashNode;
    to_insert->employee_id=employee.employee_id;
    to_insert->salary=employee.salary;
    to_insert->companyID=employee.companyID;
    to_insert->grade=employee.grade;
    to_insert->next= nullptr;
    to_insert->infoOftheCompany = employee.infoOftheCompany;

    if(employees[index]== nullptr)
    {
        employees[index]=to_insert;
    }

    else
    {
        to_insert->next=employees[index];
        employees[index]=to_insert;
    }
    number_of_employees++;

    double proportion= ((double)number_of_employees)/((double)array_size);

    reallocateArray(proportion);
}

void hashTable::removeForRealloc(employeeHashNode* employee)
{
    int index=hashFunction(employee->employee_id);

    if(employees[index]->employee_id==employee->employee_id)
    {
        employeeHashNode* temp=employee->next;
        employees[index]=temp;
        delete employee;
    }
    else{
        employeeHashNode* prev= employees[index];
        employeeHashNode* current=employees[index]->next;

        while (current!= nullptr)
        {
            if(current->employee_id==employee->employee_id)
            {
                prev->next=current->next;
                delete employee;
                break;
            }
            prev=prev->next;
            current=current->next;
        }
    }
    this->number_of_employees--;
}

void hashTable::remove(employeeHashNode* employee)
{
    int index=hashFunction(employee->employee_id);

    if(employees[index]->employee_id==employee->employee_id)
    {
        employeeHashNode* temp=employee->next;
        employees[index]=temp;
        delete employee;
    }
    else{
        employeeHashNode* prev= employees[index];
        employeeHashNode* current=employees[index]->next;

        while (current!= nullptr)
        {
            if(current->employee_id==employee->employee_id)
            {
                prev->next=current->next;
                delete employee;
                break;
            }
            prev=prev->next;
            current=current->next;
        }
    }
    this->number_of_employees--;
    double proportion= ((double)number_of_employees)/((double)array_size);
    reallocateArray(proportion);

}


employeeHashNode* hashTable::find(int employee_id)
{
    int index=hashFunction(employee_id);

    employeeHashNode* source_cell=employees[index];

    while(source_cell!= nullptr)
    {
        if(employee_id==source_cell->employee_id)
        {
            return source_cell;
        }
        source_cell=source_cell->next;
    }
    return nullptr;
}


void hashTable::reallocateArray(double proportion)
{
    if(proportion<0.25)
    {
        reduceArray();
    }
    else if(proportion>0.75)
        enlargeArray();

}

void hashTable::enlargeArray()
{
    int old_array_size= this->array_size;

    this->array_size*=2;

    employeeHashNode** old_array= employees;

    employees=new employeeHashNode*[this->array_size];
    for(int i=0; i<array_size; i++)
    {
        employees[i]= nullptr;
    }
    this->number_of_employees=0;

    for(int i=0; i<old_array_size; i++)
    {
        employeeHashNode* to_insert=old_array[i];
        while(to_insert!= nullptr)
        {
            this->insertForRealloc(*to_insert);
            to_insert=to_insert->next;
        }
    }
    for (int i=0;i<old_array_size;i++){
        employeeHashNode* temp = old_array[i];
        while(temp!= nullptr){
            old_array[i] = old_array[i]->next;
            delete temp;
            temp = old_array[i];
        }
    }
    delete[] old_array;
}



void hashTable::reduceArray()
{
    int old_array_size= this->array_size;

    this->array_size/=2;

    employeeHashNode** old_array= employees;

    employees=new employeeHashNode*[this->array_size];
    for (int i=0; i<this->array_size; i++){

        employees[i] = nullptr;
    }
    this->number_of_employees=0;

    for(int i=0; i<old_array_size; i++)
    {
        employeeHashNode* to_insert=old_array[i];
        while(to_insert!= nullptr)
        {
            this->insert(*to_insert);
            to_insert=to_insert->next;
        }
    }
    for (int i=0;i<old_array_size;i++){
        employeeHashNode* temp = old_array[i];
        while(temp!= nullptr){
            old_array[i] = old_array[i]->next;
            delete temp;
            temp = old_array[i];
        }
    }
    delete[] old_array;
}


int hashTable::hashFunction(int employee_id)
{

    int index= employee_id%(this->array_size);

    return index;
}


int hashTable::getSize()
{
    return this->array_size;
}



