// ======================================================================
// Skateboard Motherboard.v generated from TopDesign.cysch
// 06/12/2012 at 19:22
// ======================================================================

/* -- WARNING: The following section of defines are deprecated and will be removed in a future release -- */
`define CYDEV_CHIP_DIE_LEOPARD 1
`define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3
`define CYDEV_CHIP_REV_LEOPARD_ES3 3
`define CYDEV_CHIP_REV_LEOPARD_ES2 1
`define CYDEV_CHIP_REV_LEOPARD_ES1 0
`define CYDEV_CHIP_DIE_PANTHER 2
`define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1
`define CYDEV_CHIP_REV_PANTHER_ES1 1
`define CYDEV_CHIP_REV_PANTHER_ES0 0
`define CYDEV_CHIP_DIE_EXPECT 2
`define CYDEV_CHIP_REV_EXPECT 1
`define CYDEV_CHIP_DIE_ACTUAL 2
/* -- WARNING: The previous section of defines are deprecated and will be removed in a future release -- */
`define CYDEV_CHIP_FAMILY_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_UNKNOWN 0
`define CYDEV_CHIP_FAMILY_PSOC3 1
`define CYDEV_CHIP_MEMBER_3A 1
`define CYDEV_CHIP_REVISION_3A_PRODUCTION 3
`define CYDEV_CHIP_REVISION_3A_ES3 3
`define CYDEV_CHIP_REVISION_3A_ES2 1
`define CYDEV_CHIP_REVISION_3A_ES1 0
`define CYDEV_CHIP_FAMILY_PSOC5 2
`define CYDEV_CHIP_MEMBER_5A 2
`define CYDEV_CHIP_REVISION_5A_PRODUCTION 1
`define CYDEV_CHIP_REVISION_5A_ES1 1
`define CYDEV_CHIP_REVISION_5A_ES0 0
`define CYDEV_CHIP_FAMILY_USED 2
`define CYDEV_CHIP_MEMBER_USED 2
`define CYDEV_CHIP_REVISION_USED 1
// Component: B_PWM_v2_10
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v2_10"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v2_10\B_PWM_v2_10.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v2_10"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v2_10\B_PWM_v2_10.v"
`endif

// Component: cy_virtualmux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`endif

// Component: OneTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal\OneTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal\OneTerminal.v"
`endif

// Component: ZeroTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`endif

// PWM_v2_10(CaptureMode=0, CompareStatusEdgeSense=true, CompareType1=1, CompareType1Software=0, CompareType2=1, CompareType2Software=0, CompareValue1=0, CompareValue2=63, CtlModeReplacementString=AsyncCtl, CyGetRegReplacementString=CY_GET_REG16, CySetRegReplacementString=CY_SET_REG16, DeadBand=0, DeadBand2_4=0, DeadBandUsed=0, DeadTime=1, DitherOffset=0, EnableMode=0, FixedFunction=false, FixedFunctionUsed=0, InterruptOnCMP1=false, InterruptOnCMP2=false, InterruptOnKill=false, InterruptOnTC=false, IntOnCMP1=0, IntOnCMP2=0, IntOnKill=0, IntOnTC=0, KillMode=0, KillModeMinTime=0, MinimumKillTime=1, OneCompare=true, Period=1091, PWMMode=0, PWMModeCenterAligned=0, RegDefReplacementString=reg16, RegSizeReplacementString=uint16, Resolution=16, RstStatusReplacementString=sSTSReg_nrstSts, RunMode=0, TriggerMode=0, UseControl=true, UseInterrupt=true, UseStatus=true, VerilogSectionReplacementString=sP16, CY_COMPONENT_NAME=PWM_v2_10, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=PwmMotor, CY_INSTANCE_SHORT_NAME=PwmMotor, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=10, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=PwmMotor, )
module PWM_v2_10_0 (pwm2, tc, clock, reset, pwm1, interrupt, capture, kill, enable, trigger, cmp_sel, pwm, ph1, ph2);
    output  pwm2;
    output  tc;
    input   clock;
    input   reset;
    output  pwm1;
    output  interrupt;
    input   capture;
    input   kill;
    input   enable;
    input   trigger;
    input   cmp_sel;
    output  pwm;
    output  ph1;
    output  ph2;

    parameter Resolution = 16;

    wire  Net_113;
    wire  Net_114;
    wire  Net_107;
    wire  Net_96;
    wire  Net_55;
    wire  Net_57;
    wire  Net_101;
    wire  Net_54;
    wire  Net_63;

    B_PWM_v2_10 PWMUDB (
        .reset(reset),
        .clock(clock),
        .tc(Net_101),
        .pwm1(pwm1),
        .pwm2(pwm2),
        .interrupt(Net_55),
        .kill(kill),
        .capture(capture),
        .enable(enable),
        .cmp_sel(cmp_sel),
        .trigger(trigger),
        .pwm(Net_96),
        .ph1(ph1),
        .ph2(ph2));
    defparam PWMUDB.CaptureMode = 0;
    defparam PWMUDB.CompareStatusEdgeSense = 1;
    defparam PWMUDB.CompareType1 = 1;
    defparam PWMUDB.CompareType2 = 1;
    defparam PWMUDB.DeadBand = 0;
    defparam PWMUDB.DitherOffset = 0;
    defparam PWMUDB.EnableMode = 0;
    defparam PWMUDB.KillMode = 0;
    defparam PWMUDB.PWMMode = 0;
    defparam PWMUDB.Resolution = 16;
    defparam PWMUDB.RunMode = 0;
    defparam PWMUDB.TriggerMode = 0;
    defparam PWMUDB.UseStatus = 1;

	// vmCompare (cy_virtualmux_v1_0)
	assign pwm = Net_96;

	// vmIRQ (cy_virtualmux_v1_0)
	assign interrupt = Net_55;

	// vmTC (cy_virtualmux_v1_0)
	assign tc = Net_101;

    OneTerminal OneTerminal_1 (
        .o(Net_113));

	// FFKillMux (cy_virtualmux_v1_0)
	assign Net_107 = Net_114;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_114));



endmodule

