.. _device_discovery:

.. toctree::
   :maxdepth: 2

Device Discovery with SYCL
==========================

This example is based on :cite:`intel_device_discovery_with_sycl` and illustrates
how to use SYCL API to identify and query the information regarding the devices
available for computing.
Devices are organized into *platforms*.
A platform is a collection of devices managed by a single backend.

.. doxygenfile:: src/00-device-discovery.cpp 
   :project: sycl-examples
