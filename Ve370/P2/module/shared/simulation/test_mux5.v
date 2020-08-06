`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/06/29 10:40:11
// Design Name: 
// Module Name: test_mux5
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


module test_mux5;
    // parameter half_period = 50;
    parameter size = 5;
    
    reg [size-1:0] in0, in1;
    reg sel;
    wire [size-1:0] out;
    
    mux5 #(size) UUT (in0, in1, sel, out);
       
    initial begin
        #0 in0 = 0; in1 = 12; sel = 0;
        #100 sel = 1;
        #100 in0 = -1; sel = 0;
    end
    // always #half_period clk = ~clk;
    initial #400 $stop;
endmodule
