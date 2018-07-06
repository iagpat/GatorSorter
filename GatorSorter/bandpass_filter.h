#include <string>
#ifndef BANDPASS_FILTER_H
#define BANDPASS_FILTER_H


using namespace std;

class bandpass_filter {
public:
	bandpass_filter(int64_t * min_freq, int64_t * max_freq, int64_t * sampling_frequency, int64_t * number_channels, int64_t * number_segments, int64_t * timepoints_per_segment);
	bandpass_filter(const bandpass_filter& orig);
    virtual ~bandpass_filter();
private:

};

#endif /* BANDPASS_FILTER_H */

