#pragma once
#include <iostream>

struct Color {
    Color() : red(0), green(0), blue(0) {};
    Color(const double red, const double green, const double blue) : red(red), green(green), blue(blue) {};
    Color(const int red, const int green, const int blue) : red(1. * red / 255),
                                                            green(1. * green / 255),
                                                            blue(1. * blue / 255) {};
    friend std::istream& operator>>(std::istream& is, Color& c);
    friend Color operator+(const Color & a, const Color & b);
    friend Color& operator+=(Color & a, const Color & b);
    friend Color& operator*=(Color & a, const double b);
    friend Color& operator/=(Color & a, const double b);
    void cut();

    void convertRGBToXYZ();
    void convertRGBToLab();

    void convertLabToXYZ();
    void convertLabToRGB();

    enum type {
        ht_rgb,
        ht_xyz,
        ht_lab
    } current;

    double red;
    double green;
    double blue;
};
