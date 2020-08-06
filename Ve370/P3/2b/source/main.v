`timescale 1ns / 1ps

module main(
    input readWrite, // 1 for read, 0 for write
    input [9:0] addr, // byte address, [9:5] tag, [4] cache index, [3:2] word offset, [1:0] byte offset
    input [31:0] writeData, //word data from cpu to be writen
    output hitMiss, // 1 for hit, 0 for miss, state flag
    output [31:0] readData // data to cpu
);

    wire [127:0] readDataMem, writeDataMem;
    wire [9:0] memAddr;
    wire readWriteOut;
    MainMem mem(readWriteOut, memAddr, writeDataMem, readDataMem);
    cache2b cache (readWrite, addr, writeData, readDataMem, readWriteOut, hitMiss, memAddr, readData, writeDataMem);

endmodule