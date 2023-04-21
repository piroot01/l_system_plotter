
#include "LSystemPlot.hpp"
#include "LinePlot.hpp"

LSystemPlot::LSystemPlot(double initAngle, double stepSize, double stepAngle) 
    : m_initAngle_deg(initAngle), m_stepSize(stepSize), m_stepAngle_deg(stepAngle) {
    LinePlot();
}

void LSystemPlot::LoadModel(std::string* model) {
    this->m_model = model;
}

void Plot(void) {
}
