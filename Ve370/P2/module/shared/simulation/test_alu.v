`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Rui Ding
// 
// Create Date: 2020/06/29 11:18:44
// Design Name: 
// Module Name: test_alu
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


module test_alu;
    // parameter half_period = 50;
    parameter size = 32;
    
    reg [size-1:0] in1, in2;
    reg [size-29:0] control;
    wire zero;
    wire [31:0] out;
    
    alu #(size) UUT (in1,in2, control, zero, out);
       
    initial begin
        #0 in1 = 21; in2 = 12; control = 4'b0000;
        #100 control = 4'b0001;
        #100 control = 4'b0010;
        #100 control = 4'b0111;
        #100 in1 = 12; control = 4'b0110;
    end
    // always #half_period clk = ~clk;
    initial #600 $stop;
endmodule
