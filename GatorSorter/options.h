#include <string>
#ifndef OPTIONS_H
#define OPTIONS_H


using namespace std;

class options {
public:
	options();
	options(const options& orig);
    virtual ~options();
	int64_t min_freq = 300;
	int64_t max_freq = 6000;
	int64_t sampling_frequency = 24414;
	int64_t ram_limit = 1000000000;
private:

};

#endif /* OPTIONS_H */

