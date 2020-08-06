`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/03 22:02:31
// Design Name: 
// Module Name: memory_mux
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module memory_mux(// a mux used for decide which write_data to choose, the data from EX/MEM register or the forwarding path
  input[31:0] ex_mem_writedata,
  input [31:0] mem_wb_readdata,
  input [31:0] mem_wb_ALU_result,
  input [1:0]memsrc,
  output reg [31:0] out
    );
    always @(ex_mem_writedata or mem_wb_readdata or memsrc)
    begin
        case(memsrc)
        2'b00:out<=ex_mem_writedata;
        2'b01:out<=mem_wb_readdata;
        2'b10: out<=mem_wb_ALU_result;
        default: out<=32'b0;
        endcase
    end
    endmodule
