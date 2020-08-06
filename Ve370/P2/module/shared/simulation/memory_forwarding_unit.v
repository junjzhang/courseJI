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
    input [4:0] mem_wb_rt, ex_mem_rt,
    output reg memsrc
    );
    always @(mem_wb_memread or ex_mem_memwrite or mem_wb_rt or ex_mem_rt)
    begin
        if(mem_wb_rt==ex_mem_rt && mem_wb_memread==1 && ex_mem_memwrite==1 )
           memsrc=1;
        else
           memsrc=0;
    end
endmodule
