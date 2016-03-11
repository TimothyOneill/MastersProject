#pragma once
#include <map>
#include <iostream>
#include <fstream>

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