//
// Created by alivasples 2020.
// Adapted from gonzaga 2016.
//

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>

using namespace std;

// ===================================================== Attribute Class ===================================================
class Attribute
{
	private:
		// ATTRIBUTES
		string name; // name of the Relation attribute
		string type; // type of the Relation attribute (float, string, etc)
		int size; // size of the Relation attribute (1 if simple numeric attribute, >1 if string or complex)
		int headerIndex; // index number of appearance in the Relation header

	public:
		// METHODS
		// Constructors
		/** Attribute full constructor */
		Attribute(const string &name, const string &type, const int &size, const int &headerIndex) :
			name(name), type(type), size(size), headerIndex(headerIndex)
		{};

		/** Attribute default constructor */
		Attribute(): size(0), headerIndex(-1) { };

		// Getters
		string getName(){return name;}
		string getType(){return type;}
		int getSize(){return size;}
		int getHeaderIndex(){return headerIndex;}

		// << operator Overloading
		friend ostream& operator<<(ostream& os, const Attribute& att);
};

// << operator Overloading
ostream& operator<<(ostream& os, const Attribute& att)
{
    os << "Attribute " << att.name << " (type : " << att.type << ", size : " << att.size
    		<< ", index : " << att.headerIndex << ")";
    return os;
}

#endif
