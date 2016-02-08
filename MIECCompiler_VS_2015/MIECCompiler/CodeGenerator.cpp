/**
* @file   CodeGenerator.cpp
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  Implementation of CodeGenerator Class. 
*
*
*/
#include "CodeGenerator.h"
#include <cassert>
#include "Symbol.h"
#include "VarSymbol.h"
#include "ConstIntSymbol.h"
#include <algorithm>
#include <iostream>

using namespace std;
/** initialize Register admin and copy daclist */
CodeGenerator::CodeGenerator(TDACList dacList)
{
	mpGenProl16 = new MIEC::CodeGenProl16();
	//mpGenProl16 = std::make_unique<MIEC::CodeGenProl16>(MIEC::CodeGenProl16()); // Does not work with unique pointer
	RegisterAdmin regadmin(mpGenProl16);
	mpRegAdmin = std::make_unique<RegisterAdmin>(regadmin);
	copy(dacList.begin(), dacList.end(), back_inserter(mDACList));
}
/** mandatory cleanup */
CodeGenerator::~CodeGenerator(){
	delete mpGenProl16;
}

void CodeGenerator::Compare(DACEntry* dacEntry) {
	int reg1 = mpRegAdmin->GetRegister(dacEntry->GetArg1());
	int reg2 = mpRegAdmin->GetRegister(dacEntry->GetArg2());
	
	mpGenProl16->Comp(reg1, reg2);
	mpRegAdmin->FreeRegister(reg1);
	mpRegAdmin->FreeRegister(reg2);
}

void CodeGenerator::CompareInverse(DACEntry* dacEntry) {
	int reg1 = mpRegAdmin->GetRegister(dacEntry->GetArg1());
	int reg2 = mpRegAdmin->GetRegister(dacEntry->GetArg2());

	mpGenProl16->Comp(reg2, reg1);
	mpRegAdmin->FreeRegister(reg1);
	mpRegAdmin->FreeRegister(reg2);
}


