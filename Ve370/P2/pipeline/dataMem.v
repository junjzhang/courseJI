`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Author: 
//  Junjie ZHang
// Module Name: dataMem
// Description: 
//  Data memory.
// Dependencies: 
//  None
//////////////////////////////////////////////////////////////////////////////////


module dataMem(
    input clk, memRead, memWrite, reset,
    input [31:0] address, writeData,
    output [31:0] readData
    );
    
    parameter size = 1024; //  unit: size
    integer ii;
    
    reg signed [7:0] mem [0:size-1];
    
    initial
    begin
        for (ii = 0;ii < size;ii = ii + 1)
            mem[ii] <= 8'b0;
    end
    
    always @ (negedge clk or posedge reset)
    begin
        if (reset == 1'b1)
            for (ii = 0;ii < size; ii = ii + 1)
                mem[ii] <= 8'b0;
        else if (memWrite == 1'b1)
        begin
                {mem[address], mem[address+1], mem[address+2],mem[address+3]} <= writeData; 
                $display("dataMem::dataMem[%h] = %h", address, writeData); // test
        end
    end
    
    assign readData = memRead?{mem[address], mem[address+1], mem[address+2],mem[address+3]}: 32'b0;
    
endmodule
