#include <string>
#ifndef THRESHOLDING_H
#define THRESHOLDING_H


using namespace std;

class thresholding {
public:
	thresholding(int64_t * number_channels, int64_t * number_segments, int64_t * absolute_threshold_in_micro_volts, int64_t * threshold_sign);
	thresholding(const thresholding& orig);
    virtual ~thresholding();
private:
};

#endif /* BANDPASS_FILTER_H */

