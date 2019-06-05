#ifndef __AFN_H
#define __AFN_H

// -----------------------------------------------------------------------------
int ground_truth(					// find ground truth
	int   n,							// number of data  objects
	int   qn,							// number of query objects
	int   d,							// dimensionality
	const char *data_set,				// address of data  set
	const char *query_set,				// address of query set
	const char *truth_set);				// address of truth set
	
// -----------------------------------------------------------------------------
int indexing(						// indexing of Drusilla_Select
	int   n,							// number of data objects
	int   d,							// dimensionality
	int   B,							// page size
	int   l,							// number of projections
	int   m,							// number of candidates on each proj
	const char *data_set,				// address of data set
	const char *output_folder);			// output folder

// -----------------------------------------------------------------------------
int drusilla_select_RAM(				// c-k-AFN via Drusilla_Select /* xikafe: RAM based */
	int   n,							/* no. of base points */
	int   qn,							// number of query objects
	int   d,							// dimensionality
	const char *data_set,				// address of base data set
	const char *query_set,				// address of query set
	const char *truth_set,				// address of truth set
	const char *output_folder);			// output folder

#endif // __AFN_H
