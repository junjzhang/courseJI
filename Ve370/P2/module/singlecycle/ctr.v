`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Author: 
//  Junjie ZHang
// Module Name: ctr
// Description: 
//  Control unit
// Dependencies: 
//  None
//////////////////////////////////////////////////////////////////////////////////


module ctr(
    input [5:0] opCode,
    output reg regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite,
    output reg [1:0] aluOp
    );
    
    always @ (opCode)
    begin
        case (opCode)
            6'b000000: // R-type
                {regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp} <= 11'b10000000110;
            6'b000010: // j
                {regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp} <= 11'b01000000000;
            6'b000100: // beq
                {regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp} <= 11'b00100000001;
            6'b000101: // bne
                {regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp} <= 11'b00010000001;
            6'b001000: // addi
                {regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp} <= 11'b00000001100;
            6'b001100: // andi
                {regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp} <= 11'b00000001111;
            6'b100011: // lw
                {regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp} <= 11'b00001101100;
            6'b101011: // sw
                {regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp} <= 11'b00000011000;
            default:
                {regDst, jump, branchEq, branchNeq, memRead, memtoReg, memWrite, aluSrc, regWrite, aluOp} <= 11'b00000000000;
        endcase
    end
endmodule
