`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/01 23:33:47
// Design Name: 
// Module Name: MEM_WB_reg
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


module MEM_WB_reg(
input clk,
input RegWrite, MemtoReg,
input [31:0] read_memory,
input [31:0] ALU_result,
input [4:0] reg_dst,
input reset,
input memread, // because of hazard when sw is after lw, so we should transport memread to wb stage
output reg RegWrite_out, MemtoReg_out,memread_out,
output reg [31:0] read_memory_out,
output reg [31:0] ALU_result_out,
output reg [4:0] reg_dst_out

    );
    always @(posedge clk or posedge reset)
    begin
    if (reset==1)
    begin
       {RegWrite_out, MemtoReg_out,memread_out}<=3'b0;
       read_memory_out<=32'b0;
       ALU_result_out<=32'b0;
       reg_dst_out<=5'b0;
    end
    else
    begin
       {RegWrite_out, MemtoReg_out,memread_out}<={RegWrite, MemtoReg,memread};
       read_memory_out<=read_memory;
       ALU_result_out<=ALU_result;
       reg_dst_out<=reg_dst;
    end
    end
endmodule
