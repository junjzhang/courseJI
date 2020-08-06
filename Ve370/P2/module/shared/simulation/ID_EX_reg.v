`timescale 1ns / 1ps

// Create Date: 2020/07/01 22:10:19
// Author: QI SUN
// Design Name: 
// Module Name: ID_EX_reg
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: ID/EX reg
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// author: QI SUN
//////////////////////////////////////////////////////////////////////////////////


module ID_EX_reg(
 input clk,
 input regDst, memRead, memtoReg, memWrite, aluSrc, regWrite,// beq, bne, j are already used
 input [1:0] aluop,
 input [31:0] read_data1, read_data2,
 input [31:0] sign_ext,
 input [4:0] reg_rs,reg_rt,reg_rd,
 input reset,
 output reg regDst_out, memRead_out, memtoReg_out, memWrite_out, aluSrc_out, regWrite_out,
 output reg [1:0] aluop_out,
 output reg [31:0] read_data1_out, read_data2_out,
 output reg [31:0] sign_ext_out,
 output reg [4:0] reg_rs_out,reg_rt_out,reg_rd_out
 

 
 

    );
    always @(posedge clk or posedge reset)
      begin
      if(reset==1)
      begin
      {regDst_out, memRead_out, memtoReg_out, memWrite_out, aluSrc_out, regWrite_out}<=6'b0;
        aluop_out<=2'b0;
        {read_data1_out, read_data2_out,sign_ext_out}<=96'b0;
        {reg_rs_out,reg_rt_out,reg_rd_out}<=15'b0;
       end
      else
      begin
        {regDst_out, memRead_out, memtoReg_out, memWrite_out, aluSrc_out, regWrite_out}<={regDst, memRead, memtoReg, memWrite, aluSrc, regWrite};
        aluop_out<=aluop;
        {read_data1_out, read_data2_out,sign_ext_out}<={read_data1,read_data2,sign_ext};
        {reg_rs_out,reg_rt_out,reg_rd_out}<={reg_rs,reg_rt,reg_rd};
 
      end
      end
      endmodule
