`timescale 1ns / 1ps

/*****
//////
* Description:
**  A cache memory with following features:
***   write back
***   2-way associate
***   write allocate
***   replace ment policy: least recently used (LRU)
***   ONlY request word!!
//////
* Author: Junjie Zhang
*****/


module Cache(
    input readWrite, // 0 for read, 1 for write
    input [9:0] addr, // byte address, [9:5] tag, [4] cache index, [3:2] word offset, [1:0] byte offset
    input [31:0] writeData, //word data from cpu to be writen
    input [127:0] readDataMem, // block data from memory 
    output reg readWriteOut, // read or write state to memory, 0 for read, 1 for write
    output reg hitMiss, // 1 for hit, 0 for miss, state flag
    output reg [9:0] memAddr, // request address to memory
    output reg [31:0] readData, // data to cpu for 
    output reg [127:0] writeDataMem //block data from memory to be writen
);

/***
* In total, 4 blocks, 2 sets
* For a block:
**  1 bit for LRU policy [135]
***  notice that only the first and third block's LRU bit is useful
**  1 valIdate bit (V) [134]
**  1 dirty bit (D) [133]
**  tag 5 bits [132:128]
**  data 4 words = 16 bytes [127:96] [95:64] [63:32] [31:0]
***/
parameter numBlocks = 4;
reg [135:0] cache[0:numBlocks-1]; 

reg setBlockId; // the index of block within a set, used for allocate and check match
                
// Initialize
integer ii; // For initialize the cache

initial begin
    $display("Cache Version: 2b");
    for (ii = 0; ii < numBlocks; ii = ii + 1)
        cache[ii][135:128] = 8'b0; // Initialize LRU bit, V, D, tag
        cache[ii][127:0] = 128'bx; // Initialize data
    hitMiss = 1'b0;
end

always @(readWrite or addr or writeData) begin
    // initialize in each loop is needed
    hitMiss = 1'b0; 

    // a. Judege Miss or hit
    // * {addr[4],1'b0} stands for the first block of given set
    // {addr[4],1'b1} stands for the second block of given set
    // First block of set
    if (cache[{addr[4],1'b0}][134]) // Check if valId
        if (addr[9:5] == cache[{addr[4],1'b0}][132:128]) begin
            setBlockId = 1'b0;
            hitMiss = 1'b1;
        end
        // Second block of set
    else if (cache[{addr[4],1'b1}][134]) // Check if valId
        if (addr[9:5] == cache[{addr[4],1'b1}][132:128]) begin
            setBlockId = 1'b1;
            hitMiss = 1'b1;
        end
    
    // a.1 if not hit
    if (!hitMiss) begin
        // a.1.a allocate
        // ...a check for empty ones
        // block 0 of the set
        if (~(cache[{addr[4],1'b0}][134])) 
            setBlockId = 1'b0;
        // block 1 of the set
        else if (~(cache[{addr[4],1'b1}][134]))
            setBlockId = 1'b1;
        // ...b no empty ones, replace based on LRU policy
        // the LRU bit is cache[{addr[4],0}][135]
        else 
            setBlockId = !cache[{addr[4],1'b0}][135];

        // a.1.b Check for dirty
        // ...1 dirty
        if (cache[{addr[4],setBlockId}][133]) begin
            memAddr = {cache[{addr[4],setBlockId}][132:128],addr[4],4'b0};
            readWriteOut = 1'b1; // write back
            writeDataMem = cache[{addr[4],setBlockId}][127:0];
            #2; // wait for memory
        end

        // a.1.c Load data from lower part
        readWriteOut = 1'b0; // read
        memAddr = addr;
        #2; // wait for memory
        cache[{addr[4],setBlockId}][132:128] = addr[9:5]; // Update tag
        cache[{addr[4],setBlockId}][127:0] = readDataMem; // Update data
        cache[{addr[4],setBlockId}][134] = 1'b1; // valid
        

        //b.1.a read operation, need to mark it as not dirty
        if (!readWrite)
            //b.1.a mark as not dirty
            cache[{addr[4],setBlockId}][133] = 1'b0; // not dirty
    end
    
    //b.1 read data
    if (!readWrite) begin
        //b.1.b return data
        // * {addr[3:2],5'b0} +: 31 is to translate word offset to
        // corresponding word address
        cache[{addr[4],1'b0}][135] = setBlockId; // LRU bit update
        cache[{addr[4],1'b1}][135] = setBlockId;
        readData = cache[{addr[4],setBlockId}][{addr[3:2],5'b0} +: 31];
    end

    //b.2 write data
    else begin
        //b.2.a write new data
        cache[{addr[4],1'b0}][135] = setBlockId; // LRU bit update
        cache[{addr[4],1'b1}][135] = setBlockId;
        cache[{addr[4],setBlockId}][132:128] = addr[9:5]; // Update tag
        // * {addr[3:2],5'b0} +: 31 is to translate word offset to
        // corresponding word address
        cache[{addr[4],setBlockId}][{addr[3:2],5'b0} +: 31] = writeData; // Update data
        cache[{addr[4],setBlockId}][134] = 1'b1; // valid
        
        //b.2.b set the dirty bit to 1
        cache[{addr[4],setBlockId}][133] = 1'b1; // dirty
    end
end

endmodule