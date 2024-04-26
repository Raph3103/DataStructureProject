//
// Created by ayele on 28/05/2022.
//

#ifndef SPRING2022WET2DATASTRUCTURES_AVLTREEWITHRANKANDSUMS_H
#define SPRING2022WET2DATASTRUCTURES_AVLTREEWITHRANKANDSUMS_H


#include <iostream>
#include <math.h>


#define OUT_OF_REACH -1

/*AVL node - definition of the class*/

template<class Data> // maybe delete file warning
class AVLtree;

template<class Data>
class AVLnode
{

public:
    Data data;
    AVLnode* father;
    AVLnode* left_son;
    AVLnode* right_son;
    int height;

    AVLnode();
    ~AVLnode() = default;
    AVLnode(const AVLnode& node_to_copy);
    AVLnode &operator=(const AVLnode& node);
    bool operator<( const AVLnode& node) const;
    bool operator>( const AVLnode& node) const;
    bool operator== ( const AVLnode& node) const;
    int getBalanceFactor();
    Data getData();
    Data* getDataPointer();
    // delete change data and location never used
//  delete change data helper never used
    void clear(AVLnode<Data>* first_node_to_clear);
    void updateHeight ();

    // delete friend class manager

};

template<class Data>
AVLnode<Data>::AVLnode() : data(), father(nullptr), left_son(nullptr), right_son(nullptr), height(0){}


template<class Data>
AVLnode<Data>::AVLnode(const AVLnode<Data> &node_to_copy)  :data(node_to_copy.data), father(node_to_copy.father), left_son(node_to_copy.left_son),
                                                            right_son(node_to_copy.right_son), height(node_to_copy.height) {}

template<class Data>
AVLnode<Data>& AVLnode<Data> ::operator=(const AVLnode<Data> &node)
{
    if (*this == node) {         //  rajouter verification pour eviter peoulot inutiles
        return *this;
    }
    this->data=node.data;
    this->father=node.father;
    this->right_son=node.right_son;
    this->left_son=node.left_son;
    this->height=node.height;
    return *this;
}

template<class Data>
bool AVLnode<Data>::operator<( const AVLnode<Data> &node) const
{
    if (this->data < node.data)
    {
        return true;
    }
    return false;
}

template<class Data>
bool AVLnode<Data>::operator>( const AVLnode<Data> &node) const
{
    {
        if (this->data > node.data)
        {
            return true;
        }
        return false;
    }
}

template<class Data>
bool AVLnode<Data>::operator==( const AVLnode<Data> &node) const
{
    if(this->data==node.data)
    {
        return true;
    }
    return false;
}

template<class Data>
int AVLnode<Data>::getBalanceFactor()
{
    
    int left_height=-1;
    int right_height=-1;
    if(this->right_son!= nullptr)
    {
        right_height=this->right_son->height;
    }
    if(this->left_son!= nullptr)
    {
        left_height=this->left_son->height;
    }
    return left_height-right_height;
}

template<class Data>
Data AVLnode<Data>::getData()
{
    return this->data;
}

template<class Data>
Data * AVLnode<Data>::getDataPointer()
{
    return &(this->data);
}
/*

template<class Data>
AVLnode<Data>* AVLnode<Data>::changeDataAndLocation(Data &new_data, AVLtree<Data>* tree)
{
    AVLnode<Data>* changedNode(new AVLnode<Data>);
    changedNode->data = new_data;
    tree->remove(this->data);
    AVLnode<Data>* toReturn = tree->insert(changedNode->getData());
    delete changedNode;
    return toReturn;
}

//this function is used for addPlayer, doesn't take out the node and put back in
template<class Data>
void AVLnode<Data>::changeDataHelper(Data &new_data)
{
    this->data= new_data;
}

 */

template<class Data>
void AVLnode<Data>::clear(AVLnode<Data> *first_node_to_clear)
{
    if (first_node_to_clear == nullptr){
        return;
    }
    if(first_node_to_clear->left_son!=nullptr)
    {
        clear(first_node_to_clear->left_son);
    }

    if(first_node_to_clear->right_son!= nullptr)
    {
        clear(first_node_to_clear->right_son);
    }
    delete first_node_to_clear;
}


static int max(int a, int b)
{
    return a>b ? a:b;
}

template<class Data>
void AVLnode<Data>::updateHeight()
{
    
    int left_height=-1;
    int right_height=-1;

    if(this->left_son!= nullptr)
    {
        left_height=this->left_son->height;
    }
    if(this->right_son!= nullptr)
    {
        right_height=this->right_son->height;
    }
    this->height= max(right_height, left_height)+1;
}

enum SIDE{RIGHT,LEFT};

/*AVL tree*/
template<class Data>
class AVLtree
{
public:

    AVLnode<Data>* root;
    AVLnode<Data>* min_node;
    AVLnode<Data>* max_node;
    int number_of_nodes;
    int height;

