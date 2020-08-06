`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/04 22:51:16
// Design Name: 
// Module Name: brunch_jump_mux_sel
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


module branch_jump_mux_sel(
    input brancheq, branchneq, comparatorresult,
    output reg sel
    );
    
    always @ (brancheq or branchneq or comparatorresult)
    begin
        if (brancheq == 1 & comparatorresult==1)
            sel=1;
        else if (branchneq==1 & comparatorresult==0)
            sel=1;
        else
            sel=0;
    end
    
endmodule
