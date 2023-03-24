/*************************************************
 * ADS Praktikum 2.2
 * TreeNode.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include <string>

using namespace std;

class TreeNode
{

private:
    ///////////////////////////////////////
    // Ihr Code hier:
    int NodeOrderID, NodeChronologicalID, Age, PostCode;
    std::string Name;
    double Income;
    TreeNode* left;
    TreeNode* right;
    //
    ////////////////////////////////////

public:
    ///////////////////////////////////////
    // Ihr Code hier:
    TreeNode();
    TreeNode(int order, int chronological, std::string Nm, int Alter, double In, int Post);
    
    void print();

    int getNodeOrderID();
    void setNodeOrderID(int id);

    int getNodeChronologicalID();
    void setNodeChronologicalID(int id);

    int getAge();
    void setAge(int a);

    int getPostCode();
    void setPostCode(int PC);

    std::string getName();
    void setName(std::string N);

    double getIncome();
    void setIncome(double I);

    TreeNode* getLeft();
    void setLeft(TreeNode* L);

    TreeNode* getRight();
    void setRight(TreeNode* R);

    //
    ////////////////////////////////////
};
