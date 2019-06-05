#ifndef __DRUSILLA_SELECT_H
#define __DRUSILLA_SELECT_H

// -----------------------------------------------------------------------------
//  Drusilla_Index: data structure of Drusilla_Select for c-k-AFN search
// -----------------------------------------------------------------------------
class Drusilla_Index {
public:
	Drusilla_Index();				// default constructor
	~Drusilla_Index();				// destructor

	// -------------------------------------------------------------------------
	int build(						// build index
		int   n,						// number of data objects
		int   d,						// number of dimensions
		int   l,						// number of projections
		int   m,						// number of candidates on each proj
		int   B,						// page size
		const char *index_path,			// index path
		const float **data);			// data objects

	// -------------------------------------------------------------------------
	int load(						// load index
		const char *index_path);		// index path

	// -------------------------------------------------------------------------
	int search_RAM(						// c-k-AFN search (return number of candidates)
		const float **data,				/* base data points */
		const float *query,				// query object
		MaxK_List* list);				// top-k results (return)

protected:
	int  n_pts_;					// number of data objects
	int  dim_;						// dimensionality
	int  l_;						// number of random projections
	int  m_;						// number of candidates
	int  B_;						// page size

	char fname_[200];				// address of index
	int  *fn_cand_;					// candidates on each projection

	// -------------------------------------------------------------------------
	int bulkload(					// build hash tables
		const float **data);			// data objects

	// -------------------------------------------------------------------------
	void display();					// display parameters

	// -------------------------------------------------------------------------
	int write_params();				// write parameters to disk

	// -------------------------------------------------------------------------
	int read_params();				// read parameters from disk
};

#endif // __DRUSILLA_SELECT_H
