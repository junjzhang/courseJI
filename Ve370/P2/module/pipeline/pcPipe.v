`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Author: 
//  Junjie ZHang
// Module Name: pcPipe
// Description: 
//   program counter for pipeline CPU, rising edge synchronous
// Dependencies: 
//  None
//////////////////////////////////////////////////////////////////////////////////


module pcPipe(
    input clk, pcWrite, reset,
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
        else if(pcWrite == 1'b1)
            out <= in;
    end
    
endmodule