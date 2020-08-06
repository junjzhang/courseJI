`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/06/29 11:32:01
// Design Name: 
// Module Name: test_aluctr
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


module test_aluctr;
    // parameter half_period = 50;
    // parameter size = 32;
    
    reg [5:0] funct;
    reg [1:0] aluOp;
    wire [3:0] control;
    
    aluCtr UUT (funct, aluOp, control);
       
    initial begin
        #0 funct = 6'b100010; aluOp = 2'b00;
        #100 aluOp = 2'b01;
        #100 aluOp = 2'b10;
        #100 aluOp = 2'b11;
    end
    // always #half_period clk = ~clk;
    initial #600 $stop;
endmodule
