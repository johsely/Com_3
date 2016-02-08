/**
* @file   IDACEntry.h
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  IDACEntry base class for DAC and Symbols
*
*
*/
#ifndef MIEC_IDACENTRY_H
#define MIEC_IDACENTRY_H

#include "Object.h"
#include <iostream>

/** <summary>  The base class for DAC entries and Symbols. </summary> */
class IDACEntry : public Object {
public:
	virtual ~IDACEntry() {}

	/**
	* <summary>  Print function no implementation -->virtual. </summary>
	*
	* <param name="ost">   Where to print. </param>
	*/
	virtual void Print(std::ostream &ost) const = 0;
	/**
	* <summary>  Gets the type. </summary>
	*
	* <returns>  The type. </returns>
	*/
	//virtual Type::sPtr getType() const = 0; ??
protected:
	/** <summary>  Default constructor. </summary> */
	IDACEntry() = default;
};

#endif /* IDACENTRY_H */