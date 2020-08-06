`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/06/29 10:50:15
// Design Name: 
// Module Name: test_mux32
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


module test_mux32;
    // parameter half_period = 50;
    parameter size = 32;
    
    reg [size-1:0] in0, in1;
    reg sel;
    wire [size-1:0] mux_out;
    
    mux32 #(size) UUT (in0, in1, sel, mux_out);
       
    initial begin
        #0 in0 = 0; in1 = 12; sel = 0;
        #100 sel = 1;
        #100 in0 = -1; sel = 0;
    end
    // always #half_period clk = ~clk;
    initial #400 $stop;
endmodule
