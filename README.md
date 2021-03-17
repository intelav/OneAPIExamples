# OneAPIExamples

### Examples here are executed on Intel DevCloud as well as on Intel's 10th Gen CometLake Processor..


### Example 1:- 
#### kernel.cpp needs compilation with dpcpp as "dpcpp -o kernel.cpp kernelbin" and then running kernelbin generates output from three different arrays , A, B and C where kernel1 and Kernel2 works on Array A and kernel3 works on Array B while kernel4 works on Array C. This example shows buffer dependency between different kernels in case they work on same buffer..As kernel1 and kernel2 works on same buffer, having a print block between both these kernels would demonstrate that kernel2 won't be executed as kernel1 got the return back to Host due to enabling print block from line number 19-23.. 


### Example 2:- 
#### subgroup.cpp demontrates distribution of work groups, sub groups and work items. please refer to output_subgroup.txt for understanding of it. 