#pragma once

#define HPDF_API_H_
#ifdef HPDF_API_H_

#include <string>
#include <stdexcept>
#include <vector>
#include <hpdf.h>

#include "Colors.hpp"

class HpdfException : public std::runtime_error {
public:
    explicit HpdfException(const std::string& message) : std::runtime_error(message) {}

};

class Hpdf {
public:
    Hpdf(const std::string& outName = "out.pdf");
    ~Hpdf();

    void OutName(const std::string& outName = "out.pdf");
    void AddPage(HPDF_REAL pageWidth = 255, HPDF_REAL pageHeight = 255);
    void SetSize(std::size_t pageNum = 0, HPDF_REAL pageWidth = 255, HPDF_REAL pageHeight = 255);
    HPDF_Font GetFont(const std::string& fontName) const;
    HPDF_Page* GetPage(std::size_t pageNum = 0);

    Hpdf(const Hpdf&) = delete;
    Hpdf(const Hpdf&&) = delete;
    Hpdf& operator=(const Hpdf&) = delete;
    Hpdf& operator=(Hpdf&&) = delete;

    HPDF_Page* operator()(std::size_t pageNum);

private:
    static void errorHandler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void* user_data);

    std::string m_outName;
    HPDF_Doc m_pdf;
    std::vector<HPDF_Page> m_pages;

};

struct Point {
    Point(float x, float y) : x(x), y(y) {}
    float x;
    float y;
};

class Painter {
public:
    Painter(HPDF_Page* page) : m_page(page) {}
    ~Painter() = default;

    void Line(const Point& a, const Point& b, const HPDF_REAL lineWidth = 1, const Color& color = Colors::Black, const HPDF_LineCap lineCap = HPDF_BUTT_END);
    void Line(const std::vector<Point>& line, const HPDF_REAL lineWidth = 1, const Color& color = Colors::Black, const HPDF_LineCap lineCap = HPDF_BUTT_END, const HPDF_LineJoin lineJoin = HPDF_MITER_JOIN);
    void PageFill(const Color& color);
    void PageLabel(const std::string& text, const HPDF_Font fontName, const HPDF_REAL fontSize = 8, const Color& color = Colors::Black);

    Painter(const Painter&) = delete;
    Painter& operator=(const Painter&) = delete;
    Painter(const Painter&&) = delete;
    Painter& operator=(const Painter&&) = delete;

private:
    HPDF_Page* m_page;

};

#endif