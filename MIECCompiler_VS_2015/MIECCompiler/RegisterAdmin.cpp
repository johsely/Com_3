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


/**constructor*/
RegisterAdmin::RegisterAdmin(MIEC::CodeGenProl16 & codeGen) : mpGenProl16(codeGen) {

	// fill map with register and pointers to zero
	//for (int i = 0; i < PROL16_REGNUM; i++) {
	//	mRegisters.insert(std::pair<Register, Symbol*>(Register(i), 0));
	//}
}


/** tries to find r */
int RegisterAdmin::GetRegister() {
	for (int i = 0; i < PROL16_REGNUM; i++) {
		if (mRegisters[i].isFree) {
			mRegisters[i].isFree = false;
			mRegisters[i].connected = nullptr; // ?
			return i;
		}
	}

}
/** getregister with DACEntry */
int RegisterAdmin::GetRegister(IDACEntry* dacEntry) {


	/**try const int cast*/
	auto constInt = dynamic_cast<ConstIntSymbol*>(dacEntry);


	int reg = GetRegister();

	if (constInt != nullptr) {
		mpGenProl16.LoadI(reg, constInt->GetValue());

	}
	else {
		/**try variable cast*/
		auto Var1 = dynamic_cast<VarSymbol*>(dacEntry);
		if (Var1 == nullptr){
			std::cout << "RegAdmin: Error in GetRegister: no correct operand!";
			return -1;
		}
		int destination_reg = GetRegister();
		mpGenProl16.LoadI(destination_reg, Var1->GetOffset());
		mpGenProl16.Load(reg, destination_reg);
		FreeRegister(destination_reg);
	}

	return reg;

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