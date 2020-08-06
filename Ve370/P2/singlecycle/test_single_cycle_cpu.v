`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// Rui Ding
// Create Date: 2020/07/01 10:59:29
// Design Name: 
// Module Name: test_single_cycle_cpu
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


module test_single_cycle_cpu;
    parameter half_period = 50;
    
    reg clk;
    integer counter;
    
    // always #half_period clk = ~clk;
    
    cpu single_cycle_cpu(clk);
    
    initial begin
        counter = 0;
        clk = 0;
    end
    
    // always #half_period clk = ~clk;
    
    always @ (posedge clk) begin
        // #0 clk = 0;
        #50 clk <= ~clk;
        if (counter == 10);
            $stop;
            
        // display the register file
        $display("Time: %4d,  CLK = %b,  PC = 0x%h", $time, clk, single_cycle_cpu.new_pc);
        $display($time,,"R0(r0) =%d, R8 (t0) =%b, R16(s0) =%d, R24(t8) =%d", single_cycle_cpu.Register_File.file[0], single_cycle_cpu.Register_File.file[8] , single_cycle_cpu.Register_File.file[16], single_cycle_cpu.Register_File.file[24]);
        $display($time,,"R1(at) =%d, R9 (t1) =%b, R17(s1) =%b, R25(t9) =%d", single_cycle_cpu.Register_File.file[1], single_cycle_cpu.Register_File.file[9] , single_cycle_cpu.Register_File.file[17], single_cycle_cpu.Register_File.file[25]);
        $display($time,,"R2(v0) =%d, R10(t2) =%d, R18(s2) =%b, R26(k0) =%d", single_cycle_cpu.Register_File.file[2], single_cycle_cpu.Register_File.file[10], single_cycle_cpu.Register_File.file[18], single_cycle_cpu.Register_File.file[26]);
        $display($time,,"R3(v1) =%d, R11(t3) =%d, R19(s3) =%d, R27(k1) =%d", single_cycle_cpu.Register_File.file[3], single_cycle_cpu.Register_File.file[11], single_cycle_cpu.Register_File.file[19], single_cycle_cpu.Register_File.file[27]);
        $display($time,,"R4(a0) =%d, R12(t4) =%d, R20(s4) =%d, R28(gp) =%d", single_cycle_cpu.Register_File.file[4], single_cycle_cpu.Register_File.file[12], single_cycle_cpu.Register_File.file[20], single_cycle_cpu.Register_File.file[28]);
        $display($time,,"R5(a1) =%d, R13(t5) =%d, R21(s5) =%d, R29(sp) =%d", single_cycle_cpu.Register_File.file[5], single_cycle_cpu.Register_File.file[13], single_cycle_cpu.Register_File.file[21], single_cycle_cpu.Register_File.file[29]);
        $display($time,,"R6(a2) =%d, R14(t6) =%d, R22(s6) =%d, R30(s8) =%d", single_cycle_cpu.Register_File.file[6], single_cycle_cpu.Register_File.file[14], single_cycle_cpu.Register_File.file[22], single_cycle_cpu.Register_File.file[30]);
        $display($time,,"R7(a3) =%d, R15(t7) =%d, R23(s7) =%d, R31(ra) =%d", single_cycle_cpu.Register_File.file[7], single_cycle_cpu.Register_File.file[15], single_cycle_cpu.Register_File.file[23], single_cycle_cpu.Register_File.file[31]);
        
        // display the data memory
        $display($time,,"Data mem.: 0x00 =%x", {single_cycle_cpu.Data_Memory.mem[3] , single_cycle_cpu.Data_Memory.mem[2] , single_cycle_cpu.Data_Memory.mem[1] , single_cycle_cpu.Data_Memory.mem[0] });
        $display($time,,"Data mem.: 0x04 =%x", {single_cycle_cpu.Data_Memory.mem[7] , single_cycle_cpu.Data_Memory.mem[6] , single_cycle_cpu.Data_Memory.mem[5] , single_cycle_cpu.Data_Memory.mem[4] });
        $display($time,,"Data mem.: 0x08 =%x", {single_cycle_cpu.Data_Memory.mem[11], single_cycle_cpu.Data_Memory.mem[10], single_cycle_cpu.Data_Memory.mem[9] , single_cycle_cpu.Data_Memory.mem[8] });
        $display($time,,"Data mem.: 0x0c =%x", {single_cycle_cpu.Data_Memory.mem[15], single_cycle_cpu.Data_Memory.mem[14], single_cycle_cpu.Data_Memory.mem[13], single_cycle_cpu.Data_Memory.mem[12]});
        $display($time,,"Data mem.: 0x10 =%x", {single_cycle_cpu.Data_Memory.mem[19], single_cycle_cpu.Data_Memory.mem[18], single_cycle_cpu.Data_Memory.mem[17], single_cycle_cpu.Data_Memory.mem[16]});

        $display("\n");
        counter = counter + 1;
    end
    
    always #half_period clk = ~clk;
    
endmodule
