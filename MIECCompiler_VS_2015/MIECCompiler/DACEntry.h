#ifndef MIEC_DAC_ENTRY_H
#define MIEC_DAC_ENTRY_H


#include "IDACEntry.h"
#include <iostream>
#include <string>

enum OpKind {
	eAdd, eSubtract, eMultiply, eDivide, eIsEqual, eIsLessEqual, eIsGreaterEqual,
	eIsNotEqual, eIsLess, eIsGreater, eAssign, eJump, eIfJump, eIfFalseJump, ePrint,
	eExit
};


#include "Object.h"
class DACEntry : public IDACEntry {
public:
	DACEntry(OpKind opKind, IDACEntry* arg1, IDACEntry* arg2) : mOpKind(opKind), mArg1(arg1), mArg2(arg2) {}
	void ChangeArg1(IDACEntry* arg1) { mArg1 = arg1; }
	void ChangeArg2(IDACEntry* arg2) { mArg2 = arg2; }
	void ChangeOpKind(OpKind op) { mOpKind = op; }
	IDACEntry* GetArg1() { return mArg1; }
	IDACEntry* GetArg2() { return mArg2; }
	OpKind GetOpKind() { return mOpKind; }

	void SetTmpResult(int reg) { indexTmpResult = reg;}
	int GetTmpResult() { return indexTmpResult; }


#ifdef _DEBUG
	void Print(std::ostream &out) const;
#endif

private:
	int indexTmpResult;
	OpKind mOpKind;
	IDACEntry* mArg1;
	IDACEntry* mArg2;
};

#endif