// Component: B_UART_v2_10
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_UART_v2_10"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_UART_v2_10\B_UART_v2_10.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_UART_v2_10"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_UART_v2_10\B_UART_v2_10.v"
`endif

// UART_v2_10(Address1=0, Address2=0, BaudRate=9600, BreakBitsRX=13, BreakBitsTX=13, BreakDetect=false, CRCoutputsEn=false, CtrlModeReplacementString=AsyncCtl, Enable_RX=1, Enable_RXIntInterrupt=1, Enable_TX=1, Enable_TXIntInterrupt=1, EnableHWAddress=0, EnIntRXInterrupt=true, EnIntTXInterrupt=true, FlowControl=0, HalfDuplexEn=false, HwTXEnSignal=false, InternalClock=true, InternalClockUsed=1, InterruptOnAddDetect=0, InterruptOnAddressMatch=0, InterruptOnBreak=0, InterruptOnByteRcvd=1, InterruptOnOverrunError=0, InterruptOnParityError=0, InterruptOnStopError=0, InterruptOnTXComplete=false, InterruptOnTXFifoEmpty=true, InterruptOnTXFifoFull=false, InterruptOnTXFifoNotFull=false, IntOnAddressDetect=false, IntOnAddressMatch=false, IntOnBreak=false, IntOnByteRcvd=true, IntOnOverrunError=false, IntOnParityError=false, IntOnStopError=false, NumDataBits=8, NumStopBits=1, OverSamplingRate=8, ParityType=0, ParityTypeSw=false, RequiredClock=76800, RXAddressMode=0, RXBufferSize=50, RxBuffRegSizeReplacementString=uint8, RXEnable=true, TXBitClkGenDP=true, TXBufferSize=50, TxBuffRegSizeReplacementString=uint8, TXEnable=true, Use23Polling=true, CY_COMPONENT_NAME=UART_v2_10, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=UartXbee, CY_INSTANCE_SHORT_NAME=UartXbee, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=10, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=UartXbee, )
module UART_v2_10_1 (rx_clk, rx_data, tx_clk, tx_data, rx_interrupt, tx_interrupt, tx, tx_en, rts_n, reset, cts_n, clock, rx);
    output  rx_clk;
    output  rx_data;
    output  tx_clk;
    output  tx_data;
    output  rx_interrupt;
    output  tx_interrupt;
    output  tx;
    output  tx_en;
    output  rts_n;
    input   reset;
    input   cts_n;
    input   clock;
    input   rx;

    parameter Address1 = 0;
    parameter Address2 = 0;
    parameter EnIntRXInterrupt = 1;
    parameter EnIntTXInterrupt = 1;
    parameter FlowControl = 0;
    parameter HalfDuplexEn = 0;
    parameter HwTXEnSignal = 0;
    parameter NumDataBits = 8;
    parameter NumStopBits = 1;
    parameter ParityType = 0;
    parameter RXEnable = 1;
    parameter TXEnable = 1;

    wire  Net_289;
    wire  Net_9;
    wire  Net_61;


	cy_isr_v1_0
		#(.int_type(2'b10))
		TXInternalInterrupt
		 (.int_signal(tx_interrupt));



	cy_clock_v1_0
		#(.id("b0162966-0060-4af5-82d1-fcb491ad7619/be0a0e37-ad17-42ca-b5a1-1a654d736358"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("13020833333.3333"),
		  .is_direct(0),
		  .is_digital(1))
		IntClock
		 (.clock_out(Net_9));



	cy_isr_v1_0
		#(.int_type(2'b10))
		RXInternalInterrupt
		 (.int_signal(rx_interrupt));


	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_61 = Net_9;

    B_UART_v2_10 BUART (
        .cts_n(cts_n),
        .tx(tx),
        .rts_n(rts_n),
        .tx_en(tx_en),
        .clock(Net_61),
        .reset(reset),
        .rx(rx),
        .tx_interrupt(tx_interrupt),
        .rx_interrupt(rx_interrupt),
        .tx_data(tx_data),
        .tx_clk(tx_clk),
        .rx_data(rx_data),
        .rx_clk(rx_clk));
    defparam BUART.Address1 = 0;
    defparam BUART.Address2 = 0;
    defparam BUART.BreakBitsRX = 13;
    defparam BUART.BreakBitsTX = 13;
    defparam BUART.BreakDetect = 0;
    defparam BUART.CRCoutputsEn = 0;
    defparam BUART.FlowControl = 0;
    defparam BUART.HalfDuplexEn = 0;
    defparam BUART.HwTXEnSignal = 0;
    defparam BUART.NumDataBits = 8;
    defparam BUART.NumStopBits = 1;
    defparam BUART.OverSampleCount = 8;
    defparam BUART.ParityType = 0;
    defparam BUART.ParityTypeSw = 0;
    defparam BUART.RXAddressMode = 0;
    defparam BUART.RXEnable = 1;
    defparam BUART.RXStatusIntEnable = 1;
    defparam BUART.TXBitClkGenDP = 1;
    defparam BUART.TXEnable = 1;
    defparam BUART.Use23Polling = 1;



endmodule

// PWM_v2_10(CaptureMode=0, CompareStatusEdgeSense=true, CompareType1=3, CompareType1Software=0, CompareType2=3, CompareType2Software=0, CompareValue1=127, CompareValue2=128, CtlModeReplacementString=AsyncCtl, CyGetRegReplacementString=CY_GET_REG16, CySetRegReplacementString=CY_SET_REG16, DeadBand=0, DeadBand2_4=0, DeadBandUsed=0, DeadTime=1, DitherOffset=0, EnableMode=0, FixedFunction=false, FixedFunctionUsed=0, InterruptOnCMP1=false, InterruptOnCMP2=false, InterruptOnKill=false, InterruptOnTC=false, IntOnCMP1=0, IntOnCMP2=0, IntOnKill=0, IntOnTC=0, KillMode=0, KillModeMinTime=0, MinimumKillTime=1, OneCompare=true, Period=197, PWMMode=0, PWMModeCenterAligned=0, RegDefReplacementString=reg16, RegSizeReplacementString=uint16, Resolution=16, RstStatusReplacementString=sSTSReg_nrstSts, RunMode=0, TriggerMode=0, UseControl=true, UseInterrupt=true, UseStatus=true, VerilogSectionReplacementString=sP16, CY_COMPONENT_NAME=PWM_v2_10, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=PwmPiezo, CY_INSTANCE_SHORT_NAME=PwmPiezo, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=10, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=PwmPiezo, )
module PWM_v2_10_2 (pwm2, tc, clock, reset, pwm1, interrupt, capture, kill, enable, trigger, cmp_sel, pwm, ph1, ph2);
    output  pwm2;
    output  tc;
    input   clock;
    input   reset;
    output  pwm1;
    output  interrupt;
    input   capture;
    input   kill;
    input   enable;
    input   trigger;
    input   cmp_sel;
    output  pwm;
    output  ph1;
    output  ph2;

    parameter Resolution = 16;

    wire  Net_114;
    wire  Net_113;
    wire  Net_107;
    wire  Net_96;
    wire  Net_55;
    wire  Net_57;
    wire  Net_101;
    wire  Net_54;
    wire  Net_63;

    B_PWM_v2_10 PWMUDB (
        .reset(reset),
        .clock(clock),
        .tc(Net_101),
        .pwm1(pwm1),
        .pwm2(pwm2),
        .interrupt(Net_55),
        .kill(kill),
        .capture(capture),
        .enable(enable),
        .cmp_sel(cmp_sel),
        .trigger(trigger),
        .pwm(Net_96),
        .ph1(ph1),
        .ph2(ph2));
    defparam PWMUDB.CaptureMode = 0;
    defparam PWMUDB.CompareStatusEdgeSense = 1;
    defparam PWMUDB.CompareType1 = 3;
    defparam PWMUDB.CompareType2 = 3;
    defparam PWMUDB.DeadBand = 0;
    defparam PWMUDB.DitherOffset = 0;
    defparam PWMUDB.EnableMode = 0;
    defparam PWMUDB.KillMode = 0;
    defparam PWMUDB.PWMMode = 0;
    defparam PWMUDB.Resolution = 16;
    defparam PWMUDB.RunMode = 0;
    defparam PWMUDB.TriggerMode = 0;
    defparam PWMUDB.UseStatus = 1;

	// vmCompare (cy_virtualmux_v1_0)
	assign pwm = Net_96;

	// vmIRQ (cy_virtualmux_v1_0)
	assign interrupt = Net_55;

	// vmTC (cy_virtualmux_v1_0)
	assign tc = Net_101;

    OneTerminal OneTerminal_1 (
        .o(Net_113));

	// FFKillMux (cy_virtualmux_v1_0)
	assign Net_107 = Net_114;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_114));



endmodule

// Component: B_Timer_v2_20
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Timer_v2_20"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Timer_v2_20\B_Timer_v2_20.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Timer_v2_20"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Timer_v2_20\B_Timer_v2_20.v"
`endif

