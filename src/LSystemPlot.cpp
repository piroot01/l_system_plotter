#include <cmath>
#include <iostream>

#include "LSystemPlot.hpp"
#include "LinePlot.hpp"

LSystemPlot::LSystemPlot(double initAngle, double stepSize, double stepAngle) 
    : m_stepSize(stepSize), m_stepAngle_deg(stepAngle) {
    m_pen.direction = initAngle;
    m_pen.position = {-20, 0};
}

void LSystemPlot::LoadModel(std::string* model) {
    this->m_model = model;
}

Point LSystemPlot::CalculateNewPoint(void) {
    return {std::cos(m_pen.direction * PI / 180) * this->m_stepSize, std::sin(m_pen.direction * PI / 180) * this->m_stepSize};
}

void LSystemPlot::DrawLine(void) {
    Point t = CalculateNewPoint();
    Line line(this->m_pen.position, this->m_pen.position + t);
    PlotLine(line);
    Move();
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
