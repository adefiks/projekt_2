#pragma once
#include "common.h"

class Timer
{
private:
    string nameOfSection;
    chrono::time_point<chrono::high_resolution_clock> startOfMeasure;

public:
    Timer(string InputNameOfSection) : nameOfSection(InputNameOfSection)
    {
        startOfMeasure = chrono::high_resolution_clock::now();
    };
    ~Timer()
    {
        StopTimer();
    };

    void StopTimer()
    {
        auto endOfMeasure = chrono::high_resolution_clock::now();

        auto startOfMeasureInMicroSec = chrono::time_point_cast<chrono::microseconds>(startOfMeasure).time_since_epoch().count();
        auto endOfMeasureInMicroSec = chrono::time_point_cast<chrono::microseconds>(endOfMeasure).time_since_epoch().count();

        auto durationOfSectionInMicroSec = endOfMeasureInMicroSec - startOfMeasureInMicroSec;
        auto durationOfSectionInMiliSec = durationOfSectionInMicroSec * 0.001;

        cout << "Section duration in uS: " << durationOfSectionInMicroSec << " mS: " << durationOfSectionInMiliSec << endl;
    }
};
