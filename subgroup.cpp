#include <CL/sycl.hpp>
using namespace sycl;

static const size_t N = 512; // global size
static const size_t B = 128; // work-group size

int main() {
  queue q;
  std::cout << "Device : " << q.get_device().get_info<info::device::name>() << std::endl;

  q.submit([&](handler &h) {
    //# setup sycl stream class to print standard output from device code
    auto out = stream(8192, 768, h);

    //# nd-range kernel
    h.parallel_for(nd_range<1>(N, B), [=](nd_item<1> item) {
      //# get sub_group handle
      intel::sub_group sg = item.get_sub_group();

      //# query sub_group and print sub_group info once per sub_group
    //if (sg.get_local_id()[0] == 0) {
     
     out << "local_id(index of work-item):" << sg.get_local_id()[0] << ",sub_group id: " 
       << sg.get_group_id()[0] << ",size of subgroup(number of work items)=" << sg.get_local_range()[0] 
	   << ",number of subgroups in parent workgroup:" << sg.get_group_range()[0] << endl;
    //}
    });
  }).wait();
}