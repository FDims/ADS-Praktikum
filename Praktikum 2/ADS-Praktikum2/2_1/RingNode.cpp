/*************************************************
* ADS Praktikum 2.1
* RingNode.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "RingNode.h"


// Ihr Code hier:
RingNode::RingNode() {
	age = 0;
	desc = "";
	data = "";
}
RingNode::RingNode(int alt, std::string dsc, std::string neu) {
	age = alt;
	desc = dsc;
	data = neu;
}
int RingNode::getAge() {
	return age;
}
void RingNode::setAge(int alt) {
	age = alt;
}
std::string RingNode::getDescription() {
	return desc;
}
void RingNode::setDescription(std::string dsc) {
	desc = dsc;
}
std::string RingNode::getData() {
	return data;
}
void RingNode::setData(std::string neu) {
	data = neu;
}
RingNode* RingNode::getNext() {
	return next;
}
void RingNode::setNext(RingNode* nxt) {
	if (nxt != 0)
		next = nxt;
}
// 
////////////////////////////////////