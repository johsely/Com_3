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
	BaseType(eType type, size_t size) : mType(type), Type(size) {}
	eType GetType(){ return mType; }

private:
	eType mType;
};

#endif