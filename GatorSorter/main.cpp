#include "arrayDivider.h"
#include "bandpass_filter.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {	
	//
	//Options
	//
	
	int64_t min_freq = 300;
	int64_t max_freq = 6000;
	int sampling_frequency = 24414;
	int64_t ram_limit = 1000000000;
	
	//
	//Pipeline
	//
		
	arrayDivider("raw.mda", sampling_frequency, ram_limit);
	std::cout <<"Process completed"<< endl;    
	return 1;
}
