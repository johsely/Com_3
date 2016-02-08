/**
* @file   BaseType.h
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  Base Type specialization Class, only integer BaseType supported by our implementation
*
* 
*/


#ifndef MIEC_BASETYPE_H
#define MIEC_BASETYPE_H

#include "Type.h"

enum eType {Integer};

class BaseType : public Type {
public:

	/**
	* <summary>  Constructor. </summary>
	*
	* <param name="type">   eType. </param>
	* <param name="size">  Size of the type basically 2. </param>
	*/
	BaseType(eType type, size_t size) : mType(type), Type(size) {}

	/**
	* <summary>  get access to private mType. </summary>
	*
	* <param name="mType">   eType. </param>
	*/
	eType GetType(){ return mType; }

private:
	eType mType;
};

#endif