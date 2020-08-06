`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/01 20:33:23
// Design Name: 
// Module Name: forwarding_mux
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
// author: QI SUN
//////////////////////////////////////////////////////////////////////////////////


module forwarding_mux(//solve mem hazard, ex hazard in chapter 8
     input [31:0] current, mem_wb, ex_mem,
     input [1:0] sel,
     output reg[31:0] out
     
    );
    always @(current, mem_wb, ex_mem, sel)
    begin
    case(sel)
    2'b00:out=current;
    2'b01:out=mem_wb;
    2'b10:out=ex_mem;
    default: out=32'b0;
    endcase
    end
    
endmodule
