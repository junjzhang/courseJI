`timescale 1ns / 1ps

module MainMem(
    input readWrite, // 1 for read, 0 for write
    input [9:0] addr,
    input [127:0] writeData,
    output [127:0] readData
);

    parameter size = 256;
    reg [31:0] memory [0:size - 1]; //main memory, including 64 blocks, each with 4 words

    integer i;
    initial begin
        for (i = 0; i < size; i = i + 1)
            memory[i] = i;
        `include "mainMemory.mem"
    end
    assign readData = {memory[{addr[9:4], 2'b0} + 3], memory[{addr[9:4], 2'b0} + 2], memory[{addr[9:4], 2'b0} + 1], memory[{addr[9:4], 2'b0}]};
    always @ (readWrite)begin
        //$display("ReadData: Word0=%d; Word1=%d; Word2=%d; Word3=%d",memory[{addr[9:4], 2'b0}], memory[{addr[9:4], 2'b0} + 1], memory[{addr[9:4], 2'b0} + 2], memory[{addr[9:4], 2'b0}+3]);
        if (readWrite) //write data into main mem
            {memory[{addr[9:4], 2'b0} + 3], memory[{addr[9:4], 2'b0} + 2], memory[{addr[9:4], 2'b0} + 1], memory[{addr[9:4], 2'b0}]} = writeData;
    end
endmodule