    AVLtree();
    ~AVLtree();
    AVLtree(const AVLtree<Data> &avl_to_copy)=delete;
    AVLtree<Data>& operator= ( AVLtree<Data>)=delete;
    AVLtree<Data>* mergeWith(AVLtree<Data>* otherTree);
    int rankAux(AVLnode<Data>* to_search, AVLnode<Data>* first_node);
    int rank(AVLnode<Data>* to_search);
    AVLnode<Data>* getMax();
    Data* getMaxReturnData();
    AVLnode<Data>* getMin();
    AVLnode<Data>* findNodeAux(Data data, AVLnode<Data>* first_node);
    AVLnode<Data>* findNode (Data data);
    Data* findNodeUsingIDReturnData (int id, int salary);
    Data* findNodeUsingIDReturnDataAux(int id, int salary, AVLnode<Data>* first_node);
    AVLnode<Data>* findNodeUsingIDReturnNode(int id, int salary);
    AVLnode<Data>* findNodeUsingIDReturnNodeAux(int id, int salary,AVLnode<Data>* first_node);
    void inOrderAux(AVLnode<Data>* first_node);
    void inOrder (AVLnode<Data>* first_node);
    void preOrderAux(AVLnode<Data> *first_node);
    void preOrder(AVLnode<Data> *first_node);
    void postOrderUpdatingRanksAndSumsAux(AVLnode<Data>* first_node);
    void postOrderUpdatingRanksAndSums (AVLnode<Data>* first_node);
    AVLnode<Data>* findNext(AVLnode<Data> *myNode);
    AVLnode<Data>* findPrev(AVLnode<Data> *myNode);
    void transformTreeToInOrderArray (AVLnode<Data>* first_node, Data** arr);
    void avlTreeToArr(Data** data);
    void ino(AVLnode<Data>* r, Data** vals, int* index);
    AVLnode<Data>* insert(const Data& data);
    SIDE checkSide(AVLnode<Data> *father, AVLnode<Data> *son);
    void remove(const Data &data);
    void removeRoot(AVLnode<Data>* to_remove);
    void removeLeaf(AVLnode<Data> *to_remove, SIDE mySide);
    void removeOneSon(AVLnode<Data> *to_remove, SIDE mySide, SIDE otherSide);
    void removeTwoSons(AVLnode<Data> *to_remove, bool isRoot);
    void doingRotation (AVLnode<Data>* node);
    void rotateRight (AVLnode<Data>* node);
    void rotateLeft (AVLnode<Data>* node);
    void rotateLeftThanRight (AVLnode<Data>* node);
    void rotateRightThanLeft (AVLnode<Data>* node);
    AVLnode<Data>* turnArrayIntoTree(Data** playersArray,int start, int end, int high);// changer height en high
    AVLnode<Data>* select (int index);
    AVLnode<Data>* selectAux (int index, AVLnode<Data>* first_node );
    int sumBefore(AVLnode<Data> * to_search);

    friend class AVLnode<Data>;
};

template<class Data>
AVLtree<Data>::AVLtree()
{
    number_of_nodes=0;
    height=0;
    root=nullptr;
    min_node= root;
    max_node= root;
}

template<class Data>
AVLtree<Data>::~AVLtree()
{
    root->clear(root);
    this->root= nullptr;
}


template<class Data>
AVLtree<Data>* AVLtree<Data>::mergeWith(AVLtree<Data>* otherTree)
{
    int origNumberOfNodes = this->number_of_nodes;
    int otherNumberOfNodes = otherTree->number_of_nodes;

    //allocate place for two initials arrays and transform two initials avl to arrays
    Data** origArray;
    Data** otherArray;
    origArray = new Data*[origNumberOfNodes];
    otherArray = new Data*[otherNumberOfNodes];
    this->avlTreeToArr(origArray);
    otherTree->avlTreeToArr(otherArray);


    //allocate place for the final merged array
    Data** finalGroup;
    finalGroup = new Data*[origNumberOfNodes+otherNumberOfNodes];
    for (int i=0;i<origNumberOfNodes+otherNumberOfNodes; i++)
    {
        finalGroup[i] = new Data;
    }

    //merge of origArray and otherArray into finalGroup
    int origCounter = 0;
    int otherCounter = 0;
    //  int counterOfSameElements =0;     //counter to know how much elements are same to reallocate the final group

    for (int i=0; i<(origNumberOfNodes+otherNumberOfNodes) && otherCounter < otherNumberOfNodes && origCounter < origNumberOfNodes; i++)
    {
        if (*(otherArray[otherCounter]) < *(origArray[origCounter]))
        {
            *(finalGroup[i]) = *(otherArray[otherCounter]);
            otherCounter++;
        } else if (*(otherArray[otherCounter]) > *(origArray[origCounter]))
        {
            *(finalGroup[i]) = *(origArray[origCounter]);
            origCounter++;
        }
    }
    if (otherCounter!=otherNumberOfNodes)
    {
        for (int i=otherCounter+origNumberOfNodes; i<(origNumberOfNodes+otherNumberOfNodes); i++)
        {
            *(finalGroup[otherCounter+origCounter]) = *(otherArray[otherCounter]);
            otherCounter++;
        }
    }
    if (origCounter!=origNumberOfNodes)
    {
        for (int i=origCounter+otherNumberOfNodes; i<(otherNumberOfNodes+origNumberOfNodes); i++){
            *(finalGroup[origCounter+otherCounter]) = *(origArray[origCounter]);
            origCounter++;
        }
    }

    Data** finalFinalGroup;
    finalFinalGroup = new Data*[origNumberOfNodes+otherNumberOfNodes];
    for (int i=0; i<otherNumberOfNodes+origNumberOfNodes; i++)
    {
        finalFinalGroup[i] = finalGroup[i];
    }

    AVLtree<Data>* treeToReturn = new AVLtree<Data>;

    //this->root->clear(this->root);
    AVLnode<Data>* first_node= turnArrayIntoTree(finalFinalGroup, 0, otherNumberOfNodes+origNumberOfNodes-1, 0);
    treeToReturn->root = first_node;
    treeToReturn->number_of_nodes = otherNumberOfNodes+origNumberOfNodes;
    if (treeToReturn->root == nullptr)
    {
        treeToReturn->height = 0;
        treeToReturn->min_node= nullptr;
        treeToReturn->max_node=nullptr;
    }
    else{
        treeToReturn->height=treeToReturn->root->height;
        treeToReturn->min_node=treeToReturn->findNode(*(finalGroup[0]));
        treeToReturn->max_node=treeToReturn->findNode(*(finalGroup[otherNumberOfNodes+origNumberOfNodes-1]));
    }
    treeToReturn->postOrderUpdatingRanksAndSums(treeToReturn->root);

    delete[] origArray;
    delete[] otherArray;
    for (int i=0; i<origNumberOfNodes+otherNumberOfNodes; i++){
        delete finalGroup[i];
    }
    delete[] finalGroup;
    delete[] finalFinalGroup;
    return treeToReturn;


}

