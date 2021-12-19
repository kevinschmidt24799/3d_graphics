//
// Created by Kevin Schmidt on 12/18/21.
//

#include <cmath>
#include "linearization.hpp"
#include <iostream>

Linearization::Linearization(int d1, int d2, int r1, int r2, int i)
: d1_(d1), d2_(d2), r1_(r1), r2_(r2), i_(i)
{
    if (d1_ > d2_)
    {
        i_ = -i_;
    }


    dd_ = d2_ - d1_;
    dr_ = r2_ - r1_;
    rdirection_ = 1;

    if(dr_ < 0)
    {
        dr_ = -dr_;
        rdirection_ = -1;
    }

    D_ = 0;
    d_ = d1_;
    r_ = r1_;

    rincrement_ = abs(dr_/dd_);

    dr_%=dd_;
    dr_ = abs(dr_);
    dd_ = abs(dd_);
}

void Linearization::next()
{
        r_+=rdirection_*rincrement_;
        if(D_ > 0)
        {
            r_+=rdirection_;
            D_-=dd_;
        }
        D_+=dr_;
        d_+=i_;
}

bool test(int d1, int d2, int r1, int r2, int i)
{
    Linearization l(d1,d2,r1,r2, i);
    while(true)
    {
        //std::cout<<l.d_<<", "<<l.r_<<"\n";
        if(l.d_ == l.d2_)
        {
            break;
        }
        l.next();
    }
    //std::cout<<"\n\n";

    return l.r_ == l.r2_;
}

Linfloat::Linfloat(int d1, int d2, float r1, float r2)
:d_(d1), d2_(d2), r_(r1), r2_(r2)
{

    i_ = (d2_ > d_) ? 1 : -1;
    if(d2_==d_){
        rincrement_ = 0;
    }else
    {
        rincrement_ = (r2_ - r_) / (d2_ - d_);
    }
}

void Linfloat::next()
{
    r_ += i_*rincrement_;
    d_ += i_;
}



