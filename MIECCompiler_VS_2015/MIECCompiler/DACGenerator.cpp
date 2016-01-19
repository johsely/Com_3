#include "DACGenerator.h"

DACGenerator* DACGenerator::DACGenerator_instance = NULL;

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

IDACEntry* DACGenerator::AddStatement(OpKind opKind, IDACEntry* sym1, IDACEntry* sym2) {
	
	if (mLastEmptyStatement) {
		
		mStatements.back()->ChangeArg1(sym1);
		mStatements.back()->ChangeArg2(sym2);
		mStatements.back()->ChangeOpKind(opKind);
	}
	else {
		auto dacEntry = new DACEntry(opKind, sym1, sym2);
		mStatements.push_back(dacEntry);
	}	
	return mStatements.back();
}

void DACGenerator::Clear() {
	for (auto x : mStatements) {
		delete x;
	}
}

IDACEntry* DACGenerator::GetNext(){
	mStatements.push_back(new DACEntry(eExit,0,0));
	mLastEmptyStatement = true;
	return mStatements.back();
}


#ifdef _DEBUG
void DACGenerator::Print(std::ostream& out){
	for (auto elem : mStatements) {
		elem->Print(out);
		out << std::endl;
	}
}
#endif