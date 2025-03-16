module PWM (
    input clk,     // ϵͳʱ��
    input rstn,    // �͵�ƽ��λ
    output pwm     // ���PWM��������LED
);
    reg [11:0] contH; // �ߵ�ƽ��������
    reg [11:0] contL; // �͵�ƽ��������
    reg HL;          // �ߵ�ƽ/�͵�ƽ״̬

    // �����ʵ��ļ�������
    reg [11:0] cycleCount;
    localparam COUNT_PERIOD = 12_000_000; // ʱ��������������ϵͳʱ��Ƶ��Ϊ12MHz����1��һ������
    localparam DESIRED_CYCLE_TIME = 25; // ����ѭ��ʱ�䣨�룩
    localparam COUNT_TARGET = COUNT_PERIOD * DESIRED_CYCLE_TIME; // Ŀ�����������

    // ��ʼ��������
    initial begin
        cycleCount = 0;
    end

    // �����͵�ƽ������
    always @(posedge clk or negedge rstn) begin
        if (!rstn)
            contL <= 1'b0; // �ڸ�λ�ڼ佫����������Ϊ0
        else if (contL >= COUNT_TARGET)
            contL <= 1'b0; // ���������ﵽĿ���������ʱ��������Ϊ0
        else
            contL <= contL + 1'b1; // ������������ֵ
    end

    // �����ߵ�ƽ�������Ϳ���״̬
    always @(posedge clk or negedge rstn) begin
        if (!rstn) begin
            contH <= 1'b0; // �ڸ�λ�ڼ佫����������Ϊ0
            HL <= 1'b0; // �ڸ�λ�ڼ佫״̬����Ϊ�͵�ƽ
        end
        else if (contH >= COUNT_TARGET) begin
            contH <= 1'b0; // ���������ﵽĿ���������ʱ��������Ϊ0
            HL <= !HL; // �л��ߵ�ƽ/�͵�ƽ״̬
        end
        else if (contL == 1'b1)
            contH <= contH + 1'b1; // ������������ֵ
    end

    // ���ݼ�������״̬ȷ��PWM���
    assign pwm = (HL == 1'b1) ? ((contH >= contL) ? 1'b1 : 1'b0) : ((contH <= contL) ? 1'b1 : 1'b0);
    // ��״̬Ϊ�ߵ�ƽʱ������ߵ�ƽ���������ڵ��ڵ͵�ƽ������������ߵ�ƽ����������͵�ƽ
    // ��״̬Ϊ�͵�ƽʱ������ߵ�ƽ������С�ڵ��ڵ͵�ƽ��������������ߵ�ƽ����������͵�ƽ
    // ����ʵ�����𽥱�������Ϩ��ĺ�����Ч��
endmodule