template <class Data>
int AVLtree<Data>::rankAux(AVLnode<Data>* to_search, AVLnode<Data>* first_node)
{
    AVLnode<Data>* temp= first_node;
    int sum=0;
    while(temp!= nullptr)
    {
        if(temp->getData() < to_search->getData())
        {
            sum++;
            if (temp->left_son != nullptr)
            {
                sum+=temp->left_son->getDataPointer()->num_of_employees_in_subtree;
            }
            temp=temp->right_son;
        }
        else if(temp->getData() == to_search->getData())
        {
            sum++;
            if (temp->left_son != nullptr)
            {
                sum+=temp->left_son->getDataPointer()->num_of_employees_in_subtree;
            }
            return sum;
        }
        else{
            temp=temp->left_son;
        }
    }
    return sum;
}

template <class Data>
int AVLtree<Data>::rank(AVLnode<Data>* to_search)
{
    return this->rankAux(to_search,root);
}

template<class Data>
AVLnode<Data>* AVLtree<Data>::getMax()
{
    return this->max_node;
}

template<class Data>
Data* AVLtree<Data>::getMaxReturnData()
{
    return &(this->max_node->data);
}

template<class Data>
AVLnode<Data>* AVLtree<Data>::getMin()
{
    return this->min_node;
}

template<class Data>
AVLnode<Data>* AVLtree<Data>::findNodeAux(Data data, AVLnode<Data>* first_node)
{
    if(first_node==nullptr)
    {
        return nullptr;
    }
    if(first_node->data==data)
    {
        return first_node;
    }
    else if(data< first_node->data)
    {
        return findNodeAux(data, first_node->left_son);
    }
    return findNodeAux(data, first_node->right_son);
}

template<class Data>
AVLnode<Data>* AVLtree<Data>::findNode(Data data)
{
    return this->findNodeAux(data, this->root);
}

template<class Data>
AVLnode<Data>* AVLtree<Data>::findNodeUsingIDReturnNodeAux (int id, int salary, AVLnode<Data>* first_node)
{
    Data* datat=first_node->getDataPointer();
    if (datat == nullptr)
    {
        return nullptr;
    }
    if (first_node->getDataPointer()->isEqual(salary, id))
    {
        return first_node;
    }
    else if (first_node->getDataPointer()->isGreatherThan(salary, id))
    {
        return findNodeUsingIDReturnNodeAux(id,salary,first_node->left_son);
    }
    else
    {
        return findNodeUsingIDReturnNodeAux(id,salary,first_node->right_son);
    }
}

template<class Data>
AVLnode<Data>* AVLtree<Data>::findNodeUsingIDReturnNode(int id, int salary)
{
    if (this->root == nullptr)
    {
        return nullptr;
    }
    return this->findNodeUsingIDReturnNodeAux(id,salary,this->root);
}

template<class Data>
Data* AVLtree<Data>::findNodeUsingIDReturnDataAux (int id, int salary, AVLnode<Data>* first_node)
{
    if (first_node == nullptr){
        return nullptr;
    }
    if (first_node->getDataPointer()->isEqual(salary, id))
    {
        return first_node->getDataPointer();
    }
    else if (first_node->getDataPointer()->isGreatherThan(salary, id))
    {
        return findNodeUsingIDReturnDataAux(id,salary,first_node->left_son);
    }
    else
    {
        return findNodeUsingIDReturnDataAux(id,salary,first_node->right_son);
    }
}

template<class Data>
Data* AVLtree<Data>::findNodeUsingIDReturnData(int id, int salary)
{
    return this->findNodeUsingIDReturnDataAux(id,salary,this->root);
}

template<class Data>
void AVLtree<Data>::inOrderAux(AVLnode<Data> *first_node)
{
    if(first_node== nullptr)
    {
        return;
    }
    inOrderAux(first_node->left_son);
    std::cout << first_node->data <<" ",
            inOrderAux(first_node->right_son);
}

template<class Data>
void AVLtree<Data>::inOrder(AVLnode<Data> *first_node)
{
    inOrderAux(first_node);
}

template<class Data>
void AVLtree<Data>::preOrderAux(AVLnode<Data> *first_node)
{
    if(first_node== nullptr)
    {
        return;
    }
    std::cout <<first_node->data <<std::endl;
    preOrderAux(root->left_son);
    preOrderAux(root->right_son);
}

template<class Data>
void AVLtree<Data>::preOrder(AVLnode<Data> *first_node)
{
    preOrderAux(first_node);
}


template<class Data>
void AVLtree<Data>::postOrderUpdatingRanksAndSumsAux(AVLnode<Data> *first_node)
{
    if(first_node== nullptr)
    {
        return;
    }
    int right_subtree_employees;
    int left_subtree_employees;

    long int right_sum;
    long int left_sum;

    postOrderUpdatingRanksAndSumsAux(first_node->left_son);
    postOrderUpdatingRanksAndSumsAux(first_node->right_son);
    if (first_node->right_son == nullptr)
    {
        right_subtree_employees = 0;
        right_sum=0;
    }
    else{
        right_subtree_employees= first_node->right_son->getDataPointer()->num_of_employees_in_subtree;
        right_sum=first_node->right_son->getDataPointer()->sum_of_grades_of_employees_in_subtree;
    }
    if (first_node->left_son == nullptr)
    {
        left_subtree_employees = 0;
        left_sum=0;
    }
    else{
        left_subtree_employees= first_node->left_son->getDataPointer()->num_of_employees_in_subtree;
        left_sum=first_node->left_son->getDataPointer()->sum_of_grades_of_employees_in_subtree;
    }
    first_node->getDataPointer()->num_of_employees_in_subtree = 1 + right_subtree_employees + left_subtree_employees;
    first_node->getDataPointer()->sum_of_grades_of_employees_in_subtree=(first_node->getDataPointer()->grade)+right_sum+left_sum;

}

template<class Data>
void AVLtree<Data>::postOrderUpdatingRanksAndSums(AVLnode<Data> *first_node)
{
    postOrderUpdatingRanksAndSumsAux(first_node);
}


