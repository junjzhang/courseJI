`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/06 12:35:26
// Design Name: 
// Module Name: test_pipeline_cpu
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


module test_pipeline_cpu;
    parameter half_period = 5;
    reg clk;
    reg reset;

    integer counter;   
    
    pipcpu Pipcpu(clk, reset);
    

    initial begin
        counter = 0;
        clk = 0;
        forever 
            #half_period clk = ~clk;
    end

    always @ (posedge clk) begin

        if (counter == 50)
            $stop;

            

        $display("Time: %4d,  CLK = %b", $time, clk);
        $display("RF_data1=%x",Pipcpu.read_data1_ID);
        $display("RF_data2=%x",Pipcpu.read_data2_ID);
        $display("Forward1=%b", Pipcpu.Forward1);
        $display("Forward2=%b", Pipcpu.Forward2);
        $display("Comparatorinput1=%x", Pipcpu.Forward1Out);
        $display("Comparatorinput2=%x", Pipcpu.Forward2Out);
        $display("comparatorout=%b", Pipcpu.ComparatorResult);
        $display("IFflush: %b", Pipcpu.IFflush);
        $display("PC = %d", Pipcpu.pc_out_IF);
        $display("PC+4 = %d", Pipcpu.pc_plus_4);
        $display("New_PC = %d", Pipcpu.pc_in_IF);
        $display("Forward1Input0 = %x", Pipcpu.read_data1_ID);
        $display("ForwardA=%b",Pipcpu.ForwardA);
        $display("ForwardB=%b",Pipcpu.ForwardB);
        $display("ALU_in1=%x", Pipcpu.ForwardAOut_EX);
        $display("ALU_in2=%x", Pipcpu.ALUIN_B);
        $display("ALU_Out=%x", Pipcpu.ALUOut_EX);
        $display("ALU_Out_MEM=%x", Pipcpu.ALUOut_MEM);
        $display("WriteData_MEM=%x", Pipcpu.WriteData_MEM);
        $display("MemWrite_MEM=%x", Pipcpu.MemWrite_MEM);
        $display("ALU_Out_WB=%x", Pipcpu.ALUOut_WB);
        $display("Data_back=%x", Pipcpu.data_back_WB);
        $display("RegWrite=%b",Pipcpu.RegWrite_WB);
        $display("MemtoReg=%b",Pipcpu.MemtoReg_WB);
        $display("Instruction in IF = %b", Pipcpu.instruction_IF);
        $display("Instruction in ID = %b", Pipcpu.instruction_ID);
        $display("ALUOp in ID= %b",Pipcpu.alu_op_ID);
        $display("ALUOp in EX= %b",Pipcpu.alu_op_EX);

        // display the register file

        $display("----------REGISTER FILE----------");

        $display($time,,"R0(r0) =%x, R8 (t0) =%x, R16(s0) =%x, R24(t8) =%x", Pipcpu.Register_File.file[0], Pipcpu.Register_File.file[8] , Pipcpu.Register_File.file[16], Pipcpu.Register_File.file[24]);
        $display($time,,"R1(at) =%x, R9 (t1) =%x, R17(s1) =%x, R25(t9) =%x", Pipcpu.Register_File.file[1], Pipcpu.Register_File.file[9] , Pipcpu.Register_File.file[17], Pipcpu.Register_File.file[25]);
        $display($time,,"R2(v0) =%x, R10(t2) =%x, R18(s2) =%x, R26(k0) =%x", Pipcpu.Register_File.file[2], Pipcpu.Register_File.file[10], Pipcpu.Register_File.file[18], Pipcpu.Register_File.file[26]);
        $display($time,,"R3(v1) =%x, R11(t3) =%x, R19(s3) =%x, R27(k1) =%x", Pipcpu.Register_File.file[3], Pipcpu.Register_File.file[11], Pipcpu.Register_File.file[19], Pipcpu.Register_File.file[27]);
        $display($time,,"R4(a0) =%x, R12(t4) =%x, R20(s4) =%x, R28(gp) =%x", Pipcpu.Register_File.file[4], Pipcpu.Register_File.file[12], Pipcpu.Register_File.file[20], Pipcpu.Register_File.file[28]);
        $display($time,,"R5(a1) =%x, R13(t5) =%x, R21(s5) =%x, R29(sp) =%x", Pipcpu.Register_File.file[5], Pipcpu.Register_File.file[13], Pipcpu.Register_File.file[21], Pipcpu.Register_File.file[29]);
        $display($time,,"R6(a2) =%x, R14(t6) =%x, R22(s6) =%x, R30(s8) =%x", Pipcpu.Register_File.file[6], Pipcpu.Register_File.file[14], Pipcpu.Register_File.file[22], Pipcpu.Register_File.file[30]);
        $display($time,,"R7(a3) =%x, R15(t7) =%x, R23(s7) =%x, R31(ra) =%x", Pipcpu.Register_File.file[7], Pipcpu.Register_File.file[15], Pipcpu.Register_File.file[23], Pipcpu.Register_File.file[31]);

        
        // display the data memory

        $display($time,,"Data mem.: 0x00 =%x", {Pipcpu.Data_Memory.mem[0] , Pipcpu.Data_Memory.mem[1] , Pipcpu.Data_Memory.mem[2] , Pipcpu.Data_Memory.mem[3] });
        $display($time,,"Data mem.: 0x04 =%x", {Pipcpu.Data_Memory.mem[4] , Pipcpu.Data_Memory.mem[5] , Pipcpu.Data_Memory.mem[6] , Pipcpu.Data_Memory.mem[7] });
        $display($time,,"Data mem.: 0x08 =%x", {Pipcpu.Data_Memory.mem[8], Pipcpu.Data_Memory.mem[9], Pipcpu.Data_Memory.mem[10] , Pipcpu.Data_Memory.mem[11] });
        $display($time,,"Data mem.: 0x0c =%x", {Pipcpu.Data_Memory.mem[12], Pipcpu.Data_Memory.mem[13], Pipcpu.Data_Memory.mem[14], Pipcpu.Data_Memory.mem[15]});
        $display($time,,"Data mem.: 0x10 =%x", {Pipcpu.Data_Memory.mem[16], Pipcpu.Data_Memory.mem[17], Pipcpu.Data_Memory.mem[18], Pipcpu.Data_Memory.mem[19]});

        $display("\n");

        counter = counter + 1;

    end


endmodule
