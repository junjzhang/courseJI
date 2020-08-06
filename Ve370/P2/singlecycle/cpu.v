`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Author: 
// Rui Ding
// Module Name: cpu(single_cycle)
// Description: 
// The combination of different components of single cycle processor
// Dependencies: 
//  None
//////////////////////////////////////////////////////////////////////////////////


module cpu(
    clk
    );
    
    input clk;
    
    // wires with 32-bit dataflow
    wire [31:0]instruction, alu_in_1, alu_in_2, pc_plus_4, jumpaddr, branchshift, 
    branch_pc, mm, new_pc, pc_im, extended, read_data2, alu_result, read_data_mem, write_back, displayData;
    
    // wires with 5-bit dataflow
    wire [4:0] write_register_addr;
    
    // wires with 4-bit dataflow
    wire [3:0] alu_control_in;
    
    // wires with 2-bit dataflow
    wire [1:0] alu_op;
    
    // wires with 1-bit dataflow
    wire IfBranch, RegDst, Branch, Branchneq, Jump, MemRead, MemtoReg, MemWrite, ALUSrc, RegWrite, Zero;
    
    reg rst;
    reg displayReg;
    // reg [31:0] PC;
    
    // always @(posedge clk)
    
    pcSingle PCmodule(clk, rst, new_pc, pc_im);
    shiftLeft2N26 Shiftleft1(jumpaddr[27:0], instruction[25:0]);
    and(IfBranch, Branch, Zero);
    and(IfBranch, Branchneq, ~Zero);
    pcadder PC_adder(pc_im, pc_plus_4);
    insMem Instruction_Memory(pc_im, instruction);
    ctr Control(instruction[31:26], RegDst, Jump, Branch, Branchneq, MemRead, MemtoReg, MemWrite, ALUSrc, RegWrite, alu_op);
    mux5 Mux1(instruction[25:21], instruction[20:16], RegDst, write_register_addr);
    regFile Register_File(instruction[25:21], instruction[20:16], write_register_addr, displayReg ,write_back, clk, RegWrite, rst, alu_in_1, read_data2, displayData);
    signExt Sign_extension(instruction[15:0],extended);
    shiftLeft2N32 Address_shifter(extended, branchshift);
    alu Alu_adder(branchshift, pc_plus_4, 4'b0010, ,branch_pc);
    mux32 Mux2(ALUSrc, alu_in_2, read_data2, extended);
    aluCtr Alu_control(instruction[5:0], alu_op, alu_control_in);
    alu ALU(alu_control_in,alu_in_1, alu_in_2, Zero, alu_result);
    dataMem Data_Memory(clk, MemRead, MemWrite, rst ,alu_result, read_data2, read_data_mem);
    mux32 Mux3(read_data_mem, alu_result, MemtoReg, write_back);
    mux32 Mux4(pc_plus_4, branch_pc, IfBranch, mm);
    mux32 Mux5(jumpaddr, mm, Jump, new_pc);
    
    
endmodule
