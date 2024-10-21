#include <iostream>

#include <sycl/sycl.hpp>

/**
 * @brief We import the namespace sycl to avoid excessive typing.
 *
 */
using namespace sycl;

int main(void) {
  for (auto platform : platform::get_platforms()) {
    std::cout << "Platform: " << platform.get_info<info::platform::name>()
              << std::endl;

    for (auto device : platform.get_devices())
      std::cout
          << "\tDevice: " << device.get_info<info::device::name>()
          << ", vendor_id = " << device.get_info<info::device::vendor_id>()
          << ", max_compute_units = "
          << device.get_info<info::device::max_compute_units>()
          << ", max_work_item_dimensions = "
          << device.get_info<info::device::max_work_item_dimensions>() << " <"
          << device.get_info<info::device::max_work_item_sizes<3>>().get(0)
          << ", "
          << device.get_info<info::device::max_work_item_sizes<3>>().get(0)
          << ", "
          << device.get_info<info::device::max_work_item_sizes<3>>().get(0)
          << ">" << std::endl;
  }

  return 0;
}
