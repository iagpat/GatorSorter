#include "arrayDivider.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

arrayDivider::arrayDivider(char const *path, int64_t * sampling_frequency, int64_t * ram_limit) {
	FILE *input_file;
	input_file = fopen(path,"rb"); //Opening the file
	if (input_file == 0){
		 std::cout << "Failed to open file" << endl;
	}
	//
	//Read header
	//
	int num_read = fread(&data_type, 4, 1, input_file);
	if (num_read < 1) {
		printf("Problem reading input file.\n");
	}
	num_read = fread(&num_bytes_per_entry, 4, 1, input_file);
	if (num_read < 1 || num_bytes_per_entry !=4) {
		printf("Problem reading input file.\n");
	}
	num_read = fread(&num_dims, 4, 1, input_file);
	if (num_read < 1 || num_dims != 2) {
		printf("Problem reading input file.\n");
	}
	num_read = fread(&number_channels, 4, 1, input_file);
	if (num_read < 1) {
		printf("Problem reading input file.\n");
	}
	num_read = fread(&number_timepoints, 4, 1, input_file);
	if (num_read < 1) {
		printf("Problem reading input file.\n");
	}
	//
	//Segmentation calculator
	//
	number_segments = (num_bytes_per_entry*number_channels*number_timepoints) / *ram_limit;
	timepoints_per_segment = number_timepoints / number_segments;
	
	//
	//Segementation machine
	//
	for (int j = 0; j < number_channels; j++) {	
		for (int i = 0; i < number_segments;i++) {
			//Create new file
			FILE *outfile;
			string mystring = "temp/Channel_";
			mystring += to_string(j);
			mystring += "_Segment_";
			mystring += to_string(i);
			mystring += "_.mda";
			const char *name = mystring.c_str();
			printf(name);
			outfile = fopen(name, "wb");
			
			//Read from origin
			float *tmp=(float *)malloc(sizeof(float)*timepoints_per_segment); 
			int problem = fread(tmp,sizeof(float),timepoints_per_segment,input_file); 
			if (problem == 0) printf("Problem reading the data from the original file");
			
			//Write to new file
			fwrite(tmp, sizeof(float), timepoints_per_segment, outfile);
			free(tmp); 
		}
	}
	fclose(input_file);
}

arrayDivider::arrayDivider(const arrayDivider& orig) {
}

arrayDivider::~arrayDivider() {
}





