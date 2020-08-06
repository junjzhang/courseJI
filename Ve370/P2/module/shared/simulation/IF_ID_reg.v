`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/01 21:13:39
// Design Name: 
// Module Name: IF_ID_reg
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


module IF_ID_reg(
 input [31:0] pc_if,//used in ID stage, serve for beq, bne, j
 input [31:0]inst_if,
 input reset,
 input idflush,// decide whether to make all the things to 0
 input clk,
 input IF_ID_write,//decide whether to update
 output reg [31:0] pc_id,
 output reg [31:0] inst_id

 
    );
  always @ (posedge clk or posedge reset )
    begin
        if (reset==1)
        begin
           pc_id<=32'b0;
            inst_id<=32'b0;
         end
        else if( idflush== 1'b1)
           begin
            pc_id<=32'b0;
            inst_id<=32'b0;
           end
        else if (IF_ID_write==0)
           begin
            pc_id<=pc_id;
            inst_id<=inst_id;
           end 
        else
        begin
            pc_id<=pc_if;
            inst_id<=inst_if;
        end
    end
endmodule
