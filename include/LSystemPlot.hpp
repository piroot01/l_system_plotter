#pragma once

#define L_SYSTEM_PLOT_H_
#ifdef L_SYSTEM_PLOT_H_

#include "LinePlot.hpp"

class LSystemPlot : public LinePlot {
public:
    LSystemPlot(double initAngle = 0, double stepSize = 1, double stepAngle = 90);
    void LoadModel(std::string* model);
    void Plot(void);

private:
    Point m_pen;
    double m_dir;

    std::string* m_model;
    double m_initAngle_deg;
    double m_stepSize;
    double m_stepAngle_deg;

};

#endif
