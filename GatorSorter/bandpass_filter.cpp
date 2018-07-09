#include "bandpass_filter.h"
#include <string>
#include "filt.h"
#include <iostream>
#include <stack>
#include <fstream>

using namespace std;

bandpass_filter::bandpass_filter(int64_t * min_freq, int64_t * max_freq, int64_t * sampling_frequency, int64_t * number_channels, int64_t * number_segments, int64_t * timepoints_per_segment) {
	printf("Bandpass filter started \n");
	Filter *my_filter;
	string mystring;
	FILE *input;
	FILE *output;
	const char *name;
	float raw;
	float filtered;
	
	for (int channel = 0; channel < *number_channels; channel++) { //For every channel 
		for (int segment = 0; segment < *number_segments; segment++) {//For every segment
			my_filter = new Filter(BPF, 5, (double)(*sampling_frequency / 1000), (double)(*min_freq / 1000), (double)(*max_freq / 1000));

			//Find the file name of the raw segmented file
			mystring = "temp/Channel_";
			mystring += to_string(channel);
			mystring += "_Segment_";
			mystring += to_string(segment);
			mystring += "_.mda";
			name = mystring.c_str();

			//Open the segmented raw file
			input = fopen(name, "rb"); 
			if (input == 0) std::cout << "Failed to open file" << endl;
			
			//Creat the file name of the filtered segmented file
			mystring = "temp/filtered_channel_";
			mystring += to_string(channel);
			mystring += "_Segment_";
			mystring += to_string(segment);
			mystring += "_.mda";
			name = mystring.c_str(); 

			//Create a filtered segmented file
			output = fopen(name, "wb");
			if (output == 0) std::cout << "Failed to open file" << endl;


			//Declare our stack
			stack<float> reverse; 
			stack<float> straight;
			
			//Filter data and push to stack
			for (int timepoint = 0; timepoint < *timepoints_per_segment; timepoint++) { //For every timepoint
				int problem = fread(&raw, sizeof(float), 1, input);
				if (problem != 1) {
					std::cout << "Problem reading the data from the segmented raw file: " << problem << endl;
				}
				filtered = my_filter->do_sample(raw);
				reverse.push(filtered);
			}
			free(my_filter);
			my_filter = new Filter(BPF, 5, (double)(*sampling_frequency / 1000), (double)(*min_freq / 1000), (double)(*max_freq / 1000));
			//Filter our data in reverse order
			for (int timepoint = 0; timepoint < *timepoints_per_segment; timepoint++) { //For every timepoint
				filtered = reverse.top();
				reverse.pop();
				filtered = my_filter->do_sample(filtered);
				straight.push(filtered);
			}
			if (reverse.empty() == 0) printf("Problem in the stack system");

			//Write the zero phased data 
			for (int timepoint = 0; timepoint < *timepoints_per_segment; timepoint++) { //For every timepoint
				filtered = straight.top();
				straight.pop();
				int problem2 = fwrite(&filtered, sizeof(float), 1, output);
				if (problem2 != 1) printf("Problem wrtiting the filtered data");
			}
			if (straight.empty() == 0) printf("Problem in the stack system");

			free(my_filter);
			fclose(input);
			fclose(output);
			
		}
	}
	printf("Bandpass filter finished \n");
}

bandpass_filter::bandpass_filter(const bandpass_filter& orig) {
}

bandpass_filter::~bandpass_filter() {
}





