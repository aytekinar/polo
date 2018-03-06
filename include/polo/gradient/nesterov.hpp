#ifndef NESTEROV_HPP_
#define NESTEROV_HPP_

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <vector>

namespace polo {
namespace gradient {
template <class value_t> struct nesterov {
  nesterov(const value_t mu = 0.95, const value_t epsilon = 1E-3)
      : mu{mu}, epsilon{epsilon} {}

  nesterov(const nesterov &) = default;
  nesterov &operator=(const nesterov &) = default;
  nesterov(nesterov &&) = default;
  nesterov &operator=(nesterov &&) = default;

  template <class InputIt, class OutputIt>
  OutputIt grad(InputIt gold_begin, InputIt gold_end, OutputIt gnew_begin) {
    std::size_t idx{0};
    value_t nu_prev, g_val;
    while (gold_begin != gold_end) {
      g_val = *gold_begin++;
      nu_prev = nu[idx];
      nu[idx] = mu * nu_prev + epsilon * g_val;
      *gnew_begin++ = mu * mu * nu_prev + (1 + mu) * epsilon * g_val;
      idx++;
    }
    return gnew_begin;
  }

protected:
  void params(const value_t mu, const value_t epsilon) {
    this->mu = mu;
    this->epsilon = epsilon;
  }

  template <class InputIt> void initialize(InputIt xbegin, InputIt xend) {
    nu = std::vector<value_t>(std::distance(xbegin, xend));
  }

  ~nesterov() = default;

private:
  value_t mu{0.95}, epsilon{1E-3};
  std::vector<value_t> nu;
};
} // namespace gradient
} // namespace polo

#endif
