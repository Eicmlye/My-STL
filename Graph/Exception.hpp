#include <iostream>

/* Exception */
Exception::Exception(void)
{

}
Exception::~Exception(void)
{

}

/* IndexOverflow */
IndexOverflow::IndexOverflow(size_t maxSize, size_t indSrch) :
	Exception(),
	maxSize_(maxSize),
	indSrch_(indSrch)
{
	this->what(); 
}
IndexOverflow::~IndexOverflow(void)
{

}

void IndexOverflow::what(void) const
{
	std::cout << "IndexOverflow: #" << this->indSrch_ << " node not found. " << std::endl;
	if (this->maxSize_ == 0) {
		std::cout << "\tThe container is empty. " << std::endl;
	}
	else {
		std::cout << "\tShould be less than " << this->maxSize_ << ". " << std::endl;
	}

	return;
}

/* EdgeNotFound */
EdgeNotFound::EdgeNotFound(size_t head, size_t tail) :
	Exception(),
	head_(head),
	tail_(tail)
{
	this->what(); 
}
EdgeNotFound::~EdgeNotFound(void)
{

}

void EdgeNotFound::what(void) const
{
	std::cout << "EdgeNotFound: (" << this->head_ << ", " << this->tail_ << ") does not exist. " << std::endl;

	return;
}

/* UnweightedGraph */
UnweightedGraph::UnweightedGraph(void) :
	Exception()
{
	this->what(); 
}
UnweightedGraph::~UnweightedGraph(void)
{

}

void UnweightedGraph::what(void) const
{
	std::cout << "UnweightedGraph: Attempting to access weights of edges of an unweighted graph. " << std::endl;

	return;
}

/* SelfAdjointNode */
SelfAdjointNode::SelfAdjointNode(void) :
	Exception()
{
	this->what(); 
}
SelfAdjointNode::~SelfAdjointNode(void)
{

}

void SelfAdjointNode::what(void) const
{
	std::cout << "SelfAdjointNode: Attempting to create self-adjoint nodes in simple graph. " << std::endl;

	return;
}

/* InvalidModeTag */
InvalidModeTag::InvalidModeTag(unsigned int mode) :
	Exception(), 
	mode_(mode)
{
	this->what(); 
}
InvalidModeTag::~InvalidModeTag(void)
{

}

void InvalidModeTag::what(void) const
{
	std::cout << "InvalidModeTag: Mode #" << this->mode_ << " undefined. " << std::endl;

	return;
}

/* MultiConnectedGraph */
MultiConnectedGraph::MultiConnectedGraph(void) :
	Exception()
{
	this->what(); 
}
MultiConnectedGraph::~MultiConnectedGraph(void)
{

}

void MultiConnectedGraph::what(void) const
{
	std::cout << "MultiConnectedGraph: This algorithm is not suitable for multi-connected graphs. " << std::endl;

	return;
}