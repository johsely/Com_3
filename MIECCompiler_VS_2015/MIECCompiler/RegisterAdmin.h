#ifndef MIEC_REGISTER_ADMIN
#define MIEC_REGISTER_ADMIN

#include "Register.h"
#include "IDACEntry.h"
#include "Symbol.h"
#include <map>

size_t const PROL16_REGNUM = 8;


struct TRegister {
	IDACEntry* connected;
	bool isFree;
};


class RegisterAdmin : public Object {
public:
	RegisterAdmin();
	
	int GetRegister();
	int GetRegister(IDACEntry* dacEntry);
	int AssignRegister(IDACEntry* dacEntry);
	void FreeRegister(int regNum);

private:
	TRegister mRegisters[PROL16_REGNUM];

	//std::map<Register, Symbol*> mRegisters;

};




#endif