/*
  ==============================================================================

    Filter.h
    Created: 5 Jul 2020 7:20:18pm
    Author:  August

  ==============================================================================
*/

#pragma once
class AbstractFilter
{
public:
    AbstractFilter() : OldFreq(0.0), OldRes(0.0)
    { }
    ~AbstractFilter()
    {}
    inline static void SetSampleRate(double Rate) { sampleRate = Rate; };
    void UpdateValues(double CutOff, double Res)
    {
        if (CutOff == OldFreq && Res == OldRes) return;
        OldFreq = CutOff; OldRes = Res;
        UpdateParameters(CutOff, Res);
    }
private:
    double OldFreq;
    double OldRes;
protected:
    virtual void UpdateParameters(double CutOff, double Res) = 0;
    static double sampleRate;
};
