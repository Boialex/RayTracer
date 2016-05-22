#include "Color.h"
#include <iostream>
#include"HelpFunc.h"

std::istream & operator>>(std::istream & is, Color & c)
{
    int x, y, z;
    is >> x >> y >> z;
    c.red = x / 255.;
    c.green = y / 255.;
    c.blue = z / 255.;
    c.current = Color::ht_rgb;
    return is;
}

Color operator+(const Color & a, const Color & b)
{ 
    return Color(a.red + b.red, a.green + b.green, a.blue + b.blue);
}

Color& operator+=(Color & a, const Color & b)
{
    a.red += b.red;
    a.green += b.green;
    a.blue += b.blue;
    return a;
}

Color& operator*=(Color & a, const double b)
{
    a.red *= b;
    a.green *= b;
    a.blue *= b;
    return a;
}

Color& operator/=(Color & a, const double b)
{
    a.red /= b;
    a.green /= b;
    a.blue /= b;
    return a;
}

void Color::cut()
{
    red = min(red, 100);
}

void Color::convertRGBToXYZ()
{
    //srgb
    if (red > 0.04045)
        red = std::pow((red + 0.055) / 1.055, 2.4);
    else
        red = red / 12.92;
    if (green > 0.04045)
        green = std::pow((green + 0.055) / 1.055, 2.4);
    else
        green = green / 12.92;
    if (blue > 0.04045)
        blue = std::pow((blue + 0.055) / 1.055, 2.4);
    else
        blue = blue / 12.92;

    double x = red, y = green, z = blue;
    red = 0.4124564 * x + 0.3575761 * y + 0.1804375 * z;
    green = 0.2126729 * x + 0.7151522 * y + 0.0721750 * z;
    blue = 0.0193339 * x + 0.1191920 * y + 0.9503041 * z;
    current = ht_xyz;
} 

void Color::convertLabToXYZ()
{
    double xr, yr, zr, e, k;
    double fx, fy, fz;
    e = 0.008856;
    k = 903.3;
    fy = (red + 16) / 116;
    fz = fy - blue / 200;
    fx = green / 500 + fy;
    if (pow(fx, 3) > e)
        xr = pow(fx, 3);
    else
        xr = (116 * fx - 16) / k;
    if (pow(fy, 3) > e)
        yr = pow(fy, 3);
    else
        yr = (116 * fy - 16) / k;
    if (pow(fz, 3) > e)
        zr = pow(fz, 3);
    else
        zr = (116 * fz - 16) / k;

    red = xr * 0.9505;
    green = yr * 1.0000;
    blue = zr * 1.0890;
    current = ht_xyz;
}

void Color::convertLabToRGB()
{
    convertLabToXYZ();
    double x = red, y = green, z = blue;
    red = 3.2404542 * x - 1.5371385 * y - 0.4985314 * z;
    green = -0.9692660 * x + 1.8760108 * y + 0.0415560 * z;
    blue = 0.0556434 * x - 0.2040259 * y + 1.0572252 * z;
    if (red <= 0.0031308)
        red *= 12.92;
    else
        red = 1.055 * pow(red, 1 / 2.4) - 0.055;
    if (green <= 0.0031308)
        green *= 12.92;
    else
        green = 1.055 * pow(green, 1 / 2.4) - 0.055;
    if (blue <= 0.0031308)
        blue *= 12.92;
    else
        blue = 1.055 * pow(blue, 1 / 2.4) - 0.055;
    current = ht_rgb;
}

void Color::convertRGBToLab()
{
    convertRGBToXYZ();
    red /= 0.9505;
    green /= 1.0000;
    blue /= 1.0890;
    double fx, fy, fz, e, k;
    e = 0.008856;
    k = 903.3;
    if (red > e)
        fx = std::pow(red, 1.0 / 3);
    else
        fx = (k * red + 16) / 116;
    if (green > e)
        fy = std::pow(green, 1.0 / 3);
    else
        fy = (k * green + 16) / 116;
    if (blue > e)
        fz = std::pow(blue, 1.0 / 3);
    else
        fz = (k * blue + 16) / 116;

    current = ht_lab;
    red = 116 * fy - 16;
    green = 500 * (fx - fy);
    blue = 200 * (fy - fz);
}