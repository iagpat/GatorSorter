#include <string>
#ifndef ARRAYDIVIDER_H
#define ARRAYDIVIDER_H


using namespace std;

class arrayDivider {
public:
    arrayDivider(char const *path, int64_t * sampling_frequency, int64_t * ram_limit, int64_t * number_channels, int64_t * number_segments, int64_t * timepoints_per_segment);
    arrayDivider(const arrayDivider& orig);
	int data_type = 0;
	int num_bytes_per_entry = 0;
	
	int num_dims = 0;
	int number_timepoints = 0;
	
	

    virtual ~arrayDivider();
private:

};

#endif /* ARRAYDIVIDER_H */

