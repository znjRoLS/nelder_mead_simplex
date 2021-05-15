#pragma once

#include <vector>
#include <function>

using std::vector;
using std::pair;
using std::function;

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

  NelderMead(function<double(const vector<double>&)> f, int dimension);

  void SetAlgorithmOptions(const AlgorithmOptions& algo_opt);
  void SetConvergenceOptions(const ConvergenceOptions& conv_opt);

  /// Constraints are given for each dimension, as a vector (index being the dimension) of pairs of min and max values.
  /// If the constraint pair is {0,0}, it will be ignored.
  void SetConstraints(vector<pair<double,double>> constraints);

  /// Runing optimization, starting with simplex defined with _x.
  /// These run functions are equivalent to:
  ///   - Call GetPoints if needed
  ///   - Run iteration until convergence is reached
  Point Run(vector<Point> x);
  /// Runing optimization, will generate simplex based on one point.
  Point Run(Point x0);
  /// Runing optimization, will generate simplex uniformly.
  Point Run();

  /// Generate points from a single one. Works the same as SciPy.
  /// Generate a set of points from the original one by altering a single coordinate.
  /// If a coord is 0, set it to 0.00025, and if not set coord to 1.05 of the original.
  vector<Point> GetPoints(Point x0);

  /// Generate points in the uniform manner accross the constraints. If a constriant is not set, (0,1) will be assumed.
  vector<Point> GetPointsUniform();

  /// Generate random points following constriants. If a constraint is not set, use (-inf, +inf).
  vector<Point> GetPointsRandom();

  /// Perform a single iteration of this algorithm.
  bool Iteration(vector<Point>& points);

 private:
  function<double(const vector<double>&)> _f;
  int _dimension;
  AlgorithmOptions _algo_opt;
  ConvergenceOptions _conv_opt;

  vector<pair<double,double>> _constraints;
};
