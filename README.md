# IAS-Architecture-Simulation
It is designed to simulate the functionality of a first-generation electronic computer. The program utilizes a machine-first approach, where the instruction set and architecture of the simulated computer closely resemble that of a real-world electronic computer.

Using the c++/cpp language i have implemented the IAS computer and some of its INSTRUCTIONS about which it is mentioned in this file.

Components of IAS Computer--

#### MAIN MEMORY: A main memory in which both data and instruction of the program are stored.

#### ALU(ARITHMETIC AND LOGIC UNIT) : this is capable of performing various operations on binary data.

#### Control Uint: This decides which instructions is to be executed in which sequence and accordingly provides the signal for there execution.

#### I/O (INPUT/OUTPUT) : This is controlled by the control unit.

#### ac is the Accumulator : The work of the accumulator is to store the temporary operands or results of the ALU operations.And after that those results are stored in the memory at the defined location.

#### ir is the Instructions Register :The work of the instruction register to store the opcode of the instructions which is currently being executed.
	
#### ibr is the Instructions Buffer register : The work of the instruction buffer register is to hold the right instruction temporarily (if available) untill the left instruction is getting executed after that sends the right side instruction to the mar and ir.

#### mq is the Multiplier/Quotient Register : The work of the this register is to store the LSB of the product which is performed in the ALU .


#### mbr is the Memory BUffer register this is used store the word which is to be stored in the memory and also to store the data from the memory.
	
#### mar is the Memory Adress register this stores the address from where the data is to be read or where data is to be written .

#### pc is the Program Counter : The work of the Program Counter is to hold the address of the next instruction.


### IAS has two cycles for the program :
1)Fetch cycle:In this opcode of the instruction is loaded into the IR and simulatneously the address part is stored in the MAR after that we increment the program counter and value at that memory location is moved into MBR which is when executed then the next instruction which is stored in IBR is passed to the MAR and IR 
2)Execute Cycle :In this first the data which is fetched is decoded based on the instruction opcode and binary number is converted into the assembly code .

Then comes the phase where ALU comes in the picture it functions as written in the assembly code .


### STEPS TO RUN THE PROGRAM

1) Enter your choice which program you want to run--
i-a)Then if you have entered choice as 1 or 2 then program will ask for the length and breadth of the polygon.
i-b)So enter the length and breadth of the polygon after that you will get the output which will show the ias code of the program so that you can know that how the architecture works .

ii-a)if you have entered the value as 3 then program will ask for a number greater than 7 so enter any number greater than 7 and you will get the ias code for the whole calculation and also the answer that is the Nth term of the sequence.

iii)if you want to end the program then give the choice as 4 and the program will terminate.

### SOME IMPORTANT INFO ABOUT PROGRAM

1)In this program i have also implemented SUB M(X) i.e the SUB M(X) in the way --as when we are taking the input from the user the length and breadth of the polygon then to show whether the polygon is square or rectangle we will substract its length and breadth and if the difference is zero then it is square otherwise it is rectangle.

2)In the fibonacci series question i have made the input and output for numbers greater than 7 (as main aim was to show the implementation of the instruction)but the series will calculate each and every term inside the program .

3)In the array memory which i have created i have stored the instruction in the form of hexadecimal numbers storing 40 bit integer is not possible in cpp because the largest data type which we can use is long long int.

4)the instruction which are stored in the memory has 10 digits in the format as 0x00000000 in which first five bits represent the left ins and next 5 bit represent the right ins ,,in left ins first two bit represent the opcode and next three bit represent the memory location in the hexa format.

5)The passing of values between function is in form of the pointers as we want to update the value of each variable.
