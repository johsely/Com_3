#include <cassert>
#include "SymbolTable.h"
#include "Symbol.h"
#include "ConstIntSymbol.h"
#include "../MIECCompiler/BaseType.h"
#include "../MIECCompiler/VarSymbol.h"

int main(){
	SymbolTable* symTable = SymbolTable::GetInstance();
	ConstIntSymbol constInt(3, "constVariable", BaseType(Integer, 2));
	VarSymbol varSym(3, "var", BaseType(Integer, 2));

	symTable->AddSymbol(&constInt);
	
	assert(symTable->Find("constVariable"));
	symTable->Find("constint");
	assert(!symTable->Find("constInt"));
	

	return 0;
}