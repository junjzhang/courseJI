`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/06/28 21:57:18
// Design Name: 
// Module Name: test_instru_mem
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module test_instru_mem;
    parameter half_period = 50;
    parameter size = 256;
    parameter width = 32;
    
    reg [width-1:0] address;
    wire [width-1:0] instruction;
    
    insMem #(size) UUT (address, instruction);
      
    initial begin
        #0 address = 0;
        #100 address = 4;
        #100 address = 28;
    end
//    always #half_period clk = ~clk;
    initial #400 $stop;
endmodule
