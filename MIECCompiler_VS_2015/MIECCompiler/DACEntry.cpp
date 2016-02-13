/**
* @file   DACEntry.cpp
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  DACEntry Implementation
*
*
*/
#include "DACEntry.h"
#include <utility>

using namespace std;

/** Transform Opkind enum into string */
std::string GetOpKindStr(OpKind opKind) {
	switch (opKind)
	{
	case eAdd:
		return "Add";
		break;
	case eSubtract:
		return "Substract";
		break;
	case eMultiply:
		return "Multiply";
		break;
	case eDivide:
		return "Divide";
		break;
	case eIsEqual:
		return "IsEqual";
		break;
	case eIsLessEqual:
		return "IsLessEqual";
		break;
	case eIsGreaterEqual:
		return "IsGreaterEqual";
		break;
	case eIsNotEqual:
		return "IsNotEqual";
		break;
	case eIsLess:
		return "IsLess";
		break;
	case eIsGreater:
		return "IsGreater";
		break;
	case eAssign:
		return "Assign";
		break;
	case eJump:
		return "Jump";
		break;
	case eIfJump:
		return "IfJump";
		break;
	case eIfFalseJump:
		return "IfFalseJump";
		break;
	case ePrint:
		return "Print";
		break;
	case eExit:
		return "Exit";
		break;
	default:
		break;
	}
}

#ifdef _DEBUG
/** Debug Code in order to print arguments of DACEntrys */
void DACEntry::Print(std::ostream &out) const {
	std::string s(GetOpKindStr(mOpKind));
	out << "Op: " << s << std::endl;
	if (mOpKind != eExit) {
		out << "	Arg1: ";
		if (mArg1 == 0) { 
			out << "nullptr"; 
		}
		else{
			mArg1->Print(out);
		}
		out << endl;

		out << "	Arg2: ";
		if (mArg2 == 0) {
			out << "nullptr";
		}
		else{
			mArg2->Print(out);
		}
		out << endl;
	}

	out << std::endl;
}
#endif


void DACEntry::ChangeArg1(IDACEntry* arg1) { mArg1 = arg1; }

void DACEntry::ChangeArg2(IDACEntry* arg2) { mArg2 = arg2; }

void DACEntry::ChangeOpKind(OpKind op) { mOpKind = op; }

IDACEntry* DACEntry::GetArg1() { return mArg1; }

IDACEntry* DACEntry::GetArg2() { return mArg2; }

OpKind DACEntry::GetOpKind() { return mOpKind; }

void DACEntry::SetTmpResult(int reg) { indexTmpResult = reg; }

int DACEntry::GetTmpResult() { return indexTmpResult; }

void DACEntry::SetAdress(WORD adress) { mAdress = adress; isAdressSet = true; }

WORD DACEntry::GetAdress() { return mAdress; }

bool DACEntry::IsAdressSet() { return isAdressSet; }