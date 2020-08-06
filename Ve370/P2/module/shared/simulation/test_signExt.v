`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/06/25 12:16:09
// Design Name: 
// Module Name: test_signExt
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


module test_signExt;
    parameter half_perod = 50;
    parameter size = 16;
    
    reg [size-1:0] in;
    wire [size-1+16:0] out;
    
    signExt #(size+16) UUT (in,out);
       
    initial begin
        #0 in = 1;
        #200 in = -1;
    end
    initial #400 $stop;
endmodule
