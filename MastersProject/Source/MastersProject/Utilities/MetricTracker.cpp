#include "MastersProject.h"
#include "MastersProjectWorldSettings.h"
#include "MetricTracker.h"

MetricTracker* MetricTracker::_Instance = 0;

// Standard Singleton Declartion.
MetricTracker* MetricTracker::Instance()
{
    if (_Instance == 0)
    {
        _Instance = new MetricTracker();
    }
    return _Instance;
}

MetricTracker::MetricTracker()
{
    FilePath = FPaths::GameDir();
    FileName = Cast<AMastersProjectWorldSettings>(GWorld->GetWorldSettings())->GetFile(); 
    FullPath = FilePath + FileName;
}

// Reports a single metric under current section header with the given unique key.
void MetricTracker::ReportDiscreteMetric(FString key, int value)
{
    std::map<FString, int>::iterator itr = DiscreteValues.find(key);

    if (itr == DiscreteValues.end())
    {
        DiscreteValues.insert({key, value});
    }
    else
    {
        itr->second += value;
    }
}

//reports another metric under the given Key allowing for multiple values under one key in the current section header.
void MetricTracker::ReportContinousMetric(FString key, FString value)
{
    std::map<FString, FString>::iterator itr = ContinuousValues.find(key);

    if (itr == ContinuousValues.end())
    {
        ContinuousValues.insert({ key, value });
    }
    else
    {
        itr->second += value;
    }
}

// Writes all metrics to file under the given section header.
void MetricTracker::WriteMetricsToFile()
{
    if (!File.is_open())
    {
        File.open(*(FullPath), std::fstream::app);
    }

    File << '[' << TCHAR_TO_UTF8(*(SectionName)) << ']' << '\n';

    if (!DiscreteValues.empty() && File.is_open())
    {
        for (auto& e : DiscreteValues)
        {
            File << TCHAR_TO_UTF8(*(e.first)) << '=' << e.second << '\n';
        }
    }

    if (!ContinuousValues.empty())
    {
        for (auto& e : ContinuousValues)
        {
            File << TCHAR_TO_UTF8(*(e.first)) << ",\n" << TCHAR_TO_UTF8(*(e.second)) << '\n';
        }
    }

    File.close();
}

// Wipes the metrics buffers.
void MetricTracker::ClearAllMetrics()
{
    ContinuousValues.clear();
    DiscreteValues.clear();
}

void MetricTracker::ClearSpecificDiscreteMetric(FString key)
{
    DiscreteValues.erase(*(key));
}

void MetricTracker::ClearSpecificContinuousMetric(FString key)
{
    ContinuousValues.erase(*(key));
}

FString MetricTracker::GetSectionName()
{
    return SectionName;
}

void MetricTracker::SetSectionName(FString NewSectionName)
{
    SectionName = NewSectionName;
}
