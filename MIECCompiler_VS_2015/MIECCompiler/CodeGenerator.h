/**
* @file   CodeGenerator.h
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  machine code generation. creates machine code from a list of Dac entries by using CodeGenProl16.
*
*
*/


#include "Object.h"
#include <iostream>
#include <list>
#include "DACEntry.h"
#include "CodeGenProl16.h"
#include "RegisterAdmin.h"
#include <memory>

class CodeGenerator : public Object {
public:
	using TDACList = std::list < DACEntry* >;
	
	CodeGenerator(TDACList dacList);
	void GenerateCode(std::ostream& os);
	~CodeGenerator();

private:
	typedef std::list < std::pair < WORD, DACEntry const*> > TUnresolvedJumps;
	
	/**
	* <summary>  Creates Add Operation Machine Code. </summary>
	*
	* <param name="apDacEntry">   DAcEntry with Operands and operation. </param>
	*/
	void OperationAdd(DACEntry* apDacEntry);
	/**
	* <summary>  Creates Subtract Operation Machine Code. </summary>
	*
	* <param name="apDacEntry">   DAcEntry with Operands and operation. </param>
	*/
	void OperationSubtract(DACEntry* apDacEntry);
	/**
	* <summary>  Creates Multiply Operation Machine Code. </summary>
	*
	* <param name="apDacEntry">   DAcEntry with Operands and operation. </param>
	*/
	void OperationMultiply(DACEntry* apDacEntry);
	/**
	* <summary>  Creates Divide Operation Machine Code. </summary>
	*
	* <param name="apDacEntry">   DAcEntry with Operands and operation. </param>
	*/
	void OperationDivide(DACEntry* apDacEntry);
	/**
	* <summary>  Creates Assign Operation Machine Code. </summary>
	*
	* <param name="apDacEntry">   DAcEntry with Operands and operation. </param>
	*/
	void OperationAssign(DACEntry* apDacEntry);
	/**
	* <summary>  Creates Jump Operation Machine Code. </summary>
	*
	* <param name="apDacEntry">   DAcEntry with Operands and operation. </param>
	* <param name="arUnresolvedJumps">   Unresolved jumps available. </param>
	*/
	void OperationJump(DACEntry* apDacEntry, TUnresolvedJumps& arUnresolvedJumps);

	/**
	* <summary>  Creates Jump Operation Machine Code. </summary>
	*
	* <param name="apDacEntry">   DAcEntry with Operands and operation. </param>
	* <param name="arUnresolvedJumps">   Unresolved jumps available. </param>
	*/
	void OperationConditionalJump(DACEntry*	apDacEntry, TUnresolvedJumps& arUnresolvedJumps);
	/**
	* <summary>  Creates Print Operation Machine Code. </summary>
	*
	* <param name="apDacEntry">   DAcEntry with Operands and operation. </param>
	*/
	void OperationPrint(DACEntry* apDacEntry);



	MIEC::CodeGenProl16* mpGenProl16;
	std::unique_ptr<RegisterAdmin> mpRegAdmin;
	TDACList mDACList;

};
