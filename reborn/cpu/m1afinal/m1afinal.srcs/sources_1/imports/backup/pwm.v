`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/12/02 10:02:20
// Design Name: 
// Module Name: pwm
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


module pwm(
  input rst, // ���ã�ȫ�����
  input clk, // ʱ��

  //�������������� ��������������Ӧ�������ź�
  input wire[`WordRange] addr,
  input wire en, // ʹ��
  input wire[3:0] byte_sel,
  input wire[`WordRange] data_in, // �������루����cpu��
  input wire we, //дʹ��

  //���͸��ٲ��� �������趼Ӧ�д����
  output wire[`WordRange] data_out,

  output reg result // PWM���ƽ��
);

  reg[15:0] threshold; // ���ֵ�Ĵ���
  reg[15:0] compare; // �Ա�ֵ�Ĵ���
  reg enable; // ���ƼĴ���
  reg[15:0] current; // ��ǰֵ
  assign data_out = `ZeroWord;

  always @(posedge clk) begin
    if (rst) begin
      threshold <= 16'hFFFF;
      compare <= 16'h7FFF;
      enable <= 0;
      current <= 0;
    end else begin
      // internal logic
      if (current == threshold) begin
        current <= 0;
      end else begin
        current <= current + 1;
      end
      
      // result logic
      if (current > compare) begin
        result <= 1;
      end else begin
        result <= 0; 
      end
      
      
      // write logic
      if (we && en && addr[31:4] == 28'hfffffc3) begin
        if (addr[3:0] == 4'b0000) begin
          threshold <= data_in[15:0];
        end else if (addr[3:0] == 4'b0010) begin
          compare <= data_in[15:0];
        end else if (addr[3:0] == 4'b0100) begin
          enable <= data_in[0];
        end
      end
    end
  end
endmodule
