`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/12/02 10:02:20
// Design Name: 
// Module Name: switches
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


module switches(
  input rst, // ����
  input clk, // ʱ��

  //�������������� ��������������Ӧ�������ź�
  input wire[`WordRange] addr,
  input wire en, // ʹ��
  input wire[3:0] byte_sel,
  input wire[`WordRange] data_in, // �������루����cpu��
  input wire we, //дʹ��


  //���͸��ٲ��� �������趼Ӧ�д����
  output reg[`WordRange] data_out,

  input[23:0] switch_in // 24λ����  ��������
  );
  
  reg[23:0] switch_reg; //�ڲ��Ĵ���
  
  always @(posedge clk) begin  //���������д��Ĵ��� �˼Ĵ����������cpuд��
    if (rst) begin
      switch_reg <= 24'd0;
    end else begin
      switch_reg <= switch_in;
    end
  end
  
  always @(*) begin
    if(rst == `Enable) begin
      data_out <= `ZeroWord;
    end else if(addr == 32'hfffffc70 && en == `Enable && we == `Disable)begin
      data_out <= switch_reg;
    end else begin
      data_out <= `ZeroWord;
    end
  end
endmodule
