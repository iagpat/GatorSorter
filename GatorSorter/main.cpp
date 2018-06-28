#include "arrayDivider.h"
#include "bandpass_filter.h"
#include "options.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {	
	//
	//Options
	//

	options *myoptions = new options;
	int64_t min_freq = myoptions->min_freq;
	int64_t max_freq = myoptions->max_freq;
	int64_t sampling_frequency = myoptions->sampling_frequency;
	int64_t ram_limit = myoptions->ram_limit;

	//
	//Pipeline
	//
		
	arrayDivider("raw.mda", sampling_frequency, ram_limit);
	std::cout <<"Process completed"<< endl;    
	return 1;
}
