/**
* @file   DACEntry.h
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