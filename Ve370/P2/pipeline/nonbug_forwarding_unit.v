`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/08 15:24:24
// Design Name: 
// Module Name: nonbug_forwarding_unit
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


module nonbug_forwarding_unit(
    input [4:0] wb_dst, reg_dst,
    output reg sel
    
    
    );
    initial
    begin
        sel <=0;
    end
    
    always @(wb_dst or reg_dst)
    begin
        if (wb_dst==reg_dst)
            sel <=1;
        else
            sel <=0;
     end
            
    
endmodule
