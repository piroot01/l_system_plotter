#include <bits/chrono.h>
#include <hpdf.h>
#include <hpdf_objects.h>
#include <hpdf_types.h>
#include <sstream>
#include <vector>
#include <iostream>

#include "Colors.hpp"
#include "Timer.hpp"
#include "HpdfApi.hpp"
#include "Time.hpp"

int main(int argv, char* argc[]) {
    Timer t;
    CurrentTime cr;
    Hpdf test("test.pdf");
    test.AddPage();

    Painter p(test.GetPage(0));
    p.Line({10, 10}, {245, 245}, 2, Colors::Blue, HPDF_ROUND_END);
    p.PageLabel(std::string(argc[0]) + " - " + cr.GetCurrentTime(), test.GetFont("Courier-Bold"), 6);
}
