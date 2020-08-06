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
// Author:QI SUN
//////////////////////////////////////////////////////////////////////////////////


module hazard_detect_unit(//Ö÷ÒªÕë¶Ôload use hazard
  input id_ex_memread,
  input [4:0] id_ex_dst, if_id_rs, if_id_rt,
  output reg pc_write, if_id_write,
  output reg mux_sel  //deciding whether to make all the controls signals in id/ex to be 0
  

    );
      initial
      begin
      pc_write=1;
      if_id_write=1;
      mux_sel=0;
      end
      
    always @(id_ex_memread or id_ex_dst or if_id_rs or if_id_rt)
    begin
      if(id_ex_memread==1 &&(id_ex_dst==if_id_rt || id_ex_dst==if_id_rs))
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
