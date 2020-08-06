`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/01 23:15:20
// Design Name: 
// Module Name: EX_MEM_reg
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


module EX_MEM_reg(//only change during the rising edge of the clock
   input clk,
   input memRead, memtoReg, memWrite,regWrite,
   input [31:0]ALUresult,
   input [31:0]writedata,
   input [4:0] reg_dst,
   input reset,
   output reg memRead_out, memtoReg_out, memWrite_out,regWrite_out,
  output reg [31:0]ALUresult_out,
  output reg [31:0]writedata_out,
  output reg [4:0] reg_dst_out

    );
    always @(posedge clk or posedge reset)
    begin
    if(reset==1)
    begin
       {memRead_out, memtoReg_out, memWrite_out,regWrite_out}<=4'b0;
       ALUresult_out<=32'b0;
       writedata_out<=32'b0;
       reg_dst_out<=5'b0;
    end
    else
    begin
       {memRead_out, memtoReg_out, memWrite_out,regWrite_out}<={ memRead, memtoReg, memWrite,regWrite};
       ALUresult_out<=ALUresult;
       writedata_out<=writedata;
       reg_dst_out<=reg_dst;
    end
    end
endmodule
