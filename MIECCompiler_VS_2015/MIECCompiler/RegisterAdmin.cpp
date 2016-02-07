/**
* @file   RegisterAdmin.cpp
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  Register Admin implementation
*
*
*/
#include "RegisterAdmin.h"


RegisterAdmin::RegisterAdmin() {
	// fill map with register and pointers to zero
	//for (int i = 0; i < PROL16_REGNUM; i++) {
	//	mRegisters.insert(std::pair<Register, Symbol*>(Register(i), 0));
	//}
}


// tries to find r
int RegisterAdmin::GetRegister() {
	for (int i = 0; i < PROL16_REGNUM; i++) {
		if (mRegisters[i].isFree) {
			mRegisters[i].isFree = false;
			mRegisters[i].connected = nullptr; // ?
			return i;
		}
	}

}

int RegisterAdmin::GetRegister(IDACEntry* dacEntry) {
	return -1;
}


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

void RegisterAdmin::FreeRegister(int regNum) {
	if (regNum < 0 || regNum >= PROL16_REGNUM) {
		throw std::string("register num too big or too low, freeRegister");
	}
	
	mRegisters[regNum].isFree = true;
	mRegisters[regNum].connected = nullptr;
}