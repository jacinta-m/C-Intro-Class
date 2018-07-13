////============================================================================
// Name        : Moore7.cpp
// Author      :Jacinta. Moore
// Version     :
// Copyright   : Your copyright notice
// Description : Implementation of Assignment 7, Buffon's Needle, Akira's Version
//				This program estimates Pi.
//============================================================================

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Graph.h"         // get access to our graphics library facilities
#include "GUI.h"
#include "Window.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;
using namespace std;

//------------------------------------------------------------------------------

struct Needle_window :Graph_lib:: Window {
    Needle_window(Point xy, int w, int h, const string& title );
private:
    int mx;
    int my;
    vector<Point*>nmiddle;
    vector<Line*>need;
    vector<Line*>grid;
    vector<Text*>numbers;
	Graph_lib::Rectangle box;
    Text est_pi;

// Graph_lib: Rectangle; //for text box

    // Widgets:
    Button drop_button;
    Button quit_button;    // end program
    In_box drop_count;
    Menu motion_menu;
    Button menu_button;

    void hide_menu() { motion_menu.hide(); menu_button.show(); }

    // actions invoked by callbacks://functions!!!!!!!!!!!!!!!!!!!!
    void count_pressed() { Pical();hide_menu(); }
    void rotate_pressed() { rotate(); hide_menu(); }
    void list_pressed() { list(); hide_menu(); }
    void menu_pressed() { menu_button.hide(); motion_menu.show(); }
    void drop();
    void quit();
    void rotate();
    void Pical();
    void list();

    // callback functions:
    static void cb_count(Address, Address);
    static void cb_rotate(Address, Address);
    static void cb_list(Address, Address);
    static void cb_menu(Address, Address);
    static void cb_drop(Address, Address);
    static void cb_quit(Address, Address);
};

//------------------------------------------------------------------------------

Needle_window::Needle_window(Point xy, int w, int h, const string& title)
    :Window(xy,w,h,title),

    motion_menu(Point(x_max()-70,30),70,20,Menu::vertical,"motion"),
    menu_button(Point(x_max()-90,30), 90, 20, "Motion Menu", cb_menu),
    drop_button(Point(x_max()-145,0), 70, 20, "Drop", cb_drop),
    quit_button(Point(x_max()-70,0), 70, 20, "Quit", cb_quit),
    drop_count(Point(x_max()-250,0), 100, 20, "Enter drop count"),
    est_pi(Point(250,250),""),
    box (Point(240,230),420,30)

{//creating the parallel lines
	int b =20; int b2 = 520;
	for(int i =120; i<840;i+=120){
	   	Line* g = new Line(Point(i,b), Point(i,b2));
		grid.push_back(g);
		g->set_color(Color::green);
	 	attach(*g);
	    }

	attach(drop_button);
    attach(quit_button);
    attach(drop_count);
    motion_menu.attach(new Button(Point(0,0),0,0,"Count",cb_count));
    motion_menu.attach(new Button(Point(0,0),0,0,"Rotate",cb_rotate));
    motion_menu.attach(new Button(Point(0,0),0,0,"(Un)list",cb_list));
    attach(motion_menu);
    motion_menu.hide();
    attach(menu_button);

}

//------------------------------------------------------------------------------

void Needle_window::cb_quit(Address, Address pw)    // "the usual"
{
       reference_to<Needle_window>(pw).quit();
}

//------------------------------------------------------------------------------

void Needle_window::quit()
{
    hide();        // curious FLTK idiom for delete window
}

//------------------------------------------------------------------------------

void Needle_window::cb_drop(Address, Address pw)     // "the usual"
{
       reference_to<Needle_window>(pw).drop();
}

//------------------------------------------------------------------------------