// Timer_v2_20(CaptureAlternatingFall=false, CaptureAlternatingRise=false, CaptureCount=2, CaptureCounterEnabled=false, CaptureInputEnabled=false, CaptureMode=0, ControlRegRemoved=0, CtlModeReplacementString=AsyncCtl, CyGetRegReplacementString=CY_GET_REG8, CySetRegReplacementString=CY_SET_REG8, DeviceFamily=PSoC5, EnableMode=0, FF16=false, FF8=false, FixedFunction=false, FixedFunctionUsed=0, HWCaptureCounterEnabled=false, InterruptOnCapture=false, InterruptOnFIFOFull=false, InterruptOnTC=true, IntOnCapture=0, IntOnFIFOFull=0, IntOnTC=1, NumberOfCaptures=1, param45=1, Period=9, RegDefReplacementString=reg8, RegSizeReplacementString=uint8, Resolution=8, RstStatusReplacementString=nrstSts, RunMode=0, SiliconRevision=1, SoftwareCaptureModeEnabled=false, SoftwareTriggerModeEnabled=false, TriggerInputEnabled=false, TriggerMode=0, UDB16=false, UDB24=false, UDB32=false, UDB8=true, UsesHWEnable=0, VerilogSectionReplacementString=sT8, CY_COMPONENT_NAME=Timer_v2_20, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=TimerMainTick, CY_INSTANCE_SHORT_NAME=TimerMainTick, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=20, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=TimerMainTick, )
module Timer_v2_20_3 (clock, reset, interrupt, enable, capture, trigger, capture_out, tc);
    input   clock;
    input   reset;
    output  interrupt;
    input   enable;
    input   capture;
    input   trigger;
    output  capture_out;
    output  tc;

    parameter CaptureCount = 2;
    parameter CaptureCounterEnabled = 0;
    parameter DeviceFamily = "PSoC5";
    parameter InterruptOnCapture = 0;
    parameter InterruptOnTC = 1;
    parameter Resolution = 8;
    parameter SiliconRevision = "1";

    wire  Net_260;
    wire  Net_261;
    wire  Net_266;
    wire  Net_102;
    wire  Net_55;
    wire  Net_57;
    wire  Net_53;
    wire  Net_51;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_260));

	// VirtualMux_2 (cy_virtualmux_v1_0)
	assign interrupt = Net_55;

	// VirtualMux_3 (cy_virtualmux_v1_0)
	assign tc = Net_53;

    B_Timer_v2_20 TimerUDB (
        .reset(reset),
        .interrupt(Net_55),
        .enable(enable),
        .trigger(trigger),
        .capture_in(capture),
        .capture_out(capture_out),
        .tc(Net_53),
        .clock(clock));
    defparam TimerUDB.Capture_Count = 2;
    defparam TimerUDB.CaptureCounterEnabled = 0;
    defparam TimerUDB.CaptureMode = 0;
    defparam TimerUDB.EnableMode = 0;
    defparam TimerUDB.InterruptOnCapture = 0;
    defparam TimerUDB.Resolution = 8;
    defparam TimerUDB.RunMode = 0;
    defparam TimerUDB.TriggerMode = 0;

    OneTerminal OneTerminal_1 (
        .o(Net_102));

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_266 = Net_102;



