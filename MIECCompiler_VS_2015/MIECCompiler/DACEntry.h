/**
* @file   DACEntry.h
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  DacEntry class, used for one DAC operation. 
*
*
*/
#ifndef MIEC_DAC_ENTRY_H
#define MIEC_DAC_ENTRY_H

#include "Object.h"
#include "GlobalDef.h"
#include "IDACEntry.h"
#include <iostream>
#include <string>
#include <minmax.h>

enum OpKind {
	eAdd, eSubtract, eMultiply, eDivide, eIsEqual, eIsLessEqual, eIsGreaterEqual,
	eIsNotEqual, eIsLess, eIsGreater, eAssign, eJump, eIfJump, eIfFalseJump, ePrint,
	eExit
};



class DACEntry : public IDACEntry {
public:
	DACEntry(OpKind opKind, IDACEntry* arg1, IDACEntry* arg2) : mOpKind(opKind), mArg1(arg1), mArg2(arg2), isAdressSet(false) {}
	void ChangeArg1(IDACEntry* arg1) { mArg1 = arg1; }
	void ChangeArg2(IDACEntry* arg2) { mArg2 = arg2; }
	void ChangeOpKind(OpKind op) { mOpKind = op; }
	IDACEntry* GetArg1() { return mArg1; }
	IDACEntry* GetArg2() { return mArg2; }
	OpKind GetOpKind() { return mOpKind; }

	void SetTmpResult(int reg) { indexTmpResult = reg;}
	int GetTmpResult() { return indexTmpResult; }

	void SetAdress(WORD adress) { mAdress = adress; isAdressSet = true; }
	WORD GetAdress() { return mAdress; }
	bool IsAdressSet() { return isAdressSet; }
	


#ifdef _DEBUG
	void Print(std::ostream &out) const;
#endif

private:
	WORD mAdress;
	bool isAdressSet;
	int indexTmpResult;
	OpKind mOpKind;
	IDACEntry* mArg1;
	IDACEntry* mArg2;
};

#endif
