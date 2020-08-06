`timescale 1ns / 1ps

module test2a();

    reg [31:0] write_data;
    reg [9:0] address;
    reg read_write;
    wire [31:0] readData;
    wire hitMiss;
    integer i;
    integer j;
    integer k;
    integer index;
    parameter break = 10;

    main uut(read_write, address, write_data, hitMiss, readData);

    initial begin
        i = 0;
        #0 read_write = 0; address = 10'b0000000000; //should miss
        #10 read_write = 1; address = 10'b0000000000; write_data = 8'b11111111; //should hit
        #10 read_write = 0; address = 10'b0000000000; //should hit and read out 0xff

        //here check main memory content,
        //the first byte should remain 0x00 if it is write-back,
        //should change to 0xff if it is write-through.

        #10 read_write = 0; address = 10'b1000000000; //should miss
        #10 read_write = 0; address = 10'b0000000000; //should hit for 2-way associative, should miss for directly mapped

        #10 read_write = 0; address = 10'b1100000000; //should miss
        #10 read_write = 0; address = 10'b1000000000; //should miss both for directly mapped and for 2-way associative (Least-Recently-Used policy)

        //here check main memory content,
        //the first byte should be 0xff
        $stop;
    end

    always #break begin
        $display("Round %d: hit/miss = %0d, readWrite = %0d, addr = %b", i, hitMiss, read_write, address);
        $display("readData = %h, writeData = %h", readData, write_data);
        $display("******cache******");
        for (j = 0; j < 4; j = j+1) begin
            $display("Block %0d: V:%b, D:%b,",j,uut.cache.cache[j][134],uut.cache.cache[j][133]);
            $display("Tag: %b, Data 0:%h, Data 1:%h, Data 2: %h, Data 3: %h",uut.cache.cache[j][132:128],uut.cache.cache[j][127:96],uut.cache.cache[j][95:64],uut.cache.cache[j][63:32],uut.cache.cache[j][31:0]);
        end
        $display("----------------------------------------------------------");
        i = i + 1;
    end


endmodule