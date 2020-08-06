`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/06/28 21:51:03
// Design Name: 
// Module Name: test_pcadder
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


module test_pcadder;
    parameter half_period = 50;
    parameter size = 32;
    
    reg [size-1:0] oldpc;
    wire [size-1:0] pc_plus_4;
    
    pcadder #(size) UUT (oldpc, pc_plus_4);
       
    initial begin
        #0 oldpc = 0;
        #100 oldpc = 4;
        #100 oldpc = 12;
    end

    initial #400 $stop;
endmodule
