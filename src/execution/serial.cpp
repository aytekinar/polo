#ifndef SERIAL_CPP_
#define SERIAL_CPP_

namespace pbopt {
namespace execution {

template <class float_t> struct serial {
  serial() = default;

  serial(const serial &) = default;
  serial &operator=(const serial &) = default;
  serial(serial &&) = default;
  serial &operator=(serial &&) = default;

  template <class InputIt> void initialize(InputIt, InputIt) {}

protected:
  ~serial() = default;
};

} // namespace execution
} // namespace pbopt

#endif
