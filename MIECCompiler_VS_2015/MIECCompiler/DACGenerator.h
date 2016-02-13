/**
* @file   DACGenerator.h
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  DAC Generator: creates a list of DACEntries with all statements from the code
*
*
*/
#ifndef MIEC_DAC_GENERATOR
#define MIEC_DAC_GENERATOR

#include "Object.h"
#include "IDACEntry.h"
#include "DACEntry.h"
#include <list>
#include <iostream>


class DACGenerator : public Object {
public:
	/**
	* <summary>  GetInstance Singleton Getter. </summary>
	*
	*/
	static DACGenerator* GetInstance() {
		if (!DACGenerator_instance){
			DACGenerator_instance = new DACGenerator();
		}
		return DACGenerator_instance;
	}
	/**
	* <summary>  Delete Instance (Singleton). </summary>
	*
	*/
	static void Delete() {
		if (DACGenerator_instance){
			delete DACGenerator_instance;
		}
	}
	/**
	* <summary>  AddStatement Add next IdacEntry one argument. </summary>
	*
	* <param name="opkind">  opcode of operation </param>
	* <param name="sym1">  argument 1 IDACEntry </param>

	*/
	IDACEntry* AddStatement(OpKind opKind, IDACEntry* sym1);
	/**
	* <summary>  AddStatement Add next IdacEntry two arguments. </summary>
	*
	* <param name="opkind">  opcode of operation </param>
	* <param name="sym1">  argument 1 IDACEntry </param>
	* <param name="sym2">  argument 2 IDACEntry </param>
	*/
	IDACEntry* AddStatement(OpKind opKind, IDACEntry* sym1, IDACEntry* sym2);
	/**
	* <summary>  GetNext returns next IDACEntry in list </summary>
	*
	*/
	IDACEntry* GetNext();
	/**
	* <summary>  Clear  Cleanup. </summary>
	*
	*/
	void Clear();
	/**
	* <summary>  GetStatements returns the list of DAC Entries. </summary>
	*
	*/
	std::list<DACEntry*> GetStatements();

#ifdef _DEBUG
	/**
	* <summary>  Print  Debugging purpose. </summary>
	*
	* <param name="out">  stream to print on </param>
	*/
	void Print(std::ostream& out);
#endif

private:
	/**
	* <summary>  Constructor. </summary>
	*
	*/
	DACGenerator() { mLastEmptyStatement = false; };
	/**
	* <summary>  Copy Constructor  Deleted no implementation. </summary>
	*
	* <param name="obj">  DACGenerator object to copy </param>
	*/
	DACGenerator(DACGenerator const& obj) = delete;
	/**
	* <summary>  Assignment Operator  Deleted no implementation. </summary>
	*
	* <param name="obj">  DACGenerator object to assign </param>
	*/
	void operator=(DACGenerator const& obj) = delete;

	bool mLastEmptyStatement;

	static DACGenerator* DACGenerator_instance;
	std::list<DACEntry*> mStatements;
};


#endif