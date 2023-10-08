`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/12/02 10:02:20
// Design Name: 
// Module Name: watchdog
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


module watchdog(
  input rst, // ���ã�ȫ�����
  input clk, // ʱ��

  //�������������� ��������������Ӧ�������ź�
  input wire[`WordRange] addr,
  input wire en, // ʹ��
  input wire[3:0] byte_sel,
  input wire[`WordRange] data_in, // �������루����cpu��
  input wire we, //дʹ��
  output reg cpu_rst // ֪ͨCPU��λ
  );
  
  reg[15:0] current; // ��ǰ����ֵ
  reg[1:0] keeper; // ��������4��ʱ�����ڵ�cpu_rst

  always @(*) begin
    // ����rst�����߱�����ʱ������
    if (rst == `Enable) begin
      current <= 16'hffff;
      cpu_rst <= `Disable;
      keeper <= 2'd0;
    end
  end

  always @(posedge clk) begin  //д��������д
    current <= current - 16'd1;
    // count-down�������أ�����ʼ֪ͨCPU����
    if(addr == 32'hfffffc50 && en == `Enable && we == `Enable) begin
      current <= 16'hffff;
    end else if (current == 16'd0) begin
      current <= 16'hffff;
      keeper <= 2'b11;
    end
    // ����4��ʱ�����ڵ�cpu_rst
    if (keeper == 0) begin
      cpu_rst <= `Disable;
    end
    if (keeper > 0) begin
      cpu_rst <= `Enable;
      keeper = keeper - 2'd1;
    end
  end

endmodule
