#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>
using namespace std;

//#define q 0x1A0111EA397FE69A4B1BA7B6434BACD764774B84F38512BF6730D2A0F6B0F6241EABFFFEB153FFFFB9FEFFFFFFFFAAAB

//q = 4002409555221667393417789825735904156556882819939007885332058136124031650490837864442687629129015664037894272559787

//#define r 0x73EDA753299D7D483339D80809A1D80553BDA402FFFE5BFEFFFFFFFF00000001

/*  to generate a point 
gx = 0x17F1D3A73197D7942695638C4FA9AC0FC3688C4F9774B905A14E3A3F171BAC586C55E83FF97A1AEFFB3AF00ADB22C6BB mod q

gy = 0x08B3F481E3AAA0F1A09E30ED741D8AE4FCF5E095D5D00AF600DB18CB2C04B3EDD03CC744A2888AE40CAA232946C5E7E1 mod q

*/

//#include "ec.hpp"
#include "ec_bnum.hpp"

//#include "./bignum_lin/bint.hpp"

int main(void)
{

    //std::uniform_int_distribution<unsigned int> dist(0, modulus-1);
    //std::random_device urandom("/dev/urandom");
    //unsigned number = dist(urandom);

    srand((unsigned) time(0));
    //__int64_t  x_coordinate = rand();// % R;
    
    //The y coordinate must be such that y^2 = x^3 + 4 ==> y = sqrt(x^3 + 4)
    //To generate a point over the curve just use gx and gy an then multiply the number by a random scalar within [0,r-1] to obtain a random point
    //AffinePoint Point = AffinePoint(gx, gy);

    /*
    def y_for_x(x, ec=default_ec, FE=Fq):
    """
    Solves y = sqrt(x^3 + ax + b) for both valid ys
    """
    if not isinstance(x, FE):
        x = FE(ec.q, x)

    u = x * x * x + ec.a * x + ec.b

    y = u.modsqrt()
    if y == 0 or not AffinePoint(x, y, False, ec).is_on_curve():
        raise ValueError("No y for point x")
    return y
    */

  
    
    bint q = "4002409555221667393417789825735904156556882819939007885332058136124031650490837864442687629129015664037894272559787";

    bint r = "52435875175126190479447740508185965837690552500527637822603658699938581184513";
    
    bint gx = "3685416753713387016781088315183077757961620795782546409894578378688607592378376318836054947676345821548104185464507"; 
    bint x_coordinate = gx % q;
    
    bint gy = "1339506544944476473020471379941921221584933875938349620426543736416511423956333506472724655353366534992391756441569"; 
    bint y_coordinate = gy % q;

   // bint k = rand()
    bint scalar_k = r- rand();

    AffinePoint Point = AffinePoint(x_coordinate,y_coordinate);
    
    AffinePoint Point_B = AffinePoint::ScalarMult_Big_endian(scalar_k, Point);
    
    std::cout <<"your x number is: "<<Point_B.Get_x()<<"  "<<std::endl;

    return 0;

}
