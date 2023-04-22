#pragma once

#define L_SYSTEM_PLOT_H_
#ifdef L_SYSTEM_PLOT_H_

#include <vector>
#include <cstdint>
#include <memory>
#include <cmath>

#include "LinePlot.hpp"

constexpr double PI = 3.1415926535;

struct Pen {
    Point position;
    double direction;
    double width;
    uint32_t iteration;
};

struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

class LineModifier {
public:
    virtual ~LineModifier() = default;
    virtual void Apply(Pen& pen) = 0;
};

class LineWidth : public LineModifier {
public:
    enum class Deform {
        Constant,
        Log,
    };

public:
    LineWidth() : m_deform(Deform::Constant) {}

    void SetLineGradient(const double coef);
    void SetDeform(const Deform& deform);
    void Apply(Pen& pen) override;

private:
    inline double Log(const uint32_t iteration) {
        return (std::log(1 + m_lineGrad) / std::log(m_lineGrad + iteration));
    }

private:
    double m_lineGrad;
    Deform m_deform;

};

/*
class LineColor : public LineModifier {
public:
    enum class Colors {
        Green,
        Brown,
        Black,
    };

public:
    LineColor(const Color& color = Green);

*/

class LSystemPlot : public LinePlot {
public:
    LSystemPlot(double initAngle = 0, double stepSize = 1, double stepAngle = 90);
    void LoadModel(std::string* model);
    void LoadLineModifier(const std::shared_ptr<LineModifier>& mod);
    void Plot(void);

    void SetLineWidth(const double width);
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

private:
    Pen m_pen;
    std::vector<std::shared_ptr<LineModifier>> m_lineMods;

    std::string* m_model;
    double m_stepSize;
    double m_stepAngle_deg;
    uint32_t m_segCount;

    std::vector<Pen> lifo;

    const double m_defaultLineWidth = 1;
    const Point m_defaultPosition = {0, 0};
};

#endif
