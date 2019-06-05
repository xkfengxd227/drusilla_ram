#include "headers.h"

// -----------------------------------------------------------------------------
int ground_truth(					// find ground truth
	int   n,							// roundber of data  objects
	int   qn,							// roundber of query objects
	int   d,							// dimensionality
	const char *data_set,				// address of data  set
	const char *query_set,				// address of query set
	const char *truth_set)				// address of truth set
{
	timeval start_time, end_time;

	// -------------------------------------------------------------------------
	//  read data set and query set
	// -------------------------------------------------------------------------
	gettimeofday(&start_time, NULL);
	float **data = new float*[n];
	for (int i = 0; i < n; ++i) data[i] = new float[d];
	if (read_data(n, d, data_set, data) == 1) {
		printf("Reading Dataset Error!\n");
		exit(1);
	}

	float **query = new float*[qn];
	for (int i = 0; i < qn; ++i) query[i] = new float[d];
	if (read_data(qn, d, query_set, query) == 1) {
		printf("Reading Query Set Error!\n");
		exit(1);
	}

	gettimeofday(&end_time, NULL);
	float read_file_time = end_time.tv_sec - start_time.tv_sec + 
		(end_time.tv_usec - start_time.tv_usec) / 1000000.0f;
	printf("Read Data and Query: %f Seconds\n\n", read_file_time);

	// -------------------------------------------------------------------------
	//  find ground truth results (using linear scan method)
	// -------------------------------------------------------------------------
	gettimeofday(&start_time, NULL);
	FILE *fp = fopen(truth_set, "w");
	if (!fp) {
		printf("Could not create %s.\n", truth_set);
		return 1;
	}

	MaxK_List *list = new MaxK_List(MAXK);
	fprintf(fp, "%d %d\n", qn, MAXK);
	for (int i = 0; i < qn; ++i) {
		list->reset();
		for (int j = 0; j < n; ++j) {
			float dist = calc_l2_dist(d, data[j], query[i]);
			list->insert(dist, j);
		}

		for (int j = 0; j < MAXK; ++j) {
			fprintf(fp, "%d %f ", list->ith_id(j), list->ith_key(j));
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

	gettimeofday(&end_time, NULL);
	float truth_time = end_time.tv_sec - start_time.tv_sec + 
		(end_time.tv_usec - start_time.tv_usec) / 1000000.0f;
	printf("Ground Truth: %f Seconds\n\n", truth_time);

	// -------------------------------------------------------------------------
	//  release space
	// -------------------------------------------------------------------------
	delete list; list = NULL;
	for (int i = 0; i < n; ++i) {
		delete[] data[i]; data[i] = NULL;
	}
	delete[] data; data = NULL;

	for (int i = 0; i < qn; ++i) {
		delete[] query[i]; query[i] = NULL;
	}
	delete[] query; query = NULL;

	return 0;
}

// -----------------------------------------------------------------------------
int indexing(						// indexing of Drusilla_Select
	int   n,							// number of data objects
	int   d,							// dimensionality
	int   B,							// page size
	int   l,							// number of projections
	int   m,							// number of candidates on each proj
	const char* data_set,				// address of data set
	const char* output_folder)			// output folder
{
	timeval start_time, end_time;

	// -------------------------------------------------------------------------
	//  read dataset
	// -------------------------------------------------------------------------
	gettimeofday(&start_time, NULL);
	float **data = new float*[n];
	for (int i = 0; i < n; ++i) data[i] = new float[d];
	if (read_data(n, d, data_set, data) == 1) {
		printf("Reading Dataset Error!\n");
		exit(1);
	}

	gettimeofday(&end_time, NULL);
	float read_file_time = end_time.tv_sec - start_time.tv_sec + 
		(end_time.tv_usec - start_time.tv_usec) / 1000000.0f;
	printf("Read Data: %f Seconds\n\n", read_file_time);

	// -------------------------------------------------------------------------
	//  write the data set in new format to disk
	// -------------------------------------------------------------------------
	/* xikafe: no need for this
	gettimeofday(&start_time, NULL);
	write_data_new_form(n, d, B, (const float **) data, data_folder);

	gettimeofday(&end_time, NULL);
	float write_file_time = end_time.tv_sec - start_time.tv_sec + 
		(end_time.tv_usec - start_time.tv_usec) / 1000000.0f;
	printf("Write Dataset in New Format: %f Seconds\n\n", write_file_time);
	*/	

	// -------------------------------------------------------------------------
	//  Indexing of Drusilla_Select
	// -------------------------------------------------------------------------
	gettimeofday(&start_time, NULL);
	Drusilla_Index* drusilla = new Drusilla_Index();
	drusilla->build(n, d, l, m, B, output_folder, (const float **) data);

	gettimeofday(&end_time, NULL);
	float indexing_time = end_time.tv_sec - start_time.tv_sec + 
		(end_time.tv_usec - start_time.tv_usec) / 1000000.0f;
	printf("Indexing Time: %f Seconds\n\n", indexing_time);

	// -------------------------------------------------------------------------
	//  write indexing time to disk
	// -------------------------------------------------------------------------
	char fname[200];
	strcpy(fname, output_folder);
	strcat(fname, "drusilla.index");

	FILE* fp = fopen(fname, "w");
	if (!fp) {
		printf("Could not create %s\n", fname);
		return 1;
	}
	fprintf(fp, "Indexing Time: %.6f seconds\n", indexing_time);
	fclose(fp);

	// -------------------------------------------------------------------------
	//  Release space
	// -------------------------------------------------------------------------
	delete drusilla; drusilla = NULL;
	for (int i = 0; i < n; ++i) {
		delete[] data[i]; data[i] = NULL;
	}
	delete[] data; data = NULL;

	return 0;
}

// -----------------------------------------------------------------------------
int drusilla_select_RAM(				// c-k-AFN via Drusilla_Select  /* xikafe: RAM */
	int   n,							/* no. of base data */
	int   qn,							// number of query objects
	int   d,							// dimensionality
	const char* data_set,				// address of base data set
	const char* query_set,				// address of query set
	const char* truth_set,				// address of ground truth file
	const char* output_folder)			// output folder
{
	timeval start_time, end_time;

	// -------------------------------------------------------------------------
	//  read base set, query set and truth set
	// -------------------------------------------------------------------------
	gettimeofday(&start_time, NULL);

	float** data = new float*[n];
	for (int i = 0; i < n; ++i) data[i] = new float[d];
	if (read_data(n, d, data_set, data) == 1) {
		printf("Reading Base Point Set Error!\n");
		exit(1);
	}

	float** query = new float*[qn];
	for (int i = 0; i < qn; ++i) query[i] = new float[d];
	if (read_data(qn, d, query_set, query) == 1) {
		printf("Reading Query Set Error!\n");
		exit(1);
	}

	Result **R = new Result*[qn];
	for (int i = 0; i < qn; ++i) R[i] = new Result[MAXK];
	if (read_ground_truth(qn, truth_set, R) == 1) {
		printf("Reading Truth Set Error!\n");
		exit(1);
	}

	gettimeofday(&end_time, NULL);
	float read_file_time = end_time.tv_sec - start_time.tv_sec + 
		(end_time.tv_usec - start_time.tv_usec) / 1000000.0f;
	printf("Read Base, Query and Ground Truth: %f Seconds\n\n", read_file_time);

	// -------------------------------------------------------------------------
	//  load index of Drusilla_Select
	// -------------------------------------------------------------------------
	Drusilla_Index *drusilla = new Drusilla_Index();
	if (drusilla->load(output_folder)) {
		printf("Could not load Drusilla_Index\n");
		exit(1);
	}

	// -------------------------------------------------------------------------
	//  c-k-AFN search via Drusilla_Select
	// -------------------------------------------------------------------------
	char output_set[200];
	strcpy(output_set, output_folder);
	strcat(output_set, "drusilla.out");

	FILE *fp = fopen(output_set, "w");
	if (!fp) {
		printf("Could not create %s\n", output_set);
		return 1;
	}

	int kFNs[] = {1, 5, 10};
	int max_round = 3;
	int top_k = 0;

	float runtime = -1.0f;
	float overall_ratio = -1.0f;
	float recall = -1.0f;
	int   io_cost = -1;


	printf("c-k-AFN Search by Drusilla Select: \n");
	printf("  Top-k\tRatio\tI/O\tTime (ms)\tRecall\n");
	for (int num = 0; num < max_round; ++num) {


		gettimeofday(&start_time, NULL);
		top_k = kFNs[num];
		MaxK_List *list = new MaxK_List(top_k);

		overall_ratio = 0.0f;
		recall        = 0.0f;
		io_cost       = 0;

		int 	*kfn = new int[qn*top_k];
		float	*kfndis = new float[qn*top_k];

		for (int i = 0; i < qn; ++i) {
			list->reset();
			io_cost += drusilla->search_RAM( (const float **)data, query[i], list);
			recall += calc_recall(top_k, (const Result *) R[i], list);

			float ratio = 0.0f;
			for (int j = 0; j < top_k; ++j) {
				ratio += R[i][j].key_ / list->ith_key(j);

				// store the kfn search result
				kfn[i*top_k+j] = list->ith_id(j);
				kfndis[i*top_k+j] = list->ith_key(j);
			}
			overall_ratio += ratio / top_k;
		}
		delete list; list = NULL;
		gettimeofday(&end_time, NULL);
		runtime = end_time.tv_sec - start_time.tv_sec + (end_time.tv_usec - 
			start_time.tv_usec) / 1000000.0f;

		overall_ratio = overall_ratio / qn;
		recall        = recall / qn;
		runtime       = (runtime * 1000.0f) / qn;		/* in ms */
		io_cost       = (int) ceil((float) io_cost / (float) qn);

		printf("  %3d\t%.4f\t%d\t%.2f\t%f\n", 
			top_k, overall_ratio, io_cost, runtime, recall / 100.0);
		fprintf(fp, "%d\t%f\t%d\t%f\t%f\n", 
			top_k, overall_ratio, io_cost, runtime, recall / 100.0);

		// -------------------------------------------------------------------------
		//  Write FN results into file
		// -------------------------------------------------------------------------
		char result_file[255];
		sprintf(result_file, "%sresult.%dFN", output_folder, top_k);
		iddispair_into_file((const int*)kfn, (const float*)kfndis, result_file, qn, top_k);

		delete[] kfn; kfn = NULL;
		delete[] kfndis; kfndis = NULL;
	}
	printf("\n");
	fclose(fp);


	

	// -------------------------------------------------------------------------
	//  Release space
	// -------------------------------------------------------------------------
	delete drusilla; drusilla = NULL;
	for (int i = 0; i < qn; ++i) {
		delete[] query[i]; query[i] = NULL;
		delete[] R[i]; R[i] = NULL;
	}
	delete[] query; query = NULL;
	delete[] R; R = NULL;

	

	return 0;
}
