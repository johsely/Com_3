#include "Symbol.h"


std::string Symbol::GetName() { return mName; }
/**
* <summary>  GetType return type of symbol. </summary>
*
*/
Type* Symbol::GetType() { return mType; }
/**
* <summary>  Print  Debugging purpose. </summary>
*
* <param name="out">  stream to print on </param>
*/
void Symbol::Print(std::ostream &ost) const {
	ost << "name: " << mName << " ";
	ost << "size: " << mType->GetSize();
};