template<class Data>
AVLnode<Data>* AVLtree<Data>::findNext(AVLnode<Data> *myNode)
{
    //check if to return
    if(myNode == root)
    {
        if(myNode->right_son == nullptr)
        {
            return nullptr;
        }
        myNode = myNode->right_son;
        while(myNode->left_son!= nullptr)
        {
            myNode = myNode->left_son;
        }
        return myNode;
    }
    SIDE mySide = checkSide(myNode->father, myNode);
    if(myNode->right_son == nullptr && mySide == LEFT)
    {
        return myNode->father;
    }
    if(myNode->right_son == nullptr && mySide == RIGHT)
    {
        while(mySide == RIGHT)
        {
            myNode = myNode->father;
            if(myNode == root)
            {
                return nullptr;
            }
            mySide = checkSide(myNode->father, myNode);
        }
        return myNode->father;
    }
    else{
        myNode = myNode->right_son;
        while(myNode->left_son != nullptr)
        {
            myNode = myNode->left_son;
        }
        return myNode;
    }
}

template<class Data>
AVLnode<Data>* AVLtree<Data>::findPrev(AVLnode<Data> *myNode)
{
    if(myNode==root)
    {
        if(myNode->left_son== nullptr)
        {
            return nullptr;
        }
        myNode=myNode->left_son;
        while (myNode->right_son!= nullptr)
        {
            myNode=myNode->right_son;
        }
        return myNode;
    }

    SIDE mySide=checkSide(myNode->father, myNode);
    if(myNode->left_son == nullptr && mySide == RIGHT)
    {
        return myNode->father;
    }
    if(myNode->left_son == nullptr && mySide == LEFT)
    {
        while(mySide == LEFT)
        {
            myNode = myNode->father;
            if(myNode == root)
            {
                return nullptr;
            }
            mySide = checkSide(myNode->father, myNode);
        }
        return myNode->father;
    }
    else{
        myNode = myNode->left_son;
        while(myNode->right_son != nullptr)
        {
            myNode = myNode->right_son;
        }
        return myNode;
    }
}

template<class Data>
void AVLtree<Data>::transformTreeToInOrderArray(AVLnode<Data> *first_node, Data **arr)
{
    if(first_node->left_son!= nullptr)
    {
        transformTreeToInOrderArray(first_node->left_son, arr);
    }

    Data* debug=first_node->getDataPointer();
    *(arr)=debug;
    arr++;
    if(first_node->right_son!= nullptr)
    {
        transformTreeToInOrderArray(first_node->right_son, arr);
    }
}

template<class Data>
void AVLtree<Data>::avlTreeToArr(Data** data)
{
    int index = 0;
    ino(root,data,&index);
}

template<class Data>
void AVLtree<Data>::ino(AVLnode<Data>* r, Data** vals, int* index)
{
    if(r == nullptr)
        return;
    ino(r->left_son,vals,index);

    (vals)[*index] = r->getDataPointer();
    (*index)++;

    ino(r->right_son,vals,index);
}


template<class Data>
AVLnode<Data>* AVLtree<Data>::insert(const Data& data)
{
//create the node itself
    AVLnode<Data>* node_to_add(new AVLnode<Data>);
    node_to_add->data=data;

//case the tree is empty
    if(this->root== nullptr)
    {
        node_to_add->getDataPointer()->num_of_employees_in_subtree=1;
        node_to_add->getDataPointer()->sum_of_grades_of_employees_in_subtree=node_to_add->getDataPointer()->grade;
        this->root=node_to_add;
        this->number_of_nodes++;
        this->height=0;
        this->max_node=node_to_add;
        this->min_node=node_to_add;
        return this->root;
    }

    //update tree's parameters
    if(this->min_node== nullptr || node_to_add->data<this->min_node->data)
    {
        min_node=node_to_add;
    }
    if( this->max_node== nullptr || node_to_add->data>this->max_node->data)
    {
        max_node=node_to_add;
    }

    //find node's father and connect him the new node
    AVLnode<Data>* curr = this->root;
    AVLnode<Data>* prev = this->root;
    while(curr!= nullptr)
    {
        if(node_to_add->data > curr->data)
        {
            curr=curr->right_son;
            if(curr!= nullptr)
            {
                prev=curr;
            }
        }
        else
        {
            curr=curr->left_son;
            if(curr!= nullptr)
            {
                prev=curr;
            }
        }
    }
    AVLnode<Data>* parent=prev;
    node_to_add->father=parent;
    if(node_to_add->data<parent->data)
    {
        parent->left_son=node_to_add;

    }
    else
    {
        parent->right_son=node_to_add;
    }
    AVLnode<Data>* forRank = node_to_add;
    while (forRank != nullptr)
    {
        forRank->getDataPointer()->num_of_employees_in_subtree++;
        forRank->getDataPointer()->sum_of_grades_of_employees_in_subtree+=node_to_add->getDataPointer()->grade;
        forRank = forRank->father;
    }

    //find eventual problem amd fix it with rotations if needed
    int balanceFactor=0;
    AVLnode<Data>* temp=node_to_add;
    while(parent!= nullptr)
    {
        // if(parent->right_son!= nullptr && parent->left_son!= nullptr)
        if(parent->height>(temp->height))
        {
            break;
        }
        (parent->height)++;
        balanceFactor= parent->getBalanceFactor();
        if(balanceFactor<-1 || balanceFactor>1)
        {
            this->doingRotation(parent);
            break;
        }
        temp=temp->father;
        parent=parent->father;
    }
    this->number_of_nodes++;
    return node_to_add;
}

template<class Data>
AVLnode<Data>* minValueNode (AVLnode<Data>* node)
{
    AVLnode<Data>* current=node;

    while(current->left_son!= nullptr)
    {
        current=current->left_son;
    }
    return current;
}

template<class Data>
SIDE AVLtree<Data>::checkSide(AVLnode<Data> *father, AVLnode<Data> *son)
{
    if(son!=this->root)
    {
        if(father->right_son == son){
            return RIGHT;
        }
        return LEFT;
    }
    return LEFT;
}

