`timescale 1ns / 1ps

/*****
//////
* Description:
**  A cache memory with following features:
***   write back
***   direct mapped
***   write allocate
***   ONlY request word!!
//////
* Author: Junjie Zhang
*****/


module cache2a(
    input readWrite, // 0 for read, 1 for write
    input [9:0] addr, // byte address, [9:6] tag, [5:4] cache index, [3:2] word offset, [1:0] byte offset
    input [31:0] writeData, //word data from cpu to be writen
    input [127:0] readDataMem, // block data from memory 
    output reg readWriteOut, // read or write state to memory, 0 for read, 1 for write
    output reg hitMiss, // 1 for hit, 0 for miss, state flag
    output reg [9:0] memAddr, // request address to memory
    output reg [31:0] readData, // data to cpu for 
    output reg [127:0] writeDataMem //block data from memory to be writen
);

/***
* In total, 4 blocks
* For a block:
**  1 valIdate bit (V) [133]
**  1 dirty bit (D) [132]
**  tag 4 bits [131:128]
**  data 4 words = 16 bytes [127:96] [95:64] [63:32] [31:0]
***/
parameter numBlocks = 4;
reg [133:0] cache[0:numBlocks-1]; 
                
// Initialize
integer ii; // For initialize the cache

initial begin
    for (ii = 0; ii < numBlocks; ii = ii + 1)
        cache[ii][133:128] = 6'b0; // Initialize LRU bit, V, D, tag
        cache[ii][127:0] = 128'bx; // Initialize data
    hitMiss = 1'b0;
end

always @(readWrite or addr or writeData) begin
    // initialize in each loop is needed
    hitMiss = 1'b0; 

    // a. Judege Miss or hit
    if (cache[addr[5:4]][133]) // Check if valId
        if (addr[9:6] == cache[addr[5:4]][131:128])
            hitMiss = 1'b1;

    // a.1 if not hit
    if (!hitMiss) begin
        // a.1.a Check for dirty
        // ...1 dirty
        if (cache[addr[5:4]][132]) begin
            memAddr = addr;
            readWriteOut = 1'b1; // write back
            writeDataMem = cache[addr[5:4]][127:0];
            #2; // wait for memory
        end

        // a.1.b Load data from lower part
        readWriteOut = 1'b0; // load data
        memAddr = addr;
        #2; // wait for memory
        cache[addr[5:4]][131:128] = addr[9:6]; // Update tag
        cache[addr[5:4]][127:0] = readDataMem; // Update data
        cache[addr[5:4]][133] = 1'b1; // valid
        
        

        //b.1.a read operation, need to mark it as not dirty
        if (!readWrite)
            //b.1.a mark as not dirty
            cache[addr[5:4]][132] = 1'b0; // not dirty
    end
    
    //b.1 read data
    if (!readWrite)
        //b.1.b return data
        // * {addr[3:2],5'b0}+31 -: 31 is to translate word offset to
        // corresponding word address
        readData = cache[addr[5:4]][{addr[3:2],5'b0} +: 31];
        
    //b.2 write data
    else begin
        //b.2.a write new data
        cache[addr[5:4]][131:128] = addr[9:6]; // Update tag
        // * {addr[3:2],5'b0}+31 -: 31 is to translate word offset to
        // corresponding word address
        cache[addr[5:4]][{addr[3:2],5'b0} +: 31] = writeData; // Update data
        cache[addr[5:4]][133] = 1'b1; // valid
        
        //b.2.b set the dirty bit to 1
        cache[addr[5:4]][132] = 1'b1; // dirty
    end
end

endmodule