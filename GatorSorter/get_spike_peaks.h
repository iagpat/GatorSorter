#include <string>
#ifndef GET_SPIKE_PEAKS_H
#define GET_SPIKE_PEAKS_H


using namespace std;

class get_spike_peaks {
public:
	get_spike_peaks(int64_t * max_freq, int64_t * sampling_frequency, int64_t * number_channels, int64_t * number_segments, int64_t * timepoints_per_segment);
	get_spike_peaks(const get_spike_peaks& orig);
    virtual ~get_spike_peaks();
private:
	int64_t max_length_of_event;
};

#endif /* GET_SPIKE_PEAKS_H */

