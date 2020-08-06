`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/02 23:29:47
// Design Name: 
// Module Name: comparator
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


module comparator(// comparator for branch in id stage
   input [31:0]reg_rs, reg_rt,
   output reg zero

    );
    always @(reg_rs or reg_rt)
    begin
    if(reg_rs-reg_rt==0)
       zero=1;
     else
        zero=0;
       
    end
endmodule
