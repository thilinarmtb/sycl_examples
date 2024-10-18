#include <iostream>

#include <sycl/sycl.hpp>

// https://www.intel.com/content/www/us/en/developer/articles/technical/device-discovery-with-sycl.html
using namespace sycl;

int main(int argc, char *argv[]) {
  for (auto platform : platform::get_platforms()) {
    std::cout << "Platform: " << platform.get_info<info::platform::name>()
              << std::endl;

    for (auto device: platform.get_devices())
      std::cout << "\tDevice: " << device.get_info<info::device::name>()
                << ", vendor_id = " << device.get_info<info::device::vendor_id>()
                << ", max_compute_units = " << device.get_info<info::device::max_compute_units>()
                << ", max_work_item_dimensions = " << device.get_info<info::device::max_work_item_dimensions>()
                << " <" << device.get_info<info::device::max_work_item_sizes<3>>().get(0)
                << ", " << device.get_info<info::device::max_work_item_sizes<3>>().get(0)
                << ", " << device.get_info<info::device::max_work_item_sizes<3>>().get(0)
                << ">" << std::endl;
  }

  return 0;
}
