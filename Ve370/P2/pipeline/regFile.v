`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Author: 
//  Junjie Zhang
// Module Name: regFile
// Description: 
//  register File. Ansychronous reset.
// Dependencies: 
//  None
//////////////////////////////////////////////////////////////////////////////////


module regFile(
    input [4:0] readReg1, readReg2, writeReg, displayReg,// displayReg is for displaying on board
    input [31:0] writeData,
    input clk, regWrite, reset,
    output [31:0] readData1, readData2, displayData
    );
    
    reg signed [31:0] file [0:31];
    integer ii;

    initial 
    begin
         for (ii = 0;ii < 32;ii = ii + 1)
                file[ii] <= 32'b0;
    end
    
    always @ (negedge clk or posedge reset)
    begin
        if (reset == 1'b1)
            for (ii = 0;ii < 32;ii = ii + 1)
                file[ii] <= 32'b0;
        else if (regWrite)
            file[writeReg] <= writeData;
    end
    
    assign readData1 = file[readReg1];
    assign readData2 = file[readReg2];
    assign displayData = file[displayReg]; // for display
    
endmodule
