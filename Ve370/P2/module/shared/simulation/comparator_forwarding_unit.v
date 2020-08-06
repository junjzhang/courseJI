`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/02 23:29:47
// Design Name: 
// Module Name: comparator_forwarding_unit
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



module comparator_forwarding_unit( //decide which data to choose when there should be a forwarding path, solving the data hazard because of moving branch to ID stage
   input [4:0] ex_mem_dst,mem_wb_dst,
   input [4:0] id_rs, id_rt,
   input ex_mem_write,mem_wb_write,
   output reg [1:0]forward1, forward2
   
    
    
    );
    
    
    initial
    begin  
        forward1 <= 2'b0;
        forward2 <= 2'b0;
    end
    
    always @(ex_mem_dst,mem_wb_dst, id_rs, id_rt)
    begin
    if(ex_mem_write==1 && ex_mem_dst==id_rs )
    
      forward1<=2'b10;
    else if (mem_wb_write==1 && mem_wb_dst==id_rs )
      forward1<=2'b01;
    else
      forward1<=2'b0;
    if(ex_mem_write==1 && ex_mem_dst==id_rt)
    
      forward2<=2'b10;
    else if (mem_wb_write==1 &&  mem_wb_dst==id_rt)
      forward2<=2'b01;
    else
      forward2<=2'b0;
    end
endmodule