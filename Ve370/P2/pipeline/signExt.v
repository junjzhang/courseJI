`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Author: 
//  Junjie ZHang
// Module Name: signExt
// Description: 
//  Transform the 16bits input into 32bits output by extending its sign bit
// Dependencies: 
//  None
//////////////////////////////////////////////////////////////////////////////////


module signExt(
    input [15:0] in,
    output [31:0] out
    );
    
    assign out = {{16{in[15]}},in[15:0]};
    
endmodule
