`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Author: 
//  Junjie ZHang
// Module Name: insMem
// Description: 
//  Instruction memory. Byte addressed
// Dependencies: 
//  None
//////////////////////////////////////////////////////////////////////////////////


module insMem(
    input [31:0] address,
    output [31:0] instruction
    );
    
    parameter size = 256; // unit: byte
    
    reg signed [7:0] mem [0:size-1];
    integer i;
    initial
    begin
        $readmemb("C:/Users/lenovo/Desktop/module/module/test.txt", mem);
        // for (i=0;i<128;i=i+1) // for testing
         //   $display("%b", mem[i]);
    end

    assign instruction = {mem[address],mem[address+1],mem[address+2],mem[address+3]};
   
endmodule
