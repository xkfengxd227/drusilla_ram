#ifndef __PRI_QUEUE_H
#define __PRI_QUEUE_H

struct Result;

// -----------------------------------------------------------------------------
//  MaxK_List: the structure is one which maintains the largest k values (of 
//  type float) and associated object id (of type int).
// -----------------------------------------------------------------------------
class MaxK_List {
public:
	MaxK_List(int max);				// constructor (given max size)
	~MaxK_List();					// destructor

	// -------------------------------------------------------------------------
	void reset() { num_ = 0; }

	// -------------------------------------------------------------------------
	float max_key()	{ return num_ > 0 ? list_[0].key_ : MINREAL; }

	// -------------------------------------------------------------------------
	float min_key() { return num_ == k_ ? list_[k_-1].key_ : MINREAL; }

	// -------------------------------------------------------------------------
	float ith_key(int i) { return i < num_ ? list_[i].key_ : MINREAL; }

	// -------------------------------------------------------------------------
	int ith_id(int i) { return i < num_ ? list_[i].id_ : MININT; }

	// -------------------------------------------------------------------------
	int size() { return num_; }

	// -------------------------------------------------------------------------
	bool isFull();					// is full?

	// -------------------------------------------------------------------------
	float insert(					// insert item
		float key,						// key of item
		int id);						// id of item

private:
	int k_;							// max numner of keys
	int num_;						// number of key current active
	Result *list_;					// the list itself
};

#endif // __PRI_QUEUE_H
