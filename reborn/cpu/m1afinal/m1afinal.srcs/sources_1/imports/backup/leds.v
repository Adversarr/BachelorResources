`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/12/02 10:02:20
// Design Name: 
// Module Name: leds
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

module leds(
  input rst, // ���ã�ȫ�����
  input clk, // ʱ��
  
  //�������������� ��������������Ӧ�������ź�
  input wire[`WordRange] addr,
  input wire en, // ʹ��
  input wire[3:0] byte_sel,
  input wire[`WordRange] data_in, // �������루����cpu��
  input wire we, //дʹ��
  
  //���͸��ٲ��� �������趼Ӧ�д����
  output reg[`WordRange] data_out,
  
  
  //���͸�����
  output reg[7:0] RLD, // ���
  output reg[7:0] YLD, // �Ƶ�
  output reg[7:0] GLD  // �̵�
  );

  always @(posedge clk) begin  //д��Ҫ������(minisys: ~cpuclk)
    if (rst == `Enable) begin
      RLD <= 8'h00;
      YLD <= 8'h00;
      GLD <= 8'h00;
    end else if(addr == 32'hfffffc60 && en == `Enable && we == `Enable) begin //��ַ��ȷ дʹ����Ч ��ʹ����Ч
      RLD <= data_in[23:16];
      YLD <= data_in[15:8];
      GLD <= data_in[7:0];
    end
  end
  
  always @(*) begin
    if(rst == `Enable) begin
      data_out <= `ZeroWord;
    end else if (addr == 32'hfffffc60 && en == `Enable && we ==`Disable) begin
        data_out <= {8'h00, RLD, YLD, GLD};
    end else begin
        data_out <= `ZeroWord;
    end
   end

  
endmodule
