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
// author:QI SUN
//////////////////////////////////////////////////////////////////////////////////


module forwarding_unit(// deal with ex hazard and mem hazard in chapter 8
    input ex_mem_write,mem_wb_write,
    input [4:0]ex_mem_dst,mem_wb_dst,
    input [4:0]id_ex_rs,id_ex_rt,
    output reg [1:0]forwardA,forwardB

    );
    always @(ex_mem_write or mem_wb_write or ex_mem_dst or  mem_wb_dst or id_ex_rs or id_ex_rt)
    begin
       if(ex_mem_write==1 && ex_mem_dst!=0 && ex_mem_dst==id_ex_rs)
        forwardA<=2'b10;//exhazard
       else if(mem_wb_write==1 && mem_wb_dst!=0 && mem_wb_dst==id_ex_rs  )
         forwardA<=2'b01;//memhazard
       else 
         forwardA<=2'b00;
         
         
       if(ex_mem_write==1 && ex_mem_dst!=0 && ex_mem_dst==id_ex_rt)
        forwardB<=2'b10;//exhazard
       else if(mem_wb_write==1 && mem_wb_dst!=0 && mem_wb_dst==id_ex_rt )
         forwardB<=2'b01;//memhazard
       else 
         forwardB<=2'b00;
         
        
    end
endmodule