endmodule

// UART_v2_10(Address1=0, Address2=0, BaudRate=57600, BreakBitsRX=13, BreakBitsTX=13, BreakDetect=false, CRCoutputsEn=false, CtrlModeReplacementString=AsyncCtl, Enable_RX=1, Enable_RXIntInterrupt=1, Enable_TX=1, Enable_TXIntInterrupt=1, EnableHWAddress=0, EnIntRXInterrupt=true, EnIntTXInterrupt=true, FlowControl=0, HalfDuplexEn=false, HwTXEnSignal=false, InternalClock=true, InternalClockUsed=1, InterruptOnAddDetect=0, InterruptOnAddressMatch=0, InterruptOnBreak=0, InterruptOnByteRcvd=1, InterruptOnOverrunError=0, InterruptOnParityError=0, InterruptOnStopError=0, InterruptOnTXComplete=false, InterruptOnTXFifoEmpty=true, InterruptOnTXFifoFull=false, InterruptOnTXFifoNotFull=false, IntOnAddressDetect=false, IntOnAddressMatch=false, IntOnBreak=false, IntOnByteRcvd=true, IntOnOverrunError=false, IntOnParityError=false, IntOnStopError=false, NumDataBits=8, NumStopBits=1, OverSamplingRate=8, ParityType=0, ParityTypeSw=false, RequiredClock=460800, RXAddressMode=0, RXBufferSize=50, RxBuffRegSizeReplacementString=uint8, RXEnable=true, TXBitClkGenDP=true, TXBufferSize=50, TxBuffRegSizeReplacementString=uint8, TXEnable=true, Use23Polling=true, CY_COMPONENT_NAME=UART_v2_10, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=UartDebug, CY_INSTANCE_SHORT_NAME=UartDebug, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=10, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=UartDebug, )
module UART_v2_10_4 (rx_clk, rx_data, tx_clk, tx_data, rx_interrupt, tx_interrupt, tx, tx_en, rts_n, reset, cts_n, clock, rx);
    output  rx_clk;
    output  rx_data;
    output  tx_clk;
    output  tx_data;
    output  rx_interrupt;
    output  tx_interrupt;
    output  tx;
    output  tx_en;
    output  rts_n;
    input   reset;
    input   cts_n;
    input   clock;
    input   rx;

    parameter Address1 = 0;
    parameter Address2 = 0;
    parameter EnIntRXInterrupt = 1;
    parameter EnIntTXInterrupt = 1;
    parameter FlowControl = 0;
    parameter HalfDuplexEn = 0;
    parameter HwTXEnSignal = 0;
    parameter NumDataBits = 8;
    parameter NumStopBits = 1;
    parameter ParityType = 0;
    parameter RXEnable = 1;
    parameter TXEnable = 1;

    wire  Net_289;
    wire  Net_9;
    wire  Net_61;


	cy_isr_v1_0
		#(.int_type(2'b10))
		TXInternalInterrupt
		 (.int_signal(tx_interrupt));



	cy_clock_v1_0
		#(.id("06aa64ce-eff7-4330-b0da-30aeabcc89c0/be0a0e37-ad17-42ca-b5a1-1a654d736358"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("2170138888.88889"),
		  .is_direct(0),
		  .is_digital(1))
		IntClock
		 (.clock_out(Net_9));



	cy_isr_v1_0
		#(.int_type(2'b10))
		RXInternalInterrupt
		 (.int_signal(rx_interrupt));


	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_61 = Net_9;

    B_UART_v2_10 BUART (
        .cts_n(cts_n),
        .tx(tx),
        .rts_n(rts_n),
        .tx_en(tx_en),
        .clock(Net_61),
        .reset(reset),
        .rx(rx),
        .tx_interrupt(tx_interrupt),
        .rx_interrupt(rx_interrupt),
        .tx_data(tx_data),
        .tx_clk(tx_clk),
        .rx_data(rx_data),
        .rx_clk(rx_clk));
    defparam BUART.Address1 = 0;
    defparam BUART.Address2 = 0;
    defparam BUART.BreakBitsRX = 13;
    defparam BUART.BreakBitsTX = 13;
    defparam BUART.BreakDetect = 0;
    defparam BUART.CRCoutputsEn = 0;
    defparam BUART.FlowControl = 0;
    defparam BUART.HalfDuplexEn = 0;
    defparam BUART.HwTXEnSignal = 0;
    defparam BUART.NumDataBits = 8;
    defparam BUART.NumStopBits = 1;
    defparam BUART.OverSampleCount = 8;
    defparam BUART.ParityType = 0;
    defparam BUART.ParityTypeSw = 0;
    defparam BUART.RXAddressMode = 0;
    defparam BUART.RXEnable = 1;
    defparam BUART.RXStatusIntEnable = 1;
    defparam BUART.TXBitClkGenDP = 1;
    defparam BUART.TXEnable = 1;
    defparam BUART.Use23Polling = 1;



endmodule

// Component: cy_analog_virtualmux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_analog_virtualmux_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_analog_virtualmux_v1_0\cy_analog_virtualmux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_analog_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_analog_virtualmux_v1_0\cy_analog_virtualmux_v1_0.v"
`endif

// Component: cy_vref_v1_50
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_vref_v1_50"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_vref_v1_50\cy_vref_v1_50.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_vref_v1_50"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_vref_v1_50\cy_vref_v1_50.v"
`endif

