// Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
// Date        : Tue Dec 20 16:55:39 2022
// Host        : DESKTOP-GH9H0GG running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub -rename_top clkdiv -prefix
//               clkdiv_ clkdiv_stub.v
// Design      : clkdiv
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a100tfgg484-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
module clkdiv(cpuclk, uartclk, clk_in1)
/* synthesis syn_black_box black_box_pad_pin="cpuclk,uartclk,clk_in1" */;
  output cpuclk;
  output uartclk;
  input clk_in1;
endmodule
