`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Author: 
//  Junjie ZHang
// Module Name: aluCtr
// Description: 
//  Control unit for ALU
// Dependencies: 
//  None
//////////////////////////////////////////////////////////////////////////////////


module aluCtr(
    input [5:0] funct,
    input [1:0] aluOp,
    output reg [3:0] control
    );
    
    always @ (funct or aluOp)
    begin
        case(aluOp)
            2'b00: // sw, lw, addi, j -> add
                control <= 4'b0010;
            2'b01: // beq, bne -> sub
                control <= 4'b0110;
            2'b10: // R-type
                case(funct)
                    6'b100000: // add -> add
                        control <= 4'b0010;
                    6'b100010: // sub -> sub
                        control <= 4'b0110;
                    6'b100100: // and -> and
                        control <= 4'b0000;
                    6'b100101: // or -> or
                        control <= 4'b0001;
                    6'b101010: // slt -> slt
                        control <= 4'b0111;
                    default:
                        control <= 4'b1111;
                endcase
            2'b11: // andi -> and
                control <= 4'b0000;
        endcase
    end
    
endmodule
