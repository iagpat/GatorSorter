#include "get_spike_peaks.h"
#include <string>
#include <omp.h>
#include <iostream>
#include <stack>
#include <fstream>

using namespace std;

get_spike_peaks::get_spike_peaks(int64_t * min_freq, int64_t * sampling_frequency, int64_t * number_channels, int64_t * number_segments, int64_t * timepoints_per_segment) {
	std::cout << "Module started: get_spike_peaks" << std::endl;

	#pragma omp parallel for
	for (int channel = 0; channel < *number_channels; channel++) { //For every channel 
		#pragma omp parallel for
		for (int segment = 0; segment < *number_segments; segment++) {//For every segment
			max_length_of_event = 0.25 * (*sampling_frequency / *min_freq);
			string mystring;
			FILE *input;
			FILE *indices;
			FILE *corresponding_voltages;
			const char *name;
			float raw;
			int64_t index = 0;
			int64_t counter = 0;
			float local_max_voltage = 0;
			//Find the file name of the thresholded file
			mystring = "temp/thresholded_channel_";
			mystring += to_string(channel);
			mystring += "_Segment_";
			mystring += to_string(segment);
			mystring += "_.mda";
			name = mystring.c_str();

			//Open the segmented raw file
			input = fopen(name, "rb");
			if (input == 0) std::cout << "Failed to open file" << endl;

			//Create the file name of the indices file
			mystring = "temp/peak_indices_channel_";
			mystring += to_string(channel);
			mystring += "_Segment_";
			mystring += to_string(segment);
			mystring += "_.mda";
			name = mystring.c_str();

			//Create a filtered segmented file
			indices = fopen(name, "wb");
			if (indices == 0) std::cout << "Failed to open file" << endl;

			//Create the file name of the peak voltages file
			mystring = "temp/peak_voltages_channel_";
			mystring += to_string(channel);
			mystring += "_Segment_";
			mystring += to_string(segment);
			mystring += "_.mda";
			name = mystring.c_str();

			//Create a filtered segmented file
			corresponding_voltages = fopen(name, "wb");
			if (corresponding_voltages == 0) std::cout << "Failed to open file" << endl;

			//Find the peaks
			for (int timepoint = 0; timepoint < *timepoints_per_segment; timepoint++) { //For every timepoint
				
				//Read the data
				int problem = fread(&raw, sizeof(float), 1, input);
				if (problem != 1) { std::cout << "Problem reading the data" << problem << endl;}
				
				//std::cout << raw << std::endl; //Debugging


				if ((raw>local_max_voltage) && (counter<=max_length_of_event)) { //We found a peak
					local_max_voltage = raw;
					index = timepoint;
					counter++;
				}
				else if ((raw<=local_max_voltage) && (raw>0) && (counter<=max_length_of_event)) { //We didn't find a peak but we also didn't finish the event
					counter++;
				}
				else if (local_max_voltage>0){ //Action potential is finished
					//Write the data
					int problem2 = fwrite(&index, sizeof(int64_t), 1, indices);
					if (problem2 != 1) printf("Problem writing the indices");
					
					int problem3 = fwrite(&local_max_voltage, sizeof(float), 1, corresponding_voltages);
					if (problem3 != 1) printf("Problem writing the corresponding voltages");
					
					counter = 0;
					local_max_voltage = 0;
					index = 0;
				}
			}
			fclose(input);
			fclose(indices);
			fclose(corresponding_voltages);
		}
	}

	std::cout << "Module ended: get_spike_peaks" << std::endl;
}

get_spike_peaks::get_spike_peaks(const get_spike_peaks& orig) {
}

get_spike_peaks::~get_spike_peaks() {
}





