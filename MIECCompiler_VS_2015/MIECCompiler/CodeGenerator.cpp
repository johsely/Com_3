#include "CodeGenerator.h"
#include <cassert>
#include "Symbol.h"
#include "VarSymbol.h"
#include <algorithm>

CodeGenerator::CodeGenerator(TDACList dacList)
{
	mpGenProl16 = new MIEC::CodeGenProl16();
	//mpGenProl16 = std::make_unique<MIEC::CodeGenProl16>(MIEC::CodeGenProl16()); // Does not work with unique pointer
	mpRegAdmin = std::make_unique<RegisterAdmin>(RegisterAdmin());
	copy(dacList.begin(), dacList.end(), back_inserter(mDACList));
}

CodeGenerator::~CodeGenerator(){
	delete mpGenProl16;
}

void CodeGenerator::GenerateCode(std::ostream& os) {		
	for (auto x : mDACList){
		auto opKind = x->GetOpKind();
		switch (opKind)
		{
		case eAdd:
			break;
		case eSubtract:
			break;
		case eMultiply:
			break;
		case eDivide:
			break;
		case eIsEqual:
			break;
		case eIsLessEqual:
			break;
		case eIsGreaterEqual:
			break;
		case eIsNotEqual:
			break;
		case eIsLess:
			break;
		case eIsGreater:
			break;
		case eAssign:
			OperationAssign(x);
			break;
		case eJump:
			break;
		case eIfJump:
			break;
		case eIfFalseJump:
			break;
		case ePrint:
			OperationPrint(x);
			break;
		case eExit:
			mpGenProl16->Sleep();
			break;
		default:
			break;
		}
	}

	mpGenProl16->WriteIex(os);


}

void CodeGenerator::OperationAssign(DACEntry* apDacEntry) {
	assert(apDacEntry->GetOpKind() == eAssign);
	
	// ...
	auto right = dynamic_cast<Symbol*>(apDacEntry->GetArg2());
	auto left = dynamic_cast<VarSymbol*>(apDacEntry->GetArg1());
	if (right != nullptr && left != nullptr) {
		
		
		WORD value = 3;
		BYTE reg1 = 0;
		BYTE reg2 = 1;

		WORD adress = 0;
		
		// load value in register
		mpGenProl16->LoadI(reg1, value);
		// load adress in register 2
		mpGenProl16->LoadI(reg2, adress);
		// store value
		mpGenProl16->Store(reg1, reg2);			
	}
	else {
		std::cout << "Error casting" << std::endl;
	}


}


void CodeGenerator::OperationPrint(DACEntry* apDacEntry) {
	assert(apDacEntry->GetOpKind() == ePrint);
	WORD adress = 0;
	BYTE reg1 = 0;

	// load variable from adress and then print it
	mpGenProl16->LoadI(reg1, adress);	
	mpGenProl16->Load(reg1, reg1);
	mpGenProl16->PrintInt(reg1);

}