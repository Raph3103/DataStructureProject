//
// Created by ayele on 29/05/2022.
//

#include "CompanyManagerWet2.h"
// remove include union hash tree definitions
#include "companyInfo.h"
#include <cmath>


void doNothing()
{
    return;
}
CompanyManager::CompanyManager(int k)
{

    employeesHash = new hashTable();
    companies = new UnionFind(k);

}

CompanyManager::~CompanyManager()
{

    delete companies;                   //on appelle les destructeurs
    delete employeesHash;
}

StatusType CompanyManager::addEmployee(int EmployeeID, int CompanyID, int Grade)
{


    if(EmployeeID<=0 || CompanyID<=0 || CompanyID>companies->numOfCompanies || Grade<0)
    {
        return INVALID_INPUT;
    }


    if(employeesHash->find(EmployeeID)!= nullptr)
    {
        return FAILURE;
    }

    //insert  the employee in the main hashTable
    employeeHashNode* newEmployee;
    try{
        newEmployee= new employeeHashNode;
    }
    catch(const std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
    newEmployee->salary=0;
    newEmployee->employee_id=EmployeeID;
    newEmployee->grade=Grade;
    newEmployee->companyID=CompanyID;
    groupCompanyInfo* hisGroup= companies->find(CompanyID);
    newEmployee->infoOftheCompany=hisGroup;
    employeesHash->insert(*newEmployee);

    //insert the employee in the hashTable of his group

    newEmployee->infoOftheCompany= nullptr;
    hisGroup->allEmployeesInGroup->insert(*newEmployee);

    //update the infos in the metaer akvoutsa // bizarre pour employee  vec id 499104 ne rentre pas dans hash ingroup
    hisGroup->numOfEmployees++;
    hisGroup->numberOfEmployeesWithSalary0++;
    hisGroup->sumOfGradesWithSalary0+=Grade;
    delete newEmployee;

    //update the BigBox
    companies->bigBoxOfTheSystem->numOfEmployees++;
    companies->bigBoxOfTheSystem->numOfEmployeesWithSalary0++;
    companies->bigBoxOfTheSystem->sumOfGradesOfEmployeesWithSalary0+=Grade;

    return SUCCESS;

}

StatusType CompanyManager::removeEmployee(int EmployeeID)
{
    
    if (EmployeeID <= 0)
    {
        return INVALID_INPUT;
    }

    employeeHashNode* employee = employeesHash->find(EmployeeID);

    if (employee == nullptr) {     // check if the employee exist in the system
        return FAILURE;
    }
    groupCompanyInfo* employeeCompanyInfo = employee->infoOftheCompany;

    int salary=employee->salary;
    long int grade = employee->grade; // rajouter


    // remove employee from hash in companuinfo
    employeeHashNode* employee_in_group_hash = employeeCompanyInfo->allEmployeesInGroup->find(EmployeeID); // add this line
    employeeCompanyInfo->allEmployeesInGroup->remove(employee_in_group_hash); // add this line

    if(salary==0)     // avant employee->salary
    {
        employeeCompanyInfo->numberOfEmployeesWithSalary0--;
        employeeCompanyInfo->sumOfGradesWithSalary0 -= grade; // avant employee->grade
        employeeCompanyInfo->numOfEmployees--;
    }

    // delete from the avl in companyinfo
    if (salary != 0) {

        nodeInAVL *employee_in_tree = employeeCompanyInfo->treeOfGrades->findNodeUsingIDReturnData(EmployeeID,salary);// ava,t employee->salary
        employeeCompanyInfo->treeOfGrades->remove(*employee_in_tree);

    }

    // delete from the avl with all the employees in the system if salary is not 0

    if (salary != 0) {

        companies->bigBoxOfTheSystem->numOfEmployees--;
        nodeInAVL *employee_in_all_tree = companies->bigBoxOfTheSystem->treeOfAllGrades->findNodeUsingIDReturnData(EmployeeID,salary);//avant employee->salary
        companies->bigBoxOfTheSystem->treeOfAllGrades->remove(*employee_in_all_tree);
    }

        //update the variables in the tree with all employees if his salary is 0
    else {

        companies->bigBoxOfTheSystem->numOfEmployees--;
        companies->bigBoxOfTheSystem->numOfEmployeesWithSalary0--;
        companies->bigBoxOfTheSystem->sumOfGradesOfEmployeesWithSalary0 -=grade;//avant employee->grade

    }
    // finally remove the employee from the hash of all the employees.
    employeeHashNode* to_remove=employeesHash->find(EmployeeID);
    employeesHash->remove(to_remove);

    return SUCCESS;
}


StatusType CompanyManager::acquireCompany(int AcquirerID, int TargetID, double Factor)
{

    
    if(AcquirerID<=0 || TargetID<=0 || AcquirerID>companies->numOfCompanies || TargetID>companies->numOfCompanies || AcquirerID==TargetID || Factor<=0.0)
    {
        return INVALID_INPUT;
    }
    if(companies->find(AcquirerID)==companies->find(TargetID))
    {
        return INVALID_INPUT;
    }


    groupCompanyInfo* targetStruct= companies->find(TargetID);
    groupCompanyInfo* acquirerStruct=companies->find(AcquirerID);

    //double new_value_of_the_union=acquirerStruct->valueOfTheUnion+((targetStruct->valueOfTheUnion)*Factor);

    //we will merge the two metaer akvoutsa so we have to update the pointers from the employees in the hashtable
    //is we have more companies in Acquirer, at the end of the merge, all the employees that were in the group of target id will point to the metaer akvoutsa of acquirer
    int num_of_companies_in_target=targetStruct->numOfCompaniesInTheUnion;
    int num_of_companies_in_acquire=acquirerStruct->numOfCompaniesInTheUnion;

    if(num_of_companies_in_acquire>=num_of_companies_in_target)
    {
        int targetSize= targetStruct->allEmployeesInGroup->array_size;
        for(int i=0; i<targetSize; i++)
        {
            employeeHashNode* to_search= targetStruct->allEmployeesInGroup->employees[i];
            while(to_search!= nullptr)
            {
                int employee_to_update=to_search->employee_id;
                employeesHash->find(employee_to_update)->infoOftheCompany=acquirerStruct;
                to_search=to_search->next;
            }
        }
    }
    else{
        int acquirerSize=acquirerStruct->allEmployeesInGroup->array_size;
        for(int i=0; i<acquirerSize; i++)
        {
            employeeHashNode* to_search=acquirerStruct->allEmployeesInGroup->employees[i];
            while(to_search!= nullptr)
            {
                int employee_to_update=to_search->employee_id;
                employeesHash->find(employee_to_update)->infoOftheCompany=targetStruct;
                to_search=to_search->next;
            }
        }
    }
    companies->mergeGroups(AcquirerID, TargetID, Factor);
    return SUCCESS;
}

StatusType CompanyManager::employeeSalaryIncrease(int EmployeeID, int SalaryIncrease)
{
    
    if (EmployeeID <= 0 || SalaryIncrease <= 0) {

        return INVALID_INPUT;

    }


    employeeHashNode* employee = employeesHash->find(EmployeeID);

    if (employee == nullptr) {

        return FAILURE;

    }
    // update the salary of the employee in the hash of all employees
    int old_salary = employee->salary;
    employee->salary += SalaryIncrease;
    int new_salary = employee->salary;

    groupCompanyInfo* employee_company_info = employee->infoOftheCompany;
    //update the salary of the employee in the hash in company
    employeeHashNode* employee_hash_company = employee_company_info->allEmployeesInGroup->find(EmployeeID);
    employee_hash_company->salary += SalaryIncrease;


    // if the salary of the employee was  not 0 , we want to remove the employee from the tree and insert it
    if (old_salary != 0)
    {
        // remove and insert from the tree in company
        nodeInAVL *employee_to_insert = nullptr;
        nodeInAVL* employee_to_remove = employee_company_info->treeOfGrades->findNodeUsingIDReturnData(EmployeeID,old_salary);
        try {
            employee_to_insert = new nodeInAVL(*employee_to_remove);
        }
        catch (const std::bad_alloc &) {
            return StatusType::ALLOCATION_ERROR;
        }
        employee_company_info->treeOfGrades->remove(*employee_to_remove);
        employee_to_insert->salary = new_salary;
        employee_to_insert->num_of_employees_in_subtree =0;
        employee_to_insert->sum_of_grades_of_employees_in_subtree=0;  // add this condition

        employee_company_info->treeOfGrades->insert(*employee_to_insert);

        // remove and insert from the tree with all the employees

        nodeInAVL *employee_to_insert_in_bigbox = nullptr;
        nodeInAVL* employee_to_remove_in_bigbox = companies->bigBoxOfTheSystem->treeOfAllGrades->findNodeUsingIDReturnData(EmployeeID,old_salary);
        try {
            employee_to_insert_in_bigbox = new nodeInAVL(*employee_to_remove_in_bigbox);
        }
        catch (const std::bad_alloc &) {
            delete employee_to_insert;
            return StatusType::ALLOCATION_ERROR;
        }
        companies->bigBoxOfTheSystem->treeOfAllGrades->remove(*employee_to_remove_in_bigbox);
        employee_to_insert_in_bigbox->salary = new_salary;
        employee_to_insert_in_bigbox->num_of_employees_in_subtree=0;           // add this condition
        employee_to_insert_in_bigbox->sum_of_grades_of_employees_in_subtree=0;
        companies->bigBoxOfTheSystem->treeOfAllGrades->insert(*employee_to_insert_in_bigbox);
        delete employee_to_insert;
        delete employee_to_insert_in_bigbox;
    }

    else {                // the case old salary = 0

        // we update the variable in the company and insert the employee in the tree of this company
        employee_company_info->numberOfEmployeesWithSalary0--;
        employee_company_info->sumOfGradesWithSalary0 -= employee->grade;
        nodeInAVL* employee_to_insert = nullptr;

        try {
            employee_to_insert = new nodeInAVL(new_salary,EmployeeID,employee->grade);
        }
        catch (const std::bad_alloc &) {
            return StatusType::ALLOCATION_ERROR;
        }
        employee_company_info->treeOfGrades->insert(*employee_to_insert);

        // we update the variables in the big box
        companies->bigBoxOfTheSystem->numOfEmployeesWithSalary0--;
        companies->bigBoxOfTheSystem->sumOfGradesOfEmployeesWithSalary0 -= employee->grade;
        nodeInAVL* employee_to_insert2 = nullptr;

        try {
            employee_to_insert2 = new nodeInAVL(new_salary,EmployeeID,employee->grade);
        }
        catch (const std::bad_alloc &) {
            return StatusType::ALLOCATION_ERROR;
        }

        companies->bigBoxOfTheSystem->treeOfAllGrades->insert(*employee_to_insert2);

        delete employee_to_insert;
        delete employee_to_insert2;

    }
    return SUCCESS;
}


StatusType CompanyManager::promoteEmployee(int EmployeeID, int BumpGrade)
{

    if(EmployeeID<=0)
    {
        return INVALID_INPUT;
    }


    if(employeesHash->find(EmployeeID)== nullptr)
    {
        return FAILURE;
    }
    if (BumpGrade <= 0) // add this condition
    {
        return SUCCESS;
    }

    //update his grade in the two hashTables (of all the system and of his group)
    employeeHashNode* employeeToUpdate= employeesHash->find(EmployeeID);
    employeeToUpdate->grade+=BumpGrade;
    int his_salary= employeeToUpdate->salary;
    groupCompanyInfo* hisGroup=employeeToUpdate->infoOftheCompany;
    hisGroup->allEmployeesInGroup->find(EmployeeID)->grade+=BumpGrade;

    //if salary 0 update the sum of all the grades of employees with salary 0
    if(his_salary==0 )
    {
        //update in the variable of the group
        hisGroup->sumOfGradesWithSalary0+=BumpGrade;

        //update in the variable of all the system
        companies->bigBoxOfTheSystem->sumOfGradesOfEmployeesWithSalary0+=BumpGrade;
    }

        //else update in the tree of employees by salary
    else{
        //update in the tree of the group, remove of the employee and insert him with his new salary
        //we dont have to remove or insert any employee of the tree just add BumpGrade to all nodes in search path
        AVLnode<nodeInAVL>* node_to_modify= hisGroup->treeOfGrades->findNodeUsingIDReturnNode(EmployeeID, his_salary);
        node_to_modify->getDataPointer()->grade+=BumpGrade;
        while(node_to_modify!= nullptr)
        {
            node_to_modify->getDataPointer()->sum_of_grades_of_employees_in_subtree+=BumpGrade;
            node_to_modify=node_to_modify->father;
        }

        //update in the tree of all the system = doing the same thing
        AVLnode<nodeInAVL>* node_to_modify2= companies->bigBoxOfTheSystem->treeOfAllGrades->findNodeUsingIDReturnNode(EmployeeID, his_salary);
        node_to_modify2->getDataPointer()->grade+=BumpGrade;
        while(node_to_modify2!= nullptr)
        {
            node_to_modify2->getDataPointer()->sum_of_grades_of_employees_in_subtree+=BumpGrade;
            node_to_modify2=node_to_modify2->father;
        }
    }
    return SUCCESS;
}


StatusType CompanyManager::sumOfBumpGradeBetweenTopWorkersByGroup( int CompanyID, int m)
{
   
    if ( m <= 0 || CompanyID < 0 || CompanyID > companies->numOfCompanies)
    {
        return INVALID_INPUT;
    }

    bigBox *bigbox = companies->bigBoxOfTheSystem;
    groupCompanyInfo *company_info = companies->find(CompanyID);

    if (company_info->treeOfGrades->number_of_nodes < m || (CompanyID == 0 && (bigbox->treeOfAllGrades->number_of_nodes) < m))
    {
        return FAILURE;
    }

    long int sum = 0; // add to identify
    if (CompanyID == 0)
    {
        AVLnode<nodeInAVL>* m_value = bigbox->treeOfAllGrades->select(bigbox->treeOfAllGrades->number_of_nodes - m + 1);
        if(m_value== nullptr) //dont have to happen
        {
            return FAILURE;
        }
        long int total_sum=bigbox->treeOfAllGrades->sumBefore(bigbox->treeOfAllGrades->max_node);
        long int sum_before=bigbox->treeOfAllGrades->sumBefore(m_value);
        if (m_value == bigbox->treeOfAllGrades->max_node && m_value != nullptr)
        {
            sum = m_value->getData().grade;// add this condition
            printf("SumOfBumpGradeBetweenTopWorkersByGroup: %ld\n",sum);
            return SUCCESS;
        }
        sum=total_sum-sum_before;
        if(m_value!= nullptr)
            sum+=m_value->getData().grade;
    }
    else
    {
        groupCompanyInfo *companyInfo = companies->find(CompanyID);
        AVLnode<nodeInAVL> *m_value = companyInfo->treeOfGrades->select(companyInfo->treeOfGrades->number_of_nodes - m + 1);
        if(m_value== nullptr)
        {
            return FAILURE;  //dont have to happen
        }
        long int total_sum=companyInfo->treeOfGrades->sumBefore(companyInfo->treeOfGrades->max_node);
        long int sum_before=companyInfo->treeOfGrades->sumBefore(m_value);

        sum=total_sum-sum_before;
        if(m_value!= nullptr)
            sum+=m_value->getData().grade;
    }

    printf("SumOfBumpGradeBetweenTopWorkersByGroup: %ld\n",sum);
    return SUCCESS;
}


StatusType CompanyManager::averageBumpGradeBetweenSalaryByGroup( int CompanyID, int lowerSalary,
                                                                 int higherSalary)
{
    

    if (lowerSalary < 0 || higherSalary < 0 || lowerSalary > higherSalary || CompanyID > companies->numOfCompanies ||
        CompanyID < 0)
    {
        return INVALID_INPUT;
    }
    int num_of_employees_in_intervall = 0;
    long int sum_of_grades_of_employees_in_intervall = 0;

    //we are in the tree of all the system
    if (CompanyID == 0)
    {
        if (lowerSalary == 0)   //we have to add the grades of the employees with salary0
        {
            num_of_employees_in_intervall += companies->bigBoxOfTheSystem->numOfEmployeesWithSalary0;
            sum_of_grades_of_employees_in_intervall += companies->bigBoxOfTheSystem->sumOfGradesOfEmployeesWithSalary0;
        }
        //add the two extremities before the lower and after the higher
        AVLnode<nodeInAVL>* start_point= nullptr;
        AVLnode<nodeInAVL>* end_point= nullptr;

        AVLnode<nodeInAVL>* to_insert_start= nullptr;
        try{
            to_insert_start=new AVLnode<nodeInAVL>();
        }
        catch(const std::bad_alloc&)
        {
            return ALLOCATION_ERROR;
        }
        to_insert_start->getDataPointer()->salary=lowerSalary;
        to_insert_start->getDataPointer()->employee_id=-1;
        to_insert_start->getDataPointer()->grade=0;
        to_insert_start->getDataPointer()->sum_of_grades_of_employees_in_subtree=0;
        to_insert_start->getDataPointer()->num_of_employees_in_subtree=0;// changed to 0 was 1

        try{
            start_point=companies->bigBoxOfTheSystem->treeOfAllGrades->insert(*to_insert_start->getDataPointer());
        }
        catch(const std::bad_alloc&)
        {
            delete to_insert_start;
            return ALLOCATION_ERROR;
        }
        delete to_insert_start;
        AVLnode<nodeInAVL>* to_remove=start_point;
        start_point=companies->bigBoxOfTheSystem->treeOfAllGrades->findNext(start_point);
        companies->bigBoxOfTheSystem->treeOfAllGrades->remove(to_remove->data);

        AVLnode<nodeInAVL>* to_insert_end= nullptr;
        try{
            to_insert_end=new AVLnode<nodeInAVL>();
        }
        catch(const std::bad_alloc&)
        {
            return ALLOCATION_ERROR;
        }
        to_insert_end->getDataPointer()->salary=higherSalary+1;
        to_insert_end->getDataPointer()->employee_id=-1;
        to_insert_end->getDataPointer()->grade=0;
        to_insert_end->getDataPointer()->sum_of_grades_of_employees_in_subtree=0;
        to_insert_end->getDataPointer()->num_of_employees_in_subtree=0;// changed to 0 was 1

        try{
            end_point=companies->bigBoxOfTheSystem->treeOfAllGrades->insert(*to_insert_end->getDataPointer());
        }
        catch(const std::bad_alloc&)
        {
            return ALLOCATION_ERROR;
        }
        delete to_insert_end;
        AVLnode<nodeInAVL>* to_remove2=end_point;
        end_point=companies->bigBoxOfTheSystem->treeOfAllGrades->findPrev(end_point);
        companies->bigBoxOfTheSystem->treeOfAllGrades->remove(to_remove2->data);

        if(start_point==end_point && start_point!= nullptr)
        {
            num_of_employees_in_intervall+=1;
            sum_of_grades_of_employees_in_intervall+=start_point->getData().grade;
        }
        else if(start_point== nullptr || end_point== nullptr)
        {
            num_of_employees_in_intervall+=0;
            sum_of_grades_of_employees_in_intervall+=0;
        }
        else{
            int num_before_start=companies->bigBoxOfTheSystem->treeOfAllGrades->rank(start_point);
            int num_before_end=companies->bigBoxOfTheSystem->treeOfAllGrades->rank(end_point);
            num_of_employees_in_intervall+=(num_before_end-num_before_start);
            num_of_employees_in_intervall++; //for the start_point itself

            long int sum_before_start=companies->bigBoxOfTheSystem->treeOfAllGrades->sumBefore(start_point);
            long int sum_before_end=companies->bigBoxOfTheSystem->treeOfAllGrades->sumBefore(end_point);
            sum_of_grades_of_employees_in_intervall+=(sum_before_end-sum_before_start);
            sum_of_grades_of_employees_in_intervall+=start_point->data.grade;
        }

    }
    else
    {
        //we have to calculate on the tree of his own company
        groupCompanyInfo *relevant_group = companies->find(CompanyID);

        if (lowerSalary == 0)
        {
            num_of_employees_in_intervall += relevant_group->numberOfEmployeesWithSalary0;
            sum_of_grades_of_employees_in_intervall += relevant_group->sumOfGradesWithSalary0;
        }

        AVLnode<nodeInAVL>* start_point= nullptr;
        AVLnode<nodeInAVL>* end_point= nullptr;

        AVLnode<nodeInAVL>* to_insert_start= nullptr;
        try{
            to_insert_start=new AVLnode<nodeInAVL>();
        }
        catch(const std::bad_alloc&)
        {
            return ALLOCATION_ERROR;
        }
        to_insert_start->getDataPointer()->salary=lowerSalary;
        to_insert_start->getDataPointer()->employee_id=-1;
        to_insert_start->getDataPointer()->grade=0;
        to_insert_start->getDataPointer()->sum_of_grades_of_employees_in_subtree=0;
        to_insert_start->getDataPointer()->num_of_employees_in_subtree=0; // initialise to 0 ? was 1

        try{
            relevant_group->treeOfGrades->insert(*to_insert_start->getDataPointer());
        }
        catch(const std::bad_alloc&)
        {
            return ALLOCATION_ERROR;
        }
        delete to_insert_start;
        start_point=relevant_group->treeOfGrades->findNodeUsingIDReturnNode(-1,lowerSalary);
        AVLnode<nodeInAVL>* to_remove_start=start_point;
        start_point=relevant_group->treeOfGrades->findNext(start_point);
        relevant_group->treeOfGrades->remove(to_remove_start->getData());

        AVLnode<nodeInAVL>* to_insert_end= nullptr;
        try{
            to_insert_end=new AVLnode<nodeInAVL>();
        }
        catch(const std::bad_alloc&)
        {
            return ALLOCATION_ERROR;
        }
        to_insert_end->getDataPointer()->salary=higherSalary+1;
        to_insert_end->getDataPointer()->employee_id=-1;
        to_insert_end->getDataPointer()->grade=0;
        to_insert_end->getDataPointer()->sum_of_grades_of_employees_in_subtree=0;
        to_insert_end->getDataPointer()->num_of_employees_in_subtree=0;// change to 0 was 1

        try{
            relevant_group->treeOfGrades->insert(*to_insert_end->getDataPointer());
        }
        catch(const std::bad_alloc&)
        {
            return ALLOCATION_ERROR;
        }
        delete to_insert_end;
        end_point=relevant_group->treeOfGrades->findNodeUsingIDReturnNode(-1,higherSalary+1);
        AVLnode<nodeInAVL>* to_remove_end=end_point;
        end_point=relevant_group->treeOfGrades->findPrev(end_point);
        relevant_group->treeOfGrades->remove(to_remove_end->getData());

        if(start_point==end_point && start_point!= nullptr)
        {
            num_of_employees_in_intervall+=1;
            sum_of_grades_of_employees_in_intervall+=start_point->getData().grade;
        }
        else if(start_point== nullptr || end_point== nullptr)
        {
            num_of_employees_in_intervall+=0;
            sum_of_grades_of_employees_in_intervall+=0;
        }
        else{
            int num_before_start = relevant_group->treeOfGrades->rank(start_point);
            int num_before_end = relevant_group->treeOfGrades->rank(end_point);
            num_of_employees_in_intervall+=num_before_end-num_before_start;
            num_of_employees_in_intervall++; //for the start point itself

            long int sum_before_start = relevant_group->treeOfGrades->sumBefore(start_point);
            long int sum_before_end = relevant_group->treeOfGrades->sumBefore(end_point);
            sum_of_grades_of_employees_in_intervall+=sum_before_end-sum_before_start;
            sum_of_grades_of_employees_in_intervall+=start_point->getData().grade;
        }

    }
    if(num_of_employees_in_intervall==0)
    {
        return FAILURE;
    }

    long double result= ((long double)sum_of_grades_of_employees_in_intervall)/((long double)num_of_employees_in_intervall);

    printf("AverageBumpGradeBetweenSalaryByGroup: %.1Lf\n", result);
    return SUCCESS;

}
StatusType CompanyManager::companyValue( int CompanyID)
{
    if( CompanyID<=0 || CompanyID>companies->numOfCompanies)          // retirer verif de null
    {
        return INVALID_INPUT;
    }


    companies->find(CompanyID);//on a fait le kivouts masloulim
    companyNode* company=companies->companyTable[CompanyID];

    double helper_value = 0;
    while (company != nullptr)
    {
        helper_value+=company->r_value;
        company = company->father;
    }


    printf("CompanyValue: %.1f\n",helper_value);


    return SUCCESS;
}

StatusType CompanyManager::bumpGradeToEmployees(int lowerSalary, int higherSalary, int BumpGrade)
{

    return SUCCESS;

}



