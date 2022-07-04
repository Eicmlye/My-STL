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

/* InvalidModeTag */
InvalidModeTag::InvalidModeTag(unsigned int mode, unsigned int modelower, unsigned int modeupper) :
	Exception(), 
	mode_(mode), 
	modelower_(modelower), 
	modeupper_(modeupper)
{
	this->what();
}
InvalidModeTag::~InvalidModeTag(void)
{

}

void InvalidModeTag::what(void) const
{
	std::cout << "InvalidModeTag: Mode #";
	std::cout << this->mode_ << " is not available. " << std::endl; 
	std::cout << "\tMode number should be "; 
	std::cout << this->modelower_ << " to " << this->modeupper_ << ". " << std::endl;

	return; 
}

/* MissingTreeNode */
MissingTreeNode::MissingTreeNode(size_t size1, size_t size2) :
	Exception(), 
	size1_(size1),
	size2_(size2)
{
	this->what();
}
MissingTreeNode::~MissingTreeNode(void)
{

}

void MissingTreeNode::what(void) const
{
	std::cout << "MissingTreeNode: " << this->size1_ << "-node list doesn't match "; 
	std::cout << "" << this->size2_ << "-node list. " << std::endl;

	return; 
}