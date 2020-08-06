`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Author: 
//  Junjie ZHang
// Module Name: alu
// Description: 
//  32 bits ALU which can do and, or, add ,subtract, set on less than and nor
// Dependencies: 
//  None
//////////////////////////////////////////////////////////////////////////////////


module alu(
    input [31:0] in0, in1,
    input [3:0] control,
    output zero,
    output reg [31:0] out
    );
    
    always @ (control or in0 or in1)
    begin
        case (control)
            4'b0000: // and
                out <= in0 & in1; 
            4'b0001: // or
                out <= in0 | in1;
            4'b0010: // add
                out <= in0 + in1;
            4'b0110: // sub
                out <= in0 - in1;
            4'b0111: // slt
                out <= (in0 < in1) ? 1 : 0;
            4'b1100: // nor
                out = ~(in0 | in1);
            default:
                out <= in1;
        endcase
    end
    
    assign zero = ((in0 - in1) == 0); 
    
endmodule