template<class Data>
void AVLtree<Data>::remove(const Data &data)
{
    number_of_nodes--;
    AVLnode<Data>* to_remove = findNode(data);
    if(to_remove==max_node)
    {
        max_node=findPrev(to_remove);
    }
    if(to_remove==min_node)
    {
        min_node=findNext(min_node);
    }

    //if the node to remove is the root
    if(to_remove == this->root)
    {
        removeRoot(to_remove);
    }
    else{
        SIDE side = checkSide(to_remove->father, to_remove);

        //the node to remove is a leaf, dont have any sons
        if(to_remove->left_son == nullptr && to_remove->right_son == nullptr)
        {
            removeLeaf(to_remove, side);
        }
            //the node to remove has just one son on the right side
        else if (to_remove->left_son == nullptr && to_remove->right_son != nullptr){
            removeOneSon(to_remove, side, RIGHT);
        }

            //the node to remove has just one son, on the left side
        else if(to_remove->left_son != nullptr && to_remove->right_son == nullptr){
            removeOneSon(to_remove, side, LEFT);
        }

            //the node to remove has two sons
        else{
            int i=0;
            i++;
            removeTwoSons(to_remove, false);
        }
    }
}

template<class Data>
void AVLtree<Data>::removeRoot(AVLnode<Data>* to_remove)
{
    if(to_remove->left_son == nullptr && to_remove->right_son == nullptr)
    {//has no sons //only one node in the tree

        this->root = nullptr;
        this->min_node = nullptr;
        this->max_node = nullptr;
        delete to_remove;
    }
    else if(to_remove->left_son == nullptr && to_remove->right_son != nullptr){ //only two nodes in the tree
        this->root = to_remove->right_son;
        this->min_node = to_remove->right_son;
        this->max_node = to_remove->right_son;
        //note that height of the now root is already 0
        root->father = nullptr;
        AVLnode<Data>* forRank = to_remove;


        while (forRank != nullptr)
        {
            forRank->updateHeight();
            forRank->getDataPointer()->num_of_employees_in_subtree --;
            forRank->getDataPointer()->sum_of_grades_of_employees_in_subtree-=to_remove->getDataPointer()->grade;
            forRank = forRank->father;
        }
        delete to_remove;
    }
    else if(to_remove->right_son == nullptr && to_remove->left_son != nullptr){
        this->root = to_remove->left_son;
        this->min_node = to_remove->left_son;
        this->max_node = to_remove->left_son;
        AVLnode<Data>* forRank = to_remove;


        while (forRank != nullptr)
        {   
            forRank->updateHeight();
            forRank->getDataPointer()->num_of_employees_in_subtree --;
            forRank->getDataPointer()->sum_of_grades_of_employees_in_subtree-=to_remove->getDataPointer()->grade;
            forRank = forRank->father;
        }
        //height is already 0
        root->father = nullptr;
        delete to_remove;
    }
    else{ //has two sons //can be a otherSide grown tree
        removeTwoSons(to_remove, true);
    }
}

template<class Data>
void AVLtree<Data>::removeLeaf(AVLnode<Data> *to_remove, SIDE mySide){

    //update tree's parameters
    if(to_remove == min_node)
    {
        min_node = to_remove->father;
    }
    if(to_remove == max_node)
    {
        max_node = to_remove->father;
    }

   

    //update node to remove's parent
    if(mySide == RIGHT)
    {
        to_remove->father->right_son = nullptr;
    }
    else
    {
        to_remove->father->left_son = nullptr;
    }

    //update the ranks in all the path
    AVLnode<Data>* forRank = to_remove;
    while (forRank != nullptr)
    {   
        forRank->updateHeight();
        forRank->getDataPointer()->num_of_employees_in_subtree --;
        forRank->getDataPointer()->sum_of_grades_of_employees_in_subtree-=to_remove->getDataPointer()->grade;
        forRank = forRank->father;
    }

    //rotations
    AVLnode<Data>* temp=to_remove;
    
    while(temp!= nullptr)
    {
        int bf=temp->getBalanceFactor();
        if(bf<-1 || bf>1)
        {
            doingRotation(temp);
        }
        temp=temp->father;
    }

    delete to_remove;
}

template<class Data>
//the node that we have to remove is on the "myside" of his parent and has only one son, on his "otherside"
void AVLtree<Data>::removeOneSon(AVLnode<Data> *to_remove, SIDE mySide, SIDE otherSide)
{
    //update tree's parameters
    if(to_remove == min_node)
    {
        min_node = to_remove->right_son;
    }
    if(to_remove == max_node)
    {
        max_node = to_remove->left_son;
    }
    if(mySide == RIGHT && otherSide == RIGHT)
    {

        to_remove->father->right_son = to_remove->right_son;
        to_remove->right_son->father = to_remove->father;

        AVLnode<Data>* forRank = to_remove->father;
        while (forRank != nullptr)
        {
            forRank->updateHeight();
            forRank->getDataPointer()->num_of_employees_in_subtree --;
            forRank->getDataPointer()->sum_of_grades_of_employees_in_subtree-=to_remove->getDataPointer()->grade;
            forRank = forRank->father;
        }
    }
    else if(mySide == RIGHT && otherSide == LEFT)
    {

        to_remove->father->right_son = to_remove->left_son;
        to_remove->left_son->father = to_remove->father;

        AVLnode<Data>* forRank = to_remove->father;
        while (forRank != nullptr)
        {
            forRank->updateHeight();
            forRank->getDataPointer()->num_of_employees_in_subtree --;
            forRank->getDataPointer()->sum_of_grades_of_employees_in_subtree-=to_remove->getDataPointer()->grade;
            forRank = forRank->father;
        }
    }
    else if(mySide == LEFT && otherSide == RIGHT){

        to_remove->father->left_son = to_remove->right_son;
        to_remove->right_son->father = to_remove->father;
        AVLnode<Data>* forRank = to_remove->father;
        while (forRank != nullptr)
        {
            forRank->updateHeight();
            forRank->getDataPointer()->num_of_employees_in_subtree --;
            forRank->getDataPointer()->sum_of_grades_of_employees_in_subtree-=to_remove->getDataPointer()->grade;
            forRank = forRank->father;
        }
    }
    else{ //if(mySide == LEFT && otherSide == LEFT)
        to_remove->father->left_son = to_remove->left_son;
        to_remove->left_son->father = to_remove->father;

        AVLnode<Data>* forRank = to_remove->father;
        while (forRank != nullptr)
        {
            forRank->updateHeight();
            forRank->getDataPointer()->num_of_employees_in_subtree --;
            forRank->getDataPointer()->sum_of_grades_of_employees_in_subtree-=to_remove->getDataPointer()->grade;
            forRank = forRank->father;
        }
    }
    AVLnode<Data>* temp=to_remove->father;
    while(temp!= nullptr)
    {
        int bf=temp->getBalanceFactor();
        if(bf<-1 || bf>1)
        {
            doingRotation(temp);
        }
        temp=temp->father;
    }

    delete to_remove;
}

