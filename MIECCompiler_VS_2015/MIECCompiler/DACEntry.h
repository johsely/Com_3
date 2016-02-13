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
	/**
	* <summary>  Constructor. </summary>
	*
	* <param name="opkind">   Opcode of Operation. </param>
	* <param name="arg1">  IDAC Entry argument 1 </param>
	* <param name="arg2">  IDAC Entry argument 2 </param>
	*/
	DACEntry(OpKind opKind, IDACEntry* arg1, IDACEntry* arg2) : mOpKind(opKind), mArg1(arg1), mArg2(arg2), isAdressSet(false) {}
	/**
	* <summary>  ChangeArg1. </summary>
	*
	* <param name="arg1">  IDAC Entry Argument to Change </param>
	*/
	void ChangeArg1(IDACEntry* arg1) { mArg1 = arg1; }
	/**
	* <summary>  ChangeArg2. </summary>
	*
	* <param name="arg2">  IDAC Entry Argument to Change </param>
	*/
	void ChangeArg2(IDACEntry* arg2) { mArg2 = arg2; }
	/**
	* <summary>  ChangeOpKind. </summary>
	*
	* <param name="opkind">  Opcode to Change </param>
	*/
	void ChangeOpKind(OpKind op) { mOpKind = op; }
	/**
	* <summary>  GetArg1 Getter for Arg1. </summary>
	*
	*/
	IDACEntry* GetArg1() { return mArg1; }
	/**
	* <summary>  GetArg2 Getter for Arg2. </summary>
	*
	*/
	IDACEntry* GetArg2() { return mArg2; }
	/**
	* <summary>  GetOpKind Getter for Opkind. </summary>
	*
	*/
	OpKind GetOpKind() { return mOpKind; }
	/**
	* <summary>  SetTmpResult Setter for TempResult Used for tmp variables indexing. </summary>
	*
	* <param name="reg">  Tmp Index change </param>
	*/
	void SetTmpResult(int reg) { indexTmpResult = reg;}
	/**
	* <summary>  GetTmpResult Getter for Tmp index. </summary>
	*
	*/
	int GetTmpResult() { return indexTmpResult; }
	/**
	* <summary>  SetAdress Setter for Adress. </summary>
	*
	* <param name="adress">  new adress value </param>
	*/
	void SetAdress(WORD adress) { mAdress = adress; isAdressSet = true; }
	/**
	* <summary>  GetAdress Getter for Adress. </summary>
	*
	*/
	WORD GetAdress() { return mAdress; }
	/**
	* <summary>  IsAdressSet Check if adress has a valid value. </summary>
	*
	*/
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
