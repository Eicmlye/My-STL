/* Error */
#ifndef TREE_EXCEPTION_H_
#define TREE_EXCEPTION_H_

	class Exception
	{
	public:
		Exception(void);
		virtual ~Exception(void);

		virtual void what(void) const = 0; 
	};

	class IndexOverflow : public Exception
	{
	public:
		IndexOverflow(void);
		~IndexOverflow(void);

		void what(void) const override;
	};

	class InvalidModeTag : public Exception
	{
	public:
		InvalidModeTag(unsigned int mode, unsigned int modelower, unsigned int modeupper);
		~InvalidModeTag(void);

		void what(void) const override;

	private:
		unsigned int mode_; 
		unsigned int modelower_; 
		unsigned int modeupper_; 
	};

	class MissingTreeNode : public Exception
	{
	public:
		MissingTreeNode(size_t size1, size_t size2);
		~MissingTreeNode(void);

		void what(void) const override;

	private:
		size_t size1_;
		size_t size2_;
	};

	/* Implementations */
	#include "Exception.hpp"

#endif /* Error */