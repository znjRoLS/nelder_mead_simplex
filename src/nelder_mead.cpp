#include "nelder_mead.h"

using Point = NelderMead::Point;
using AlgorithmOptions = NelderMead::AlgorithmOptions;
using ConvergenceOptions = NelderMead::ConvergenceOptions;

NelderMead::NelderMead(function<double(const vector<double>&)> f, int dimension_opt):
    _f(f),
    _dimension(dimension),
    _algo_opt({1, 2, 0.5, 0.5}),
    _conv_opt({0, 0, 1e-7}) {
}

void NelderMead::SetAlgorithmOptions(const AlgorithmOptions& algo_opt) {
  _algo_opt = algo_opt;
}

void NelderMead::SetConvergenceOptions(const ConvergenceOptions& conv_opt) {
  _conv_opt = conv_opt;
}

void NelderMead::SetConstraints(vector<pair<double, double>> constraints) {
  _constraints = constraints;
}

Point NelderMead::Run(vector<Point> x) {
  while(!Iteration(x));
  return x[0];
}

Point NelderMead::Run(Point x0) {
  vector<Point> x = GetPoints(x0);
  return Run(x);
}

Point NelderMead::Run() {
  vector<Point> x = GetPointsUniform();
  return Run(x);
}

vector<Point> NelderMead::GetPoints(Point x0) {
  return vector<Point>();
}

vector<Point> NelderMead::GetPointsUniform() {
  return vector<Point>();
}

vector<Point> NelderMead::GetPointsRandom() {
  return vector<Point>();
}

bool NelderMead::Iteration(vector<Point> &points) {
  sort(points.begin(), points.end(), [](const Point& lhs, const Point& rhs) {
    return lhs.val < rhs.val;
  });

  vector<double>
  Point x_mean

}
