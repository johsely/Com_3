#include "DACGenerator.h"

DACGenerator* DACGenerator::DACGenerator_instance = NULL;

IDACEntry* DACGenerator::AddStatement(OpKind opKind, IDACEntry* sym1) {
	DACEntry dacEntry(opKind, sym1, 0);
	mStatements.push_back(dacEntry);
	return &mStatements.back();
}

IDACEntry* DACGenerator::AddStatement(OpKind opKind, IDACEntry* sym1, IDACEntry* sym2) {
	DACEntry dacEntry(opKind, sym1, sym2);
	mStatements.push_back(dacEntry);
	return &mStatements.back();
}

void DACGenerator::Clear() {
	for (auto x : mStatements) {
	
	}
}

#ifdef _DEBUG
void DACGenerator::Print(std::ostream& out){
	for (auto elem : mStatements) {
		elem.Print(out);
		out << std::endl;
	}
}
#endif