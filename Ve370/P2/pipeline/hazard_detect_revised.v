`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/01 20:19:20
// Design Name: 
// Module Name: hazard_detect_unit
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
// Author:QI SUN & Junjie Zhang
//////////////////////////////////////////////////////////////////////////////////


module hazard_detect_unit_bonus(
  input if_id_branch, id_ex_regwrite, id_ex_regDst, id_ex_memread, ex_mem_memread,
input [4:0] id_ex_rd, id_ex_rt, if_id_rs, if_id_rt, ex_mem_dst,
output reg pc_write, if_id_write,
output reg mux_sel  //deciding whether to make all the controls signals in id/ex to be 0
);

  always @(if_id_branch or id_ex_regwrite or id_ex_regDst or id_ex_memread or ex_mem_memread or id_ex_rd or id_ex_rt or if_id_rs or if_id_rt or ex_mem_dst) 
  begin
    if(id_ex_memread &&(id_ex_rt==if_id_rt || id_ex_rt==if_id_rs))
    // load use hazard
    begin
      pc_write=0;
      if_id_write=0;
      mux_sel=1;//fill in 0
    end
    else if (id_ex_regwrite&&if_id_branch&&((id_ex_regDst==0&&(id_ex_rt==if_id_rt || id_ex_rt==if_id_rs))||(id_ex_rd == if_id_rt || id_ex_rd==if_id_rs)))
    // r-type or addi or andi or lw followed by beq
    begin
      pc_write=0;
      if_id_write=0;
      mux_sel=1;//fill in 0
    end
    else if (ex_mem_memread&&if_id_branch&&(ex_mem_dst == if_id_rs||ex_mem_dst == if_id_rt))
     // lw followed by another instruction and then beq
    begin
      pc_write=0;
      if_id_write=0;
      mux_sel=1;//fill in 0
    end
    else
    begin
      pc_write=1;
      if_id_write=1;
      mux_sel=0;//fill in 0
    end
  end
  
  
endmodule