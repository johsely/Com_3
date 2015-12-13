#ifndef MIEC_TYPE_H
#define MIEC_TYPE_H

class Type {
public:
	size_t GetSize() const { return mSize; }
protected:
	Type(size_t size) : mSize(size){};
private:
	size_t mSize;
};


#endif