/** loops through all DacEntries and Creates machineCode for each operation */
void CodeGenerator::GenerateCode(std::ostream& os) {		
	
	TUnresolvedJumps unresolvedJumps;
	for (auto x : mDACList){
		auto opKind = x->GetOpKind();
		WORD codePos;
		codePos = mpGenProl16->GetCodePosition();
		for (auto unResJmp : unresolvedJumps) {
			if (unResJmp.second == x) {
				mpGenProl16->SetAddress(unResJmp.first * 2, codePos);
			}
		}

		switch (opKind)
		{
		case eAdd:
			OperationAdd(x);
			break;
		case eSubtract:
			OperationSubtract(x);
			break;
		case eMultiply:
			OperationMultiply(x);
			break;
		case eDivide:
			OperationDivide(x);
			break;
		case eIsEqual:
			Compare(x);
			break;
		case eIsLessEqual:
			Compare(x);
			break;
		case eIsGreaterEqual:
			Compare(x);
			break;
		case eIsNotEqual:
			CompareInverse(x);
			break;
		case eIsLess:
			Compare(x);
			break;
		case eIsGreater:
			Compare(x);
			break;
		case eAssign:
			OperationAssign(x);
			break;
		case eJump:
			OperationJump(x, unresolvedJumps);
			break;
		case eIfJump:
			OperationConditionalJump(x, unresolvedJumps);
			break;
		case eIfFalseJump:
			OperationConditionalJump(x, unresolvedJumps);
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

/** returns the register number, where the result is stored */
int EvaluateArgument(IDACEntry* dacEntry) {
	


	return 1;

}
/** creates code for assign operation */
void CodeGenerator::OperationAssign(DACEntry* apDacEntry) {


	assert(apDacEntry->GetOpKind() == eAssign);
	
	WORD codePos = mpGenProl16->GetCodePosition();
	apDacEntry->SetAdress(codePos);


	int regAddress = -1;
	int regResult = -1;

	/** get left side, must be variable! */
	auto left = dynamic_cast<VarSymbol*>(apDacEntry->GetArg1());
	if (left == nullptr){
		throw std::string("arg1 of assign is no variable");
	}
	else {
		/** get the variable from a register or have to load it? */
		regAddress = mpRegAdmin->AssignRegister(left); /** maybe just getregister */
		size_t address = left->GetOffset();
		mpGenProl16->LoadI(regAddress, address);
	}

	/** get the right side, we need a register where the calculated value is inside */


	auto rightVar = dynamic_cast<VarSymbol*>(apDacEntry->GetArg2());
	auto rightIntConst = dynamic_cast<ConstIntSymbol*>(apDacEntry->GetArg2());
	auto rightDAC = dynamic_cast<DACEntry*>(apDacEntry->GetArg2());
	
	if (rightVar != nullptr){
		// load right adress into register
		int regRightAdress = mpRegAdmin->GetRegister();
		size_t adress = rightVar->GetOffset();
		mpGenProl16->LoadI(regRightAdress, adress);
		
		// load var from memory
		regResult = mpRegAdmin->GetRegister();
		mpGenProl16->Load(regResult, regRightAdress);
		
		mpGenProl16->Store(regResult, regAddress);
		mpRegAdmin->FreeRegister(regResult);
		mpRegAdmin->FreeRegister(regRightAdress);
	}
	else if (rightIntConst != nullptr) {
		/** load immediate in register */
		regResult = mpRegAdmin->GetRegister();
		mpGenProl16->LoadI(regResult, rightIntConst->GetValue());
		mpGenProl16->Store(regResult, regAddress);
		mpRegAdmin->FreeRegister(regResult);

	}
	else if (rightDAC != nullptr) {
		/** get the register where the result is stored */
		regResult = rightDAC->GetTmpResult();
		
		mpGenProl16->Store(regResult,regAddress);
		mpRegAdmin->FreeRegister(regResult);
	}

	mpRegAdmin->FreeRegister(regAddress);
	
	

}

/** creates code for print operation */
void CodeGenerator::OperationPrint(DACEntry* apDacEntry) {
	assert(apDacEntry->GetOpKind() == ePrint);
	
	WORD codePos = mpGenProl16->GetCodePosition();
	apDacEntry->SetAdress(codePos);
	
	auto var = dynamic_cast<VarSymbol*>(apDacEntry->GetArg1());
	if (var == nullptr) { throw std::string("print can only varSymbol"); }

	WORD adress = var->GetOffset();
	BYTE reg1 = mpRegAdmin->GetRegister();

	// load variable from adress and then print it
	mpGenProl16->LoadI(reg1, adress);	
	mpGenProl16->Load(reg1, reg1);
	mpGenProl16->PrintInt(reg1);

	mpRegAdmin->FreeRegister(reg1);
}

/** creates code for add operation */
void CodeGenerator::OperationAdd(DACEntry* apDacEntry) {


	WORD codePos = mpGenProl16->GetCodePosition();
	apDacEntry->SetAdress(codePos);

	int reg1 = mpRegAdmin->GetRegister(apDacEntry->GetArg1());
	int reg2 = mpRegAdmin->GetRegister(apDacEntry->GetArg2());
	int regResult = -1;

	/** there is a reg where the result is in */
	mpGenProl16->Add(reg1, reg2);
	regResult = mpRegAdmin->AssignRegister(apDacEntry);
	mpGenProl16->Move(regResult, reg1);		
	apDacEntry->SetTmpResult(regResult);
	mpRegAdmin->FreeRegister(reg1);
	mpRegAdmin->FreeRegister(reg2);

}

/** creates code for sub operation */
void CodeGenerator::OperationSubtract(DACEntry* apDacEntry) {

	WORD codePos = mpGenProl16->GetCodePosition();
	apDacEntry->SetAdress(codePos);

	int reg1 = mpRegAdmin->GetRegister(apDacEntry->GetArg1());
	int reg2 = mpRegAdmin->GetRegister(apDacEntry->GetArg2());
	int regResult = -1;

	/** there is a reg where the result is in */
	mpGenProl16->Sub(reg1, reg2);
	regResult = mpRegAdmin->AssignRegister(apDacEntry);
	mpGenProl16->Move(regResult, reg1);
	apDacEntry->SetTmpResult(regResult);
	mpRegAdmin->FreeRegister(reg1);
	mpRegAdmin->FreeRegister(reg2);

}
 

/** creates code for mult operation */
void CodeGenerator::OperationMultiply(DACEntry* apDacEntry)
 {
	WORD codePos = mpGenProl16->GetCodePosition();
	apDacEntry->SetAdress(codePos);


	 int regA = mpRegAdmin->GetRegister(apDacEntry->GetArg1()); // multiplicand
	 int regB = mpRegAdmin->GetRegister(apDacEntry->GetArg2()); // multiplier
	 int regJmp = mpRegAdmin->GetRegister(); // used for jumps
	 // regResult contains result of multiplication -> assign to DAC-Entry
	 int regResult = mpRegAdmin->AssignRegister(apDacEntry); // will contain result
	 mpGenProl16->LoadI(regResult, 0); //init
	 WORD codePosStart = mpGenProl16->GetCodePosition(); //start of loop begin
	 int helpReg = mpRegAdmin->GetRegister();
	 mpGenProl16->LoadI(helpReg, 0);
	 mpGenProl16->Comp(regB, helpReg); //compare: multiplier != 0
	 WORD jumpData1 = mpGenProl16->LoadI(regJmp, 0); //stores jump address of while-statement
	 mpGenProl16->JumpZ(regJmp); //jump if zero bit is set (multiplier = 0)
	 mpGenProl16->ShR(regB); //multiplier = mulitiplier >> 1
	
	 WORD jumpData2 = mpGenProl16->LoadI(regJmp, 0); //stores jump address of if-statement
	
		 //jump if carry bit is set ( multiplier = 3 -> 011 >> 1 = 001 (carry bit = 1) )
	 mpGenProl16->JumpC(regJmp);
	 mpGenProl16->ShL(regA); //multiplicand = multiplicand << 1
	 mpGenProl16->LoadI(regJmp, codePosStart); //prepeare jump address
	 mpGenProl16->Jump(regJmp); //jump to begin of while-statement
	 //sets jump address for if-statement
	 mpGenProl16->SetAddress(jumpData2, mpGenProl16->GetCodePosition());
	 mpGenProl16->Add(regResult, regA); //adds multiplicand to result register
	
	 mpGenProl16->ShL(regA); //multiplicand = multiplicand << 1
	 mpGenProl16->LoadI(regJmp, codePosStart); //prepeare jump address
	 mpGenProl16->Jump(regJmp); //jump to begin of while-statement
	
	 //sets jump address for end of while-statement
	 mpGenProl16->SetAddress(jumpData1, mpGenProl16->GetCodePosition());
	
	 // free all other registers
	 mpRegAdmin->FreeRegister(regA);
	 mpRegAdmin->FreeRegister(regB);
	 mpRegAdmin->FreeRegister(regJmp);
	 mpRegAdmin->FreeRegister(helpReg);
	 apDacEntry->SetTmpResult(regResult);

}


void CodeGenerator::OperationDivide(DACEntry* apDacEntry)
 {
	WORD codePos = mpGenProl16->GetCodePosition();
	apDacEntry->SetAdress(codePos);

	 int regA = mpRegAdmin->GetRegister(apDacEntry->GetArg1()); // dividend
	 int regB = mpRegAdmin->GetRegister(apDacEntry->GetArg2()); // divisor
	 int regJmp = mpRegAdmin->GetRegister(); // used for jumps
	 int regRemainder = mpRegAdmin->GetRegister(); // remainder
	 mpGenProl16->LoadI(regRemainder, 0);
	 int regBits = mpRegAdmin->GetRegister(); // bit counter
	 mpGenProl16->LoadI(regBits, 16);
	 WORD codePosStart = mpGenProl16->GetCodePosition();
	 mpGenProl16->ShL(regA);
	 mpGenProl16->ShLC(regRemainder);
	 WORD jumpData1 = mpGenProl16->LoadI(regJmp, 0);
	 mpGenProl16->JumpC(regJmp);
	 mpGenProl16->Comp(regB, regRemainder);
	 mpGenProl16->JumpC(regJmp);
	 mpGenProl16->JumpZ(regJmp);
	 WORD jumpData2 = mpGenProl16->LoadI(regJmp, 0);
	 mpGenProl16->Jump(regJmp);
	 mpGenProl16->SetAddress(jumpData1, mpGenProl16->GetCodePosition());
	 mpGenProl16->Sub(regRemainder, regB);
	 int helpReg = mpRegAdmin->GetRegister();
	 mpGenProl16->LoadI(helpReg, 1);
	 mpGenProl16->Or(regA, helpReg);
	 mpGenProl16->SetAddress(jumpData2, mpGenProl16->GetCodePosition());
	 mpGenProl16->Dec(regBits);
	 WORD jumpData3 = mpGenProl16->LoadI(regJmp, 0);
	 mpGenProl16->JumpZ(regJmp);
	 mpGenProl16->LoadI(regJmp, codePosStart);
	 mpGenProl16->Jump(regJmp);
	 mpGenProl16->SetAddress(jumpData3, mpGenProl16->GetCodePosition());

	 // regA contains result of division -> assign to DAC-Entry
	int regResult = mpRegAdmin->AssignRegister(apDacEntry);
	mpGenProl16->Move(regResult, regA);
	apDacEntry->SetTmpResult(regResult);

	 // free all other registers
	 mpRegAdmin->FreeRegister(regB);
	 mpRegAdmin->FreeRegister(regA);
	 mpRegAdmin->FreeRegister(regJmp);
	 mpRegAdmin->FreeRegister(regRemainder);
	 mpRegAdmin->FreeRegister(regBits);
	 mpRegAdmin->FreeRegister(helpReg);

	 
}


void CodeGenerator::OperationJump(DACEntry* apDacEntry, TUnresolvedJumps& arUnresolvedJumps){
	WORD codePos = mpGenProl16->GetCodePosition();
	apDacEntry->SetAdress(codePos);


	auto jumpDest = dynamic_cast<DACEntry*>(apDacEntry->GetArg1());
	if (jumpDest == nullptr) { throw std::string("operationJump error, no dac entry"); }
	
	int regAdress = mpRegAdmin->GetRegister();
	
	mpGenProl16->LoadI(regAdress, jumpDest->GetAdress());
	mpGenProl16->Jump(regAdress);

	mpRegAdmin->FreeRegister(regAdress);
}

void CodeGenerator::OperationConditionalJump(DACEntry*	apDacEntry, TUnresolvedJumps& arUnresolvedJumps) {
	assert(apDacEntry->GetOpKind() == eIfJump || apDacEntry->GetOpKind() == eIfFalseJump);

	WORD codePos = mpGenProl16->GetCodePosition();
	apDacEntry->SetAdress(codePos);
	
	
	
	// load jump adress into register
	auto jumpDst = dynamic_cast<DACEntry*>(apDacEntry->GetArg2());

	int regJumpAdress = mpRegAdmin->GetRegister();
	mpGenProl16->LoadI(regJumpAdress, jumpDst->GetAdress());

	if (apDacEntry->GetOpKind() == eIfJump) {



		auto condOp = dynamic_cast<DACEntry*>(apDacEntry->GetArg1()); // what conditional Operation
		auto opKindCond = condOp->GetOpKind();
		switch (opKindCond)
		{
		case eIsEqual:
			mpGenProl16->JumpZ(regJumpAdress);




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
		default:
			throw std::string("error in conditional jump, default switch");
			break;
		}
	}
	else {
		auto condOp = dynamic_cast<DACEntry*>(apDacEntry->GetArg1()); // what conditional Operation
		auto opKindCond = condOp->GetOpKind();
		switch (opKindCond)
		{
		case eIsEqual:
			mpGenProl16->JumpC(regJumpAdress);
			CompareInverse(condOp);
			mpGenProl16->JumpC(regJumpAdress);
			break;
		case eIsLessEqual:
			mpGenProl16->JumpC(regJumpAdress);
			break;
		case eIsGreaterEqual:
			mpGenProl16->JumpC(regJumpAdress);
			break;
		case eIsNotEqual:						
			mpGenProl16->JumpZ(regJumpAdress);	
			if (!jumpDst->IsAdressSet()) {
				arUnresolvedJumps.push_back(std::pair<WORD, DACEntry* const>(codePos+1, jumpDst));
			}

			break;
		case eIsLess:
			mpGenProl16->JumpC(regJumpAdress);
			break;
		case eIsGreater:
			mpGenProl16->JumpC(regJumpAdress);
			break;
		default:
			throw std::string("error in conditional jump, default switch");
			break;
		}


	}



}