#include <string>
#ifndef OPTIONS_H
#define OPTIONS_H


using namespace std;

class options {
public:
	options();
	options(const options& orig);
    virtual ~options();
	int64_t threshold_sign = -1; // We may be looking for positive spikes, negative or even both. If threshold sign is set at -1, we look for negative spikes, if it is set at 1 we look for positive spikes and if it is set at 0 we look for both positive and negative spikes. 
	int64_t absolute_threshold_in_micro_volts = 40; //If threshold sign is negative then it will be -40, is it is positive it will be +40 and if notit will be zero.  
	int64_t min_freq = 300;
	int64_t max_freq = 6000;
	int64_t sampling_frequency = 24414;
	int64_t ram_limit = 1000000000;
	int64_t number_channels = 1;
	int64_t number_segments = 0;
	int64_t timepoints_per_segment = 0;


private:

};

#endif /* OPTIONS_H */

