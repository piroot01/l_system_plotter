#include <hpdf_types.h>
#include <memory>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

#include "Utils/Timer.hpp"
#include "Utils/Time.hpp"
#include "LibHaruFacade/Colors.hpp"
#include "LibHaruFacade/HpdfApi.hpp"
#include "LSystemInterpreter/Data.hpp"

int main(int argv, char* argc[]) {
    Timer t;

    Hpdf test("out.pdf");
    test.AddPage(100, 100);

    Painter p(test(0));

    LSystemInterpreter::Data::Line line = {{40, 40}, {60, 40}, {60, 60}, {40, 60}, {40, 40}};
    std::vector<LSystemInterpreter::Data::Line> vec;
    vec.push_back(line);

    p.Line(vec, 2, Colors::PastelPurple, HPDF_ROUND_END, HPDF_ROUND_JOIN);

    CurrentTime time("%d-%m-%Y %H:%M:%S");

    p.PageLabel(time.GetCurrentTime(), test.GetFont("Courier-Bold"), 5);

    return 0;
}

