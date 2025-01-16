#pragma once
#include <iostream>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <map>
#include <cstdlib>
#include <cstring>
double func (double x,double a){
    return a * exp(x) - 4*(x*x);
}

double derivative (double x,double a){
    return a * exp(x) - 8*x;
}