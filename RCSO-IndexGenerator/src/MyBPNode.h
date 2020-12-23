/*
 * MyBPNode.h
 *
 *  Created on: 17 de fev de 2020
 *      Author: alexis
 */

#ifndef MYBPNODE_H_
#define MYBPNODE_H_

struct MyBPNode{
	// Attrributes
	int value;

	// Constructors
	MyBPNode(){}
	MyBPNode(int rowId): value(value) {}

	// "less" method
	bool operator==(MyBPNode other) const { return value == other.value; }
	bool operator<(MyBPNode other) const { return value < other.value; }
	bool operator<=(MyBPNode other) const { return value <= other.value; }
	bool operator>(MyBPNode other) const { return value > other.value; }
	bool operator>=(MyBPNode other) const { return value >= other.value; }

	// serialize
	int GetSerializedSize(){return 0;}
	const unsigned char * Serialize(){return NULL;}
};



#endif /* MYBPNODE_H_ */
