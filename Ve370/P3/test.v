`timescale 1ns / 1ps
`include "./1a/cache1a.v"
//`include "./1b/cache1b.v"
//`include "./2a/cache2a.v"
//`include "./2b/cache2b.v"
`include "./mainMem/mainMem.v"
`include "main.v"

module test();

    reg [31:0] write_data;
    reg [9:0] address;
    reg readWrite;
    wire [31:0] readData;
    wire hitMiss;
    integer i;
    integer j;
    integer k;
    integer index;
    parameter break = 10;

    main uut(readWrite, address, write_data, hitMiss, readData);

    initial begin
        i = 0;
        #0 readWrite = 0; address = 10'b0000000000; //should miss
        #10 readWrite = 1; address = 10'b0000000000; write_data = 8'b11111111; //should hit
        #10 readWrite = 0; address = 10'b0000000000; //should hit and read out 0xff

        //here check main memory content,
        //the first byte should remain 0x00 if it is write-back,
        //should change to 0xff if it is write-through.

        #10 readWrite = 0; address = 10'b1000000000; //should miss
        #10 readWrite = 0; address = 10'b0000000000; //should hit for 2-way associative, should miss for directly mapped

        #10 readWrite = 0; address = 10'b1100000000; //should miss
        #10 readWrite = 0; address = 10'b1000000000; //should miss both for directly mapped and for 2-way associative (Least-Recently-Used policy)
        #15
        //here check main memory content,
        //the first byte should be 0xff
        $stop;
    end
    
    always #break begin
        // test for 1a version
        
            $display("Round %d: readWrite = %b, address = %d", i, readWrite, address);
            $display("hit_flag=%b, addr_cache=%b,index=%d",main.cache.hit_flag,main.cache.addr_cache,main.cache.index);
            $display("addrmem=%d,read_mem=%b",main.mem.addr,main.mem.readWrite);
            $display("ReadData=%d",main.cache.ReadData_cache);
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
        
        
        //test for 1b version
        /*
            $display("Round %d: readWrite = %b, address = %d, addr_tag=%b", i, readWrite, address, main.cache.addr_tag);
            $display("hit_flag=%b, addr_cache=%b,index=%d",main.cache.hit_flag,main.cache.addr_cache,main.cache.index);
            $display("valid bit=%b",main.cache.v[{1'b1,1'b0}]);
            $display("addrmem=%d,read_mem=%b",main.mem.addr,main.mem.readWrite);
            $display("ReadData=%d",main.cache.ReadData_cache);
            $display("Set0:LRU=%d",main.cache.LRU[0]);
            $display("Block0: Tag=%b; V=%b; Word0=%b; Word1=%b; Word2=%b; Word3=%b",main.cache.tag[0],main.cache.v[0],main.cache.set[0][31:0],main.cache.set[0][63:32],main.cache.set[0][95:64],main.cache.set[0][127:96]);
            $display("Block1: Tag=%b; V=%b; Word0=%b; Word1=%b; Word2=%b; Word3=%b",main.cache.tag[1],main.cache.v[1],main.cache.set[0][159:128],main.cache.set[0][191:160],main.cache.set[0][223:192],main.cache.set[0][255:224]);
            $display("Set1:LRU=%d",main.cache.LRU[1]);
            $display("Block0: Tag=%b; V=%b; Word0=%b; Word1=%b; Word2=%b; Word3=%b",main.cache.tag[2],main.cache.v[2],main.cache.set[1][31:0],main.cache.set[1][63:32],main.cache.set[1][95:64],main.cache.set[1][127:96]);
            $display("Block1: Tag=%b; V=%b; Word0=%b; Word1=%b; Word2=%b; Word3=%b",main.cache.tag[3],main.cache.v[3],main.cache.set[1][159:128],main.cache.set[1][191:160],main.cache.set[1][223:192],main.cache.set[1][255:224]);
            $display("Mem[4]=%d, Mem[5]=%d, Mem[6]=%d,Mem[7]=%d",main.mem.memory[4],main.mem.memory[5],main.mem.memory[6],main.mem.memory[7]);
            $display("Mem[8]=%d, Mem[9]=%d, Mem[10]=%d,Mem[11]=%d",main.mem.memory[8],main.mem.memory[9],main.mem.memory[10],main.mem.memory[11]);
            $display("Mem[12]=%d,Mem[13]=%d,Mem[14]=%d,Mem[15]=%d",main.mem.memory[12],main.mem.memory[13],main.mem.memory[14],main.mem.memory[15]);
            $display("Mem[16]=%d,Mem[17]=%d,Mem[18]=%d,Mem[19]=%d",main.mem.memory[16],main.mem.memory[17],main.mem.memory[18],main.mem.memory[19]);
            i = i + 1;
        */
        
            
        //test for 2a version
        /*
            $display("Round %d: hit/miss = %0d, readWrite = %0d, address = %b", i, hitMiss, readWrite, address);
            $display("readData = 0x%h, writeData = 0x%h", readData, write_data);
            $display("******cache******");
            for (j = 0; j < 4; j = j+1) begin
                $display("Block %0d: V:%b, D:%b,",j,uut.cache.cache[j][134],uut.cache.cache[j][133]);
                $display("Tag: %b, Data 0:0x%h, Data 1:0x%h, Data 2: 0x%h, Data 3: 0x%h",uut.cache.cache[j][132:128],uut.cache.cache[j][127:96],uut.cache.cache[j][95:64],uut.cache.cache[j][63:32],uut.cache.cache[j][31:0]);
            end
            $display("----------------------------------------------------------");
            i = i + 1;
        */

        //test for 2b version
        /*
            $display("Round %d: hit/miss = %0d, readWrite = %0d, address = %b", i, hitMiss, readWrite, address);
            $display("readData = 0x%h, writeData = 0x%h", readData, write_data);
            $display("******cache******");
            for (j = 0; j < 2; j = j+1) begin
                    $display("set %0d:",j);
                    $display("LRU bit = %b", uut.cache.cache[2*j][135]);
                for (k = 0; k < 2;k = k+1) begin
                    $display("Block %0d: V:%b, D:%b,",k,uut.cache.cache[2*j+k][134],uut.cache.cache[2*j+k][133]);
                    $display("Tag: %b, Data 0:0x%h, Data 1:0x%h, Data 2: 0x%h, Data 3: 0x%h",uut.cache.cache[2*j+k][132:128],uut.cache.cache[2*j+k][127:96],uut.cache.cache[2*j+k][95:64],uut.cache.cache[2*j+k][63:32],uut.cache.cache[2*j+k][31:0]);
                end
            end
            $display("----------------------------------------------------------");
            i = i + 1;
        */
    end

endmodule