// ADC_SAR_v1_71(ADC_Clock=1, ADC_Clock_Frequency=1710000, ADC_Input_Range=1, ADC_Power=0, ADC_Reference=0, ADC_Resolution=12, ADC_Resolution_HW=12, ADC_SampleMode=0, Ref_Voltage=2.5, Ref_Voltage_mV=2500, Sample_Precharge=7, Sample_Rate=90000, Sample_Rate_def=631579, CY_COMPONENT_NAME=ADC_SAR_v1_71, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=AdcSar, CY_INSTANCE_SHORT_NAME=AdcSar, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=71, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=AdcSar, )
module ADC_SAR_v1_71_5 (vplus, vminus, soc, eoc, aclk, vdac_ref);
    inout   vplus;
    electrical   vplus;
    inout   vminus;
    electrical   vminus;
    input   soc;
    output  eoc;
    input   aclk;
    inout   vdac_ref;
    electrical   vdac_ref;


    wire [3:0] vp_ctl;
    wire [3:0] vn_ctl;
    electrical  Net_233;
    wire  Net_262;
    wire  Net_205;
    wire  Net_252;
    wire [11:0] Net_207;
    electrical  Net_209;
    electrical  Net_210;
    electrical  Net_267;
    electrical  Net_255;
    electrical  Net_257;
    electrical  Net_216;
    electrical  Net_149;
    electrical  Net_126;
    electrical  Net_215;
    electrical  Net_248;
    wire  Net_221;
    wire  Net_188;

	// cy_analog_virtualmux_3 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_3_connect(Net_248, Net_216);
	defparam cy_analog_virtualmux_3_connect.sig_width = 1;


	cy_isr_v1_0
		#(.int_type(2'b10))
		IRQ
		 (.int_signal(eoc));


    ZeroTerminal ZeroTerminal_1 (
        .z(vp_ctl[0]));

    ZeroTerminal ZeroTerminal_2 (
        .z(vp_ctl[2]));

    ZeroTerminal ZeroTerminal_3 (
        .z(vn_ctl[1]));

    ZeroTerminal ZeroTerminal_4 (
        .z(vn_ctl[3]));

    ZeroTerminal ZeroTerminal_5 (
        .z(vp_ctl[1]));

    ZeroTerminal ZeroTerminal_6 (
        .z(vp_ctl[3]));

    ZeroTerminal ZeroTerminal_7 (
        .z(vn_ctl[0]));

    ZeroTerminal ZeroTerminal_8 (
        .z(vn_ctl[2]));


	cy_clock_v1_0
		#(.id("9749c3fe-3bec-469f-9c0d-c8ccf1fe7041/696a0979-21fc-4185-bf38-6c79febcde7a"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("584795321.637427"),
		  .is_direct(0),
		  .is_digital(0))
		theACLK
		 (.clock_out(Net_221));


	// Clock_VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_188 = Net_221;

    cy_psoc5_sar_v2_0 ADC_SAR (
        .clock(Net_188),
        .sof_udb(soc),
        .clk_udb(),
        .vp_ctl_udb(vp_ctl[3:0]),
        .vn_ctl_udb(vn_ctl[3:0]),
        .vplus(vplus),
        .vminus(Net_126),
        .irq(Net_252),
        .data_out(Net_207[11:0]),
        .eof_udb(eoc),
        .pump_clock(Net_188),
        .ext_pin(Net_215),
        .vrefhi_out(Net_257),
        .vref(Net_248));

	// cy_analog_virtualmux_2 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_2_connect(Net_215, Net_209);
	defparam cy_analog_virtualmux_2_connect.sig_width = 1;

	// cy_analog_virtualmux_1 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_1_connect(Net_126, Net_149);
	defparam cy_analog_virtualmux_1_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 noconnect (
        .noconnect(Net_209));


	cy_vref_v1_0
		#(.autoenable(1),
		  .guid("4720866E-BC14-478d-B8A0-3E44F38CADAC"),
		  .ignoresleep(0),
		  .name("Vdda/2"))
		vRef_Vdda
		 (.vout(Net_216));


	// cy_analog_virtualmux_4 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_4_connect(Net_257, Net_149);
	defparam cy_analog_virtualmux_4_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 cy_analog_noconnect_1 (
        .noconnect(Net_255));



endmodule

