#pragma once
#include <map>
#include <iostream>
#include <fstream>

/**
* MetricTracker is a singlton allowing it to be accesed anywhere
* Allows setting of fileName,section names, metrics.

* Stores metrics in a buffer and writes to file later when called
* due to low amount of metrics being reported gives a smaller performance save
* rather than writing 1-3 numbers to files every tick

**/

class MetricTracker
{
public:

    static MetricTracker* Instance();

    void ReportDiscreteMetric(FString key, int value);
    void ReportContinousMetric(FString key, FString value);

    void WriteMetricsToFile();
    void ClearAllMetrics();
    void ClearSpecificDiscreteMetric(FString key);
    void ClearSpecificContinuousMetric(FString key);

    FString GetSectionName();
    void SetSectionName(FString NewSectionName);

protected:

    MetricTracker();

private:

    static MetricTracker* _Instance;

    FString SectionName = "";
    std::map<FString, int> DiscreteValues;
    std::map<FString, FString> ContinuousValues;
    std::ofstream File;
    FString FilePath = "";
    FString FileName = "TestMetrics.txt";
    FString FullPath = "";
};