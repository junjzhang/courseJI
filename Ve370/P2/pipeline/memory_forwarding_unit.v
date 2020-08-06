`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/03 21:52:12
// Design Name: 
// Module Name: memory_forwarding_unit
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


module memory_forwarding_unit(// useful when sw is behind lw and two rt are the same
    input mem_wb_memread, ex_mem_memwrite, 
    input mem_wb_regwrite,
    input [4:0] mem_wb_dst, ex_mem_dst,
    output reg [1:0]memsrc
    );
    always @(mem_wb_memread or ex_mem_memwrite or mem_wb_dst or ex_mem_dst or mem_wb_regwrite)
    begin
        if(mem_wb_dst==ex_mem_dst && mem_wb_memread==1 && ex_mem_memwrite==1 && mem_wb_regwrite==1)
           memsrc=2'b01;
        else if(mem_wb_dst==ex_mem_dst && mem_wb_memread==0 && ex_mem_memwrite==1 && mem_wb_regwrite==1)
           memsrc=2'b10;
        else
            memsrc=2'b00;
    end
endmodule
