


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
	

	void OperationAdd(DACEntry* apDacEntry);
	void OperationSubtract(DACEntry* apDacEntry);
	void OperationMultiply(DACEntry* apDacEntry);
	void OperationDivide(DACEntry* apDacEntry);
	void OperationAssign(DACEntry* apDacEntry);
	void OperationJump(DACEntry* apDacEntry, TUnresolvedJumps& arUnresolvedJumps);
	void OperationConditionalJump(DACEntry*	apDacEntry, TUnresolvedJumps& arUnresolvedJumps);
	void OperationPrint(DACEntry* apDacEntry);


	//std::unique_ptr<MIEC::CodeGenProl16> mpGenProl16;
	MIEC::CodeGenProl16* mpGenProl16;
	std::unique_ptr<RegisterAdmin> mpRegAdmin;
	TDACList mDACList;

};
