#include "bandpass_filter.h"
#include <string>
#include "filt.h"
#include <iostream>
#include <fstream>

using namespace std;

bandpass_filter::bandpass_filter(int64_t * min_freq, int64_t * max_freq, int64_t * sampling_frequency) {
	printf("Bandpass filter started \n");
	Filter *my_filter;
	my_filter = new Filter(BPF, 5, (double)(*sampling_frequency / 1000), (double)(*min_freq / 1000), (double)(*max_freq / 1000));
	
	*min_freq = 999;
	*max_freq = 999;
	*sampling_frequency = 999;


	delete my_filter;
	printf("Bandpass filter finished \n");
}

bandpass_filter::bandpass_filter(const bandpass_filter& orig) {
}

bandpass_filter::~bandpass_filter() {
}