template<class Data>
void AVLtree<Data>::removeTwoSons(AVLnode<Data> *to_remove, bool isRoot)
{
//if the node we want to remove has two sons then it is for sure not the min/max

    //helperNode starts by going RIGHT of to_remove so it is also not the tail
    AVLnode<Data> *helperNode = to_remove->right_son; //will not be tail
    while(helperNode->left_son != nullptr)
    {
        helperNode = helperNode->left_son;
    }
    int original_rem = to_remove->height;
    to_remove->height = helperNode->height;
    helperNode->height = original_rem;

    int original_num_in_subtree=to_remove->getDataPointer()->num_of_employees_in_subtree;
    int helper_num_in_sub_tree=helperNode->getDataPointer()->num_of_employees_in_subtree;
    helperNode->getDataPointer()->num_of_employees_in_subtree=original_num_in_subtree;
    to_remove->getDataPointer()->num_of_employees_in_subtree=helper_num_in_sub_tree;

    long int original_sum=to_remove->getDataPointer()->sum_of_grades_of_employees_in_subtree;
    long int helper_sum_in_sub_tree=helperNode->getDataPointer()->sum_of_grades_of_employees_in_subtree;
    helperNode->getDataPointer()->sum_of_grades_of_employees_in_subtree=original_sum;
    to_remove->getDataPointer()->sum_of_grades_of_employees_in_subtree=helper_sum_in_sub_tree;

    if(helperNode == to_remove->right_son)
    {
        long int difference=helperNode->getDataPointer()->grade-to_remove->getDataPointer()->grade;
        to_remove->getDataPointer()->sum_of_grades_of_employees_in_subtree-=difference;
        //helperNode->father is to_remove in this case and we know it is on the right side of to_remove
        //we also know that helperNode is a leaf or has a right son only
        if(isRoot)
        {
            root = helperNode;
            helperNode->father = nullptr;
            to_remove->father = helperNode;
        }
        else{
            SIDE mySide = checkSide(to_remove->father, to_remove);
            if (mySide == RIGHT)
            {
                to_remove->father->right_son = helperNode;
            } else {
                to_remove->father->left_son = helperNode;
            }
            helperNode->father = to_remove->father;
            to_remove->father = helperNode;
        }
        bool helperNode_leaf = (helperNode->right_son == nullptr);
        if(!helperNode_leaf){ //helperNode->right != nullptr
            to_remove->right_son = helperNode->right_son;
        }
        else{
            to_remove->right_son = nullptr;
        }
        helperNode->right_son = to_remove;
        helperNode->left_son = to_remove->left_son;
        to_remove->left_son->father = helperNode;
        to_remove->left_son = nullptr;
        if(!helperNode_leaf){
            removeOneSon(to_remove, RIGHT, RIGHT);
        }
        else{
            removeLeaf(to_remove, RIGHT);
        }
        return;
    }
    //Change father:
    if(isRoot)
    {
        root = helperNode;
        SIDE helperNode_mySide = checkSide(helperNode->father, helperNode);
        if(helperNode_mySide == RIGHT){
            helperNode->father->right_son = to_remove; //because helperNode can be the node directly to the RIGHT of to_remove
        }
        else{
            helperNode->father->left_son = to_remove;
        }
        to_remove->father = helperNode->father;
        helperNode->father = nullptr;
    }

    else{
        SIDE mySide = checkSide(to_remove->father, to_remove);
        if(mySide == RIGHT)
        {
            to_remove->father->right_son = helperNode;
        }
        else
        {
            to_remove->father->left_son = helperNode;
        }
        SIDE helperNode_mySide = checkSide(helperNode->father, helperNode);
        if(helperNode_mySide == RIGHT)
        {
            helperNode->father->right_son = to_remove;
        }
        else
        {
            helperNode->father->left_son = to_remove;
        }
        AVLnode<Data>* helperNode_dad = helperNode->father;
        helperNode->father = to_remove->father;
        to_remove->father = helperNode_dad;
    }
    //Change sons:
    helperNode->left_son = to_remove->left_son; //helperNode->LEFT was definitely empty/pointed at
    helperNode->left_son->father = helperNode;
    to_remove->left_son = nullptr;
    if(helperNode->right_son != nullptr)
    {
        AVLnode<Data> *r_swap = helperNode->right_son;
        helperNode->right_son = to_remove->right_son;
        helperNode->right_son->father = helperNode;
        to_remove->right_son = r_swap;
        r_swap->father = to_remove;

        to_remove->getDataPointer()->sum_of_grades_of_employees_in_subtree+=r_swap->getDataPointer()->sum_of_grades_of_employees_in_subtree;
        AVLnode<Data>* please= to_remove;
        while(please->father!= nullptr)
        { 
            please->updateHeight();
            please->getDataPointer()->sum_of_grades_of_employees_in_subtree=(please->getDataPointer()->grade);
            please->getDataPointer()->num_of_employees_in_subtree=1;
            if(please->right_son!= nullptr)
            {
                please->getDataPointer()->sum_of_grades_of_employees_in_subtree+=please->right_son->getDataPointer()->sum_of_grades_of_employees_in_subtree;
                please->getDataPointer()->num_of_employees_in_subtree+=please->right_son->getDataPointer()->num_of_employees_in_subtree;
            }
            if(please->left_son!= nullptr)
            {
                please->getDataPointer()->sum_of_grades_of_employees_in_subtree+=please->left_son->getDataPointer()->sum_of_grades_of_employees_in_subtree;
                please->getDataPointer()->num_of_employees_in_subtree+=please->left_son->getDataPointer()->num_of_employees_in_subtree;
            }

            please=please->father;
        }


        removeOneSon(to_remove, LEFT, RIGHT);
    }
    else
    {
        helperNode->right_son = to_remove->right_son;
        helperNode->right_son->father = helperNode;
        to_remove->right_son = nullptr;

        long int difference=helperNode->getDataPointer()->grade-to_remove->getDataPointer()->grade;
        AVLnode<Data>* temp=to_remove->father;
        while(temp!= helperNode)
        {
            temp->updateHeight();
            temp->getDataPointer()->sum_of_grades_of_employees_in_subtree-=difference;
            temp=temp->father;
        }

        removeLeaf(to_remove, LEFT);
    }

}

