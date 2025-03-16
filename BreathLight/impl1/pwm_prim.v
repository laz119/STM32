// Verilog netlist produced by program LSE :  version Diamond (64-bit) 3.10.0.111.2
// Netlist written on Sun Jun 18 16:15:46 2023
//
// Verilog Description of module PWM
//

module PWM (clk, rstn, pwm) /* synthesis syn_module_defined=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(1[8:11])
    input clk;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(2[11:14])
    input rstn;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(3[11:15])
    output pwm;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(4[12:15])
    
    wire clk_c /* synthesis SET_AS_NETWORK=clk_c, is_clock=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(2[11:14])
    
    wire GND_net, VCC_net, rstn_c;
    wire [11:0]contH;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(6[16:21])
    wire [11:0]contL;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(7[16:21])
    
    wire clk_c_enable_12, n220, n20, n19, pwm_c, n54, n55, n56, 
        n57, n58, n59, n60, n61, n62, n63, n64, n65, n218, 
        n206, n213, n54_adj_1, n55_adj_2, n56_adj_3, n57_adj_4, 
        n58_adj_5, n59_adj_6, n60_adj_7, n61_adj_8, n62_adj_9, n63_adj_10, 
        n64_adj_11, n65_adj_12, n204, n203, n205, n211, n209, 
        n210, n208, n217, n216, n215, n214, n212, n207, n202, 
        n201;
    
    VHI i117 (.Z(VCC_net));
    LUT4 i114_4_lut (.A(contL[4]), .B(contL[1]), .C(contL[7]), .D(contL[2]), 
         .Z(n220)) /* synthesis lut_function=(!(A+(B+(C+(D))))) */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(43[18:31])
    defparam i114_4_lut.init = 16'h0001;
    IB clk_pad (.I(clk), .O(clk_c));   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(2[11:14])
    LUT4 i116_3_lut (.A(n220), .B(n19), .C(n20), .Z(clk_c_enable_12)) /* synthesis lut_function=(!((B+(C))+!A)) */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(43[18:31])
    defparam i116_3_lut.init = 16'h0202;
    OB pwm_pad (.I(pwm_c), .O(pwm));   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(4[12:15])
    LUT4 i7_4_lut (.A(contL[10]), .B(contL[5]), .C(contL[0]), .D(contL[8]), 
         .Z(n19)) /* synthesis lut_function=(A+(B+((D)+!C))) */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(43[18:31])
    defparam i7_4_lut.init = 16'hffef;
    LUT4 i8_4_lut (.A(contL[9]), .B(contL[6]), .C(contL[3]), .D(contL[11]), 
         .Z(n20)) /* synthesis lut_function=(A+(B+(C+(D)))) */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(43[18:31])
    defparam i8_4_lut.init = 16'hfffe;
    PUR PUR_INST (.PUR(VCC_net));
    defparam PUR_INST.RST_PULSE = 1;
    VLO i1 (.Z(GND_net));
    TSALL TSALL_INST (.TSALL(GND_net));
    FD1P3AX contH_33__i0 (.D(n65_adj_12), .SP(clk_c_enable_12), .CK(clk_c), 
            .Q(contH[0])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33__i0.GSR = "ENABLED";
    IB rstn_pad (.I(rstn), .O(rstn_c));   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(3[11:15])
    FD1P3AX contH_33__i11 (.D(n54_adj_1), .SP(clk_c_enable_12), .CK(clk_c), 
            .Q(contH[11])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33__i11.GSR = "ENABLED";
    CCU2D sub_29_add_2_7 (.A0(contL[5]), .B0(contH[5]), .C0(GND_net), 
          .D0(GND_net), .A1(contL[6]), .B1(contH[6]), .C1(GND_net), 
          .D1(GND_net), .CIN(n203), .COUT(n204));
    defparam sub_29_add_2_7.INIT0 = 16'h5999;
    defparam sub_29_add_2_7.INIT1 = 16'h5999;
    defparam sub_29_add_2_7.INJECT1_0 = "NO";
    defparam sub_29_add_2_7.INJECT1_1 = "NO";
    CCU2D contL_32_add_4_3 (.A0(contL[1]), .B0(GND_net), .C0(GND_net), 
          .D0(GND_net), .A1(contL[2]), .B1(GND_net), .C1(GND_net), .D1(GND_net), 
          .CIN(n207), .COUT(n208), .S0(n64), .S1(n63));   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32_add_4_3.INIT0 = 16'hfaaa;
    defparam contL_32_add_4_3.INIT1 = 16'hfaaa;
    defparam contL_32_add_4_3.INJECT1_0 = "NO";
    defparam contL_32_add_4_3.INJECT1_1 = "NO";
    CCU2D contL_32_add_4_11 (.A0(contL[9]), .B0(GND_net), .C0(GND_net), 
          .D0(GND_net), .A1(contL[10]), .B1(GND_net), .C1(GND_net), 
          .D1(GND_net), .CIN(n211), .COUT(n212), .S0(n56), .S1(n55));   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32_add_4_11.INIT0 = 16'hfaaa;
    defparam contL_32_add_4_11.INIT1 = 16'hfaaa;
    defparam contL_32_add_4_11.INJECT1_0 = "NO";
    defparam contL_32_add_4_11.INJECT1_1 = "NO";
    CCU2D contH_33_add_4_13 (.A0(contH[11]), .B0(GND_net), .C0(GND_net), 
          .D0(GND_net), .A1(GND_net), .B1(GND_net), .C1(GND_net), .D1(GND_net), 
          .CIN(n218), .S0(n54_adj_1));   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33_add_4_13.INIT0 = 16'hfaaa;
    defparam contH_33_add_4_13.INIT1 = 16'h0000;
    defparam contH_33_add_4_13.INJECT1_0 = "NO";
    defparam contH_33_add_4_13.INJECT1_1 = "NO";
    CCU2D contH_33_add_4_11 (.A0(contH[9]), .B0(GND_net), .C0(GND_net), 
          .D0(GND_net), .A1(contH[10]), .B1(GND_net), .C1(GND_net), 
          .D1(GND_net), .CIN(n217), .COUT(n218), .S0(n56_adj_3), .S1(n55_adj_2));   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33_add_4_11.INIT0 = 16'hfaaa;
    defparam contH_33_add_4_11.INIT1 = 16'hfaaa;
    defparam contH_33_add_4_11.INJECT1_0 = "NO";
    defparam contH_33_add_4_11.INJECT1_1 = "NO";
    CCU2D contH_33_add_4_9 (.A0(contH[7]), .B0(GND_net), .C0(GND_net), 
          .D0(GND_net), .A1(contH[8]), .B1(GND_net), .C1(GND_net), .D1(GND_net), 
          .CIN(n216), .COUT(n217), .S0(n58_adj_5), .S1(n57_adj_4));   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33_add_4_9.INIT0 = 16'hfaaa;
    defparam contH_33_add_4_9.INIT1 = 16'hfaaa;
    defparam contH_33_add_4_9.INJECT1_0 = "NO";
    defparam contH_33_add_4_9.INJECT1_1 = "NO";
    CCU2D contH_33_add_4_7 (.A0(contH[5]), .B0(GND_net), .C0(GND_net), 
          .D0(GND_net), .A1(contH[6]), .B1(GND_net), .C1(GND_net), .D1(GND_net), 
          .CIN(n215), .COUT(n216), .S0(n60_adj_7), .S1(n59_adj_6));   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33_add_4_7.INIT0 = 16'hfaaa;
    defparam contH_33_add_4_7.INIT1 = 16'hfaaa;
    defparam contH_33_add_4_7.INJECT1_0 = "NO";
    defparam contH_33_add_4_7.INJECT1_1 = "NO";
    CCU2D contH_33_add_4_5 (.A0(contH[3]), .B0(GND_net), .C0(GND_net), 
          .D0(GND_net), .A1(contH[4]), .B1(GND_net), .C1(GND_net), .D1(GND_net), 
          .CIN(n214), .COUT(n215), .S0(n62_adj_9), .S1(n61_adj_8));   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33_add_4_5.INIT0 = 16'hfaaa;
    defparam contH_33_add_4_5.INIT1 = 16'hfaaa;
    defparam contH_33_add_4_5.INJECT1_0 = "NO";
    defparam contH_33_add_4_5.INJECT1_1 = "NO";
    CCU2D contH_33_add_4_3 (.A0(contH[1]), .B0(GND_net), .C0(GND_net), 
          .D0(GND_net), .A1(contH[2]), .B1(GND_net), .C1(GND_net), .D1(GND_net), 
          .CIN(n213), .COUT(n214), .S0(n64_adj_11), .S1(n63_adj_10));   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33_add_4_3.INIT0 = 16'hfaaa;
    defparam contH_33_add_4_3.INIT1 = 16'hfaaa;
    defparam contH_33_add_4_3.INJECT1_0 = "NO";
    defparam contH_33_add_4_3.INJECT1_1 = "NO";
    CCU2D contH_33_add_4_1 (.A0(GND_net), .B0(GND_net), .C0(GND_net), 
          .D0(GND_net), .A1(contH[0]), .B1(GND_net), .C1(GND_net), .D1(GND_net), 
          .COUT(n213), .S1(n65_adj_12));   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33_add_4_1.INIT0 = 16'hF000;
    defparam contH_33_add_4_1.INIT1 = 16'h0555;
    defparam contH_33_add_4_1.INJECT1_0 = "NO";
    defparam contH_33_add_4_1.INJECT1_1 = "NO";
    CCU2D sub_29_add_2_5 (.A0(contL[3]), .B0(contH[3]), .C0(GND_net), 
          .D0(GND_net), .A1(contL[4]), .B1(contH[4]), .C1(GND_net), 
          .D1(GND_net), .CIN(n202), .COUT(n203));
    defparam sub_29_add_2_5.INIT0 = 16'h5999;
    defparam sub_29_add_2_5.INIT1 = 16'h5999;
    defparam sub_29_add_2_5.INJECT1_0 = "NO";
    defparam sub_29_add_2_5.INJECT1_1 = "NO";
    CCU2D contL_32_add_4_13 (.A0(contL[11]), .B0(GND_net), .C0(GND_net), 
          .D0(GND_net), .A1(GND_net), .B1(GND_net), .C1(GND_net), .D1(GND_net), 
          .CIN(n212), .S0(n54));   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32_add_4_13.INIT0 = 16'hfaaa;
    defparam contL_32_add_4_13.INIT1 = 16'h0000;
    defparam contL_32_add_4_13.INJECT1_0 = "NO";
    defparam contL_32_add_4_13.INJECT1_1 = "NO";
    CCU2D contL_32_add_4_9 (.A0(contL[7]), .B0(GND_net), .C0(GND_net), 
          .D0(GND_net), .A1(contL[8]), .B1(GND_net), .C1(GND_net), .D1(GND_net), 
          .CIN(n210), .COUT(n211), .S0(n58), .S1(n57));   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32_add_4_9.INIT0 = 16'hfaaa;
    defparam contL_32_add_4_9.INIT1 = 16'hfaaa;
    defparam contL_32_add_4_9.INJECT1_0 = "NO";
    defparam contL_32_add_4_9.INJECT1_1 = "NO";
    CCU2D contL_32_add_4_1 (.A0(GND_net), .B0(GND_net), .C0(GND_net), 
          .D0(GND_net), .A1(contL[0]), .B1(GND_net), .C1(GND_net), .D1(GND_net), 
          .COUT(n207), .S1(n65));   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32_add_4_1.INIT0 = 16'hF000;
    defparam contL_32_add_4_1.INIT1 = 16'h0555;
    defparam contL_32_add_4_1.INJECT1_0 = "NO";
    defparam contL_32_add_4_1.INJECT1_1 = "NO";
    CCU2D sub_29_add_2_11 (.A0(contL[9]), .B0(contH[9]), .C0(GND_net), 
          .D0(GND_net), .A1(contL[10]), .B1(contH[10]), .C1(GND_net), 
          .D1(GND_net), .CIN(n205), .COUT(n206));
    defparam sub_29_add_2_11.INIT0 = 16'h5999;
    defparam sub_29_add_2_11.INIT1 = 16'h5999;
    defparam sub_29_add_2_11.INJECT1_0 = "NO";
    defparam sub_29_add_2_11.INJECT1_1 = "NO";
    CCU2D sub_29_add_2_3 (.A0(contL[1]), .B0(contH[1]), .C0(GND_net), 
          .D0(GND_net), .A1(contL[2]), .B1(contH[2]), .C1(GND_net), 
          .D1(GND_net), .CIN(n201), .COUT(n202));
    defparam sub_29_add_2_3.INIT0 = 16'h5999;
    defparam sub_29_add_2_3.INIT1 = 16'h5999;
    defparam sub_29_add_2_3.INJECT1_0 = "NO";
    defparam sub_29_add_2_3.INJECT1_1 = "NO";
    FD1S3AX contL_32__i0 (.D(n65), .CK(clk_c), .Q(contL[0])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32__i0.GSR = "ENABLED";
    GSR GSR_INST (.GSR(rstn_c));
    FD1P3AX contH_33__i10 (.D(n55_adj_2), .SP(clk_c_enable_12), .CK(clk_c), 
            .Q(contH[10])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33__i10.GSR = "ENABLED";
    FD1P3AX contH_33__i9 (.D(n56_adj_3), .SP(clk_c_enable_12), .CK(clk_c), 
            .Q(contH[9])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33__i9.GSR = "ENABLED";
    FD1P3AX contH_33__i8 (.D(n57_adj_4), .SP(clk_c_enable_12), .CK(clk_c), 
            .Q(contH[8])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33__i8.GSR = "ENABLED";
    FD1P3AX contH_33__i7 (.D(n58_adj_5), .SP(clk_c_enable_12), .CK(clk_c), 
            .Q(contH[7])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33__i7.GSR = "ENABLED";
    FD1P3AX contH_33__i6 (.D(n59_adj_6), .SP(clk_c_enable_12), .CK(clk_c), 
            .Q(contH[6])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33__i6.GSR = "ENABLED";
    FD1P3AX contH_33__i5 (.D(n60_adj_7), .SP(clk_c_enable_12), .CK(clk_c), 
            .Q(contH[5])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33__i5.GSR = "ENABLED";
    FD1P3AX contH_33__i4 (.D(n61_adj_8), .SP(clk_c_enable_12), .CK(clk_c), 
            .Q(contH[4])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33__i4.GSR = "ENABLED";
    FD1P3AX contH_33__i3 (.D(n62_adj_9), .SP(clk_c_enable_12), .CK(clk_c), 
            .Q(contH[3])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33__i3.GSR = "ENABLED";
    FD1P3AX contH_33__i2 (.D(n63_adj_10), .SP(clk_c_enable_12), .CK(clk_c), 
            .Q(contH[2])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33__i2.GSR = "ENABLED";
    FD1P3AX contH_33__i1 (.D(n64_adj_11), .SP(clk_c_enable_12), .CK(clk_c), 
            .Q(contH[1])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(44[22:34])
    defparam contH_33__i1.GSR = "ENABLED";
    FD1S3AX contL_32__i11 (.D(n54), .CK(clk_c), .Q(contL[11])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32__i11.GSR = "ENABLED";
    CCU2D sub_29_add_2_9 (.A0(contL[7]), .B0(contH[7]), .C0(GND_net), 
          .D0(GND_net), .A1(contL[8]), .B1(contH[8]), .C1(GND_net), 
          .D1(GND_net), .CIN(n204), .COUT(n205));
    defparam sub_29_add_2_9.INIT0 = 16'h5999;
    defparam sub_29_add_2_9.INIT1 = 16'h5999;
    defparam sub_29_add_2_9.INJECT1_0 = "NO";
    defparam sub_29_add_2_9.INJECT1_1 = "NO";
    CCU2D sub_29_add_2_13 (.A0(contL[11]), .B0(contH[11]), .C0(GND_net), 
          .D0(GND_net), .A1(GND_net), .B1(GND_net), .C1(GND_net), .D1(GND_net), 
          .CIN(n206), .S1(pwm_c));
    defparam sub_29_add_2_13.INIT0 = 16'h5999;
    defparam sub_29_add_2_13.INIT1 = 16'h0000;
    defparam sub_29_add_2_13.INJECT1_0 = "NO";
    defparam sub_29_add_2_13.INJECT1_1 = "NO";
    CCU2D contL_32_add_4_7 (.A0(contL[5]), .B0(GND_net), .C0(GND_net), 
          .D0(GND_net), .A1(contL[6]), .B1(GND_net), .C1(GND_net), .D1(GND_net), 
          .CIN(n209), .COUT(n210), .S0(n60), .S1(n59));   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32_add_4_7.INIT0 = 16'hfaaa;
    defparam contL_32_add_4_7.INIT1 = 16'hfaaa;
    defparam contL_32_add_4_7.INJECT1_0 = "NO";
    defparam contL_32_add_4_7.INJECT1_1 = "NO";
    CCU2D contL_32_add_4_5 (.A0(contL[3]), .B0(GND_net), .C0(GND_net), 
          .D0(GND_net), .A1(contL[4]), .B1(GND_net), .C1(GND_net), .D1(GND_net), 
          .CIN(n208), .COUT(n209), .S0(n62), .S1(n61));   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32_add_4_5.INIT0 = 16'hfaaa;
    defparam contL_32_add_4_5.INIT1 = 16'hfaaa;
    defparam contL_32_add_4_5.INJECT1_0 = "NO";
    defparam contL_32_add_4_5.INJECT1_1 = "NO";
    FD1S3AX contL_32__i10 (.D(n55), .CK(clk_c), .Q(contL[10])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32__i10.GSR = "ENABLED";
    FD1S3AX contL_32__i9 (.D(n56), .CK(clk_c), .Q(contL[9])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32__i9.GSR = "ENABLED";
    FD1S3AX contL_32__i8 (.D(n57), .CK(clk_c), .Q(contL[8])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32__i8.GSR = "ENABLED";
    FD1S3AX contL_32__i7 (.D(n58), .CK(clk_c), .Q(contL[7])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32__i7.GSR = "ENABLED";
    FD1S3AX contL_32__i6 (.D(n59), .CK(clk_c), .Q(contL[6])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32__i6.GSR = "ENABLED";
    FD1S3AX contL_32__i5 (.D(n60), .CK(clk_c), .Q(contL[5])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32__i5.GSR = "ENABLED";
    FD1S3AX contL_32__i4 (.D(n61), .CK(clk_c), .Q(contL[4])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32__i4.GSR = "ENABLED";
    FD1S3AX contL_32__i3 (.D(n62), .CK(clk_c), .Q(contL[3])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32__i3.GSR = "ENABLED";
    FD1S3AX contL_32__i2 (.D(n63), .CK(clk_c), .Q(contL[2])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32__i2.GSR = "ENABLED";
    FD1S3AX contL_32__i1 (.D(n64), .CK(clk_c), .Q(contL[1])) /* synthesis syn_use_carry_chain=1 */ ;   // h:/fpga-program/step-mxo2-v2/breathlight/breathlight.v(32[22:34])
    defparam contL_32__i1.GSR = "ENABLED";
    CCU2D sub_29_add_2_1 (.A0(GND_net), .B0(GND_net), .C0(GND_net), .D0(GND_net), 
          .A1(contL[0]), .B1(contH[0]), .C1(GND_net), .D1(GND_net), 
          .COUT(n201));
    defparam sub_29_add_2_1.INIT0 = 16'h0000;
    defparam sub_29_add_2_1.INIT1 = 16'h5999;
    defparam sub_29_add_2_1.INJECT1_0 = "NO";
    defparam sub_29_add_2_1.INJECT1_1 = "NO";
    
endmodule
//
// Verilog Description of module PUR
// module not written out since it is a black-box. 
//

//
// Verilog Description of module TSALL
// module not written out since it is a black-box. 
//

