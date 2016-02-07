#ifndef MIEC_REGISTER_H
#define MIEC_REGISTER_H

#include "Object.h"

class Register : public Object {
public:
	Register(size_t regNr) : mRegNr(regNr) {}

	size_t GetRegNumber() { return mRegNr; }

private:
	size_t mRegNr;

};




#endif