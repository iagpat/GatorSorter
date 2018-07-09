#include "arrayDivider.h"
#include "bandpass_filter.h"
#include "options.h"
#include "thresholding.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {	
	//
	//Options
	//
	options *myoptions = new options;

	//
	//Pipeline
	//

	//1)
	arrayDivider("raw.mda", &(myoptions->sampling_frequency), &(myoptions->ram_limit), &(myoptions->number_channels), &(myoptions->number_segments), &(myoptions->timepoints_per_segment));
	
	//2)
	bandpass_filter(&(myoptions->min_freq), &(myoptions->max_freq), &(myoptions->sampling_frequency), &(myoptions->number_channels), &(myoptions->number_segments), &(myoptions->timepoints_per_segment));
	
	//3)
	thresholding(&(myoptions->number_channels), &(myoptions->number_segments), &(myoptions->absolute_threshold_in_micro_volts), &(myoptions->threshold_sign));

	//4)

	std::cout <<"Process completed"<< endl;    
	return 1;
}
