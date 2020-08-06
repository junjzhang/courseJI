`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/04 14:25:10
// Design Name: 
// Module Name: pipcpu
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


module pipcpu(
    clk
    );
    
    input clk;
    
    wire [31:0] pc_in_IF, pc_out_IF, instruction_IF, pc_plus_4, pc_ID, instruction_ID, sign_extended_addr_ID, branchshift, branchaddr, data_back_WB, read_data1_ID, read_data2_ID, displayData, Forward1Out, Forward2Out, Forward1_EX, Forward2_EX, sign_extended_addr_EX, ForwardAOut_EX, ForwardBOut_EX, ALUIN_B, ALUOut_EX, ALUOut_MEM, WriteData_MEM, DataRead_MEM, DataRead_WB, DMIN, ALUOut_WB, BJaddr;
    
    wire [27:0] jumpaddr;
    wire [4:0] displayReg, Dst_EX, Dst_MEM, Dst_WB, Rs_EX, Rt_EX, Rd_EX;
    
    wire [3:0] alu_ctrl;
    
    wire [1:0] alu_op_ID, Forward1, Forward2, alu_op_EX, ForwardA, ForwardB, MemSrc;
    
    wire pcWrite, IDflush, IFID_Write, RegDst_ID, jump, BranchEq, BranchNeq, Adder_Zero, MemRead_ID, MemtoReg_ID, MemWrite_ID, ALUSrc_ID, RegWrite_ID, IFflush, MemRead_MEM, MemtoReg_MEM, MemWrite_MEM, RegWrite_MEM, MemRead_WB, MemtoReg_WB, RegWrite_WB, NopSel, RegDst_EX, MemRead_EX, MemtoReg_EX, MemWrite_EX, ALUSrc_EX, RegWrite_EX, RegDstOut_ID, MemReadOut_ID, MemtoRegOut_ID, MemWriteOut_ID, ALUSrcOut_ID, RegWriteOut_ID, ComparatorResult, ALU_Zero, BranchJumpSel;
    
    
    reg reset;
    
    
    
    pcPipe PCmodule(clk, pcWrite, reset, pc_in_IF, pc_out_IF);
    shiftLeft2N26 addr28(instruction_ID[25:0], jumpaddr);
    pcadder PCadder1(pc_out_IF, pc_plus_4);
    insMem Instr_Mem(pc_out_IF, instruction_IF);
    IF_ID_reg IFID(pc_out_IF, instruction_IF, reset, IDflush, clk, IFID_Write, pc_ID, instruction_ID);
    signExt signExtend(instruction_ID[15:0], sign_extended_addr_ID);
    control_pipe Ctrl(instruction_ID[31:26], ComparatorResult, RegDst_ID, jump, BranchEq, BranchNeq, MemRead_ID, MemtoReg_ID, MemWrite_ID, ALUSrc_ID, RegWrite_ID, alu_op_ID, IFflush);
    shiftLeft2N32 SignEx_to_Addr(sign_extended_addr_ID, branchshift);
    alu ALUadder(branchshift, pc_ID, 4'b0010, Adder_Zero, branchaddr);
    regFile Register_File(instruction_ID[25:21], instruction_ID[20:16], Dst_WB, displayReg, data_back_WB, clk, RegWrite_WB, reset, read_data1_ID, read_data2_ID, displayData);
    hazard_detect_unit Hazard_Det(MemRead_EX, Dst_EX, instruction_ID[25:21], instruction_ID[20:16], pcWrite, IFID_Write, NopSel);
    load_use_mux NopMux(NopSel, RegDst_ID, MemRead_ID, MemtoReg_ID, MemWrite_ID, ALUSrc_ID, RegWrite_ID, alu_op_ID, RegDstOut_ID, MemReadOut_ID, MemtoRegOut_ID, MemWriteOut_ID, ALUSrcOut_ID, RegWriteOut_ID);
    comparator_forwarding_unit Comparator_Forwarding_Sel(Dst_MEM, Dst_WB, instruction_ID[25:21], instruction_ID[20:16], RegWrite_MEM, RegWrite_WB, Forward1, Forward2);
    forward_mux_comparator Forward_Unit1(read_data1_ID, ALUOut_MEM, data_back_WB, Forward1, Forward1Out);
    forward_mux_comparator Forward_Unit2(read_data2_ID, ALUOut_MEM, data_back_WB, Forward2, Forward2Out);
    comparator Comparator(Forward1Out, Forward2Out, ComparatorResult);
    branch_jump_mux_sel BJMuxSel(BranchEq, BranchNeq, ComparatorResult, BranchJumpSel);
    ID_EX_reg IDEX(clk, RegDstOut_ID, MemReadOut_ID, MemtoRegOut_ID, MemWriteOut_ID, ALUSrcOut_ID, RegWriteOut_ID, alu_op_ID, read_data1_ID, read_data2_ID, sign_extended_addr_ID, instruction_ID[25:21], instruction_ID[20:16], instruction_ID[15:11], reset, RegDst_EX, MemRead_EX, MemtoReg_EX, MemWrite_EX, ALUSrc_EX, RegWrite_EX, alu_op_EX, Forward1_EX, Forward2_EX, sign_extended_addr_EX, Rs_EX, Rt_EX, Rd_EX);
    mux5 DstMux(Rt_EX, Rd_EX, RegDst_EX, Dst_EX);
    forwarding_unit ForwardingU(RegWrite_MEM, RegWrite_WB, Dst_MEM, Dst_WB, Rs_EX, Rt_EX, ForwardA, ForwardB);
    forwarding_mux Forward_UnitA(Forward1_EX, data_back_WB, ALUOut_MEM, ForwardA, ForwardAOut_EX);
    forwarding_mux Forward_UnitB(Forward2_EX, data_back_WB, ALUOut_MEM, ForwardB, ForwardBOut_EX);
    mux32 ALUSrcMux(ForwardBOut_EX, sign_extended_addr_EX, ALUSrc_EX, ALUIN_B);
    aluCtr ALUCtrl(sign_extended_addr_EX[5:0], alu_op_EX, alu_ctrl);
    alu ALU(ForwardAOut_EX, ALUIN_B, alu_ctrl, ALU_Zero, ALUOut_EX);
    EX_MEM_reg EXMEM(clk, MemRead_EX, MemtoReg_EX, MemWrite_EX, RegWrite_EX, ALUOut_EX, ForwardBOut_EX, Dst_EX, reset, MemRead_MEM, MemtoReg_MEM, MemWrite_MEM, RegWrite_MEM, ALUOut_MEM, WriteData_MEM, Dst_MEM);
    memory_forwarding_unit MemForwardingU(MemRead_WB, MemWrite_MEM, RegWrite_WB, Dst_WB, Dst_MEM, MemSrc);
    memory_mux MemMux(WriteData_MEM, DataRead_WB, ALUOut_WB, MemSrc, DMIN);
    dataMem Data_Memory(clk, MemRead_MEM, MemWrite_MEM, reset, ALUOut_MEM, DMIN, DataRead_MEM);
    MEM_WB_reg MEMWB(clk, RegWrite_MEM, MemtoReg_MEM, DataRead_MEM, ALUOut_MEM, Dst_MEM, reset, MemRead_MEM, RegWrite_WB, MemtoReg_WB, MemRead_WB, DataRead_WB, ALUOut_WB, Dst_WB);
    mux32 DataBack(ALUOut_WB, DataRead_WB, MemtoReg_WB, data_back_WB);
    mux32 BranchJump({pc_plus_4[31:28],jumpaddr}, branchaddr, BranchJumpSel, BJaddr);
    pc_mux PCMUX(pc_plus_4, BJaddr, IFflush, pc_in_IF);
    
endmodule
