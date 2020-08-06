`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Author: 
//  Junjie ZHang
// Module Name: shiftLeft2N26
// Description: 
//  Shfit the 26bits input to left by 2bits
// Dependencies: 
//  None
//////////////////////////////////////////////////////////////////////////////////


module shiftLeft2N26(
    input [25:0] in,
    output [27:0] out
    );
    
    assign out = {in,2'b0};
    
endmodule
