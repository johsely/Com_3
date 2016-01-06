#include "DACEntry.h"



#ifdef _DEBUG
void DACEntry::Print(std::ostream &out) const {
	out << "Op: " << mOpKind << std::endl;
	
	
	out << "Arg1: ";  mArg1->Print(out); out << std::endl;
	out << "Arg2: ";  mArg2->Print(out); out << std::endl;
	out << std::endl << std::endl;
	//out << "Arg1: " << mArg1->GetName();
	//out << "Arg2: " << mArg2->GetName() << std::endl;
}
#endif