`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Author: 
//  Junjie ZHang
// Module Name: shiftLeft2N32
// Description: 
//  Shfit the 32bits input to left by 2bits
// Dependencies: 
//  None
//////////////////////////////////////////////////////////////////////////////////


module shiftLeft2N32(
    input [31:0] in,
    output [31:0] out
    );
    
    assign out = {in[29:0],2'b0};
    
endmodule
