`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Rui Ding
// 
// Create Date: 2020/06/29 10:59:37
// Design Name: 
// Module Name: test_shifter32
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


module test_shifter32;
    // parameter half_period = 50;
    parameter size = 32;
    
    reg [size-1:0] in;

    wire [size-1:0] out;
    
    shiftLeft2N32 #(size) UUT (in, out);
       
    initial begin
        #0 in = 12;
        #100 in = -1;
    end
    // always #half_period clk = ~clk;
    initial #400 $stop;
endmodule
