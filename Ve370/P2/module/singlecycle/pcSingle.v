`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Author: 
//  Junjie ZHang
// Module Name: pcSingle
// Description: 
//   program counter for single cycled CPU, rising edge synchronous
// Dependencies: 
//  None
//////////////////////////////////////////////////////////////////////////////////


module pcSingle(
    input clk, reset,
    input [31:0] in,
    output reg [31:0] out
    );

    initial
    begin
        out <= 32'b0;
    end 
    
    always @ (posedge reset or posedge clk)
    begin
        if(reset == 1'b1)
            out <= 32'b0;
        else
            out <= in;
    end
    
endmodule