#include "class2.h"

#if GNUPLOT_USE
#include "gnuplot-iostream.h"
#endif

Class2::Class2() {

}

void Class2::Method() {

#if GNUPLOT_USE

  // Demo basic

  Gnuplot gp;
  // For debugging or manual editing of commands:
  //Gnuplot gp(std::fopen("plot.gnu"));
  // or
  //Gnuplot gp("tee plot.gnu | gnuplot -persist");

  std::vector<std::pair<double, double> > xy_pts_A;
  for(double x=-2; x<2; x+=0.01) {
    double y = x*x*x;
    xy_pts_A.push_back(std::make_pair(x, y));
  }

  std::vector<std::pair<double, double> > xy_pts_B;
  for(double alpha=0; alpha<1; alpha+=1.0/24.0) {
    double theta = alpha*2.0*3.14159;
    xy_pts_B.push_back(std::make_pair(cos(theta), sin(theta)));
  }

  gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
  gp << "plot '-' with lines title 'cubic', '-' with points title 'circle'\n";
  gp.send1d(xy_pts_A);
  gp.send1d(xy_pts_B);

#endif

}