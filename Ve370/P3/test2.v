`timescale 1ns / 1ps
`include "./1a/cache1a.v"
//`include "./1b/cache1b.v"
//`include "./2a/cache2a.v"
//`include "./2b/cache2b.v"
`include "./mainMem/mainMem.v"
`include "main.v"

module test();

    reg [31:0] writeData;
    reg [9:0] addr;
    reg readWrite;
    wire [31:0] readData;
    wire hitMiss;
    integer i;

    main uut(readWrite, addr, writeData, hitMiss, readData);

    initial begin
        i = 0;
        `include "testGen.txt"
        #10
        $stop;
    end

    always #10 begin
        $display("Round %d: readWrite = %d, addr = %d", i, readWrite, addr);
        if (!readWrite)
            $display("readData = %D", readData);
        else
            $display("writeData = %D", writeData);
        $display("----------------------------------------------------------");
        i = i + 1;
    end


endmodule