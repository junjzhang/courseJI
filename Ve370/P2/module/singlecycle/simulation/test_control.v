`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Rui Ding
// 
// Create Date: 2020/06/29 10:27:54
// Design Name: 
// Module Name: test_control
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


module test_control;
    parameter half_period = 50;
    // parameter size = 32;
    
    reg [5:0] opCode;
    wire regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite;
    wire [1:0] aluOp;
    
    ctr UUT (opCode, regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp);
       
    initial begin
        #0 opCode = 6'b000000;
        #100 opCode = 6'b000100;
        #100 opCode = 6'b101011;
    end
    // always #half_period clk = ~clk;
    initial #400 $stop;
endmodule
