`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/12/02 10:02:20
// Design Name: 
// Module Name: beep
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
`include "defines.v"

module beep(
  input wire rst,
  input wire clk,
  input wire[`WordRange] addr,
  input wire en, // ʹ��
  input wire[3:0] byte_sel,
  input wire[`WordRange] data_in, // ���ź�����
  input wire we, //дʹ��
  
  //���͸��ٲ��� �������趼Ӧ�д����
  output reg[`WordRange] data_out,
  
  //���͸�������ź�
  output reg signal_out // ���ź����
  );
  
  reg [19:0] count;
  reg [19:0] mcnt;
  
  always @(posedge clk) begin  //д��������
    if(rst == `Enable) begin
      signal_out <= 1'b0;
      count <= 16'd0;
      mcnt  <= 0; // zero -> no beep!
    end else if (mcnt != 20'h00000) begin
      count <= count + 20'h0_0001;
      if (count == mcnt) begin
        signal_out <= ~signal_out;
        count <= 20'h00000;
      end
    end
    if (en == `Enable && addr == 32'hFFFF_FD10) begin
      if (we) begin
        mcnt <= data_in[20:1];
        data_out <= `ZeroWord;
      end else begin
        data_out <= {11'b0, mcnt[19:0], 1'b0};
      end
    end
  end
endmodule
