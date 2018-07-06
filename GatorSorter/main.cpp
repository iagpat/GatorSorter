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


	//
	//Pipeline
	//
		
	arrayDivider("raw.mda", &(myoptions->sampling_frequency), &(myoptions->ram_limit));
	
	bandpass_filter(&(myoptions->min_freq), &(myoptions->max_freq), &(myoptions->sampling_frequency));

	std::cout << myoptions->min_freq << endl;
	std::cout << myoptions->max_freq << endl;
	std::cout << myoptions->sampling_frequency << endl;

	std::cout <<"Process completed"<< endl;    
	return 1;
}