void Needle_window::drop()
{
	for (int i=0, len = need.size(); i<len;++i){
		detach(*need[i]);delete need[i];delete nmiddle[i];
	}
	need.clear();
	nmiddle.clear();
	for (int i=0, len = numbers.size();i<len;++i){
		detach(*numbers[i]);delete numbers[i];
	}
	numbers.clear();
	detach(est_pi);
	detach(box);

	int ned_c = drop_count.get_int();
	double x1,x2,y1,y2=0; double theta=0;
	int L_m = 60;
	constexpr double Pi = 3.141592653589;
	for(int i=0; i< ned_c; ++i){
		theta = rand()%360*(Pi/180);
		mx = rand()%720+60;
		my = rand()%500+20;
		Point* m = new Point(mx,my);
		nmiddle.push_back(m);

		x1 = mx + L_m*cos(theta);
		y1 = my + L_m*sin(theta);

		x2 = mx - (L_m*cos(theta));
		y2 = my - (L_m*sin(theta));

		Line* nl = new Line(Point(x1,y1), Point(x2,y2));
		need.push_back(nl);
		attach(*nl);
   	}
	redraw();
}

void Needle_window::rotate()
{
	for (int i=0, len=need.size(); i<len; ++i){
		detach(*need[i]);delete need[i];
	}
	need.clear();
	detach(est_pi);
	detach(box);

	int ned_c = drop_count.get_int();
	double x1,x2,y1,y2=0; double theta=0;
	int L_m = 60;constexpr double Pi = 3.141592653589;

	for(int i=0; i<ned_c; ++i){
		theta = (rand()%360)*(Pi/180);

		x1 = nmiddle[i]->x + L_m*cos(theta);
		y1 = nmiddle[i]->y + L_m*sin(theta);

   		x2 = nmiddle[i]->x - (L_m*cos(theta));
  		y2 = nmiddle[i]->y - (L_m*sin(theta));

  		Line* nl = new Line(Point(x1,y1), Point(x2,y2));
  		need.push_back(nl);
  		attach(*nl);
	}
	redraw();
}

void Needle_window::Pical()
{
	double estimate=0;
	double counter=0;
	for(int i = 0; i<6; ++i){//determining how many needles intersect with the grid
		for(int j=0, len=need.size(); j<len; ++j){
			double min_x= min(need[j]->point(0).x, need[j]->point(1).x);
			double max_x= max(need[j]->point(0).x, need[j]->point(1).x);

			if(min_x<=grid[i]->point(0).x && max_x>=grid[i]->point(0).x){
				need[j]->set_color(Color::red);
				++counter;
			}
		}
	}

	estimate = (2.0*need.size())/counter;
	box.set_color(Color::green);
	box.set_fill_color(Color::green);
	attach(box);
	ostringstream ts;
	ts << "Found " << counter << " crossed needles, and estimated pi is " <<
	estimate <<"!";
	est_pi.set_label(ts.str());
	est_pi.set_color(Color::white);
	attach(est_pi);
	redraw();
}
void Needle_window::list()
{
	int counter = numbers.size();
	int num=0;
	if (counter ==0){
		for(int i =0, len= need.size();i<len;++i){
			num =(i+1);
			int x_m = nmiddle[i]->x;
			int y_m = nmiddle[i]->y;

			ostringstream oss;
			oss << num;
			Text* t = new Text(Point(x_m,y_m), oss.str());
			numbers.push_back(t);
			attach(*t);
  		}
	redraw();
	}
	else{
	for (int i=0, len=numbers.size(); i<len; ++i){
		detach(*numbers[i]);delete numbers[i];
	}
	numbers.clear();
	redraw();
	}
}


//------------------------------------------------------------------------------

void Needle_window::cb_count(Address, Address pw)      // "the usual"
{
    reference_to<Needle_window>(pw).count_pressed();
}

//------------------------------------------------------------------------------

void Needle_window::cb_rotate(Address, Address pw)     // "the usual"
{
    reference_to<Needle_window>(pw).rotate_pressed();
}

//------------------------------------------------------------------------------

void Needle_window::cb_list(Address, Address pw)    // "the usual"
{
    reference_to<Needle_window>(pw).list_pressed();
}

//------------------------------------------------------------------------------

void Needle_window::cb_menu(Address, Address pw)     // "the usual"
{
    reference_to<Needle_window>(pw).menu_pressed();
}

//------------------------------------------------------------------------------


int main()
try {
	srand(time(0));
    Needle_window win(Point(100,100),840,550,"lines");
    return gui_main();
}
catch(exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "Some exception\n";
    return 2;
}

//------------------------------------------------------------------------------

