`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/07/20 00:18:51
// Design Name: 
// Module Name: wt2w_cache
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


module wt2w_cache(read_cpu,addr_cpu,WriteData_cpu,ReadData_mem,
            read_cache,hit,addr_cache,ReadData_cache,WriteData_cache);
input read_cpu;//1 for read 0 for write
input [9:0] addr_cpu;
input [31:0] WriteData_cpu;
input [127:0] ReadData_mem;
output reg [31:0] ReadData_cache;
output reg read_cache,hit;//1 for read, 0 for write;1 for hit, 0 for miss
output reg [9:0] addr_cache;
output reg [127:0] WriteData_cache;

reg [255:0] set [0:1];//[0:127]block1,[128:255]block2
reg v [0:3];//0 for empty, 1 for occupied
reg [4:0] tag [0:3];
reg LRU [0:1];//indicate which block is the least recently used block

integer i;
initial begin
    for (i=0;i<4;i=i+1)begin
        v[i]<=1'b0;
        tag[i]<=5'b0;
    end
    set[1]<=256'b0;
    set[0]<=256'b0;
    LRU[1]<=0;
    LRU[0]<=0;
end

reg hit_flag;
wire [1:0] byte_offset,word_offset;
wire index;//2*index(+1) indicate the 2 blocks in set[index]
wire [4:0] addr_tag;
assign byte_offset=addr_cpu[1:0];
assign word_offset=addr_cpu[3:2];
assign index=addr_cpu[4];
assign addr_tag=addr_cpu[9:5];
//assign hit_flag=((v[index*2]==1)&&(tag[index*2]==addr_tag))||((v[index*2+1]==1)&&(tag[index*2+1]==addr_tag));//indicating the addr is a hit

always @(read_cpu or addr_cpu or WriteData_cpu)begin
    hit_flag=0;
    if((v[{index,1'b0}]&&tag[{index,1'b0}]==addr_tag)||(v[{index,1'b0}+1]&&tag[{index,1'b0}+1]==addr_tag))begin
        hit_flag=1;
    end
    //$display("hitflag=%b",hit_flag);
    if(read_cpu==0)begin//cpu wants to read data
        if(hit_flag==1)begin//there is a hit in cache
            hit=1;
            if(tag[{index,1'b0}]==addr_tag)begin//in set[index] block1
                case(word_offset)
                    2'b00:ReadData_cache=set[index][31:0];
                    2'b01:ReadData_cache=set[index][63:32];
                    2'b10:ReadData_cache=set[index][95:64];
                    2'b11:ReadData_cache=set[index][127:96];
                endcase
                #2;
                LRU[index]=1;//block2 is LRU
            end
            else if(tag[{index,1'b0}+1]==addr_tag)begin//in set[index] block2
                case(word_offset)
                    2'b00:ReadData_cache=set[index][159:128];
                    2'b01:ReadData_cache=set[index][191:160];
                    2'b10:ReadData_cache=set[index][223:192];
                    2'b11:ReadData_cache=set[index][255:224];
                endcase
                #2;
                LRU[index]=0;//block1 is LRU
            end
        end
        if(hit_flag==0)begin//there is a miss in cache
            hit<=0;
            read_cache<=0;
            addr_cache<=addr_cpu;
            #2;
            case(LRU[index])
                1'b0:begin
            //replace set[index] block1
                set[index][127:0]=ReadData_mem;
                tag[{index,1'b0}]=addr_tag;
                v[{index,1'b0}]<=1;
                hit<=1;
                case(word_offset)
                    2'b00:ReadData_cache=set[index][31:0];
                    2'b01:ReadData_cache=set[index][63:32];
                    2'b10:ReadData_cache=set[index][95:64];
                    2'b11:ReadData_cache=set[index][127:96];
                endcase
                #2;
                LRU[index]=1;//block2 is LRU
                end
            //replace set[index] block2
                1'b1:begin
                set[index][255:128]=ReadData_mem;
                tag[{index,1'b0}+1]=addr_tag;
                v[{index,1'b0}+1]<=1;
                hit<=1;
                case(word_offset)
                    2'b00:ReadData_cache=set[index][159:128];
                    2'b01:ReadData_cache=set[index][191:160];
                    2'b10:ReadData_cache=set[index][223:192];
                    2'b11:ReadData_cache=set[index][255:224];
                endcase
                #2;
                LRU[index]=0;//block1 is LRU
                end
            endcase
        end
    end
    if(read_cpu==1)begin//cpu wants to write data
        if(hit_flag==1)begin//there is a hit in cache
            hit<=1;
            read_cache<=1;
            addr_cache<=addr_cpu;
            if(tag[{index,1'b0}]==addr_tag)begin//in set[index] block1
                case(word_offset)
                    2'b00:set[index][31:0]=WriteData_cpu;
                    2'b01:set[index][63:32]=WriteData_cpu;
                    2'b10:set[index][95:64]=WriteData_cpu;
                    2'b11:set[index][127:96]=WriteData_cpu;
                endcase
                WriteData_cache=set[index][127:0];
                #2;
                LRU[index]=1;//block2 is LRU
            end
            else if(tag[{index,1'b0}+1]==addr_tag)begin
                case(word_offset)
                    2'b00:ReadData_cache=set[index][159:128];
                    2'b01:ReadData_cache=set[index][191:160];
                    2'b10:ReadData_cache=set[index][223:192];
                    2'b11:ReadData_cache=set[index][255:224];
                endcase
                WriteData_cache=set[index][255:128];
                #2;
                LRU[index]=0;//block1 is LRU
            end
        end
        if(hit_flag==0)begin//there is a miss in cache
            $display("write with miss");
            hit<=0;
            read_cache<=0;
            addr_cache<=addr_cpu;
            #2;
            case(LRU[index])
                1'b0:begin//block1 written
                set[index][127:0]=ReadData_mem;
                tag[{index,1'b0}]=addr_tag;
                v[{index,1'b0}]<=1;
                hit<=1;
                case(word_offset)
                    2'b00:set[index][31:0]=WriteData_cpu;
                    2'b01:set[index][63:32]=WriteData_cpu;
                    2'b10:set[index][95:64]=WriteData_cpu;
                    2'b11:set[index][127:96]=WriteData_cpu;
                endcase
                read_cache<=1;
                WriteData_cache=set[index][127:0];
                LRU[index]=1;//block2 is LRU
                end
                1'b1:begin//block2 written
                set[index][255:128]=ReadData_mem;
                tag[{index,1'b0}+1]=addr_tag;
                v[{index,1'b0}+1]<=1;
                hit<=1;
                case(word_offset)
                    2'b00:ReadData_cache=set[index][159:128];
                    2'b01:ReadData_cache=set[index][191:160];
                    2'b10:ReadData_cache=set[index][223:192];
                    2'b11:ReadData_cache=set[index][255:224];
                endcase
                read_cache<=1;
                WriteData_cache=set[index][255:128];
                LRU[index]=0;//block1 is LRU
                end
            endcase
        end
    end
end

endmodule
