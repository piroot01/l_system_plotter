#include <cmath>
#include <iostream>
#include <memory>

#include "LSystemPlot.hpp"
#include "LinePlot.hpp"

LSystemPlot::LSystemPlot(double initAngle, double stepSize, double stepAngle) 
    : m_stepSize(stepSize), m_stepAngle_deg(stepAngle) {
    SetPosition(m_defaultPosition);
    SetLineWidth(m_defaultLineWidth);
    m_pen.direction = initAngle;
    m_pen.position = {0, -20};
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

void LSystemPlot::LoadLineModifier(const std::shared_ptr<LineModifier>& mod) {
    m_lineMods.push_back(mod);
}

void LSystemPlot::SetLineWidth(double width) {
    m_pen.width = width;
}

Point LSystemPlot::CalculateNewPoint(void) {
    return {std::cos(m_pen.direction * PI / 180) * m_stepSize, std::sin(m_pen.direction * PI / 180) * m_stepSize};
}

void LSystemPlot::DrawLine(void) {
    Point t = CalculateNewPoint();

    for (const auto& i : m_lineMods)
        i->Apply(m_pen);

    Line line(m_pen.position, m_pen.position + t, m_pen.width, "#FF00FF");
    PlotLine(line);
    Move();

    m_pen.iteration++;
    m_segCount++;
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

    std::cout << m_segCount << '\n';

    LinePlot::Execute();
}

void LineWidth::SetLineGradient(const double coef) {
    m_lineGrad = std::pow(10, coef);
}

void LineWidth::SetDeform(const Deform& deform) {
    m_deform = deform;
}

void LineWidth::Apply(Pen& pen) {
    switch (m_deform) {
    case Deform::Constant:
        return;
    case Deform::Log:
        pen.width *= Log(pen.iteration);
        break;
    }
}
