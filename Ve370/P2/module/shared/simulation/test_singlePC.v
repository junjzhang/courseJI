`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/06/28 21:34:42
// Design Name: 
// Module Name: test_singlePC
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


module test_singlePC;
    parameter half_period = 50;
    parameter size = 32;
    
    reg clk, reset;
    reg [size-1:0] in;
    wire [size-1:0] out;
    
    pcSingle #(size) UUT (clk, reset,in, out);
       
    initial begin
        #0 reset = 0; clk = 0; in = 1;
        #100 in = 2;
        #100 reset = 1;
    end
    always #half_period clk = ~clk;
    initial #400 $stop;
endmodule
