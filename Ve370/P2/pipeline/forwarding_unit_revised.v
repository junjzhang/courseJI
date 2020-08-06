`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/02 20:51:56
// Design Name: 
// Module Name: forwarding_unit
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
// author:QI SUN & Junjie Zhang
//////////////////////////////////////////////////////////////////////////////////


module forwarding_unit(// deal with ex hazard and mem hazard and control hazard
    input if_id_branch,ex_mem_write,mem_wb_write,
    input [4:0]ex_mem_dst,mem_wb_dst,
    input [4:0]if_id_rs,if_id_rt,id_ex_rs,id_ex_rt,
    output reg [1:0]forward_EX_A,forward_EX_B, // to ex and mem hazard
    output reg forward_ID_A,forward_ID_B

    );
    always @(ex_mem_write or mem_wb_write or ex_mem_dst or  mem_wb_dst or id_ex_rs or id_ex_rt)
    begin
    // ex & mem hazard
        // rs condition
       if(ex_mem_write && ex_mem_dst!=0 && ex_mem_dst==id_ex_rs)
         forward_EX_A<=2'b10;//exhazard
       else if(mem_wb_write && mem_wb_dst!=0 && mem_wb_dst==id_ex_rs)
         forward_EX_A<=2'b01;//memhazard
       else 
         forward_EX_A<=2'b00;
         
        //rt condition
       if(ex_mem_write && ex_mem_dst!=0 && ex_mem_dst==id_ex_rt)
        forward_EX_B<=2'b10;//exhazard
       else if(mem_wb_write && mem_wb_dst!=0 && mem_wb_dst==id_ex_rt )
         forward_EX_B<=2'b01;//memhazard
       else 
         forward_EX_B<=2'b00;

    // control hazard 
        // rs condition
        if(ex_mem_write && if_id_branch && ex_mem_dst!=0 && ex_mem_dst == id_ex_rs)
          forward_ID_A<=1'b1;
        else
          forward_ID_A<=1'b0;
        // rt condition
        if(ex_mem_write && if_id_branch && ex_mem_dst!=0 && ex_mem_dst == id_ex_rt)
          forward_ID_B<=1'b1;
        else
          forward_ID_B<=1'b0;
        

    end
endmodule
