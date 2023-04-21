#pragma once

#define L_SYSTEM_PLOT_H_
#ifdef L_SYSTEM_PLOT_H_

#include <vector>

#include "LinePlot.hpp"

constexpr double PI = 3.1415926535;

struct Pen {
    Point position;
    double direction;
};

class LSystemPlot : public LinePlot {
public:
    LSystemPlot(double initAngle = 0, double stepSize = 1, double stepAngle = 90);
    void LoadModel(std::string* model);
    void Plot(void);

private:
    Point CalculateNewPoint(void);
    void DrawLine(void);
    void Move(void);
    void Rotate(double angle_deg);
    void Push(void);
    void Pop(void);

private:
    Pen m_pen;

    std::string* m_model;
    double m_stepSize;
    double m_stepAngle_deg;

    std::vector<Pen> lifo;

};

#endif
