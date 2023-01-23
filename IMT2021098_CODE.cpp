#include <iostream>       //declaring the header file .
using namespace std;    
//------------------------------------------------------------------INSTRUCTION FUNCTION ------------------------------------------------------------------//

int instructions(long int *arr_Mem[],long int *mq,long int *mbr,long int *mar,long int *ir,long int *ac,long int *pc,long int *ibr)
    {
/*defining function instructions which will store the instructions and from here we will execute the instructions as needed
by the polygon function.*/
        if(*ir==0)//executed when opcode is of the form: 00
        {   
            cout<<"HALT\n\n";      //halt the program when the instruction 0x00 is fetched 
            //0 will be returned when the program is over and halt is hitted
            return 0;
        }
        if(*ir==1)//executed when opcode is of the form: 01    
        {                               
            cout << "LOAD M("<<*mar<<")\n";      //this will load the instructions in to the ac form the memory
            *ac=*(*arr_Mem+*mar);
        }

        if(*ir==5)//executed when opcode is of the form: 05 
        { 
            cout << "ADD M("<<*mar<<")\n";    //add the data and store them in the ac
            *ac=*ac+(*(*mar +*arr_Mem));
           //mar will store the address so we used the star to get the value at that address
        }
        if(*ir==6)//executed when opcode is of the form: 06 
        { 
            cout << "SUB M("<<*mar<<")\n";   //sub the data and store the ans in the ac
            *ac=*ac-(*(*mar+*arr_Mem));
        }
        if(*ir==9)//executed when opcode is of the form: 09 
        { 
            cout<<"LOAD MQ, M("<<*mar<<")\n";   //loading the content of the memory location x in the MQ
            *mq=(*(*arr_Mem+*mar));
        }
        if(*ir==11)//executed when opcode is of the form: 0B 
       { 
            cout<<"MUL M("<<*mar<<")\n";
            long int p,q,r,s;   //these are the four variables which will store the multipliction
            p=*mq%(1<<20);  //storing the right 20 bit of the mq in the p by getting the remainder 
            q=*mq>>20;   //storing the left 20 bit of the mq in the q by right shift operator
            r=(*(*arr_Mem+*mar))%(1<<20);  //storing the right 20 bit of the another number in r
            s=(*(*arr_Mem+*mar))>>20;   //similarly storing the left 20 bit of another number in s
            long int a,b,c,d;    //a,b,c,d will store the multiplication of these number
            long int temp1,temp2;   //two tempeorary variables
            a=q*s;    
            b=q*r;
            c=p*s;
            d=p*r;     
            //above we have calculated the multiplication and stored them in the variables 
            *mq = a;//storing the result of a in the mq
            temp2 = *mq;   
            *mq = *mq + b%(1<<20);   

            if(temp2>*mq)
                temp1++; 
            temp2=*mq;
            *mq=*mq+c%(1<<20);
            temp1=0;//initializing the temp variable with 0
            if(temp2>*mq)
                temp1++; 
            *ac=temp1;
            *ac=*ac+d;//    adding and storing the value in ac
            *ac=*ac+(c>>20);//right shifting the c by 20 bits
            *ac=*ac+(b>>20);    
        }
        if(*ir==33)//executed when opcode is of the form: 21 
        {
            cout << "STOR M(" << *mar << ")\n";    //this will store the value in the memory from ac
            (*(*mar + *arr_Mem))= *ac;
        }
    return 1;          //this function will return 1 when the halt is not executed that is another part of instruction is still left to execute 
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------POLYGON FUNCTION-----------------------------------------------------------------------------------//

//POLYGON--this function calculates the calculation required for the instruction and accordingly call the instructoin function to get the instructions
int polygon(long int arr_Mem[], long int pc1)
{   long int mq  = 0;//  mq means(multiplier/quotient) which will store the lsb of the product
    long int mbr = 0;//  mbr means(memory buffer register) this will contain the value from the input or ouput or form the memory
    long int ibr = 0;//  this is the instruction buffer register which will store the rhs instruction temporarily
    long int mar = 0;//  memory address register which will store t   //this will load the instructions in to the ac form the memoryhe address of the value which is to stored in the mbr
    long int ir  = 0;//  ir is the instruction register which will store the 8 bit opcode of the instruction to be executed
    long int ac  = 0;//  ac is the accumulator which stores the results of the ALU.
  
    for(long int pc=pc1;pc<500;pc++)
    {   
        mar = pc;//               first pc is loaded into pc
        mbr = *(arr_Mem+ mar);//  value stored at that address in the memory is loaded into the mbr
        ibr = mbr % (1<<20);//    rhs is extracted from the mbr and stored in the ibr by dividing the mbr with a 20 bit number and getting the remainder
        ir  = mbr>>32;//          right shifting the mbr by 32 which will give the opcode of the bit that is starting 8 bit of the mbr
        mar = (mbr>>20) % (1 << 12);// first right shifting then remainder with 12 bit number to get the address of the left instruction 
        int over=instructions(&arr_Mem,&mq,&mbr,&mar,&ir,&ac,&pc,&ibr);
        //now call the instruction function with the extracted value
        if(over==0)
        //if 0 is returned then that means halt is executed and the program is over so end this funcion also.
        return 0;
        //if 1 is returned that means halt is not yet executed now run again the program for the right instruction which was stored in the ibr
        mar = ibr % (1<<12);//  bit calculation 
        ir = ibr >> 12;//       bit calculation 
                    
        if(ir==13)
        {
            cout << "JUMP M(" << mar << ", 0:19)" << endl;//        printing the current value of mar which we have to load into pc
            pc = mar;//                      loading mar into pc so that pc can jump to that instructions
            mbr = *(arr_Mem + mar);//        mbr will get the value of that memory address where we want to jump
            ir = (mbr >> 32);//              ir is getting the new opcode of mbr
            mar = (mbr>> 20) % (1 << 12);//  shifting the mbr right by 20 bit then taking the modulas to get the 12 bit address as by taking the remainder only 
            //12 bit will remain 
            ibr = mbr % (1 << 20);//         storing the right instruction in the ibr 
            over=instructions(&arr_Mem,&mq,&mbr,&mar,&ir,&ac,&pc,&ibr);//       now i executing instructions for these new values where we have jumped
            if(over==0)
                 return 0;    
            
        }
        over=instructions(&arr_Mem,&mq,&mbr,&mar,&ir,&ac,&pc,&ibr);//    again calling for the right instruction
        if(over==0)
            return 0;//     if halt executed end the program
    }
    return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------MAIN FUNCTION-----------------------------------------------------------------//
int main()
{
    int num;
   //------------------------------------------------------------------------------------------------//
    while (1)    // a simple while loop to make the program user interactive 
    {
        //-----------------all these variables are defined above in the polygon function-----------------//
        //DEFINING ALL THESE VARIABLES IN THE WHILE LOOP BECAUSE FOR NEXT ITERATION WE HAVE TO CLEAR ALL THE VALUES
        long int mq  = 0;       //        
        long int mbr = 0;       //
        long int ibr = 0;       //  
        long int mar = 0;       //        INITIALIZING ALL THE VALUES INITAILLY AS 0
        long int ir  = 0;       //
        long int ac  = 0;       //
        long int arr_Mem[500] = {0};//memory which has a capacity of 500 of data type array
        //-----------------some choices for user to perform the function--------------------//
        cout<<"\n1)Perimeter of Polygon: ";      
        cout<<"\n2)Area of Polygon: ";
        cout<<"\n3)Nth term of Fibonacci Sequence: ";
        cout<<"\n4)End your Program: ";
        cout<<"\nEnter your choice : ";
        int value;//                    choice entered by the user is stored in value
        cin>>value;    
        if(value==1)   
        {
            cout << "\nEnter length of polygon: ";
            int length;//               length of polygon
            cin>>length;
            arr_Mem[0]=2*length;//      in the position 0 of the array storing the length
            cout << "Enter breadth of polygon: ";
            int breadth;//              breadth of the polygon
            cin>>breadth;
            arr_Mem[1]=2*breadth;//     in the position 1 storing the breadth.

//--------------------------------------------------------------ADDITION--------------------------------------------------------------------------//

            arr_Mem[3] = 0x0100105000;//    in mem-3 storing the instrucions for loading then adding  
            arr_Mem[4] = 0x2100200000;//    in mem-4 storing the another instruction for storing at location 2 and then HALT the program 


//----------------------------------------------------------SUBSTRACTION ------------------------------------------=====--------------------------//
            //to calculate whether the polygon is square or rectangle
            arr_Mem[5] = 0x0100106000;//            loading the value from loc 1 and subtracting value from loc 0
            arr_Mem[6] = 0x2100700000;//            storing value at loc-7 and then halt the program 

//i have used the substraction here as substracting the length and breadth if they are equal then it is square otherwise it is rectangle .
//------------------------------------------------------------------------------------------------------------------------------------------------------

                polygon(arr_Mem,3);//         calling the polygon function with the memory value 3
                polygon(arr_Mem,5);//         calling the polygon function with the memory value 5
            if(arr_Mem[7]!=0)      //         result of the substraction is stored at mem-7 that is if the value
                    //is not zero then it means sides are not equal hence the polygon is rectangle otherwise square
                cout<<"Your polygon is rectangle!!\n";
            else    
                cout<<"Your polygon is square!!\n";
        }
        else if(value==2)
        {
            cout << "\nEnter length of polygon: ";
            int length;//                         length of polygon
            cin>>length;
            arr_Mem[0] = length;//                in the position 0 of the array storing the length
            cout << "Enter breadth of polygon:";
            int breadth;//                        breadth of the polygon
            cin>>breadth;
            cout<<endl;
            arr_Mem[1] = breadth;//               in the position 1 storing the breadth.
//------------------------------------------------------------------------MULTIPLICATION---------------------------------------------------------------//
            arr_Mem[3] = 0x090010B000;
            arr_Mem[4] = 0x2100200000;
            
 //-----------------------------------------------------------------------SUBSTRACTION------------------------------------------------------------------//
            //to calculate whether the polygon is square or rectangle
            arr_Mem[5] = 0x0100106000;
            arr_Mem[6] = 0x2100700000;
//------------------------------------------------------------------------------------------------------------------------------------------------------//

            polygon(arr_Mem,3);//                calling the polygon function with the memory value 3
            polygon(arr_Mem,5);//                calling the polygon function with the memory value 5

            if(arr_Mem[7]!=0)  //                result of the substraction is stored at mem-7 that is if the value
                               //                is not zero then it means sides are not equal hence the polygon is rectangle otherwise square
                cout<<"Your polygon is rectangle!!\n";
            else    
                cout<<"Your polygon is square!!\n";
        }
        else if(value==3)//                       for fibonacci sequence 
        {
            cout<<"\nEnter a number GREATER THAN 7 ( 1st term of sequence is considered to be 0 ):";
            //HERE I HAVE MADE METHOD OF FINDING THE FIBONACCI SEQUENCE FOR ALL NUMBERS BUT , I/O OPERATIONS IS ONLY APPLICABLE FOR NUMBERS ABOVE 7.
            cin>>num;
            if(num<8)
            {
                cout<<"\n-------------Wrong Input!!-------------"<<endl;
                continue;
            }
            arr_Mem[0] = 1;//       --at location 0 storing the initial values of the fibonacci series
            arr_Mem[1] = 2;//       --------------------same as above--------------------------
            arr_Mem[2] = 0;//       --this will store the final answer which is to be printed.

            //-----------------------------------------INSTRUCTIONS STORED IN MEMEORY WHICH WILL BE FETCHED --------------------------------------------------------------
            arr_Mem[3] = 0x0100005001;//              loading the value at 0 then adding the value at location 1.
              //IN BELOW INSTRUCTION WE ARE JUMPING TO THE MEMORY LOCATION 6 AND THEN CONTINUING FROM THERE BY USING THE INSTRUCTION (0C006)
            arr_Mem[4] = 0x210020D006;//                storing the value at location 2 and then JUMP to the location 6
            arr_Mem[6] = 0x0100121000;//                loading value at 1 and storing value at 0
            arr_Mem[7] = 0x2100001002;//                storing value at 0 and loading value at 2.
            arr_Mem[8] = 0x2100101000;//                storing value at 1 and loading value at 0.    
                    
            arr_Mem[9]  = 0x0500121002;//               repeating the above process for other terms
            arr_Mem[10] = 0x020010D010;//               JUMP STATEMENT TO JUMP TO MEMORY LOCATION 16 AND EXECUTE INSTRUCTIONS AT LOCATION 16
            arr_Mem[16] = 0x0100121000;
            arr_Mem[17] = 0x2100002001;
            arr_Mem[18] = 0x0100221001;

            arr_Mem[19] = 0x0100005001;
            arr_Mem[20] = 0x210020D018;//                JUMP STATEMENT TO JUMP TO MEMORY LOCATION 24 WHOSE HEXA DECIMAL VALUE IS 18
            arr_Mem[24] = 0x0100121000;
            arr_Mem[25] = 0x2100001002;
            arr_Mem[26] = 0x2100101000;
                                    
            arr_Mem[27] = 0x0200005001;
            arr_Mem[28] = 0x210020D020;//                JUMP STATEMENT TO JUMP TO MEMORY LOCATION 32 .
            arr_Mem[32] = 0x0100121000;
            arr_Mem[33] = 0x2100001002;
            arr_Mem[34] = 0x2100101000;
        
            int n=35;                                    
            for(int i=0;i<num-8;i++)//                   RUNNING THE LOOP NUMBER OF TIMES TO CALCULATE THE Nth TERM OF THE SEQUENCE
            {
                arr_Mem[n]   = 0x0200005001;//           storing the value at location 0 and adding value at location 1 to it
                arr_Mem[n+1] = 0x2100202020;//           storing the value at location 2
                arr_Mem[n+2] = 0x0100121000;//           loading value at location 1 storing value at 0
                arr_Mem[n+3] = 0x2100001002;//           storing at 0 and loading at 2
                arr_Mem[n+4] = 0x2100101000;//           storing at 1 and loading at 0
                n=n+5;                      //           each time incrementing the value of n by 5 and then again storing these 5 instructions at next 5 memory location
            }
    //------------------------------------------------------------------------------------------------------------------------------------------------------
            polygon(arr_Mem,3);//       calculating the polygon function for memory location 3 as here i have stored the first location
        }

        else if(value==4)
        {
            cout<<"Thank You!!\n";//     ending the program and while loop also
            return 0;
        }
        else   
        {
            cout<<"\n-------------Wrong Input!!-------------"<<endl;//       while loop will continue if the input is wrong
            continue;
        }
        if(value==1)
            cout<<"Perimeter--"<<arr_Mem[2];//                             storing the ans at value 2.
        else if(value==2)
            cout<<"Area--"<<arr_Mem[2];//                                  answer will be stored at memory location 2
        else if(value==3)
            cout<<num<<"th term of Fibonacci Sequence--"<<arr_Mem[2];//     nth term of fibonacci is finally stored at memory loction 2
        cout << endl;
    }
    return 0;//                      ending of the program 
}
