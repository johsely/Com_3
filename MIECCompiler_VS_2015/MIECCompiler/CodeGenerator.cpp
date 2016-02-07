#include "CodeGenerator.h"
#include <cassert>
#include "Symbol.h"
#include "VarSymbol.h"
#include "ConstIntSymbol.h"
#include <algorithm>
#include <iostream>

using namespace std;

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
			OperationAdd(x);
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

// returns the register number, where the result is stored
int EvaluateArgument(IDACEntry* dacEntry) {
	


	return 1;

}

void CodeGenerator::OperationAssign(DACEntry* apDacEntry) {
	assert(apDacEntry->GetOpKind() == eAssign);
	

	int regAddress = -1;
	int regResult = -1;

	// get left side, must be variable!
	auto left = dynamic_cast<VarSymbol*>(apDacEntry->GetArg1());
	if (left == nullptr){
		throw std::string("arg1 of assign is no variable");
	}
	else {
		// get the variable from a register or have to load it?
		regAddress = mpRegAdmin->AssignRegister(left); // maybe just getregister
		size_t address = left->GetOffset();
		mpGenProl16->LoadI(regAddress, address);
	}

	// get the right side, we need a register where the calculated value is inside


	auto rightVar = dynamic_cast<VarSymbol*>(apDacEntry->GetArg2());
	auto rightIntConst = dynamic_cast<ConstIntSymbol*>(apDacEntry->GetArg2());
	auto rightDAC = dynamic_cast<DACEntry*>(apDacEntry->GetArg2());
	
	if (rightVar != nullptr){
		// load variable


	}
	else if (rightIntConst != nullptr) {
		// load immediate in register
	}
	else if (rightDAC != nullptr) {
		// get the register where the result is stored
		regResult = rightDAC->GetTmpResult();
		
		mpGenProl16->Store(regResult,regAddress);
		mpRegAdmin->FreeRegister(regResult);
	}

	mpRegAdmin->FreeRegister(regAddress);
	


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


void CodeGenerator::OperationAdd(DACEntry* apDacEntry) {
	auto constInt1 = dynamic_cast<ConstIntSymbol*>(apDacEntry->GetArg1());
	auto constInt2 = dynamic_cast<ConstIntSymbol*>(apDacEntry->GetArg2());

	if (constInt1 != nullptr && constInt2 != nullptr) {
		int reg1 = mpRegAdmin->GetRegister();
		int reg2 = mpRegAdmin->GetRegister();
		int regResult = -1;

		// load const int symbols
		// add stuff
		mpGenProl16->LoadI(reg1, constInt1->GetValue());
		mpGenProl16->LoadI(reg2, constInt2->GetValue());
		mpGenProl16->Add(reg1, reg2);
		


		// there is a reg where the result is in
		regResult = mpRegAdmin->AssignRegister(apDacEntry);
		mpGenProl16->Move(regResult, reg1);		
		apDacEntry->SetTmpResult(regResult);

	}
	else {
		cout << "error add" << endl;
	}


}