#include <cmath>
#include <iostream>

#include "LSystemPlot.hpp"
#include "LinePlot.hpp"

LSystemPlot::LSystemPlot(double initAngle, double stepSize, double stepAngle) 
    : m_stepSize(stepSize), m_stepAngle_deg(stepAngle) {
    SetPosition(m_defaultPosition);
    SetLineWidth(m_defaultLineWidth);
    this->m_lineCount = 0;
    this->m_pen.direction = initAngle;
    this->m_pen.position = {0, -20};
}

void LSystemPlot::UseGrad(void) {
    this->m_useGrad = true;
    this->m_lineGrad = this->m_defaultLineGrad;
}

void LSystemPlot::SetPosition(const double x, const double y) {
    this->m_pen.position = {x, y};
}

void LSystemPlot::SetPosition(const Point& point) {
    this->m_pen.position = point;
}

void LSystemPlot::LoadModel(std::string* model) {
    this->m_model = model;
}

void LSystemPlot::SetLineGradient(double grad) {
    this->m_lineGrad = grad;
}

void LSystemPlot::SetLineWidth(double width) {
    this->m_pen.width = width;
}

Point LSystemPlot::CalculateNewPoint(void) {
    return {std::cos(m_pen.direction * PI / 180) * this->m_stepSize, std::sin(m_pen.direction * PI / 180) * this->m_stepSize};
}

double LSystemPlot::LogGrad(const uint32_t iter) {
    return (1 + std::log(this->m_lineGrad)) / (1 + std::log(this->m_lineGrad + iter));
}

void LSystemPlot::DrawLine(void) {
    Point t = CalculateNewPoint();

    if (m_useGrad)
        this->m_pen.width *= LogGrad(this->m_pen.iteration);

    Line line(this->m_pen.position, this->m_pen.position + t, m_pen.width, "#FF00FF");
    PlotLine(line);
    Move();

    this->m_pen.iteration++;
}

void LSystemPlot::Move(void) { 
    this->m_pen.position += CalculateNewPoint();
}

void LSystemPlot::Rotate(double angle_deg) {
    this->m_pen.direction += angle_deg;
    while (this->m_pen.direction > 360.0)
        this->m_pen.direction -= 360;
}

void LSystemPlot::Push(void) {
    this->lifo.push_back(this->m_pen);
}

void LSystemPlot::Pop(void) {
    this->m_pen = this->lifo.back();
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
