`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/17 20:05:17
// Design Name: 
// Module Name: wtdm_cache
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


module wtdm_cache(read_cpu,addr_cpu,WriteData_cpu,ReadData_mem,
            ReadData_cache,read_cache,hit,addr_cache,WriteData_cache);
input read_cpu;//0 for read 1 for write
input [9:0] addr_cpu;
input [31:0] WriteData_cpu;
input [127:0] ReadData_mem;
output reg [31:0] ReadData_cache;
output reg read_cache,hit;//1 for read, 0 for write;1 for hit, 0 for miss
output reg [9:0] addr_cache;
output reg [127:0] WriteData_cache;

reg [127:0] block[0:3];
reg v[0:3];//0 for empty, 1 for occupied
reg [3:0] tag [0:3];

integer i;
initial begin
    for (i=0;i<4;i=i+1)begin
        block[i]<=128'b0;
        v[i]<=1'b0;
        tag[i]<=4'b0;
    end
end

reg hit_flag;
wire [1:0] byte_offset,word_offset,index;
wire [3:0] addr_tag;
assign byte_offset=addr_cpu[1:0];
assign word_offset=addr_cpu[3:2];
assign index=addr_cpu[5:4];
assign addr_tag=addr_cpu[9:6];

always @(*)begin
    if((v[index]==1)&&(tag[index]==addr_tag))begin
        hit_flag<=1;
    end
    else begin
        hit_flag<=0;
    end
    if(read_cpu==0)begin//cpu want to read data from mem
        if(hit_flag==0)begin//not hit
            hit=0;
            read_cache<=0;//read data from mem
            addr_cache<=addr_cpu;
            #2;
            block[index]=ReadData_mem;
            tag[index]=addr_tag;
            v[index]=1;
            hit=1;
            case(word_offset)
                2'b00:ReadData_cache=block[index][31:0];
                2'b01:ReadData_cache=block[index][63:32];
                2'b10:ReadData_cache=block[index][95:64];
                2'b11:ReadData_cache=block[index][127:96];
            endcase
        end
        if(hit_flag==1)begin//hit
            hit=1;
            case(word_offset)
                2'b00:ReadData_cache=block[index][31:0];
                2'b01:ReadData_cache=block[index][63:32];
                2'b10:ReadData_cache=block[index][95:64];
                2'b11:ReadData_cache=block[index][127:96];
            endcase
        end
    end
    /////////////////////////////////////////////////////////////////
    if(read_cpu==1)begin//cpu want to write data into mem
        if(hit_flag==0)begin//not hit
            hit<=0;
            read_cache<=0;
            addr_cache<=addr_cpu;
            #2;
            block[index]=ReadData_mem;
            tag[index]=addr_tag;
            v[index]=1;
            hit=1;
            case(word_offset)
                2'b00:block[index][31:0]=WriteData_cpu;
                2'b01:block[index][63:32]=WriteData_cpu;
                2'b10:block[index][95:64]=WriteData_cpu;
                2'b11:block[index][127:96]=WriteData_cpu;
            endcase
            read_cache<=1;
            WriteData_cache<=block[index];
        end
        if(hit_flag==1)begin//hit
            hit=1;
            case(word_offset)
                2'b00:block[index][31:0]=WriteData_cpu;
                2'b01:block[index][63:32]=WriteData_cpu;
                2'b10:block[index][95:64]=WriteData_cpu;
                2'b11:block[index][127:96]=WriteData_cpu;
            endcase
            addr_cache<=addr_cpu;
            read_cache<=1;
            WriteData_cache<=block[index];
        end
    end
end
endmodule
