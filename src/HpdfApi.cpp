#include <hpdf.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>

#include "HpdfApi.hpp"
#include "Timer.hpp"
#include "Colors.hpp"

Hpdf::Hpdf(const std::string& outName) : m_outName(outName) {
    m_pdf = HPDF_New(errorHandler, nullptr);
    if (!m_pdf)
        throw HpdfException("HPDF_New failed");
};

Hpdf::~Hpdf() {
    if (m_pdf != nullptr) {
        HPDF_SaveToFile(m_pdf, m_outName.c_str());
        HPDF_Free(m_pdf);
    }
}

void Hpdf::OutName(const std::string& outName) {
    m_outName = outName;
}

void Hpdf::AddPage(HPDF_REAL pageWidth, HPDF_REAL pageHeight) {
    HPDF_Page page = HPDF_AddPage(m_pdf);
    HPDF_Page_SetWidth(page, pageWidth);
    HPDF_Page_SetHeight(page, pageHeight);
    m_pages.push_back(page);
}

void Hpdf::SetSize(std::size_t pageNum, HPDF_REAL pageHeight, HPDF_REAL pageWidth) {
    try {
        HPDF_Page& page = m_pages.at(pageNum);
        HPDF_Page_SetHeight(page, pageHeight);
        HPDF_Page_SetWidth(page, pageWidth);
    } catch (std::out_of_range&) {
        throw HpdfException("Page number out of range");
    }
}

HPDF_Font Hpdf::GetFont(const std::string& fontName) const {
    return HPDF_GetFont(m_pdf, fontName.c_str(), nullptr);
}

HPDF_Page* Hpdf::GetPage(std::size_t pageNum) { 
    try {
        return &m_pages.at(pageNum);
    } catch (std::out_of_range&) {
        throw HpdfException("Page number out of range");
    }
}

HPDF_Page* Hpdf::operator()(std::size_t pageNum) {
    try {
        return &m_pages.at(pageNum);
    } catch (std::out_of_range&) {
        throw HpdfException("Page number out of range");
    }
}

void Hpdf::errorHandler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void* user_data) {
    std::stringstream errorMessage;
    errorMessage << "ERROR: error_no = 0x" << std::hex << std::uppercase << error_no << ", detail_no = " << detail_no;
    throw HpdfException(errorMessage.str());
}

void Painter::Line(const Point& a, const Point& b, const HPDF_REAL lineWidth, const Color& color, const HPDF_LineCap lineCap) {
    HPDF_Page_SetLineWidth(*m_page, lineWidth);
    HPDF_Page_SetRGBStroke(*m_page, color.red, color.green, color.blue);
    HPDF_Page_SetLineCap(*m_page, lineCap);

    HPDF_Page_MoveTo(*m_page, a.x, a.y);
    HPDF_Page_LineTo(*m_page, b.x, b.y);
    HPDF_Page_Stroke(*m_page);
};

void Painter::Line(const std::vector<Point>& line, const HPDF_REAL lineWidth, const Color& color, const HPDF_LineCap lineCap, const HPDF_LineJoin lineJoin) {
    if (line.empty())
        return;

    HPDF_Page_SetLineWidth(*m_page, lineWidth);
    HPDF_Page_SetRGBStroke(*m_page, color.red, color.green, color.blue);
    HPDF_Page_SetLineCap(*m_page, lineCap);
    HPDF_Page_SetLineJoin(*m_page, lineJoin);

    auto prevPoint = line.cbegin();
    HPDF_Page_MoveTo(*m_page, prevPoint->x, prevPoint->y);
    

    for (auto point = std::next(line.cbegin()); point != line.cend(); ++point) {
        HPDF_Page_LineTo(*m_page, point->x, point->y);
        prevPoint++;
    }

    HPDF_Page_Stroke(*m_page);
}

void Painter::PageFill(const Color& color) {
    HPDF_Page_SetRGBFill(*m_page, color.red, color.green, color.blue);
    HPDF_Page_Rectangle(*m_page, 0, 0, HPDF_Page_GetWidth(*m_page), HPDF_Page_GetHeight(*m_page));
    HPDF_Page_Fill(*m_page);
}

void Painter::PageLabel(const std::string& text, const HPDF_Font fontName, const HPDF_REAL fontSize, const Color& color) {
    HPDF_Page_SetFontAndSize(*m_page, fontName, fontSize);
    HPDF_Page_SetRGBFill(*m_page, color.red, color.green, color.blue);

    HPDF_REAL textWidth = HPDF_Page_TextWidth(*m_page, text.c_str());
    HPDF_REAL leftPadding = 5;
    HPDF_REAL bottomPadding = 5;

    HPDF_Page_BeginText(*m_page);
    HPDF_Page_TextOut(*m_page, HPDF_Page_GetWidth(*m_page) - textWidth - leftPadding, bottomPadding, text.c_str());
    HPDF_Page_EndText(*m_page);
}

