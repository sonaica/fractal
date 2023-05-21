#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Complex {
 private:
  double re, im;

 public:
  Complex(double re_, double im_) {
    re = re_;
    im = im_;
  }
  Complex operator+(const Complex& complex) const {
    return Complex(re + complex.re, im + complex.im);
  }
  Complex operator*(const Complex& complex) const {
    return Complex(re * complex.re - im * complex.im,
                   im * complex.re + re * complex.im);
  }
  double mod() { return sqrt(re * re + im * im); }
};
