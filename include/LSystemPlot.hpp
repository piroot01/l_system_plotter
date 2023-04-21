#pragma once

#define L_SYSTEM_PLOT_H_
#ifdef L_SYSTEM_PLOT_H_

#include <vector>

#include "LinePlot.hpp"

constexpr double PI = 3.1415926535;

struct Pen {
    Point position;
    double direction;
    double width;
    uint32_t iteration;
};

class LSystemPlot : public LinePlot {
public:
    LSystemPlot(double initAngle = 0, double stepSize = 1, double stepAngle = 90);
    void LoadModel(std::string* model);
    void Plot(void);

    void SetLineWidth(const double width);
    void SetLineGradient(const double grad);
    void SetPosition(const double x, const double y);
    void SetPosition(const Point& position);

    void UseGrad(void);

private:
    Point CalculateNewPoint(void);
    void DrawLine(void);
    void Move(void);
    void Rotate(double angle_deg);
    void Push(void);
    void Pop(void);
    double LogGrad(const uint32_t iter);

private:
    Pen m_pen;

    std::string* m_model;
    double m_stepSize;
    double m_stepAngle_deg;
    uint32_t m_lineCount;

    std::vector<Pen> lifo;

    double m_lineGrad;
    bool m_useGrad = false;

    const double m_defaultLineWidth = 1;
    const double m_defaultLineGrad = 100;
    const Point m_defaultPosition = {0, 0};
};

#endif
