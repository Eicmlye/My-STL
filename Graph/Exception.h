/* Error */
#ifndef GRAPH_EXCEPTION_H_
#define GRAPH_EXCEPTION_H_

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
		IndexOverflow(size_t maxSize, size_t indSrch);
		~IndexOverflow(void);

		void what(void) const override;

	private:
		size_t maxSize_;
		size_t indSrch_;
	};

	class EdgeNotFound : public Exception
	{
	public:
		EdgeNotFound(size_t head, size_t tail);
		~EdgeNotFound(void);

		void what(void) const override;

	private:
		size_t head_;
		size_t tail_;
	};

	class UnweightedGraph : public Exception
	{
	public:
		UnweightedGraph(void);
		~UnweightedGraph(void);

		void what(void) const override;
	};

	class SelfAdjointNode : public Exception
	{
	public:
		SelfAdjointNode(void);
		~SelfAdjointNode(void);

		void what(void) const override;
	};

	class InvalidModeTag : public Exception
	{
	public:
		InvalidModeTag(unsigned int mode);
		~InvalidModeTag(void);

		void what(void) const override;

	private:
		unsigned int mode_;
	};

	class MultiConnectedGraph : public Exception
	{
	public:
		MultiConnectedGraph(void);
		~MultiConnectedGraph(void);

		void what(void) const override;

	private:
		unsigned int mode_;
	};

	/* Implementations */
	#include "Exception.hpp"

#endif /* Error */