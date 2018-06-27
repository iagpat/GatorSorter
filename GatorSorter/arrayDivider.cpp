#include "arrayDivider.h"
#include "mda/mdaio.cpp"
#include <string>
#include <iostream>

using namespace std;

arrayDivider::arrayDivider(char const *path, int sampling_frequency) {
	FILE *input = jfopen(path, "rb");
	MDAIO_HEADER *header = new MDAIO_HEADER;
	mda_read_header(header,input); 
	number_channels = header->dims[2];
	number_timepoints = header->dims[1];
	std::cout << "Number of channels is: " << number_channels <<endl;
	std::cout << "NUmber of timepoints is: " << number_timepoints <<endl;
	jfclose(input);
}

arrayDivider::arrayDivider(const arrayDivider& orig) {
}

arrayDivider::~arrayDivider() {
}

