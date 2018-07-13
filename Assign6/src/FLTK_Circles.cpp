////============================================================================
// Name        : Moore6.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Implementation of Assignment 6, FLTK programming to create circles
//
//============================================================================
//

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include "Simple_window.h"    // get access to our window library
#include "Graph.h"       // get access to our graphics library facilities
#include "std_lib_facilities.h"
//------------------------------------------------------------------------------
using namespace std;
int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib
    srand(time(0));
    Point tl(100,100);           // to become top left  corner of window
    int R=200;
    constexpr double Pi = 3.141592653589;
 	int generations;

    while(true){

    	cout<<"Please enter the number of inner circle generations:";
    	cin>>generations;
    	if(generations<0){break;}

    	Simple_window win(tl,500,500,"Canvas");    // make a simple window

    	Circle a(Point(250,250),R);
    	a.set_color(Color(rand()%255));
    	a.set_style(Line_style(Line_style::solid,2));
    	win.attach(a);

    	ostringstream oss;
    	oss << "After " << generations << " ring" <<
   	  	((generations==1||generations==0)?"":"s")<<" generation";
      	Text phrase(Point(180,480),oss.str());
      	win.attach(phrase);
      	phrase.set_font_size(15);
      	phrase.set_color(Color::black);

    	vector<Graph_lib::Circle*>circs;
// center of the circle
    	int x_o=250;
    	int y_o=250;
//coordinates for the inner circles
    	double x = 250;
    	double y = 250;
//coordinates for the outer circle
    	double Rx = 250;
    	double Ry = 250;
//Inner circle generations
    	for(int j = 0; j<generations; ++j){
 	    	int num = rand()%40;
 	    	double theta=0;
 	    	double r = 0;
      		for(double i=0; i<num; ++i){
    			theta = ((2*Pi)/num)*i;
    			r = (R*sin(Pi/num))/(1+sin(Pi/num));
       			Rx = x_o + (R*cos(theta));
    			Ry = y_o + (R * sin(theta));
    			x = Rx - (r*cos(theta));
    			y = Ry - (r*sin(theta));
       			Graph_lib::Circle* c = new Graph_lib::Circle(Point(x,y),r);
    			c->set_color(Color(rand()%255));
    			c->set_style(Line_style(Line_style::solid,2));
    			win.attach(*c);
    			circs.push_back(c);
    		}
    	}

    	win.wait_for_button();       // give control to the display engine
    	for(unsigned int i=0; i< circs.size();++i){
    	    	win.detach(*circs[i]);
    	    	delete circs[i];
    	}
    }
}

//------------------------------------------------------------------------------
