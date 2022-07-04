/* Error */
#ifndef LIST_EXCEPTION_H_
#define LIST_EXCEPTION_H_

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

	class MemoryOverflow : public Exception
	{
	public:
		MemoryOverflow(void);
		~MemoryOverflow(void);

		void what(void) const override;
	};

	class AllocationFailure : public Exception
	{
	public:
		AllocationFailure(void);
		~AllocationFailure(void);

		void what(void) const override;
	};

	/* Implementations */
	#include "Exception.hpp"

#endif /* Error */