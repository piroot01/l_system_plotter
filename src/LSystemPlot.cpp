#include <cmath>
#include <iostream>

#include "LSystemPlot.hpp"
#include "LinePlot.hpp"

LSystemPlot::LSystemPlot(double initAngle, double stepSize, double stepAngle) 
    : m_stepSize(stepSize), m_stepAngle_deg(stepAngle) {
    SetPosition(m_defaultPosition);
    SetLineWidth(m_defaultLineWidth);
    m_lineCount = 0;
    m_pen.direction = initAngle;
    m_pen.position = {0, -20};
}

void LSystemPlot::UseGrad(void) {
    m_useGrad = true;
}

void LSystemPlot::SetPosition(const double x, const double y) {
    m_pen.position = {x, y};
}

void LSystemPlot::SetPosition(const Point& point) {
    m_pen.position = point;
}

void LSystemPlot::LoadModel(std::string* model) {
    m_model = model;
}

void LSystemPlot::SetLineGradient(double grad) {
    m_widthMod.SetLineGradient(grad);
}

void LSystemPlot::SetLineWidth(double width) {
    m_pen.width = width;
}

Point LSystemPlot::CalculateNewPoint(void) {
    return {std::cos(m_pen.direction * PI / 180) * m_stepSize, std::sin(m_pen.direction * PI / 180) * m_stepSize};
}

void LSystemPlot::DrawLine(void) {
    Point t = CalculateNewPoint();

    if (m_useGrad)
        m_pen.width *= m_widthMod.LogGrad(m_pen.iteration);

    Line line(m_pen.position, m_pen.position + t, m_pen.width, "#FF00FF");
    PlotLine(line);
    Move();

    m_pen.iteration++;
}

void LSystemPlot::Move(void) { 
    m_pen.position += CalculateNewPoint();
}

void LSystemPlot::Rotate(double angle_deg) {
    m_pen.direction += angle_deg;
    while (m_pen.direction > 360.0)
        m_pen.direction -= 360;
}

void LSystemPlot::Push(void) {
    this->lifo.push_back(m_pen);
}

void LSystemPlot::Pop(void) {
    m_pen = this->lifo.back();
    this->lifo.pop_back();
}

void LSystemPlot::Plot(void) {
    for (const auto& i : *m_model) {
        if (i >= 'A' and i <= 'U')
            DrawLine();
        else if (i >= 'a' and i <= 'u')
            Move();
        else if (i == '|')
            Rotate(180);
        else if (i == '+')
            Rotate(m_stepAngle_deg);
        else if (i == '-')
            Rotate(-m_stepAngle_deg);
        else if (i == '[')
            Push();
        else if (i == ']')
            Pop();
        else
            continue;
    }

    LinePlot::Execute();
}

void LineModifier::LineWidth::SetLineGradient(const double grad) {
    m_lineGrad = grad;
}

double LineModifier::LineWidth::LogGrad(const uint32_t iteration) {
    return (1 + std::log(m_lineGrad)) / (1 + std::log(m_lineGrad + iteration));
}
