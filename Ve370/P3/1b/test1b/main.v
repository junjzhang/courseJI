`timescale 1ns / 1ps
//`include "cache2b.v"

module main(
    input readWrite, // 0 for read, 1 for write
    input [9:0] addr, // byte address, [9:5] tag, [4] cache index, [3:2] word offset, [1:0] byte offset
    input [31:0] writeData, //word data from cpu to be writen
    output hitMiss, // 1 for hit, 0 for miss, state flag
    output [31:0] readData // data to cpu
);

    wire [127:0] readDataMem, writeDataMem;
    wire [9:0] memAddr;
    wire readWriteOut;
    wt2w_cache cache(readWrite, addr, writeData, readDataMem, readData,readWriteOut, hitMiss, memAddr, writeDataMem);
    //module wtdm_cache(read_cpu,addr_cpu,WriteData_cpu,ReadData_mem,ReadData_cache,read_cache,hit,addr_cache,WriteData_cache);
    MainMem mem(readWriteOut, memAddr, writeDataMem, readDataMem);

endmodule
