`timescale 1ns / 1ps

module test();
    reg [31:0] writeData;
    reg [9:0] addr;
    reg readWrite;
    wire [31:0] readData;
    wire hitMiss;
    integer i;
    main uut(readWrite, addr, writeData, hitMiss, readData);
    initial begin
        writeData = 32'b0;
        addr = 10'b0;
        readWrite = 1'bx;
        i = 0;
        #5;
        `include "testGen.mem"
        #10;
        $stop;
    end

    always #10 begin
        //$display("Round %d: hit/miss = %d, readWrite = %d, addr = %d", i, hitMiss, readWrite, addr);
        //$display("readData = %D, writeData = %D", readData, writeData);
        //$display("----------------------------------------------------------");
        $display("Round %d: readWrite = %b, addr = %d", i, readWrite, addr);
        $display("hit_flag=%b, addr_cache=%b,index=%d",main.cache.hit_flag,main.cache.addr_cache,main.cache.index);
        $display("addrmem=%d,read_mem=%b",main.mem.addr,main.mem.readWrite);
        $display("ReadData=%d",main.cache.ReadData_cache);
        //$display("ReadData_mem: Word0=%d; Word1=%d; Word2=%d; Word3=%d",main.cache.ReadData_mem[31:0],main.cache.ReadData_mem[63:32],main.cache.ReadData_mem[95:64],main.cache.ReadData_mem[127:96]);
        //$display("ReadData_outmem: Word0=%d; Word1=%d; Word2=%d; Word3=%d",main.mem.readData[31:0],main.mem.readData[63:32],main.mem.readData[95:64],main.mem.readData[127:96]);
        $display("Block0: V=%b; Tag=%b; Word0=%d; Word1=%d; Word2=%d; Word3=%d",main.cache.v[0],main.cache.tag[0],main.cache.block[0][31:0],main.cache.block[0][63:32],main.cache.block[0][95:64],main.cache.block[0][127:96]);
        $display("Block1: V=%b; Tag=%b; Word0=%d; Word1=%d; Word2=%d; Word3=%d",main.cache.v[1],main.cache.tag[1],main.cache.block[1][31:0],main.cache.block[1][63:32],main.cache.block[1][95:64],main.cache.block[1][127:96]);
        $display("Block2: V=%b; Tag=%b; Word0=%d; Word1=%d; Word2=%d; Word3=%d",main.cache.v[2],main.cache.tag[2],main.cache.block[2][31:0],main.cache.block[2][63:32],main.cache.block[2][95:64],main.cache.block[2][127:96]);
        $display("Block3: V=%b; Tag=%b; Word0=%d; Word1=%d; Word2=%d; Word3=%d",main.cache.v[3],main.cache.tag[3],main.cache.block[3][31:0],main.cache.block[3][63:32],main.cache.block[3][95:64],main.cache.block[3][127:96]);
        $display("Mem[4]=%d, Mem[5]=%d, Mem[6]=%d,Mem[7]=%d",main.mem.memory[4],main.mem.memory[5],main.mem.memory[6],main.mem.memory[7]);
        $display("Mem[8]=%d, Mem[9]=%d, Mem[10]=%d,Mem[11]=%d",main.mem.memory[8],main.mem.memory[9],main.mem.memory[10],main.mem.memory[11]);
        $display("Mem[12]=%d,Mem[13]=%d,Mem[14]=%d,Mem[15]=%d",main.mem.memory[12],main.mem.memory[13],main.mem.memory[14],main.mem.memory[15]);
        $display("Mem[16]=%d,Mem[17]=%d,Mem[18]=%d,Mem[19]=%d",main.mem.memory[16],main.mem.memory[17],main.mem.memory[18],main.mem.memory[19]);
        $display("----------------------------------------------------------");
        i = i + 1;
    end
endmodule
