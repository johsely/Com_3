#ifndef MIEC_VARSYMBOL_H
#define MIEC_VARSYMBOL_H

#include "Symbol.h"

class VarSymbol : public Symbol {
public:
	VarSymbol(size_t offset, std::string name, Type* type) : mOffset(offset), Symbol(name, type) {}
	size_t GetOffset() { return mOffset; }
	void Print(std::ostream &ost) const {
		Symbol::Print(ost);
		ost << " offset: " << mOffset;
	}
private:
	size_t mOffset;
};

#endif