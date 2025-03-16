module PWM (
    input clk,     // 系统时钟
    input rstn,    // 低电平复位
    output pwm     // 输出PWM波，连接LED
);
    reg [11:0] contH; // 高电平计数周期
    reg [11:0] contL; // 低电平计数周期
    reg HL;          // 高电平/低电平状态

    // 计算适当的计数周期
    reg [11:0] cycleCount;
    localparam COUNT_PERIOD = 12_000_000; // 时钟周期数，假设系统时钟频率为12MHz，即1秒一个周期
    localparam DESIRED_CYCLE_TIME = 25; // 呼吸循环时间（秒）
    localparam COUNT_TARGET = COUNT_PERIOD * DESIRED_CYCLE_TIME; // 目标计数周期数

    // 初始化计数器
    initial begin
        cycleCount = 0;
    end

    // 递增低电平计数器
    always @(posedge clk or negedge rstn) begin
        if (!rstn)
            contL <= 1'b0; // 在复位期间将计数器重置为0
        else if (contL >= COUNT_TARGET)
            contL <= 1'b0; // 当计数器达到目标计数周期时将其重置为0
        else
            contL <= contL + 1'b1; // 递增计数器的值
    end

    // 递增高电平计数器和控制状态
    always @(posedge clk or negedge rstn) begin
        if (!rstn) begin
            contH <= 1'b0; // 在复位期间将计数器重置为0
            HL <= 1'b0; // 在复位期间将状态设置为低电平
        end
        else if (contH >= COUNT_TARGET) begin
            contH <= 1'b0; // 当计数器达到目标计数周期时将其重置为0
            HL <= !HL; // 切换高电平/低电平状态
        end
        else if (contL == 1'b1)
            contH <= contH + 1'b1; // 递增计数器的值
    end

    // 根据计数器和状态确定PWM输出
    assign pwm = (HL == 1'b1) ? ((contH >= contL) ? 1'b1 : 1'b0) : ((contH <= contL) ? 1'b1 : 1'b0);
    // 当状态为高电平时，如果高电平计数器大于等于低电平计数器，输出高电平，否则输出低电平
    // 当状态为低电平时，如果高电平计数器小于等于低电平计数器，则输出高电平，否则输出低电平
    // 这样实现了逐渐变亮和逐渐熄灭的呼吸灯效果
endmodule
