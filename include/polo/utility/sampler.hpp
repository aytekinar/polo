#ifndef SAMPLER_HPP_
#define SAMPLER_HPP_

#include <random>
#include <utility>

namespace polo {
namespace utility {
namespace sampler {
namespace detail {
template <class index_t, template <class> class distribution>
struct sampler : private distribution<index_t> {
  using param_type = typename distribution<index_t>::param_type;
  using result_type = typename std::mt19937::result_type;

  sampler() { gen = std::mt19937{std::random_device{}()}; }
  sampler(const sampler &s) : distribution<index_t>{s} {
    gen = std::mt19937{std::random_device{}()};
  }
  sampler &operator=(const sampler &) = delete;
  sampler(sampler &&) = default;
  sampler &operator=(sampler &&) = default;

  sampler(const result_type seed) { gen.seed(seed); }

  void seed(const result_type seed) { gen.seed(seed); }

  template <class... Ts> void params(Ts &&... args) {
    distribution<index_t>::param(param_type(std::forward<Ts>(args)...));
  }
  void params(const param_type &params) {
    distribution<index_t>::param(params);
  }

  template <class OutputIt>
  OutputIt operator()(OutputIt sbegin, OutputIt send) {
    while (sbegin != send)
      *sbegin++ = distribution<index_t>::operator()(gen);
    return sbegin;
  }

private:
  std::mt19937 gen;
};

struct coordinate_sampler_t {};
struct component_sampler_t {};
} // namespace detail

template <class index_t = int>
using uniform = detail::sampler<index_t, std::uniform_int_distribution>;
template <class index_t = int>
using custom = detail::sampler<index_t, std::discrete_distribution>;

constexpr detail::coordinate_sampler_t coordinate;
constexpr detail::component_sampler_t component;
} // namespace sampler
} // namespace utility
} // namespace polo

#endif
