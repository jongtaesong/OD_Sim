
# Directory structure 
- **od_sim/** : contains all the source files (.cpp and .h) and makefile
- **od_sim/Share/** : contains header files and library for compilation
- **od_sim/python/** : contains example python file for generate the result graph
- **od_sim/input_file/** : contains an example file to define simulation parameters 
- **od_sim/output_file/** : contains the output files after complete the simulation

# How to build
	> cd od_sim
	> make -f OD_Sim.mak

# How to run
	> ./OD_Sim

# How to test
Follow the example simulation procedure to test the simulation source code. 
## Run first simulation 
(1) Run simulation by typing ./OD_Sim <br>
(2) Hit Enter to use default parameter defined in input_file/ConnMap.txt  <br>

	> ./OD_Sim↓ 
	↓ 
**Note that ↓ means hit Enter.** 
## Run second simulation 
(3) Hit Enter to continu with modified simulation <br>
(4) Define batch simulation parameters. Traffic load 100%, the memory bandwidth from 60Gbps to 780Gbps with increment of 40Gbps<br>
(5) Run batch simulation <br>

	↓
	15 100 100 100 60 780 40 ↓ 
	0↓ 
	
## Run third simulation 
(6) Continue with modified parameters<br>
(7) Change window size 128<br>
(8) Define batch simulation parameters<br>
(9) Run batch simulation<br>

	↓ 
	8 128 ↓ 
	15 100 100 100 60 780 40 ↓ 
	0 ↓ 
	
## Run fourth simulation 
(10) Continue with modified parameters<br>
(11) Change window size 100000 to disable flow control<br>
(12) Define batch simulation parameters<br>
(13) Run batch simulation<br>

	↓ 
	8 100000 ↓ 
	15 100 100 100 60 780 40 ↓ 
	0 ↓ 
	
## Complete simulation 
(14) Complete simulation. All the results will be stored in Sim Result Summary.txt<br>

	0 ↓ 
## Analyze the results 
(15) Change directory to python file<br>
(16) Run python script to display performance result<br>

	> cd python ↓ 
	> python for paper thruput delay.py↓ 
	
