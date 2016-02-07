/**
* @file   DACGenerator.cpp
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  DACGenerator
*
*
*/
#include "DACGenerator.h"


DACGenerator* DACGenerator::DACGenerator_instance = NULL;

/** Adds Statement and returns DACEntry, only one Operand e.g. assign */
IDACEntry* DACGenerator::AddStatement(OpKind opKind, IDACEntry* sym1) {
	auto dacEntry = new DACEntry(opKind, sym1, 0);
	if (mLastEmptyStatement) {
		delete mStatements.back();
		mStatements.back() = dacEntry;
	}
	else {
		mStatements.push_back(dacEntry);
	}
	return mStatements.back();
}

/** Adds Statement and returns DACEntry, two Operand e.g. add */
IDACEntry* DACGenerator::AddStatement(OpKind opKind, IDACEntry* sym1, IDACEntry* sym2) {
	
	if (mLastEmptyStatement) {
		
		mStatements.back()->ChangeArg1(sym1);
		mStatements.back()->ChangeArg2(sym2);
		mStatements.back()->ChangeOpKind(opKind);
		mLastEmptyStatement = false;
	}
	else {
		auto dacEntry = new DACEntry(opKind, sym1, sym2);
		mStatements.push_back(dacEntry);
	}	
	return mStatements.back();
}
/***/
/** Statements cleanup */
void DACGenerator::Clear() {
	for (auto x : mStatements) {
		delete x;
	}
}
/**returns next DACEntry*/
IDACEntry* DACGenerator::GetNext(){
	if (!mLastEmptyStatement) {
		mStatements.push_back(new DACEntry(eExit, 0, 0));
		mLastEmptyStatement = true;
	}
	return mStatements.back();
}
/**getter for dacEntry list*/
std::list<DACEntry*> DACGenerator::GetStatements() {
	return mStatements;
}


#ifdef _DEBUG
/**debug print: prints all statements in list*/
void DACGenerator::Print(std::ostream& out){
	for (auto elem : mStatements) {
		elem->Print(out);
		out << std::endl;
	}
}
#endif