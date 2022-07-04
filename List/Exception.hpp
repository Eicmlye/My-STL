#include <iostream>

/* Exception */
Exception::Exception(void)
{

}
Exception::~Exception(void)
{

}

/* IndexOverflow */
IndexOverflow::IndexOverflow(void) :
	Exception()
{
	this->what();
}
IndexOverflow::~IndexOverflow(void)
{

}

void IndexOverflow::what(void) const
{
	std::cout << "IndexOverflow" << std::endl; 

	return; 
}

/* MemoryOverflow */
MemoryOverflow::MemoryOverflow(void) :
	Exception()
{
	this->what();
}
MemoryOverflow::~MemoryOverflow(void)
{

}

void MemoryOverflow::what(void) const
{
	std::cout << "MemoryOverflow" << std::endl;

	return;
}

/* AllocationFailure */
AllocationFailure::AllocationFailure(void) :
	Exception()
{
	this->what();
}
AllocationFailure::~AllocationFailure(void)
{

}

void AllocationFailure::what(void) const
{
	std::cout << "AllocationFailure" << std::endl;

	return;
}