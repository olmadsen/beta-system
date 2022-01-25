#include <iostream>

template<int M, int K, int S> struct Unit { // a unit in the MKS system
   enum { m=M, kg=K, s=S };          
};
 
template<typename Unit> // a magnitude with a unit
struct Value {
   double val;                            // the magnitude
   explicit Value  (double d) : val(d) {} // construct a Value from a double
};

using Meter = Value<Unit<1,0,0>>;
using Second = Value<Unit<0,0,1>>;
using Speed = Value<Unit<1,0,-1>>; // meters dividend by seconds
using SquareMeter = Value<Unit<2,0,0>>;
Meter operator"" _m(long double d) { return Meter(d); };
// "literal operator" defined the meaning of a suffix for a literal
// Now 1.2m is 1.2 meters.

Second operator"" _s(long double d) { return Second(d); };  
// Now 0.5_s is 0.5 secobnds.

Speed operator/(Meter m, Second s) { return Speed(m.val/s.val); };
SquareMeter operator*(Meter m1, Meter m2) { return SquareMeter(m1.val * m2.val); };

int main() {
    std::cout << "Hello World!\n";
    Meter mx = 1.2_m;
    printf("%f\n",mx);
    Second sx = 0.5_s;
    printf("%f\n",sx); 
    Speed s = 1.2_m / 0.5_s;
    printf("%f\n",s);
    SquareMeter a = 1.2_m * 1.2_m;
    printf("%f\n",a);            
    return 0;
}
