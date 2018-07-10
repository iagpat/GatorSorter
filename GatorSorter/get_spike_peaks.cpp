#include "get_spike_peaks.h"
#include <string>
#include <iostream>
#include <stack>
#include <fstream>

using namespace std;

get_spike_peaks::get_spike_peaks(int64_t * max_freq, int64_t * sampling_frequency, int64_t * number_channels, int64_t * number_segments, int64_t * timepoints_per_segment) {
	max_length_of_event = 0.25 * (*sampling_frequency / *max_freq);
	string mystring;
	FILE *input;
	FILE *indices;
	FILE *corresponding_voltages;
	const char *name;
	float raw;
	int64_t index;
	float voltage;





}

get_spike_peaks::get_spike_peaks(const get_spike_peaks& orig) {
}

get_spike_peaks::~get_spike_peaks() {
}





