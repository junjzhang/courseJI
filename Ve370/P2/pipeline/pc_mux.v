`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/03 14:30:48
// Design Name: 
// Module Name: pc_mux
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


module pc_mux(//�����mux��ʱ��sel=idflush, ����pc������ֱ���ALU_adder��result��PC_adder ��result
input [31:0] pc_normal, pc_jump,
input sel,
output reg [31:0]out

    );
always @(pc_normal, pc_jump, sel)
    begin
    case(sel)
   0: out<=pc_normal;
   1: out<=pc_jump;
   default: out<=32'b0;
    endcase
    end
    
endmodule
