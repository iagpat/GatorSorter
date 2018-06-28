#include "arrayDivider.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {	
	int sampling_frequency = 24414;
	int64_t ram_limit = 1000000000;
	arrayDivider("raw.mda", sampling_frequency, ram_limit);
	std::cout <<"Process completed"<< endl;    
	return 1;
}
