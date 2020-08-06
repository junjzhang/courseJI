`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Author: 
//  Junjie ZHang
// Module Name: mux5
// Description: 
//  A 5bits two to one mux
// Dependencies: 
//  None
//////////////////////////////////////////////////////////////////////////////////


module mux5(
    input [4:0] in0, in1,
    input sel,
    output [4:0] mux_out
    );
    
    assign mux_out = sel?in1:in0;
    
endmodule
