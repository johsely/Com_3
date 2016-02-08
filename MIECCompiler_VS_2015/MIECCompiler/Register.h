/**
* @file   Register.h
* @Author Christoph Haslinger, Johannes Selymes
* @Date   Februar , 2016
* @brief  Register class
*
*
*/
#ifndef MIEC_REGISTER_H
#define MIEC_REGISTER_H

#include "Object.h"

class Register : public Object {
public:
	/**
	* <summary>  Constructor. </summary>
	*
	* <param name="regNr">   eType. </param>
	* <param name="size">  Size of the type basically 2. </param>
	*/
	Register(size_t regNr) : mRegNr(regNr) {}

	/**
	* <summary>  Getter for private mRegNr. </summary>
	*
	*/
	size_t GetRegNumber() { return mRegNr; }

private:
	size_t mRegNr;

};




#endif