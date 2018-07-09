#include "thresholding.h"
#include <string>
#include <iostream>
#include <stack>
#include <fstream>

using namespace std;

thresholding::thresholding(int64_t * number_channels, int64_t * number_segments, int64_t * timepoints_per_segment, int64_t * absolute_threshold_in_micro_volts, int64_t * threshold_sign) {
	float raw;
	float thresholded;
	string mystring;
	FILE *input;
	FILE *output;
	const char *name;

	//Case 1
	if (*threshold_sign == -1) {
		//Go through every file and every value. If the value is higher than negative "absolute_threshold_in_micro_volts", make it zero.
		//If the value is lower than negative "absolute_threshold_in_micro_volts", make the value positive.
		for (int channel = 0; channel < *number_channels; channel++) { //For every channel 
			for (int segment = 0; segment < *number_segments; segment++) {//For every segment
				//Find the file name of the bandpassed segmented file
				mystring = "temp/filtered_channel_";
				mystring += to_string(channel);
				mystring += "_Segment_";
				mystring += to_string(segment);
				mystring += "_.mda";
				name = mystring.c_str();

				//Open the bandpassed segmented raw file
				input = fopen(name, "rb");
				if (input == 0) std::cout << "Failed to open file" << endl;

				//Create the file name of the thresholded segmented file
				mystring = "temp/thresholded_channel_";
				mystring += to_string(channel);
				mystring += "_Segment_";
				mystring += to_string(segment);
				mystring += "_.mda";
				name = mystring.c_str();

				//Create a thresholded segmented file
				output = fopen(name, "wb");
				if (output == 0) std::cout << "Failed to open file" << endl;

				//Threshold data
				for (int timepoint = 0; timepoint < *timepoints_per_segment; timepoint++) { //For every timepoint
					int problem = fread(&raw, sizeof(float), 1, input);
					if (problem != 1) std::cout << "Problem reading the data from the segmented raw file: " << problem << endl;
					if (raw <= -(*absolute_threshold_in_micro_volts * 10 ^ -6)) {
						thresholded = -raw;
					}
					else {
						thresholded = 0; 
					}
					fwrite(&thresholded, sizeof(float), 1, output);
					
				}

				//Close the files
				fclose(input);
				fclose(output);
			}
		}
	}

	//Case 2
	else if (*threshold_sign == 0) {
		//Go through every file and every value. If the value is higher than positive "absolute_threshold_in_micro_volts", leave it alone. 
		//If the values is lower than negative "absolute_threshold_in_micro_volts", make the value positive. If the value is in between 
		//the positive "absolute_threshold_in_micro_volts" and the negative "absolute_threshold_in_micro_volts", make it zero.
		for (int channel = 0; channel < *number_channels; channel++) { //For every channel 
			for (int segment = 0; segment < *number_segments; segment++) {//For every segment
				//Find the file name of the bandpassed segmented file
				mystring = "temp/filtered_channel_";
				mystring += to_string(channel);
				mystring += "_Segment_";
				mystring += to_string(segment);
				mystring += "_.mda";
				name = mystring.c_str();

				//Open the bandpassed segmented raw file
				input = fopen(name, "rb");
				if (input == 0) std::cout << "Failed to open file" << endl;

				//Create the file name of the thresholded segmented file
				mystring = "temp/thresholded_channel_";
				mystring += to_string(channel);
				mystring += "_Segment_";
				mystring += to_string(segment);
				mystring += "_.mda";
				name = mystring.c_str();

				//Create a thresholded segmented file
				output = fopen(name, "wb");
				if (output == 0) std::cout << "Failed to open file" << endl;

				//Threshold data
				for (int timepoint = 0; timepoint < *timepoints_per_segment; timepoint++) { //For every timepoint
					int problem = fread(&raw, sizeof(float), 1, input);
					if (problem != 1) std::cout << "Problem reading the data from the segmented raw file: " << problem << endl;
					if (raw <= -(*absolute_threshold_in_micro_volts * 10 ^ -6)) {
						thresholded = -raw;
					}
					else if (raw>= (*absolute_threshold_in_micro_volts * 10 ^ -6)) {
						thresholded = raw;
					}
					else {
						thresholded = 0;
					}
					fwrite(&thresholded, sizeof(float), 1, output);
					
				}
				//Close the files
				fclose(input);
				fclose(output);
			}
		}
	}

	//Case 3

	else if (*threshold_sign == 1) {
		//Go through every file and every value. If the value is higher than positive "absolute_threshold_in_micro_volts", leave it alone. 
		//If the value is lower than positive "absolute_threshold_in_micro_volts", make it zero. 
		for (int channel = 0; channel < *number_channels; channel++) { //For every channel 
			for (int segment = 0; segment < *number_segments; segment++) {//For every segment
																		  //Find the file name of the bandpassed segmented file
				mystring = "temp/filtered_channel_";
				mystring += to_string(channel);
				mystring += "_Segment_";
				mystring += to_string(segment);
				mystring += "_.mda";
				name = mystring.c_str();

				//Open the bandpassed segmented raw file
				input = fopen(name, "rb");
				if (input == 0) std::cout << "Failed to open file" << endl;

				//Create the file name of the thresholded segmented file
				mystring = "temp/thresholded_channel_";
				mystring += to_string(channel);
				mystring += "_Segment_";
				mystring += to_string(segment);
				mystring += "_.mda";
				name = mystring.c_str();

				//Create a thresholded segmented file
				output = fopen(name, "wb");
				if (output == 0) std::cout << "Failed to open file" << endl;

				//Threshold data
				for (int timepoint = 0; timepoint < *timepoints_per_segment; timepoint++) { //For every timepoint
					int problem = fread(&raw, sizeof(float), 1, input);
					if (problem != 1) std::cout << "Problem reading the data from the segmented raw file: " << problem << endl;
					if (raw >= (*absolute_threshold_in_micro_volts * 10 ^ -6)) {
						thresholded = raw;
					}
					else {
						thresholded = 0;
					}
					fwrite(&thresholded, sizeof(float), 1, output);
					

				}
				//Close the files
				fclose(input);
				fclose(output);
			}
		}
	}

}

thresholding::thresholding(const thresholding& orig) {
}

thresholding::~thresholding() {
}





