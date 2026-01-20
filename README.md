# Low Latency - Performance Programming
Here I explore low latency concepts and try to use the most of the hardware by cleverly programming the software.
Examples
1. The CPU does branch predictions, but if the prediction goes wrong, there is a cost on the CPU cycles lost. The performance drop in a branched code when compared to an unbranched piece of code can be practically seens using a simple examplee

examples\cpu_branch_prediction.cpp -> Comparing the time taken for a branched piece of code with an unbranched piece of code.
