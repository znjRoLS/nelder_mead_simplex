#pragma once

#include <vector>

using std::vector;
using std::pair;

/// Implemented following this research paper:
/// Gao, F. and Han, L. “Implementing the Nelder-Mead simplex algorithm with adaptive parameters”
/// Computational Optimization and Applications, 51:1, 2012, pp. 259-277.
class NelderMead {

 public:

  struct AlgorithmOptions {
    /// Reflection parameter
    double alfa;
    /// Expansion parameter
    double beta;
    /// Contraction parameter
    double gamma;
    /// Shrink parameter
    double delta;
  };

  struct ConvergenceOptions {
    /// Terminate after this number of iterations. If set to zero, unlimited.
    int max_iterations;
    /// Terminate after this number of func evaluations. If set to zero, unlimited.
    int max_evaluations;
    /// Terminate when the max difference for a function for points in x is less than min_difference.
    /// max(abs(x(i)-x(j))) < min_difference
    double min_difference;
  };

  struct Point {
    vector<double> coord;
    double val;
  };

  NelderMead(const AlgorithmOptions& algo_opt, const ConvergenceOptions& conv_opt);

  /// Constraints are given for each dimension, as a vector (index being the dimension) of pairs of min and max values.
  /// If the constraint pair is {0,0}, it will be ignored.
  void SetConstraints(vector<pair<double,double>> constraints);

  /// Runing optimization, starting with simplex defined with _x.
  vector<double> Run(vector<vector<double>> x);
  /// Runing optimization, will generate simplex based on one point.
  vector<double> Run(vector<double> x0);
  /// Runing optimization, will generate simplex uniformly.
  vector<double> Run();

  /// Perform a single iteration of this algorithm.
  bool Iteration(vector<Point>& points);

 private:
  AlgorithmOptions _algo_opt;
  ConvergenceOptions _conv_opt;

  vector<pair<double,double>> _constraints;
};
