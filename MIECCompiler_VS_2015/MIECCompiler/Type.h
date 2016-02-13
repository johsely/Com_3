/**
* @file   Type.h
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  Type Class 
*
*
*/
#ifndef MIEC_TYPE_H
#define MIEC_TYPE_H

#include "Object.h"

class Type : public Object {
public:
	/**
	* <summary>  GetSize Getter for size. </summary>
	*
	*/
	size_t GetSize() const { return mSize; }
protected:
	/**
	* <summary>  Constructor. </summary>
	*
	* <param name="size">  size of type </param>
	*/
	Type(size_t size) : mSize(size){};
private:
	size_t mSize;
};


#endif