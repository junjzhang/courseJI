`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/02 22:22:06
// Design Name: 
// Module Name: control_pipe
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


module control_pipe(// add the decision of ifflush, I don't add exflush and idflush because no need for exception
    input [5:0] opCode,
    input zero ,//the output of the comparator
    output reg regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite,
    output reg [1:0] aluOp,
    output reg ifflush
    );
    
    initial
    begin
        ifflush <= 1'b0;
    end
    
    always @ (opCode or zero)
    begin
        case (opCode)
            6'b000000: // R-type
            begin
                {regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp} <= 11'b10000000110;
                ifflush<=0;
            end
            6'b000010: // j
            begin
             {regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp} <= 11'b01000000000;
             ifflush<=1;
             end
            6'b000100: // beq
            begin
                {regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp} <= 11'b00100000001;
                if(zero==1)
                begin
                   ifflush<=1;
                end
                else
                    ifflush<=0;
            end    
            6'b000101: // bne
            begin
                {regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp} <= 11'b00010000001;
                 if(zero==0)
                begin
                   ifflush<=1;
                end
                else
                    ifflush<=0;
                end
            6'b001000: // addi
            begin
                {regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp} <= 11'b00000001100;
                ifflush<=0;
            end
            6'b001100: // andi
            begin
                {regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp} <= 11'b00000001111;
                ifflush<=0;
            end
            6'b100011: // lw
            begin
                {regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp} <= 11'b00001101100;
                ifflush<=0;
            end
            6'b101011: // sw
            begin
                {regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp} <= 11'b00000011000;
                ifflush<=0;
            end
            default:
                begin
                    {regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp} <= 11'b00000000000;
                    ifflush <=0;
                end
        endcase
    end
endmodule
