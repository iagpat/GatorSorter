#include <string>
#ifndef ARRAYDIVIDER_H
#define ARRAYDIVIDER_H


using namespace std;

class arrayDivider {
public:
    arrayDivider(char const *path, int64_t * sampling_frequency, int64_t * ram_limit);
    arrayDivider(const arrayDivider& orig);
	int data_type = 0;
	int num_bytes_per_entry = 0;
	int number_channels = 0;
	int num_dims = 0;
	int number_timepoints = 0;
	int timepoints_per_segment = 0;
	int number_segments = 0;

    virtual ~arrayDivider();
private:

};

#endif /* ARRAYDIVIDER_H */

