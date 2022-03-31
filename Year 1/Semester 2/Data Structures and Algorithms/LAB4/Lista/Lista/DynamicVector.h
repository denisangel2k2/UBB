#pragma once
typedef int TElem;
class Iterator;
class DynamicVector
{
private:
	int size;
	int cp;
	TElem* elems;

	void resize();

public:
	friend class Iterator;
	DynamicVector(int);
	~DynamicVector();
	void append(TElem);
	int len() const;
	TElem elem(int) const;
	TElem& operator[](int) const;
	void del(int);
	DynamicVector& operator=(const DynamicVector& ot);
	Iterator iterator();
	
};
class Iterator 
{
private:
	const DynamicVector& v;
	int curent;
public:
	friend class DynamicVector;
	Iterator(const DynamicVector&);

	void prim();
	void urmator();
	TElem element() const;
	bool valid() const;
};

