
/*The implementation is based in the Python code written in 
https://github.com/Chia-Network/bls-signatures/tree/main/python-impl*/


#ifndef EC_BNUM_HPP
#define EC_BNUM_HPP




#include "./bignum_lin/bint.hpp"



class AffinePoint
{

    private:

        //static unsigned x;
        bint x;
        //static unsigned y;
        bint y;

        bool is_infinity;

	bint q = "4002409555221667393417789825735904156556882819939007885332058136124031650490837864442687629129015664037894272559787";

	bint r = "52435875175126190479447740508185965837690552500527637822603658699938581184513";
    
    public:

        AffinePoint()
        {
            x = 0;
            y = 0;

            is_infinity = true;
        }
        
        AffinePoint(bint X, bint Y)
        {
            x = X % q; //it must be reduced modulus R
            y = Y % q;

            if (X == 0 && Y ==0)
            {
                is_infinity = true;
            }
            else is_infinity = false;
        }
        
        void Set_x(bint X)
        {
            x = X;
        }
        
        void Set_y(bint Y)
        {
            y = Y;
        }

        bint Get_x(void){return x;}
        bint Get_y(void){return y;}
        
        static bool is_on_curve(AffinePoint &P)
        {
            //Check that y^2 = x^3 + ax + b
            if (P.is_infinity)
                return true;

            bint x_coordinate = P.Get_x();
            bint y_coordinate = P.Get_y();

            bint left = y_coordinate * y_coordinate;
            //unsigned right = P.x * P.x * P.x + P.ec.a * P.x + P.ec.b;
            bint right = x_coordinate * x_coordinate * x_coordinate + 4;

            return left == right;
        }

        static AffinePoint AddPoints(AffinePoint &P1 , AffinePoint &P2)
        {
            if (P1.is_infinity)
                return P2;

            if (P2.is_infinity)
                return P1;

            bint x1 = P1.Get_x();
            bint y1 = P1.Get_y();
            bint x2 = P2.Get_x();
            bint y2 = P2.Get_y();
            
            if (x1 == x2 && y1 == y2)
                return AffineDoublePoint(P1);

            if (x1 == x2)
                return AffinePoint();


            bint s = (y2 - y1) / (x2 - x1);

            bint new_x = s * s - x1 - x2;
            bint new_y = s * (x1 - new_x) - y1;

            return AffinePoint(new_x, new_y);

        }

        static AffinePoint AffineDoublePoint(AffinePoint &P)
        {

            bint x_coordinate = P.Get_x();
            bint y_coordinate = P.Get_y();
            //unsigned left = Fq(ec.q, 3) * x * x;//Fq class
            bint left = 3 * x_coordinate * x_coordinate;
            //left = left + ec.a; in this case a = 0
            //s = left / (Fq(ec.q, 2) * y)
            bint s = left / 2 * y_coordinate;
            bint new_x = s * s - x_coordinate - x_coordinate;
            bint new_y = s * (x_coordinate - new_x) - y_coordinate;

            return AffinePoint(new_x, new_y);

        }


        /*Big-endian format
        Q := 0
        for i = k ... 0:
            Q := double(Q)
            if(d_i = 1)
                Q := add(Q, P)
        return Q*/
        static AffinePoint ScalarMult_Big_endian(bint k , AffinePoint &P)
        {
            AffinePoint Result = AffinePoint();
            //unsigned i;
            while (k > 0)
            {

                if (k % 2 == 0)
                    Result = AffineDoublePoint(Result);
                Result = AddPoints(Result, P);
                k = k / 2;
            }
            return Result;
            /*for (i = 1 << 31 ; i > 0 ; i >>= 1)
            {
                Result = AffineDoublePoint(Result);
                if (k & i)
                    Result = AddPoints(Result, P);
            }
            return Result;*/


        }
        
        /*Little-endian version
        Q := 0
        R := P
        for i = 0 .. k:
            if(d_i = 1)
                Q = add(Q, R)
            R = double(R)
        return Q
        */
        /*static AffinePoint ScalarMult_Little_endian(const bint k , AffinePoint &P)
        {
            
            bint scalar = k;
            if (P.is_infinity || k == 0)//k % q == 0)
                return AffinePoint(0,0);
            AffinePoint Result = AffinePoint();
            AffinePoint Addend = AffinePoint(P.Get_x(),P.Get_y());
            while(scalar > 0)
            {
                if(scalar & 1)
                {
                    Result = AddPoints(Result, P);
                }
                Addend = AffineDoublePoint(Addend);
                scalar >>= 1;
            }
            return Result;
        }*/

        /*AffinePoint ScalarMult(const bint &k , const AffinePoint &P)
        {
            if (k == 0 || P.is_infinity)
                return AffinePoint(0,0);

            if ( k == 1)
                return P;

            if ( k % 2 == 1) {return AffinePoint::AddPoints(P, AffinePoint::ScalarMult( k - 1, P));}
            else {return AffinePoint::ScalarMult( k >> 1, AffinePoint::AffineDoublePoint(P) );}

        }*/

};

#endif //EC_HPP
