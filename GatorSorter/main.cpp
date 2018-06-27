#include "arrayDivider.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {	
	int sampling_frequency = 24414;
	arrayDivider("/home/drew/Desktop/725/raw.mda", sampling_frequency);
	std::cout <<"Process completed"<< endl;    
	return 1;
}
