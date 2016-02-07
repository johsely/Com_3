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
	static DACGenerator* GetInstance() {
		if (!DACGenerator_instance){
			DACGenerator_instance = new DACGenerator();
		}
		return DACGenerator_instance;
	}

	static void Delete() {
		if (DACGenerator_instance){
			delete DACGenerator_instance;
		}
	}
	
	IDACEntry* AddStatement(OpKind opKind, IDACEntry* sym1);
	IDACEntry* AddStatement(OpKind opKind, IDACEntry* sym1, IDACEntry* sym2);
	IDACEntry* GetNext();
		
	void Clear();
	std::list<DACEntry*> GetStatements();

#ifdef _DEBUG
	void Print(std::ostream& out);
#endif

private:
	DACGenerator() { mLastEmptyStatement = false; };
	DACGenerator(DACGenerator const& obj) = delete;
	void operator=(DACGenerator const& obj) = delete;

	bool mLastEmptyStatement;

	static DACGenerator* DACGenerator_instance;
	std::list<DACEntry*> mStatements;
};


#endif