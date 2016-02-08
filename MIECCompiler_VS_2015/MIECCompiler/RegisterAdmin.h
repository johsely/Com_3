/**
* @file   RegisterAdmin.h
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  Register Admin header
*
*
*/
#ifndef MIEC_REGISTER_ADMIN
#define MIEC_REGISTER_ADMIN

#include "Register.h"
#include "IDACEntry.h"
#include "Symbol.h"
#include <map>
#include "CodeGenProl16.h"
size_t const PROL16_REGNUM = 8;


struct TRegister {
	IDACEntry* connected;
	bool isFree;
};


class RegisterAdmin : public Object {
public:
	/**
	* <summary>  Constructor. </summary>
	*
	* <param name="codeGen">   Register Admin needs the codegen for getRegister. </param>

	*/
	RegisterAdmin(MIEC::CodeGenProl16 *codeGen);
	
	/**
	* <summary>  Get Register without Dac Entry mostly internally used . </summary>
	*
	*/
	int GetRegister();
	/**
	* <summary>  Normal GetRegister from DACEntry. </summary>
	*
	* <param name="dacEntry">   IDACEntry. </param>
	*/
	int GetRegister(IDACEntry* dacEntry);

	/**
	* <summary>  Assigns Register to Address. </summary>
	*
	* <param name="dacEntry">   IDACEntry. </param>
	*/
	int AssignRegister(IDACEntry* dacEntry);

	/**
	* <summary>  Free Register to Address. </summary>
	*
	* <param name="regNum">   Register Number. </param>
	*/
	void FreeRegister(int regNum);

private:
	TRegister mRegisters[PROL16_REGNUM];

	MIEC::CodeGenProl16 * mpGenProl16;
	//std::map<Register, Symbol*> mRegisters;

};




#endif