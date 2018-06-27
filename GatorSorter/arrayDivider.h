#include <string>
#ifndef ARRAYDIVIDER_H
#define ARRAYDIVIDER_H


using namespace std;

class arrayDivider {
public:
    arrayDivider(char const *path, int sampling_frequency);
    arrayDivider(const arrayDivider& orig);
    int number_channels;
    int number_timepoints;   
    int number_segments;

    virtual ~arrayDivider();
private:

};

#endif /* ARRAYDIVIDER_H */

