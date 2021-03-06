#include "WirePlane2D.h"
#include "TMath.h"
#include <cstring>
#include <cstdio>
#include <iostream>
#include <sstream>

#define DEBUG_LEVEL 0

using namespace std;

WirePlane2D::WirePlane2D(string PlaneName, double Height, double Width, double WireAngle,
                         int nWires, int wirecolor, CStransform *trans, double offset, int index)
{
    cst = trans;
    color = wirecolor;
    double th= WireAngle*3.14159/180.0;
    int ind= index;

    /// Width (left to right) = 56.0 cm
    /// Height = 113 cm
    /// Ratio H/w = 2.017857


    double x =  cst->transXtoCX(0.0) - cst->transLtoCL(Width)/2;
    double y =  cst->transYtoCY(0.0) - cst->transLtoCL(Height)/2;

    double a = cst->transLtoCL(Width);
    double b = cst->transLtoCL(Height);

    double os= cst->transLtoCL(offset);

    // n = actual number of wires
    // Num = number of wires that we draw

    if ((nWires/5.0 - int(nWires/5.0))>0) WireNum =  (int) (nWires/5.0) + 1; // must be rounded up
    else WireNum = (int) (nWires/5.0);

//Draw the Wires
    double d;
    double x1,y1,x2,y2,fac;

    if(th==0.0) {
        for(int n=0; n<WireNum; n++) {
            fac=((double)n/(double)WireNum);
            x1=x;
            y1=y+b*(1-fac)-os;
            x2=x+a;
            y2=y+b*(1-fac)-os;
            wires.push_back(new TLine(x1,y1,x2,y2));
            wires[n]->SetLineColor(kGray);
            wires[n]->Draw();
        }
    }



    else if(WireAngle==90.0) {
        for(int n=0; n<WireNum; n++) {
            fac=((double)n/(double)WireNum);
            x1=x+a*fac+os;
            y1=y;
            x2=x+a*fac+os;
            y2=y+b;
            wires.push_back(new TLine(x1,y1,x2,y2));
            wires[n]->SetLineColor(kGray);
            wires[n]->Draw();
        }
    }



    else if(fabs(th)<atan(b/a)) {


        if(WireAngle>0.0 && WireAngle<90.0) {
            d=b+a*tan(th);
            for(int  n=0; n<WireNum; n++) {
                fac=((double)n/(double)WireNum);
                if((a*tan(th)-d*fac)>0) {
                    x1=x;
                    y1=y+b-d*fac;
                    x2=x+d*fac/tan(th);
                    y2=y+b;
                } else if((b-d*fac)<0) {
                    x1=x+(d*fac-b)/tan(th);
                    y1=y;
                    x2=x+a;
                    y2=y+b-d*fac+a*tan(th);
                } else {
                    x1=x;
                    y1=y+b-d*fac;
                    x2=x+a;
                    y2=y+b-d*fac+a*tan(th);
                }
                wires.push_back(new TLine(x1,y1,x2,y2));
                wires[n]->SetLineColor(kGray);
                wires[n]->Draw();
            }
        }


        else if(WireAngle<0.0 && WireAngle>-90.0) {
            th=-th;
            d=b+a*tan(th);

            for(int  n=0; n<WireNum; n++) {
                fac=((double)n/(double)WireNum);

                if((d*fac-a*tan(th))<0) {
                    x1=x+a-d*fac/tan(th);
                    y1=y+b;
                    x2=x+a;
                    y2=y+d*(1-fac)-a*tan(th);
                } else if((d*(1-fac)-a*tan(th))<0) {
                    x2=x+d*(1-fac)/tan(th);
                    y2=y;
                    x1=x;
                    y1=y+d*(1-fac);
                } else {
                    x1=x;
                    y1=y+d*(1-fac);
                    x2=x+a;
                    y2=y+d*(1-fac)-a*tan(th);
                }
                wires.push_back(new TLine(x1,y1,x2,y2));
                wires[n]->SetLineColor(kGray);
                wires[n]->Draw();
            }
        }
    }



    //when fabs(th)>arctan(b/a)
    else {

        if(WireAngle>0.0) {
            d=a+b/tan(th);
            for(int  n=0; n<WireNum; n++) {
                fac=((double)n/(double)WireNum);

                if((d*fac)<(b/tan(th))) {
                    x1=x;
                    y1=y+b-d*fac*tan(th);
                    x2=x+d*fac;
                    y2=y+b;
                } else if((a-d*fac)<0) {
                    x1=x+d*fac-b/tan(th);
                    y1=y;
                    x2=x+a;
                    y2=y+b-(d*fac-a)*tan(th);
                } else {
                    x1=x+d*fac-b/tan(th);
                    y1=y;
                    x2=x+d*fac;
                    y2=y+b;
                }
                wires.push_back(new TLine(x1,y1,x2,y2));
                wires[n]->SetLineColor(kGray);
                wires[n]->Draw();
            }
        }

        else if(WireAngle<0.0) {
            th=-th;
            d=a+b/tan(th);

            for(int  n=0; n<WireNum; n++) {
                fac=((double)n/(double)WireNum);

                if((d*fac-b/tan(th))<0) {
                    x1=x;
                    y1=y+(d*fac)*tan(th);
                    x2=x+d*fac;
                    y2=y;
                } else if((d*fac-a)>0) {
                    x2=x+a;
                    y2=y+(d*fac-a)*tan(th);
                    x1=x+d*fac-b/tan(th);
                    y1=y+b;
                } else {
                    x1=x+d*fac;
                    y1=y;
                    x2=x+d*fac-b/tan(th);
                    y2=y+b;
                }

                wires.push_back(new TLine(x1,y1,x2,y2));
                wires[n]->SetLineColor(kGray);
                wires[n]->Draw();
            }//for loop
        }//else if(WireAngle<0.0)
    }

    //else cerr<< "WirePlane2D construct error.\n";
    //Type name and draw circle represent the WirePlane;
    circ = new TEllipse(x+a+0.02,y+b*(1-(double)ind/6), b*0.03, b*0.03);
    circ->SetFillColor(kGray);
    circ->Draw();

    TLatex *title = new TLatex(x+a+0.035,y+b*(1-(double)ind/6), PlaneName.c_str());
    title->SetTextSize(0.02);
    title->Draw();

}

WirePlane2D::~WirePlane2D()
{
}

void WirePlane2D::WireHit(int Num)
{
    int quotient = (int) Num/5; /// 1 wire drawn for every 5 "real" wires
    if (quotient<WireNum) {
#if DEBUG_LEVEL >= 3
        cout<<"****u1WireHit: "<<quotient<<endl;
#endif
        wires[quotient]->SetLineColor(color);
        wires[quotient]->SetLineWidth(3);
        circ->SetFillColor(color);
    }
}
void WirePlane2D::clear ()
{
    for(int n=0; n< WireNum; n++) {
        wires[n]->SetLineColor(kGray);
        wires[n]->SetLineWidth(1);
    }

    circ->SetFillColor(kGray);
}