template<class Data>
void AVLtree<Data>::doingRotation(AVLnode<Data> *node)
{
    if(node->getBalanceFactor()==2)
    {
        int bfl=(node->left_son== nullptr ? 0:node->left_son->getBalanceFactor());
        if(bfl>=0)
        {
            rotateLeft(node);
        }
        else
        {
            rotateLeftThanRight(node);
        }
    }
    else if(node->getBalanceFactor()==-2)
    {
        int bfr=(node->right_son== nullptr ? 0:node->right_son->getBalanceFactor());
        if(bfr<=0)
        {
            rotateRight(node);
        }
        else
        {
            rotateRightThanLeft(node);
        }
    }
}

template<class Data>
void AVLtree<Data>::rotateRight(AVLnode<Data> *node)
{
    //variables for update rank
    AVLnode<Data>* B = node;
    AVLnode<Data>* A = node->right_son;
    AVLnode<Data>* Al = A->left_son;
    AVLnode<Data>* Ar = A->right_son;
    AVLnode<Data>* Bl = B->left_son;

    int num_of_employees_in_sub_tree_Al=(Al== nullptr)? 0: Al->getDataPointer()->num_of_employees_in_subtree;
    long int sum_in_sub_tree_Al=(Al== nullptr)?0:Al->getDataPointer()->sum_of_grades_of_employees_in_subtree;

    int num_of_employees_in_sub_tree_Bl=(Bl== nullptr)? 0: Bl->getDataPointer()->num_of_employees_in_subtree;
    long int sum_in_sub_tree_Bl=(Bl== nullptr)?0:Bl->getDataPointer()->sum_of_grades_of_employees_in_subtree;

    int num_of_employees_in_sub_tree_Ar=(Ar== nullptr)? 0: Ar->getDataPointer()->num_of_employees_in_subtree;
    long int sum_in_sub_tree_Ar=(Ar== nullptr)?0:Ar->getDataPointer()->sum_of_grades_of_employees_in_subtree;

    //rotation itself
    AVLnode<Data>* parent=node->father;
    AVLnode<Data>* oneNode =node->right_son;
    AVLnode<Data>* secondNode=node;
    AVLnode<Data>* oneNodeLeft=oneNode->left_son;
    bool isRoot= (secondNode==this->root);
    secondNode->right_son=oneNodeLeft;
    oneNode->father=secondNode->father;
    secondNode->father=oneNode;
    secondNode->updateHeight();
    oneNode->left_son=secondNode;
    if(oneNodeLeft!= nullptr)
    {
        oneNodeLeft->father=secondNode;
    }
    oneNode->updateHeight();
    if(isRoot)
    {
        this->root=oneNode;
    }
    else
    {
        if(parent->left_son==secondNode)
        {
            parent->left_son=oneNode;
        }
        else
        {
            parent->right_son=oneNode;
        }
    }
    B->getDataPointer()->num_of_employees_in_subtree = 1 + num_of_employees_in_sub_tree_Bl + num_of_employees_in_sub_tree_Al;
    B->getDataPointer()->sum_of_grades_of_employees_in_subtree=sum_in_sub_tree_Bl+sum_in_sub_tree_Al+B->getDataPointer()->grade;

    A->getDataPointer()->num_of_employees_in_subtree = 1+ (B->getDataPointer()->num_of_employees_in_subtree) + num_of_employees_in_sub_tree_Ar;
    A->getDataPointer()->sum_of_grades_of_employees_in_subtree=A->getDataPointer()->grade+B->getDataPointer()->sum_of_grades_of_employees_in_subtree+sum_in_sub_tree_Ar;
}

