/*************************************************
 * ADS Praktikum 2.2
 * TreeNode.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "TreeNode.h"
#include <iostream>
#include <string>

////////////////////////////////////
// Ihr Code hier:
TreeNode::TreeNode() {
	NodeChronologicalID = 0;
	Age = 0;
	PostCode = 0;
	Income = 0;
	NodeOrderID = 0;
	Name = "";
	left = 0;
	right = 0;
}
TreeNode::TreeNode(int order, int chronological, std::string Nm, int Alter, double In, int Post) {
	NodeChronologicalID = chronological;
	Age = Alter;
	PostCode = Post;
	Income = In;
	NodeOrderID = order;
	Name = Nm;
	left = 0;
	right = 0;
}

void TreeNode::print() {
	std::cout << "NodeID: " << NodeChronologicalID << ", Name: " << Name << ", Alter: " << Age
		<< ", Einkommen: " << Income << ", PLZ: " << PostCode << ", PosID: " << NodeOrderID << std::endl;
}

int TreeNode::getNodeOrderID() {
	return NodeOrderID;
}
void TreeNode::setNodeOrderID(int id) {
	NodeOrderID = id;
}

int TreeNode::getNodeChronologicalID() {
	return NodeChronologicalID;
}
void TreeNode::setNodeChronologicalID(int id) {
	NodeChronologicalID = id;
}

int TreeNode::getAge() {
	return Age;
}
void TreeNode::setAge(int a) {
	Age = a;
}

int TreeNode::getPostCode() {
	return PostCode;
}
void TreeNode::setPostCode(int PC) {
	PostCode = PC;
}

std::string TreeNode::getName() {
	return Name;
}
void TreeNode::setName(std::string N) {
	Name = N;
}

double TreeNode::getIncome() {
	return Income;
}
void TreeNode::setIncome(double I) {
	Income = I;
}

TreeNode* TreeNode::getLeft() {
	return left;
}
void TreeNode::setLeft(TreeNode* L) {
	left = L;
}

TreeNode* TreeNode::getRight() {
	return right;
}
void TreeNode::setRight(TreeNode* R) {
	right = R;
}
//
////////////////////////////////////