// top
module top ;

    electrical  Net_194;
    wire  Net_193;
    wire  Net_192;
    wire  Net_191;
    electrical  Net_190;
    electrical  Net_184;
    wire  Net_166;
    wire  Net_165;
    wire  Net_164;
    wire  Net_163;
    wire  Net_162;
    wire  Net_161;
    wire  Net_160;
    wire  Net_159;
    wire  Net_158;
    wire  Net_157;
    wire  Net_156;
    wire  Net_155;
    wire  Net_154;
    wire  Net_124;
    wire  Net_123;
    wire  Net_122;
    wire  Net_121;
    wire  Net_120;
    wire  Net_119;
    wire  Net_118;
    wire  Net_40;
    wire  Net_42;
    wire  Net_66;
    wire  Net_65;
    wire  Net_64;
    wire  Net_63;
    wire  Net_62;
    wire  Net_61;
    wire  Net_60;
    wire  Net_59;
    wire  Net_58;
    wire  Net_140;
    wire  Net_28;
    wire  Net_57;
    wire  Net_26;
    wire  Net_56;
    wire  Net_114;
    wire  Net_113;
    wire  Net_112;
    wire  Net_111;
    wire  Net_110;
    wire  Net_109;
    wire  Net_108;
    wire  Net_107;
    wire  Net_106;
    wire  Net_105;
    wire  Net_70;
    wire  Net_104;
    wire  Net_41;
    wire  Net_75;
    wire  Net_55;
    wire  Net_54;
    wire  Net_53;
    wire  Net_52;
    wire  Net_51;
    wire  Net_50;
    wire  Net_49;
    wire  Net_48;
    wire  Net_47;
    wire  Net_46;
    wire  Net_45;
    wire  Net_6;
    wire  Net_44;
    wire  Net_117;
    wire  Net_10;
    wire  Net_220;
    wire  Net_43;

	wire [0:0] tmpOE__PinLedGreen_net;
	wire [0:0] tmpFB_0__PinLedGreen_net;
	wire [0:0] tmpIO_0__PinLedGreen_net;
	wire [0:0] tmpINTERRUPT_0__PinLedGreen_net;
	electrical [0:0] tmpSIOVREF__PinLedGreen_net;

	cy_psoc3_pins_v1_10
		#(.id("ed092b9b-d398-4703-be89-cebf998501f6"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		PinLedGreen
		 (.oe(tmpOE__PinLedGreen_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinLedGreen_net[0:0]}),
		  .io({tmpIO_0__PinLedGreen_net[0:0]}),
		  .siovref(tmpSIOVREF__PinLedGreen_net),
		  .interrupt({tmpINTERRUPT_0__PinLedGreen_net[0:0]}));

	assign tmpOE__PinLedGreen_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinLedOrange_net;
	wire [0:0] tmpFB_0__PinLedOrange_net;
	wire [0:0] tmpIO_0__PinLedOrange_net;
	wire [0:0] tmpINTERRUPT_0__PinLedOrange_net;
	electrical [0:0] tmpSIOVREF__PinLedOrange_net;

	cy_psoc3_pins_v1_10
		#(.id("f72ac192-e941-492a-83b1-18054f830ae7"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		PinLedOrange
		 (.oe(tmpOE__PinLedOrange_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinLedOrange_net[0:0]}),
		  .io({tmpIO_0__PinLedOrange_net[0:0]}),
		  .siovref(tmpSIOVREF__PinLedOrange_net),
		  .interrupt({tmpINTERRUPT_0__PinLedOrange_net[0:0]}));

	assign tmpOE__PinLedOrange_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinLedRed_net;
	wire [0:0] tmpFB_0__PinLedRed_net;
	wire [0:0] tmpIO_0__PinLedRed_net;
	wire [0:0] tmpINTERRUPT_0__PinLedRed_net;
	electrical [0:0] tmpSIOVREF__PinLedRed_net;

	cy_psoc3_pins_v1_10
		#(.id("5137b97b-911f-4897-a359-2e3c5a1e8ec7"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		PinLedRed
		 (.oe(tmpOE__PinLedRed_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinLedRed_net[0:0]}),
		  .io({tmpIO_0__PinLedRed_net[0:0]}),
		  .siovref(tmpSIOVREF__PinLedRed_net),
		  .interrupt({tmpINTERRUPT_0__PinLedRed_net[0:0]}));

	assign tmpOE__PinLedRed_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    PWM_v2_10_0 PwmMotor (
        .reset(1'b0),
        .clock(Net_6),
        .tc(Net_45),
        .pwm1(Net_46),
        .pwm2(Net_47),
        .interrupt(Net_48),
        .capture(1'b0),
        .kill(1'b1),
        .enable(1'b1),
        .trigger(1'b0),
        .cmp_sel(1'b0),
        .pwm(Net_43),
        .ph1(Net_54),
        .ph2(Net_55));
    defparam PwmMotor.Resolution = 16;

	wire [0:0] tmpOE__PinUartXbeeRx_net;
	wire [0:0] tmpIO_0__PinUartXbeeRx_net;
	wire [0:0] tmpINTERRUPT_0__PinUartXbeeRx_net;
	electrical [0:0] tmpSIOVREF__PinUartXbeeRx_net;

	cy_psoc3_pins_v1_10
		#(.id("3e562cf6-0acc-4965-ba5c-7f5e75f155a7"),
		  .drive_mode(3'b001),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b00),
		  .width(1))
		PinUartXbeeRx
		 (.oe(tmpOE__PinUartXbeeRx_net),
		  .y({1'b0}),
		  .fb({Net_75}),
		  .io({tmpIO_0__PinUartXbeeRx_net[0:0]}),
		  .siovref(tmpSIOVREF__PinUartXbeeRx_net),
		  .interrupt({tmpINTERRUPT_0__PinUartXbeeRx_net[0:0]}));

	assign tmpOE__PinUartXbeeRx_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinPwmMotor_net;
	wire [0:0] tmpFB_0__PinPwmMotor_net;
	wire [0:0] tmpIO_0__PinPwmMotor_net;
	wire [0:0] tmpINTERRUPT_0__PinPwmMotor_net;
	electrical [0:0] tmpSIOVREF__PinPwmMotor_net;

	cy_psoc3_pins_v1_10
		#(.id("5705d396-496e-4609-bc8c-851101e252ca"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		PinPwmMotor
		 (.oe(tmpOE__PinPwmMotor_net),
		  .y({Net_43}),
		  .fb({tmpFB_0__PinPwmMotor_net[0:0]}),
		  .io({tmpIO_0__PinPwmMotor_net[0:0]}),
		  .siovref(tmpSIOVREF__PinPwmMotor_net),
		  .interrupt({tmpINTERRUPT_0__PinPwmMotor_net[0:0]}));

	assign tmpOE__PinPwmMotor_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};


	cy_clock_v1_0
		#(.id("eaa34f3f-c64f-4137-890d-8a006274673a"),
		  .source_clock_id("75C2148C-3656-4d8a-846D-0CAE99AB6FF7"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(1))
		ClockPwmMotor
		 (.clock_out(Net_6));


    UART_v2_10_1 UartXbee (
        .cts_n(1'b0),
        .tx(Net_70),
        .rts_n(Net_105),
        .tx_en(Net_106),
        .clock(1'b0),
        .reset(1'b0),
        .rx(Net_75),
        .tx_interrupt(Net_109),
        .rx_interrupt(Net_110),
        .tx_data(Net_111),
        .tx_clk(Net_112),
        .rx_data(Net_113),
        .rx_clk(Net_114));
    defparam UartXbee.Address1 = 0;
    defparam UartXbee.Address2 = 0;
    defparam UartXbee.EnIntRXInterrupt = 1;
    defparam UartXbee.EnIntTXInterrupt = 1;
    defparam UartXbee.FlowControl = 0;
    defparam UartXbee.HalfDuplexEn = 0;
    defparam UartXbee.HwTXEnSignal = 0;
    defparam UartXbee.NumDataBits = 8;
    defparam UartXbee.NumStopBits = 1;
    defparam UartXbee.ParityType = 0;
    defparam UartXbee.RXEnable = 1;
    defparam UartXbee.TXEnable = 1;

    PWM_v2_10_2 PwmPiezo (
        .reset(1'b0),
        .clock(Net_26),
        .tc(Net_57),
        .pwm1(Net_28),
        .pwm2(Net_140),
        .interrupt(Net_58),
        .capture(1'b0),
        .kill(1'b1),
        .enable(1'b1),
        .trigger(1'b0),
        .cmp_sel(1'b0),
        .pwm(Net_64),
        .ph1(Net_65),
        .ph2(Net_66));
    defparam PwmPiezo.Resolution = 16;


	cy_clock_v1_0
		#(.id("318bc948-a102-4567-aaf3-303f36e11e59"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("41666666.6666667"),
		  .is_direct(0),
		  .is_digital(1))
		ClockPwmPiezo
		 (.clock_out(Net_26));


	wire [0:0] tmpOE__PinPwmPiezo_net;
	wire [0:0] tmpFB_0__PinPwmPiezo_net;
	wire [0:0] tmpIO_0__PinPwmPiezo_net;
	wire [0:0] tmpINTERRUPT_0__PinPwmPiezo_net;
	electrical [0:0] tmpSIOVREF__PinPwmPiezo_net;

	cy_psoc3_pins_v1_10
		#(.id("b56f88fb-8a99-4c80-bd6f-5af2d6b6f3e2"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		PinPwmPiezo
		 (.oe(tmpOE__PinPwmPiezo_net),
		  .y({Net_64}),
		  .fb({tmpFB_0__PinPwmPiezo_net[0:0]}),
		  .io({tmpIO_0__PinPwmPiezo_net[0:0]}),
		  .siovref(tmpSIOVREF__PinPwmPiezo_net),
		  .interrupt({tmpINTERRUPT_0__PinPwmPiezo_net[0:0]}));

	assign tmpOE__PinPwmPiezo_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinMotionSensor_net;
	wire [0:0] tmpIO_0__PinMotionSensor_net;
	electrical [0:0] tmpSIOVREF__PinMotionSensor_net;

	cy_psoc3_pins_v1_10
		#(.id("1425177d-0d0e-4468-8bcc-e638e5509a9b"),
		  .drive_mode(3'b001),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b01),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b00),
		  .width(1))
		PinMotionSensor
		 (.oe(tmpOE__PinMotionSensor_net),
		  .y({1'b0}),
		  .fb({Net_40}),
		  .io({tmpIO_0__PinMotionSensor_net[0:0]}),
		  .siovref(tmpSIOVREF__PinMotionSensor_net),
		  .interrupt({Net_220}));

	assign tmpOE__PinMotionSensor_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};


	cy_isr_v1_0
		#(.int_type(2'b10))
		IsrMotionSensor
		 (.int_signal(Net_220));


	wire [0:0] tmpOE__PinLightFront_net;
	wire [0:0] tmpFB_0__PinLightFront_net;
	wire [0:0] tmpIO_0__PinLightFront_net;
	wire [0:0] tmpINTERRUPT_0__PinLightFront_net;
	electrical [0:0] tmpSIOVREF__PinLightFront_net;

	cy_psoc3_pins_v1_10
		#(.id("a12e04c8-0e39-4992-ba73-e1e04e47db16"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		PinLightFront
		 (.oe(tmpOE__PinLightFront_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinLightFront_net[0:0]}),
		  .io({tmpIO_0__PinLightFront_net[0:0]}),
		  .siovref(tmpSIOVREF__PinLightFront_net),
		  .interrupt({tmpINTERRUPT_0__PinLightFront_net[0:0]}));

	assign tmpOE__PinLightFront_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinLightRear_net;
	wire [0:0] tmpFB_0__PinLightRear_net;
	wire [0:0] tmpIO_0__PinLightRear_net;
	wire [0:0] tmpINTERRUPT_0__PinLightRear_net;
	electrical [0:0] tmpSIOVREF__PinLightRear_net;

	cy_psoc3_pins_v1_10
		#(.id("e0c6e155-cc69-4567-869e-f4cca536943b"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		PinLightRear
		 (.oe(tmpOE__PinLightRear_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinLightRear_net[0:0]}),
		  .io({tmpIO_0__PinLightRear_net[0:0]}),
		  .siovref(tmpSIOVREF__PinLightRear_net),
		  .interrupt({tmpINTERRUPT_0__PinLightRear_net[0:0]}));

	assign tmpOE__PinLightRear_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinLightSkirting_net;
	wire [0:0] tmpFB_0__PinLightSkirting_net;
	wire [0:0] tmpIO_0__PinLightSkirting_net;
	wire [0:0] tmpINTERRUPT_0__PinLightSkirting_net;
	electrical [0:0] tmpSIOVREF__PinLightSkirting_net;

	cy_psoc3_pins_v1_10
		#(.id("8307e94a-18cf-4c16-8e82-6a21c15eca36"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		PinLightSkirting
		 (.oe(tmpOE__PinLightSkirting_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinLightSkirting_net[0:0]}),
		  .io({tmpIO_0__PinLightSkirting_net[0:0]}),
		  .siovref(tmpSIOVREF__PinLightSkirting_net),
		  .interrupt({tmpINTERRUPT_0__PinLightSkirting_net[0:0]}));

	assign tmpOE__PinLightSkirting_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinUartXbeeTx_net;
	wire [0:0] tmpFB_0__PinUartXbeeTx_net;
	wire [0:0] tmpIO_0__PinUartXbeeTx_net;
	wire [0:0] tmpINTERRUPT_0__PinUartXbeeTx_net;
	electrical [0:0] tmpSIOVREF__PinUartXbeeTx_net;

	cy_psoc3_pins_v1_10
		#(.id("7890b3d4-70c5-4b8d-a859-219fa33c40f5"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		PinUartXbeeTx
		 (.oe(tmpOE__PinUartXbeeTx_net),
		  .y({Net_70}),
		  .fb({tmpFB_0__PinUartXbeeTx_net[0:0]}),
		  .io({tmpIO_0__PinUartXbeeTx_net[0:0]}),
		  .siovref(tmpSIOVREF__PinUartXbeeTx_net),
		  .interrupt({tmpINTERRUPT_0__PinUartXbeeTx_net[0:0]}));

	assign tmpOE__PinUartXbeeTx_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinXbeeSleep_net;
	wire [0:0] tmpFB_0__PinXbeeSleep_net;
	wire [0:0] tmpIO_0__PinXbeeSleep_net;
	wire [0:0] tmpINTERRUPT_0__PinXbeeSleep_net;
	electrical [0:0] tmpSIOVREF__PinXbeeSleep_net;

	cy_psoc3_pins_v1_10
		#(.id("ef1400cf-02a0-41c8-84eb-76570c08ed5d"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		PinXbeeSleep
		 (.oe(tmpOE__PinXbeeSleep_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinXbeeSleep_net[0:0]}),
		  .io({tmpIO_0__PinXbeeSleep_net[0:0]}),
		  .siovref(tmpSIOVREF__PinXbeeSleep_net),
		  .interrupt({tmpINTERRUPT_0__PinXbeeSleep_net[0:0]}));

	assign tmpOE__PinXbeeSleep_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    Timer_v2_20_3 TimerMainTick (
        .reset(Net_117),
        .interrupt(Net_118),
        .enable(1'b1),
        .trigger(1'b0),
        .capture(1'b0),
        .capture_out(Net_122),
        .tc(Net_123),
        .clock(Net_10));
    defparam TimerMainTick.CaptureCount = 2;
    defparam TimerMainTick.CaptureCounterEnabled = 0;
    defparam TimerMainTick.DeviceFamily = "PSoC5";
    defparam TimerMainTick.InterruptOnCapture = 0;
    defparam TimerMainTick.InterruptOnTC = 1;
    defparam TimerMainTick.Resolution = 8;
    defparam TimerMainTick.SiliconRevision = "1";


	cy_clock_v1_0
		#(.id("c0fb34bd-1044-4931-9788-16b01ce89812"),
		  .source_clock_id("315365C3-2E3E-4f04-84A2-BB564A173261"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(1))
		timer_clock
		 (.clock_out(Net_10));


    ZeroTerminal ZeroTerminal_1 (
        .z(Net_117));


	cy_isr_v1_0
		#(.int_type(2'b10))
		IsrMainTick
		 (.int_signal(Net_123));


    UART_v2_10_4 UartDebug (
        .cts_n(1'b0),
        .tx(Net_155),
        .rts_n(Net_156),
        .tx_en(Net_157),
        .clock(1'b0),
        .reset(1'b0),
        .rx(Net_160),
        .tx_interrupt(Net_161),
        .rx_interrupt(Net_162),
        .tx_data(Net_163),
        .tx_clk(Net_164),
        .rx_data(Net_165),
        .rx_clk(Net_166));
    defparam UartDebug.Address1 = 0;
    defparam UartDebug.Address2 = 0;
    defparam UartDebug.EnIntRXInterrupt = 1;
    defparam UartDebug.EnIntTXInterrupt = 1;
    defparam UartDebug.FlowControl = 0;
    defparam UartDebug.HalfDuplexEn = 0;
    defparam UartDebug.HwTXEnSignal = 0;
    defparam UartDebug.NumDataBits = 8;
    defparam UartDebug.NumStopBits = 1;
    defparam UartDebug.ParityType = 0;
    defparam UartDebug.RXEnable = 1;
    defparam UartDebug.TXEnable = 1;

	wire [0:0] tmpOE__PinUartDebugTx_net;
	wire [0:0] tmpFB_0__PinUartDebugTx_net;
	wire [0:0] tmpIO_0__PinUartDebugTx_net;
	wire [0:0] tmpINTERRUPT_0__PinUartDebugTx_net;
	electrical [0:0] tmpSIOVREF__PinUartDebugTx_net;

	cy_psoc3_pins_v1_10
		#(.id("94b502ba-b8d5-4fa5-b635-517f89938abc"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		PinUartDebugTx
		 (.oe(tmpOE__PinUartDebugTx_net),
		  .y({Net_155}),
		  .fb({tmpFB_0__PinUartDebugTx_net[0:0]}),
		  .io({tmpIO_0__PinUartDebugTx_net[0:0]}),
		  .siovref(tmpSIOVREF__PinUartDebugTx_net),
		  .interrupt({tmpINTERRUPT_0__PinUartDebugTx_net[0:0]}));

	assign tmpOE__PinUartDebugTx_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinUartDebugRx_net;
	wire [0:0] tmpIO_0__PinUartDebugRx_net;
	wire [0:0] tmpINTERRUPT_0__PinUartDebugRx_net;
	electrical [0:0] tmpSIOVREF__PinUartDebugRx_net;

	cy_psoc3_pins_v1_10
		#(.id("9d7ae94c-a5c0-4788-aa44-705c08d615a1"),
		  .drive_mode(3'b001),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b00),
		  .width(1))
		PinUartDebugRx
		 (.oe(tmpOE__PinUartDebugRx_net),
		  .y({1'b0}),
		  .fb({Net_160}),
		  .io({tmpIO_0__PinUartDebugRx_net[0:0]}),
		  .siovref(tmpSIOVREF__PinUartDebugRx_net),
		  .interrupt({tmpINTERRUPT_0__PinUartDebugRx_net[0:0]}));

	assign tmpOE__PinUartDebugRx_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    ADC_SAR_v1_71_5 AdcSar (
        .vplus(Net_184),
        .vminus(Net_190),
        .soc(1'b1),
        .eoc(Net_192),
        .aclk(1'b0),
        .vdac_ref(Net_194));

	wire [0:0] tmpOE__PinBattVolt_net;
	wire [0:0] tmpFB_0__PinBattVolt_net;
	wire [0:0] tmpIO_0__PinBattVolt_net;
	wire [0:0] tmpINTERRUPT_0__PinBattVolt_net;
	electrical [0:0] tmpSIOVREF__PinBattVolt_net;

	cy_psoc3_pins_v1_10
		#(.id("497348a5-3fde-474f-9d1c-8e1cdb0fc570"),
		  .drive_mode(3'b000),
		  .ibuf_enabled(1'b0),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("A"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		PinBattVolt
		 (.oe(tmpOE__PinBattVolt_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinBattVolt_net[0:0]}),
		  .analog({Net_184}),
		  .io({tmpIO_0__PinBattVolt_net[0:0]}),
		  .siovref(tmpSIOVREF__PinBattVolt_net),
		  .interrupt({tmpINTERRUPT_0__PinBattVolt_net[0:0]}));

	assign tmpOE__PinBattVolt_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};



endmodule

