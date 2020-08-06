`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Author: 
//  Junjie ZHang
// Module Name: ssd
// Description: 
//   driver for segmented displayer
// Dependencies: 
//  None 
//////////////////////////////////////////////////////////////////////////////////


module ssd(
    input clk, // clk is the high frequency clock 
    input [31:0] data, // to be displayed
    output reg [3:0] anode,          
    output reg [7:0] cathode
    );

    parameter ratio = 200000;

    reg [17:0] count;
    reg [3:0] Q;

    initial begin
        cathode <= 7'b1000000;
        anode <= 4'b1110;
        Q <= 4'b0;
        count <= 18'b0;
    end

    always @(posedge clk)
    begin
        count <= count + 1;
        if (count == ratio) begin
            count <= 0;
            case(anode)
                4'b0111: 
                    begin
                        anode <= 4'b1110; Q <= data[15:12];
                    end
                4'b1011: 
                    begin
                        anode <= 4'b0111; Q <= data[11:8];
                    end
                4'b1101:
                    begin   
                        anode <= 4'b1011; Q <= data[7:4];
                    end
                4'b1110: 
                    begin
                        anode <= 4'b1101; Q <= data[3:0];
                    end
                default: Q <= 4'b0;
            endcase
        end
    end

    always @(Q)
        case (Q)
            4'b0001 : cathode <= 7'b1111001;   // 1
            4'b0010 : cathode <= 7'b0100100;   // 2
            4'b0011 : cathode <= 7'b0110000;   // 3
            4'b0100 : cathode <= 7'b0011001;   // 4
            4'b0101 : cathode <= 7'b0010010;   // 5
            4'b0110 : cathode <= 7'b0000010;   // 6
            4'b0111 : cathode <= 7'b1111000;   // 7
            4'b1000 : cathode <= 7'b0000000;   // 8
            4'b1001 : cathode <= 7'b0010000;   // 9
            4'b1010 : cathode <= 7'b0001000;   // a
            4'b1011 : cathode <= 7'b0000011;   // b
            4'b1100 : cathode <= 7'b1000110;   // C
            4'b1101 : cathode <= 7'b0100001;   // d
            4'b1110 : cathode <= 7'b0000110;   // E
            4'b1111 : cathode <= 7'b0001110;   // F
            default : cathode <= 7'b1000000;   // 0
        endcase

endmodule 