`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/06/28 21:20:28
// Design Name: 
// Module Name: test_shifter_26
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


module test_shifter_26;
    parameter half_period = 50;
    parameter size = 26;
    
    reg [size-1:0] in;
    wire [size+1:0] out;
    
    shiftLeft2N26 #(size) UUT (in,out);
    
    initial begin
        #0 in = 1;
        #100 in = 2;
        #100 in = 5;
    end

    initial #400 $stop;
    
endmodule
