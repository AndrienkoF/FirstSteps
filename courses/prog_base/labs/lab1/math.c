#include <math.h>

double calc(double x, double y, double z) {
   double a;

   if (x==y || (x==0 && y==0) || z==0 || (x<=0 && y<=0 ) || x==-y  )
 {
     return NAN;
 }

 else {
    a = (pow(x, (y + 1))) / (pow((x - y), (1 / z))) + y / (2 * abs(x + y)) + pow((2 + sin(y)), cos(x) / z + abs(x - y)); }
     return a;
}
