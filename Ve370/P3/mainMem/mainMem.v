`timescale 1ns / 1ps

module MainMem(
    input readWrite, // 0 for read, 1 for write
    input [9:0] addr,
    input [127:0] writeData,
    output [127:0] readData
);

    parameter size = 256;
    wire [7:0] wordAddr;
    reg [31:0] memory [0:size - 1]; //main memory, including 64 blocks, each with 4 words
    assign wordAddr = {addr[9:4], 2'b0}; //byte offset and word offset are both 2, and 6 higher bits for block left

    integer i;
    initial begin
        for (i = 0; i < size; i = i + 1)
            memory[i] = i;
        //`include "mainMemory.txt"
    end

    always @ (readWrite or addr or writeData)begin
        if (readWrite) //write data into main mem
            {memory[wordAddr + 3], memory[wordAddr + 2], memory[wordAddr + 1], memory[wordAddr]} = writeData;
    end
    assign readData = {memory[wordAddr + 3], memory[wordAddr + 2], memory[wordAddr + 1], memory[wordAddr]};
endmodule
