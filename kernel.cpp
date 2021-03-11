#include <CL/sycl.hpp>

constexpr int num=16;
using namespace sycl;

  int main() {
  auto R = range<1>{ num };
  //Create Buffers A and B
  buffer<int> A{ R }, B{ R }, C{ R };
  //Create a device queue
  queue Q;
  
  //Submit Kernel 1
  Q.submit([&](handler& h) {
    //Accessor for buffer A
    accessor out(A,h,write_only);
    h.parallel_for(R, [=](auto idx) {
      out[idx] = idx[0]; }); });
  /*
  host_accessor result_A(A,read_only);
  for (int i=0; i<num; ++i)
    std::cout << result_A[i] << "\n";  
    */
  //Submit Kernel 2
  Q.submit([&](handler& h) {
    //This task will wait till the first queue is complete
    accessor out(A,h,write_only);
    h.parallel_for(R, [=](auto idx) {
      out[idx] += idx[0]; }); });

 std::cout << "Values of A array is " << "\n";
  host_accessor result_A_out(A,read_only);
  for (int i=0; i<num; ++i)
    std::cout << result_A_out[i] << "\n";  

  //Submit Kernel 3
  Q.submit([&](handler& h) { 
    //Accessor for Buffer B
    accessor out(B,h,write_only);
    h.parallel_for(R, [=](auto idx) {
      out[idx] = idx[0]; }); });
  
  /*
  host_accessor result_B1(B,read_only);
  for (int i=0; i<num; ++i)
    std::cout << result_B1[i] << "\n";      
  */  
  
  //Submit Kernel 4
  Q.submit([&](handler& h) {
   //This task will wait till kernel 2 and 3 are complete
   accessor A_out (A,h,read_only);
   accessor B_out(B,h,read_only);
   accessor inout(C,h,write_only);
  h.parallel_for(R, [=](auto idx) {
    inout[idx] = A_out[idx] * B_out[idx]; }); }); 

std::cout << "Values of B array is " << "\n";
  host_accessor result_B_out(B,read_only);
  for (int i=0; i<num; ++i)
    std::cout << result_B_out[i] << "\n";      
    
 // And the following is back to device code
 std::cout << "Values of C = (A * B) is " << "\n";
 host_accessor result_C(C,read_only);
  for (int i=0; i<num; ++i)
    std::cout << result_C[i] << "\n";      
  return 0;
}