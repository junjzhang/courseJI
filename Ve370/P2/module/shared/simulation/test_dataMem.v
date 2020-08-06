`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/06/26 14:37:47
// Design Name: 
// Module Name: test_dataMem
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


module test_dataMem;
    parameter half_period = 50;
    parameter size = 32;
    
    reg [size-1:0] address, writeData;
    reg clk, memRead, memWrite, reset;
    wire [size-1:0] out;
    
    dataMem #(size) UUT ( clk, memRead, memWrite, reset,address, writeData, out);
       
    initial begin
        #0 clk = 0; memWrite = 1; memRead = 0; reset = 0; address = 0; writeData = 2;
        #100 memWrite = 0; memRead = 1; reset = 0; address = 0;
        #100 reset = 1;
    end
    always #half_period clk = ~clk;
    initial #400 $stop;
endmodule