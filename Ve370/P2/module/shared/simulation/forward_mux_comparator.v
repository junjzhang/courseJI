`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/02 23:29:17
// Design Name: 
// Module Name: forward_mux_comparator
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


module forward_mux_comparator(//the mux used for solve the data hazard becasue of moving branch to ID stage
   input [31:0] current_reg, ex_mem_reg,mem_wb_reg,
   input [1:0] sel,
   output reg [31:0] out

    );

// Attention�� ��Ȼ�μ���˵comparatorǰ�ġ�from mem/wb�� �����Ҫ�������ǲ������cpu�������ҿ���֮���Ǽ���
    always @(current_reg, ex_mem_reg)
    begin
      case(sel)
       2'b0:out=current_reg;
       2'b01: out=mem_wb_reg;
       2'b10:out=ex_mem_reg;
       default: out=32'b0;
    endcase
    end
endmodule
