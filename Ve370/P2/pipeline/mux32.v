`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Author: 
//  Junjie ZHang
// Module Name: mux32
// Description: 
//  A 32bits two to one mux
// Dependencies: 
//  None
//////////////////////////////////////////////////////////////////////////////////


module mux32(
    input [31:0] in0, in1,
    input sel,
    output [31:0] out
    );
    
    assign out = sel?in1:in0;
    
endmodule
