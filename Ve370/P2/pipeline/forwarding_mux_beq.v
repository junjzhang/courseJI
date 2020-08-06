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
// author: Junjie Zhang
//////////////////////////////////////////////////////////////////////////////////


module forwarding_mux_beq(//solve control hazard
     input [31:0] current, ex_mem,
     input [1:0] sel,
     output reg[31:0] out
     
    );
    always @(current,ex_mem, sel)
    begin
    case(sel)
    1'b0:out=current;
    1'b1:out=mem_wb;
    default: out=32'b0;
    endcase
    end
    
endmodule
