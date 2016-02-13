#include "MastersProject.h"
#include "MastersProjectWorldSettings.h"
#include "MetricTracker.h"

MetricTracker* MetricTracker::_Instance = 0;

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

void MetricTracker::ClearMetrics()
{
    SectionName = "";
    ContinuousValues.clear();
    DiscreteValues.clear();
}

FString MetricTracker::GetSectionName()
{
    return SectionName;
}

void MetricTracker::SetSectionName(FString NewSectionName)
{
    SectionName = NewSectionName;
}
