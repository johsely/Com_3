/**
* @file   RegisterAdmin.cpp
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  Register Admin implementation
*
*
*/
#include "RegisterAdmin.h"
#include "ConstIntSymbol.h"
#include "VarSymbol.h"
#include "DACEntry.h"


/**constructor*/
RegisterAdmin::RegisterAdmin(MIEC::CodeGenProl16 * codeGen) : mpGenProl16(codeGen) {

}


/** tries to find r */
int RegisterAdmin::GetRegister() {
	for (int i = 0; i < PROL16_REGNUM; i++) {
		if (mRegisters[i].isFree) {
			mRegisters[i].isFree = false;
			mRegisters[i].connected = nullptr; 
			return i;
		}
	}
	return -1;
}
/** getregister with DACEntry */
int RegisterAdmin::GetRegister(IDACEntry* dacEntry) {
	/**try const int cast*/
	auto constInt = dynamic_cast<ConstIntSymbol*>(dacEntry);

	int reg = GetRegister();
	if (constInt != nullptr) {
		mpGenProl16->LoadI(reg, constInt->GetValue());
		mRegisters[reg].connected = dacEntry;
		return reg;

	}

	/**try variable cast*/
	auto Var1 = dynamic_cast<VarSymbol*>(dacEntry);
	if (Var1 != nullptr) {	
		int destination_reg = GetRegister();
		mpGenProl16->LoadI(destination_reg, Var1->GetOffset());
		mpGenProl16->Load(reg, destination_reg);
		FreeRegister(destination_reg);
		mRegisters[reg].connected = dacEntry;
		return reg;
	}
	/**try dacEntry cast*/
	auto DAC1 = dynamic_cast<DACEntry*>(dacEntry);
	if (DAC1 != nullptr) {
		return DAC1->GetTmpResult();
	}


	std::cout << "ERROR in RegAdmin GetRegister: incorrect IDAC"<<std::endl;
	return -1;
}

/** AssignRegister searches for a free register and connects the DACEntry with it, returns the register number -1 if error */
int RegisterAdmin::AssignRegister(IDACEntry* dacEntry) {
	for (int i = 0; i < PROL16_REGNUM; i++) {
		if (mRegisters[i].isFree) {
			mRegisters[i].isFree = false;
			mRegisters[i].connected = dacEntry;
			return i; // return the reg number
		}

	}
	return -1;
}
/** release used register */
void RegisterAdmin::FreeRegister(int regNum) {
	if (regNum < 0 || regNum >= PROL16_REGNUM) {
		throw std::string("register num too big or too low, freeRegister");
	}
	
	mRegisters[regNum].isFree = true;
	mRegisters[regNum].connected = nullptr;
}