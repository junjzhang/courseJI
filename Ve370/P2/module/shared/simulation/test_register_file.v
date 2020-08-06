`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/06/29 19:01:56
// Design Name: 
// Module Name: test_register_file
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


module test_register_file;
    parameter half_period = 50;
    parameter size = 32;
    
    reg [size-28:0] readReg1, readReg2, writeReg, displayReg;
    reg [size-1:0] writeData;
    reg clk, regWrite, reset;
    wire [size-1:0] readData1, readData2, displayData;
    
    regFile #(size) UUT (readReg1, readReg2, writeReg, displayReg, writeData,clk, regWrite, reset, readData1, readData2,displayData);
       
    initial begin
        #0 clk = 0; reset = 1; regWrite = 0;
        #100 reset = 0; readReg1 = 1; readReg2 = 2; writeReg = 3; displayReg = 3; writeData = 12;
        #100 regWrite = 1;
        #100 readReg1 = 3;
        #100 reset = 1;
    end
    
    always #half_period clk = ~clk;
    initial #600 $stop;
endmodule