template<class Data>
void AVLtree<Data>::rotateLeft(AVLnode<Data> *node)
{
    //variables for update ranks
    AVLnode<Data>* B = node;
    AVLnode<Data>* A = node->left_son;
    AVLnode<Data>* Al = A->left_son;
    AVLnode<Data>* Ar = A->right_son;
    AVLnode<Data>* Br = B->right_son;

    int num_of_employees_in_sub_tree_Al=(Al== nullptr)? 0:Al->getDataPointer()->num_of_employees_in_subtree;
    long int sum_in_sub_tree_Al=(Al== nullptr)?0:Al->getDataPointer()->sum_of_grades_of_employees_in_subtree;

    int num_of_employees_in_sub_tree_Br=(Br== nullptr)? 0:Br->getDataPointer()->num_of_employees_in_subtree;
    long int sum_in_sub_tree_Br=(Br== nullptr)?0:Br->getDataPointer()->sum_of_grades_of_employees_in_subtree;

    int num_of_employees_in_sub_tree_Ar=(Ar== nullptr)? 0:Ar->getDataPointer()->num_of_employees_in_subtree;
    long int sum_in_sub_tree_Ar=(Ar== nullptr)?0:Ar->getDataPointer()->sum_of_grades_of_employees_in_subtree;

    //rotation itself
    AVLnode<Data>* parent=node->father;
    AVLnode<Data>* oneNode =node->left_son;
    AVLnode<Data>* secondNode=node;
    AVLnode<Data>* oneNodeRight=oneNode->right_son;
    bool isRoot= (secondNode==this->root);
    secondNode->left_son=oneNodeRight;
    oneNode->father=secondNode->father;
    secondNode->father=oneNode;
    secondNode->updateHeight();
    oneNode->right_son=secondNode;
    if(oneNodeRight!= nullptr)
    {
        oneNodeRight->father=secondNode;
    }
    oneNode->updateHeight();
    if(isRoot)
    {
        this->root=oneNode;
    }
    else
    {
        if(parent->right_son==secondNode)
        {
            parent->right_son=oneNode;
        }
        else
        {
            parent->left_son=oneNode;
        }
    }
    B->getDataPointer()->num_of_employees_in_subtree=1 +num_of_employees_in_sub_tree_Ar+num_of_employees_in_sub_tree_Br;
    B->getDataPointer()->sum_of_grades_of_employees_in_subtree=B->getDataPointer()->grade+sum_in_sub_tree_Ar+sum_in_sub_tree_Br;

    A->getDataPointer()->num_of_employees_in_subtree=1+num_of_employees_in_sub_tree_Al+(B->getDataPointer()->num_of_employees_in_subtree);
    A->getDataPointer()->sum_of_grades_of_employees_in_subtree=A->getDataPointer()->grade+sum_in_sub_tree_Al+B->getDataPointer()->sum_of_grades_of_employees_in_subtree;
}

template<class Data>
void AVLtree<Data>::rotateRightThanLeft(AVLnode<Data> *node)
{
    AVLnode<Data>* right = node->right_son;
    rotateLeft(right);
    rotateRight(node);
}

template<class Data>
void AVLtree<Data>::rotateLeftThanRight(AVLnode<Data> *node)
{
    AVLnode<Data>* left = node->left_son;
    rotateRight(left);
    rotateLeft(node);
}

template <class Data>
AVLnode<Data>* AVLtree<Data>::turnArrayIntoTree(Data** playersArray, int start, int end, int high) // changer height shadow
{
    if(start>end)
    {
        return nullptr;
    }
    int mid = (start+end)/2;

    AVLnode<Data>* first_node(new AVLnode<Data>);
    first_node->data= *(playersArray[mid]);

    first_node->left_son=turnArrayIntoTree(playersArray, start, mid-1, high);
    if(first_node->left_son!= nullptr)
    {
        first_node->left_son->father=first_node;
    }
    first_node->right_son=turnArrayIntoTree(playersArray, mid+1, end, high);
    if(first_node->right_son!= nullptr)
    {
        first_node->right_son->father=first_node;
    }
    first_node->updateHeight();
    return first_node;
}

template<class Data>
AVLnode<Data> * AVLtree<Data>::select(int index)  //return the element in the tree with index i
{
    if (this->root == nullptr)
    {
        return nullptr;
    }
    if(this->number_of_nodes < index)
    {
        return nullptr;
    }
    return selectAux(index, this->root);
}

template<class Data>
AVLnode<Data> * AVLtree<Data>::selectAux(int index, AVLnode<Data> *first_node)
{

    // j ai remplacer if par else if
    //peut etre enlever le premier tnai
    if ((first_node->left_son == nullptr && index==1) || (first_node->left_son != nullptr &&  first_node->left_son->getData().num_of_employees_in_subtree == index-1))
    {
        return first_node;
    }

    else if (first_node->left_son == nullptr && first_node->right_son != nullptr){ // j ai rajouter
        return selectAux(index-1,first_node->right_son);// doit etre index -1 ?
    }

    else if ((first_node->left_son != nullptr) && first_node->left_son->getData().num_of_employees_in_subtree > index-1)
    {
        return selectAux(index,first_node->left_son);
    }
    else if ( first_node->right_son != nullptr && first_node->left_son->getData().num_of_employees_in_subtree < index-1 && first_node->right_son != nullptr) // rajouter avant le premier &&
    {
        return selectAux(index - first_node->left_son->data.num_of_employees_in_subtree - 1,first_node->right_son);// j ai change sum to num
    }
     return nullptr;       
}

template<class Data>
int AVLtree<Data>::sumBefore(AVLnode<Data> *to_search)
{
    long int to_add = 0;
    AVLnode<Data>* iterator = root;
    Data data_to_search = to_search->getData();

    while (iterator != to_search)
    {

        if (iterator->getData() > data_to_search)
        {
            if (iterator->left_son == nullptr) // not suppose to happen
            {
                return OUT_OF_REACH;              // I ADD IN DEFINE. CODE CLEARER
            }
            iterator = iterator->left_son;           // turn left and dont add value to sum
        }
        else                       //   iterator->getData() < data_to_search. We have to add all the  left subtree and the father
        {
            if(iterator->left_son!= nullptr)
            {
                to_add += (iterator->left_son->getData().sum_of_grades_of_employees_in_subtree);
            }
            to_add +=iterator->getData().grade;      // pas certain que c etait la avant
            if (iterator->right_son == nullptr) // not suppose to happen
            {
                return OUT_OF_REACH;              // I ADD IN DEFINE. CODE CLEARER
            }
            iterator = iterator->right_son;
        }
    }
    to_add+=iterator->data.grade;

    if(iterator->left_son!= nullptr) // think i added it not sure
    {
        to_add+=iterator->left_son->getData().sum_of_grades_of_employees_in_subtree;
    }
    return to_add;
}

#endif //SPRING2022WET2DATASTRUCTURES_AVLTREEWITHRANKANDSUMS_H
