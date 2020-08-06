`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/03 17:19:51
// Design Name: 
// Module Name: load_use_mux
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


module load_use_mux(// a mux used for flush the control signals of ID/EX register
 input sel,
 input regDst, memRead, memtoReg, memWrite, aluSrc, regWrite,// beq, bne, j are already used
 input [1:0] aluop,
 output  reg regDst_out, memRead_out, memtoReg_out, memWrite_out, aluSrc_out, regWrite_out
 

    );
    always @( regDst or memRead or memtoReg or memWrite or aluSrc or regWrite  or sel)
    begin
       case( sel)
       0:
       begin
          {regDst_out, memRead_out, memtoReg_out, memWrite_out, aluSrc_out, regWrite_out}<={regDst, memRead, memtoReg, memWrite, aluSrc, regWrite};
       end
       1:
       begin
         {regDst_out, memRead_out, memtoReg_out, memWrite_out, aluSrc_out, regWrite_out}<=6'b0;
       end
       default:
       {regDst_out, memRead_out, memtoReg_out, memWrite_out, aluSrc_out, regWrite_out}<=6'b0;
       endcase
       
       
       
       
       
    end
endmodule
