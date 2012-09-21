// ======================================================================
// Skateboard Remote.v generated from TopDesign.cysch
// 06/09/2012 at 16:48
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

// Comp_v1_70(Hysteresis=0, Pd_Override=0, Polarity=0, Speed=0, Sync=1, CY_COMPONENT_NAME=Comp_v1_70, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=CompCH0, CY_INSTANCE_SHORT_NAME=CompCH0, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=70, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=CapSense_CompCH0, )
module Comp_v1_70_0 (Vplus, CmpOut, Vminus, clock);
    inout   Vplus;
    electrical   Vplus;
    output  CmpOut;
    inout   Vminus;
    electrical   Vminus;
    input   clock;


    wire  Net_2;
    wire  Net_1;

    cy_psoc3_ctcomp_v1_0 ctComp (
        .vplus(Vplus),
        .vminus(Vminus),
        .cmpout(Net_1),
        .clk_udb(clock),
        .clock(clock));

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign CmpOut = Net_1;



endmodule

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

// Component: CapSense_CSD_AMux_v3_10
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_AMux_v3_10"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_AMux_v3_10\CapSense_CSD_AMux_v3_10.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_AMux_v3_10"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_AMux_v3_10\CapSense_CSD_AMux_v3_10.v"
`endif

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

// Component: CapSense_CSD_MeasureCh_v3_10
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_MeasureCh_v3_10"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_MeasureCh_v3_10\CapSense_CSD_MeasureCh_v3_10.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_MeasureCh_v3_10"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_MeasureCh_v3_10\CapSense_CSD_MeasureCh_v3_10.v"
`endif

// Component: CapSense_CSD_ClockGen_v3_10
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_ClockGen_v3_10"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_ClockGen_v3_10\CapSense_CSD_ClockGen_v3_10.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_ClockGen_v3_10"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_ClockGen_v3_10\CapSense_CSD_ClockGen_v3_10.v"
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

// Component: or_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0\or_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0\or_v1_0.v"
`endif

// CapSense_CSD_v3_10(AnalogSwitchDivider=11, ClockSource=0, ConnectInactiveSensors=0, CtlModeReplacementString=AsyncCtrl, CurrentSource=1, EnableTuneHelper=false, EzI2CInstanceName=EZI2C, GuardSensorEnable=false, IdacRange=4, Implementation_CH0=1, Implementation_CH1=1, IntClockFrequency=12, LowBaselineReset=5, MaximumSensors=62, MultipleAnalogSwitchDivider=true, NegativeNoiseThreshold=20, NumberOfChannels=1, PrechargePolarity=3, PrescalerOptions=1, PrsOptions=2, RawDataFilterType=8, RbNumber_CH0=0, RbNumber_CH1=0, RemoveCH1=true, RemoveVrefTerm=false, ScanSpeed=7, SensorAutoReset=false, SensorNumber_CH0=4, SensorNumber_CH1=0, SensorNumberChannel0=4, SensorNumberChannel1=0, ShieldEnable=false, SignalSizeReplacementString=uint8, SnsAlias_CH0=<?xml version='1.0'?><PinAliases Version='1'><pin0>ButtonMotorOnOff__BTN</pin0><pin1>ButtonLightsOnOff__BTN</pin1><pin2>ButtonAlarmOnOff__BTN</pin2><pin3>ButtonLightMode__BTN</pin3></PinAliases>, SnsAlias_CH1=<?xml version="1.0" ?><PinAliases Version="1"><pin0>pin1_ch1</pin0></PinAliases>, TunerProperties=, TuningMethod=0, VrefOptions=0, VrefValue=64, WaterProofingEnabled=false, WidgetResolution=8, WidgetsData=<?xml version="1.0" encoding="utf-16"?> <CyWidgetsList xmlns:version="v1.00">   <ListMainTerminal>     <CyTerminal NameIndex="0" WidgetName="ButtonMotorOnOff__BTN" />     <CyTerminal NameIndex="0" WidgetName="ButtonLightsOnOff__BTN" />     <CyTerminal NameIndex="0" WidgetName="ButtonAlarmOnOff__BTN" />     <CyTerminal NameIndex="0" WidgetName="ButtonLightMode__BTN" />   </ListMainTerminal>   <ListButtons>     <CyButton Name="ButtonMotorOnOff" Type="Button" Channel="First" Count="1" Angle="0" Fliped="false" Fliped2D="false" ScaleFactor="1">       <Location>         <X>2147483647</X>         <Y>2147483647</Y>       </Location>       <Properties>         <Hysteresis>1</Hysteresis>         <Debounce>5</Debounce>         <FingerThreshold>5</FingerThreshold>         <NoiseThreshold>1</NoiseThreshold>         <ScanResolution>_10</ScanResolution>       </Properties>     </CyButton>     <CyButton Name="ButtonLightsOnOff" Type="Button" Channel="First" Count="1" Angle="0" Fliped="false" Fliped2D="false" ScaleFactor="1">       <Location>         <X>2147483647</X>         <Y>2147483647</Y>       </Location>       <Properties>         <Hysteresis>1</Hysteresis>         <Debounce>5</Debounce>         <FingerThreshold>5</FingerThreshold>         <NoiseThreshold>1</NoiseThreshold>         <ScanResolution>_10</ScanResolution>       </Properties>     </CyButton>     <CyButton Name="ButtonAlarmOnOff" Type="Button" Channel="First" Count="1" Angle="0" Fliped="false" Fliped2D="false" ScaleFactor="1">       <Location>         <X>2147483647</X>         <Y>2147483647</Y>       </Location>       <Properties>         <Hysteresis>1</Hysteresis>         <Debounce>5</Debounce>         <FingerThreshold>5</FingerThreshold>         <NoiseThreshold>1</NoiseThreshold>         <ScanResolution>_10</ScanResolution>       </Properties>     </CyButton>     <CyButton Name="ButtonLightMode" Type="Button" Channel="First" Count="1" Angle="0" Fliped="false" Fliped2D="false" ScaleFactor="1">       <Location>         <X>2147483647</X>         <Y>2147483647</Y>       </Location>       <Properties>         <Hysteresis>1</Hysteresis>         <Debounce>5</Debounce>         <FingerThreshold>5</FingerThreshold>         <NoiseThreshold>1</NoiseThreshold>         <ScanResolution>_10</ScanResolution>       </Properties>     </CyButton>   </ListButtons>   <ListMatrixButtons />   <ListTouchPads />   <ListSliders />   <GuardSensor Name="GuardSensor" Type="Button" Channel="First" Count="1" Angle="0" Fliped="false" Fliped2D="false" ScaleFactor="1">     <Location>       <X>2147483647</X>       <Y>2147483647</Y>     </Location>     <Properties>       <Hysteresis>10</Hysteresis>       <Debounce>5</Debounce>       <FingerThreshold>100</FingerThreshold>       <NoiseThreshold>20</NoiseThreshold>       <ScanResolution>_10</ScanResolution>     </Properties>   </GuardSensor>   <GuardSensorTerminal NameIndex="0" WidgetName="GuardSensor__GRD" />   <CyScanSlotsList>     <ListScanSlots>       <CyScanSlot IDACSettings="200" Sensitivity="2" AnalogSwitchDivider="11" WidgetName="ButtonMotorOnOff__BTN">         <ListTerminalsNames>           <string>ButtonMotorOnOff__BTN</string>         </ListTerminalsNames>       </CyScanSlot>       <CyScanSlot IDACSettings="200" Sensitivity="2" AnalogSwitchDivider="11" WidgetName="ButtonLightsOnOff__BTN">         <ListTerminalsNames>           <string>ButtonLightsOnOff__BTN</string>         </ListTerminalsNames>       </CyScanSlot>       <CyScanSlot IDACSettings="200" Sensitivity="2" AnalogSwitchDivider="11" WidgetName="ButtonAlarmOnOff__BTN">         <ListTerminalsNames>           <string>ButtonAlarmOnOff__BTN</string>         </ListTerminalsNames>       </CyScanSlot>       <CyScanSlot IDACSettings="200" Sensitivity="2" AnalogSwitchDivider="11" WidgetName="ButtonLightMode__BTN">         <ListTerminalsNames>           <string>ButtonLightMode__BTN</string>         </ListTerminalsNames>       </CyScanSlot>     </ListScanSlots>     <GuardSensorScanSlot IDACSettings="200" Sensitivity="2" AnalogSwitchDivider="11" WidgetName="GuardSensor__GRD">       <ListTerminalsNames>         <string>GuardSensor__GRD</string>       </ListTerminalsNames>     </GuardSensorScanSlot>   </CyScanSlotsList> </CyWidgetsList>, CY_COMPONENT_NAME=CapSense_CSD_v3_10, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=CapSense, CY_INSTANCE_SHORT_NAME=CapSense, CY_MAJOR_VERSION=3, CY_MINOR_VERSION=10, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=CapSense, )
module CapSense_CSD_v3_10_1 (clock, shield, vref, bclk);
    input   clock;
    output  shield;
    inout   vref;
    electrical   vref;
    output  bclk;


    wire  Cmp_CH1;
    wire  Ioff_CH1;
    wire  DigitalClk;
    wire  PreChargeClk;
    wire  ShieldSignal;
    wire  Ioff_CH0;
    wire  Cmp_CH0;
    wire  Net_404;
    wire  Net_405;
    wire [7:0] Net_406;
    wire  clk;
    wire  mrst;
    wire  Net_407;
    electrical  Net_408;
    wire  Net_409;
    wire  Net_410;
    wire  Net_411;
    wire  Net_412;
    wire [7:0] Net_413;
    wire  Net_414;
    wire  Net_415;
    wire [7:0] Net_416;
    wire  Net_417;
    electrical  Net_418;
    wire  Net_419;
    wire  Net_420;
    wire  Net_421;
    wire  Net_422;
    wire [7:0] Net_423;
    wire  Net_375;
    wire  Net_372;
    wire  Net_374;
    wire  Net_373;
    wire  Net_371;
    wire  Net_396;
    wire  Net_397;
    electrical  Net_424;
    electrical  Net_425;
    electrical  Net_426;
    electrical  Net_427;
    electrical  Net_428;
    electrical  Net_429;
    wire  Net_458;
    wire  Net_460;
    wire  Net_464;
    electrical  Net_2129;
    electrical  Net_2101;
    electrical  Net_1440;
    electrical  Net_2153;
    electrical  Net_2098;
    electrical  Net_2072;
    electrical  Net_2077;
    electrical  Net_2038;
    electrical  Net_2031;
    electrical  Net_1903;
    electrical  Net_2149;
    electrical  Net_2107;
    electrical  Net_1956;
    electrical  Net_2164;
    electrical  Net_1433;
    electrical  Net_1438;
    electrical [3:0] Net_1410;
    electrical  Net_1983;
    electrical  Net_1917;
    electrical  Net_1425;
    electrical  Net_282;
    wire  Net_1644;
    wire  Net_461;
    wire  Net_1603;
    wire  Net_1358;
    wire  Net_1350;

    cy_psoc3_vidac8_v1_0 IdacCH0 (
        .reset(Net_404),
        .idir(Net_405),
        .data(8'b00000000),
        .strobe(Net_407),
        .vout(Net_408),
        .iout(Net_1425),
        .ioff(Ioff_CH0),
        .strobe_udb(Net_409));
    defparam IdacCH0.is_all_if_any = 0;
    defparam IdacCH0.reg_data = 1;

    cy_psoc3_csabuf_v1_0 BufCH0 (
        .vref(Net_2129),
        .vout(Net_2072),
        .vchan(Net_2149));

    ZeroTerminal ZeroTerminal_2 (
        .z(Net_404));

    ZeroTerminal ZeroTerminal_7 (
        .z(Net_407));

    ZeroTerminal ZeroTerminal_9 (
        .z(Net_405));

    ZeroTerminal ZeroTerminal_10 (
        .z(Net_409));

    Comp_v1_70_0 CompCH0 (
        .Vplus(Net_282),
        .CmpOut(Cmp_CH0),
        .Vminus(Net_1983),
        .clock(1'b0));

    cy_analog_noconnect_v1_0 NoConnect_IdacVoutCH0 (
        .noconnect(Net_408));

	wire [0:0] tmpOE__CmodCH0_net;
	wire [0:0] tmpFB_0__CmodCH0_net;
	wire [0:0] tmpIO_0__CmodCH0_net;
	wire [0:0] tmpINTERRUPT_0__CmodCH0_net;
	electrical [0:0] tmpSIOVREF__CmodCH0_net;

	cy_psoc3_pins_v1_10
		#(.id("4aa4deb4-87ae-4bcd-8cea-665e32cafcf8/232398c5-3876-4e07-8f5b-7cd7657055e2"),
		  .drive_mode(3'b000),
		  .ibuf_enabled(1'b0),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("NONCONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases("Cmod_CH0"),
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
		  .spanning(1),
		  .vtrip(2'b10),
		  .width(1))
		CmodCH0
		 (.oe(tmpOE__CmodCH0_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__CmodCH0_net[0:0]}),
		  .analog({Net_1917}),
		  .io({tmpIO_0__CmodCH0_net[0:0]}),
		  .siovref(tmpSIOVREF__CmodCH0_net),
		  .interrupt({tmpINTERRUPT_0__CmodCH0_net[0:0]}));

	assign tmpOE__CmodCH0_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PortCH0_net;

	cy_psoc3_port_v1_0
		#(.width(4),
		  .siorefwidth(2),
		  .id("4aa4deb4-87ae-4bcd-8cea-665e32cafcf8/dd9c1af8-be5a-4b9e-b10c-b2d9f11dc9fc"),
		  .pin_aliases({"ButtonMotorOnOff","__BTN,ButtonLigh","tsOnOff__BTN,But","tonAlarmOnOff__B","TN,ButtonLightMo","de__BTN"}),
		  .access_mode("HW_ONLY"),
		  .layout_mode("NONCONTIGUOUS"),
		  .port_mode("ANALOG"),
		  .intr_mode(8'b00000000),
		  .drive_mode(12'b100100100100),
		  .por_state(0),
		  .enable_shielding(4'b0000),
		  .cs_mode(2'b11))
		PortCH0
		 (.oe(tmpOE__PortCH0_net),
		  .y(4'b0),
		  .analog(Net_1410[3:0]),
		  .precharge(PreChargeClk));

	assign tmpOE__PortCH0_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? 1'b1 : 1'b0;


	cy_vref_v1_0
		#(.autoenable(1),
		  .guid("89B398AD-36A8-4627-9212-707F2986319E"),
		  .ignoresleep(0),
		  .name("1.024V"))
		VrefRefCH0
		 (.vout(Net_2038));


    // -- AMux AMuxCH0 start -- ***
    // -- Mux A --
    
    cy_psoc3_amux_v1_0 AMuxCH0(
        .muxin({
            Net_1425,
            Net_282,
            Net_1917,
            Net_1410[3],
            Net_1410[2],
            Net_1410[1],
            Net_1410[0]
            }),
        .vout(Net_2072)
        );
    
    defparam AMuxCH0.muxin_width = 7;
    defparam AMuxCH0.init_mux_sel = 7'h0;
    defparam AMuxCH0.one_active = 0;
    
    // -- AMux AMuxCH0 end --

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_414));

    ZeroTerminal ZeroTerminal_3 (
        .z(Net_417));

    ZeroTerminal ZeroTerminal_4 (
        .z(Net_415));

    ZeroTerminal ZeroTerminal_8 (
        .z(Net_419));

    cy_analog_noconnect_v1_0 NoConnect_IdacVoutCH1 (
        .noconnect(Net_418));

	// Select_VrefCH0 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 Select_VrefCH0_connect(Net_1983, Net_2038);
	defparam Select_VrefCH0_connect.sig_width = 1;

    ZeroTerminal ZeroTerminal_5 (
        .z(Net_375));

    CapSense_CSD_MeasureCh_v3_10 MeasureCH0 (
        .cmp_in(Cmp_CH0),
        .pulse(DigitalClk),
        .clock(clk),
        .ioff(Ioff_CH0),
        .interrupt(Net_1603),
        .reset(mrst),
        .start(Net_1350),
        .enable(Net_373));
    defparam MeasureCH0.IdacOptions = 1;
    defparam MeasureCH0.ImplementationType = 1;

    CapSense_CSD_ClockGen_v3_10 ClockGen (
        .clock(clk),
        .dpulse(DigitalClk),
        .ppulse(PreChargeClk),
        .start0(Net_1350),
        .mesrst(mrst),
        .start1(Net_1358),
        .enable(Net_371),
        .reset(Net_375),
        .shield(ShieldSignal));
    defparam ClockGen.IdacOptions = 1;
    defparam ClockGen.PrescalerOptions = 1;
    defparam ClockGen.PrsOptions = 2;

    OneTerminal OneTerminal_3 (
        .o(Net_374));

    OneTerminal OneTerminal_2 (
        .o(Net_373));


	cy_isr_v1_0
		#(.int_type(2'b00))
		IsrCH0
		 (.int_signal(Net_1603));


    OneTerminal OneTerminal_1 (
        .o(Net_371));


	cy_clock_v1_0
		#(.id("4aa4deb4-87ae-4bcd-8cea-665e32cafcf8/0ad1a1a8-974e-43a0-841b-3af08590011d"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("83333333.3333333"),
		  .is_direct(0),
		  .is_digital(1))
		IntClock
		 (.clock_out(Net_1644));


	// ClockSelect_VirtualMux (cy_virtualmux_v1_0)
	assign clk = Net_1644;

    cy_analog_noconnect_v1_0 NoConnect_VchanCH0 (
        .noconnect(Net_424));

	// Connect_VdacToAmuxCH0 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 Connect_VdacToAmuxCH0_connect(Net_1903, Net_425);
	defparam Connect_VdacToAmuxCH0_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 NoConnect_1_024ToAMuxCH0 (
        .noconnect(Net_425));

	// Select_VrefOutput (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 Select_VrefOutput_connect(vref, Net_2038);
	defparam Select_VrefOutput_connect.sig_width = 1;

	// Select_VrefCH1 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 Select_VrefCH1_connect(Net_2164, Net_2038);
	defparam Select_VrefCH1_connect.sig_width = 1;

	// Connect_VdacToAmuxCH1 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 Connect_VdacToAmuxCH1_connect(Net_2107, Net_426);
	defparam Connect_VdacToAmuxCH1_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 NoConnect_1_024ToAMuxCH1 (
        .noconnect(Net_426));

	// DisableCapSBuf_VrefCH0 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 DisableCapSBuf_VrefCH0_connect(Net_2129, Net_1983);
	defparam DisableCapSBuf_VrefCH0_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 NoConnect_VrefCH0 (
        .noconnect(Net_427));

	// DisableCapSBuf_VchanCH1 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 DisableCapSBuf_VchanCH1_connect(Net_2153, Net_1956);
	defparam DisableCapSBuf_VchanCH1_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 NoConnect_VchanCH1 (
        .noconnect(Net_428));

	// DisableCapSBuf_VrefCH1 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 DisableCapSBuf_VrefCH1_connect(Net_2098, Net_2164);
	defparam DisableCapSBuf_VrefCH1_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 NoConnect_VrefCH1 (
        .noconnect(Net_429));

	// DisableCapSBuf_VchanCH0 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 DisableCapSBuf_VchanCH0_connect(Net_2149, Net_1917);
	defparam DisableCapSBuf_VchanCH0_connect.sig_width = 1;

    ZeroTerminal ZeroTerminal_6 (
        .z(Net_458));


    assign bclk = Net_460 | Net_458;


	cy_clock_v1_0
		#(.id("4aa4deb4-87ae-4bcd-8cea-665e32cafcf8/52b807b3-40a8-4a39-b1e7-e18f76c3b871"),
		  .source_clock_id("75C2148C-3656-4d8a-846D-0CAE99AB6FF7"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(1))
		Clock_tmp
		 (.clock_out(Net_460));



    assign shield = ShieldSignal;


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
module UART_v2_10_2 (rx_clk, rx_data, tx_clk, tx_data, rx_interrupt, tx_interrupt, tx, tx_en, rts_n, reset, cts_n, clock, rx);
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

// ADC_SAR_v1_71(ADC_Clock=1, ADC_Clock_Frequency=1900000, ADC_Input_Range=1, ADC_Power=0, ADC_Reference=0, ADC_Resolution=12, ADC_Resolution_HW=12, ADC_SampleMode=0, Ref_Voltage=2.5, Ref_Voltage_mV=2500, Sample_Precharge=7, Sample_Rate=100000, Sample_Rate_def=631579, CY_COMPONENT_NAME=ADC_SAR_v1_71, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=AdcSar, CY_INSTANCE_SHORT_NAME=AdcSar, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=71, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=AdcSar, )
module ADC_SAR_v1_71_3 (vplus, vminus, soc, eoc, aclk, vdac_ref);
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
		#(.id("c14db27a-08b8-4c5e-a9ba-9843df3a2c40/696a0979-21fc-4185-bf38-6c79febcde7a"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("526315789.473684"),
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

// Component: AMux_v1_50
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\AMux_v1_50"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\AMux_v1_50\AMux_v1_50.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\AMux_v1_50"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\AMux_v1_50\AMux_v1_50.v"
`endif

// UART_v2_10(Address1=0, Address2=0, BaudRate=57600, BreakBitsRX=13, BreakBitsTX=13, BreakDetect=false, CRCoutputsEn=false, CtrlModeReplacementString=AsyncCtl, Enable_RX=0, Enable_RXIntInterrupt=1, Enable_TX=1, Enable_TXIntInterrupt=1, EnableHWAddress=0, EnIntRXInterrupt=true, EnIntTXInterrupt=true, FlowControl=0, HalfDuplexEn=false, HwTXEnSignal=false, InternalClock=true, InternalClockUsed=1, InterruptOnAddDetect=0, InterruptOnAddressMatch=0, InterruptOnBreak=0, InterruptOnByteRcvd=0, InterruptOnOverrunError=0, InterruptOnParityError=0, InterruptOnStopError=0, InterruptOnTXComplete=false, InterruptOnTXFifoEmpty=true, InterruptOnTXFifoFull=false, InterruptOnTXFifoNotFull=false, IntOnAddressDetect=false, IntOnAddressMatch=false, IntOnBreak=false, IntOnByteRcvd=false, IntOnOverrunError=false, IntOnParityError=false, IntOnStopError=false, NumDataBits=8, NumStopBits=1, OverSamplingRate=8, ParityType=0, ParityTypeSw=false, RequiredClock=460800, RXAddressMode=0, RXBufferSize=50, RxBuffRegSizeReplacementString=uint8, RXEnable=false, TXBitClkGenDP=true, TXBufferSize=50, TxBuffRegSizeReplacementString=uint8, TXEnable=true, Use23Polling=true, CY_COMPONENT_NAME=UART_v2_10, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=UartDebug, CY_INSTANCE_SHORT_NAME=UartDebug, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=10, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=UartDebug, )
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
    parameter RXEnable = 0;
    parameter TXEnable = 1;

    wire  Net_289;
    wire  Net_9;
    wire  Net_61;


	cy_isr_v1_0
		#(.int_type(2'b10))
		TXInternalInterrupt
		 (.int_signal(tx_interrupt));



	cy_clock_v1_0
		#(.id("5285b6eb-aedb-49ed-a037-8e22a46b7b50/be0a0e37-ad17-42ca-b5a1-1a654d736358"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("2170138888.88889"),
		  .is_direct(0),
		  .is_digital(1))
		IntClock
		 (.clock_out(Net_9));


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
    defparam BUART.RXEnable = 0;
    defparam BUART.RXStatusIntEnable = 0;
    defparam BUART.TXBitClkGenDP = 1;
    defparam BUART.TXEnable = 1;
    defparam BUART.Use23Polling = 1;



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
module Timer_v2_20_5 (clock, reset, interrupt, enable, capture, trigger, capture_out, tc);
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

// top
module top ;

    wire  Net_229;
    wire  Net_245;
    wire  Net_244;
    wire  Net_243;
    wire  Net_242;
    wire  Net_241;
    wire  Net_230;
    wire  Net_138;
    wire  Net_137;
    wire  Net_136;
    wire  Net_135;
    wire  Net_134;
    wire  Net_133;
    wire  Net_113;
    wire  Net_132;
    wire  Net_131;
    wire  Net_130;
    wire  Net_129;
    wire  Net_114;
    wire  Net_128;
    electrical  Net_86;
    electrical  Net_85;
    electrical  Net_159;
    wire  Net_158;
    wire  Net_157;
    wire  Net_156;
    electrical  Net_155;
    electrical  Net_76;
    wire  Net_149;
    wire  Net_148;
    wire  Net_147;
    wire  Net_146;
    wire  Net_145;
    wire  Net_144;
    wire  Net_21;
    wire  Net_143;
    wire  Net_142;
    wire  Net_141;
    wire  Net_140;
    wire  Net_16;
    wire  Net_139;
    wire  Net_14;
    electrical  Net_13;
    wire  Net_12;
    wire  Net_11;
    wire  Net_10;
    wire  Net_220;

	wire [0:0] tmpOE__PinLedAlarm_net;
	wire [0:0] tmpFB_0__PinLedAlarm_net;
	wire [0:0] tmpIO_0__PinLedAlarm_net;
	wire [0:0] tmpINTERRUPT_0__PinLedAlarm_net;
	electrical [0:0] tmpSIOVREF__PinLedAlarm_net;

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
		PinLedAlarm
		 (.oe(tmpOE__PinLedAlarm_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinLedAlarm_net[0:0]}),
		  .io({tmpIO_0__PinLedAlarm_net[0:0]}),
		  .siovref(tmpSIOVREF__PinLedAlarm_net),
		  .interrupt({tmpINTERRUPT_0__PinLedAlarm_net[0:0]}));

	assign tmpOE__PinLedAlarm_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinLedMotorOn_net;
	wire [0:0] tmpFB_0__PinLedMotorOn_net;
	wire [0:0] tmpIO_0__PinLedMotorOn_net;
	wire [0:0] tmpINTERRUPT_0__PinLedMotorOn_net;
	electrical [0:0] tmpSIOVREF__PinLedMotorOn_net;

	cy_psoc3_pins_v1_10
		#(.id("a7a3245c-7018-459d-853d-e09d3c1f689d"),
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
		PinLedMotorOn
		 (.oe(tmpOE__PinLedMotorOn_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinLedMotorOn_net[0:0]}),
		  .io({tmpIO_0__PinLedMotorOn_net[0:0]}),
		  .siovref(tmpSIOVREF__PinLedMotorOn_net),
		  .interrupt({tmpINTERRUPT_0__PinLedMotorOn_net[0:0]}));

	assign tmpOE__PinLedMotorOn_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinLedInRange_net;
	wire [0:0] tmpFB_0__PinLedInRange_net;
	wire [0:0] tmpIO_0__PinLedInRange_net;
	wire [0:0] tmpINTERRUPT_0__PinLedInRange_net;
	electrical [0:0] tmpSIOVREF__PinLedInRange_net;

	cy_psoc3_pins_v1_10
		#(.id("48d29ccb-c9a1-43e7-b603-360d40b125b9"),
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
		PinLedInRange
		 (.oe(tmpOE__PinLedInRange_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinLedInRange_net[0:0]}),
		  .io({tmpIO_0__PinLedInRange_net[0:0]}),
		  .siovref(tmpSIOVREF__PinLedInRange_net),
		  .interrupt({tmpINTERRUPT_0__PinLedInRange_net[0:0]}));

	assign tmpOE__PinLedInRange_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinLedRemoteBattLevelHigh_net;
	wire [0:0] tmpFB_0__PinLedRemoteBattLevelHigh_net;
	wire [0:0] tmpIO_0__PinLedRemoteBattLevelHigh_net;
	wire [0:0] tmpINTERRUPT_0__PinLedRemoteBattLevelHigh_net;
	electrical [0:0] tmpSIOVREF__PinLedRemoteBattLevelHigh_net;

	cy_psoc3_pins_v1_10
		#(.id("df217deb-5c7b-4fac-a5ff-c14604051f57"),
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
		PinLedRemoteBattLevelHigh
		 (.oe(tmpOE__PinLedRemoteBattLevelHigh_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinLedRemoteBattLevelHigh_net[0:0]}),
		  .io({tmpIO_0__PinLedRemoteBattLevelHigh_net[0:0]}),
		  .siovref(tmpSIOVREF__PinLedRemoteBattLevelHigh_net),
		  .interrupt({tmpINTERRUPT_0__PinLedRemoteBattLevelHigh_net[0:0]}));

	assign tmpOE__PinLedRemoteBattLevelHigh_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinLedRemoteBattLevelMed_net;
	wire [0:0] tmpFB_0__PinLedRemoteBattLevelMed_net;
	wire [0:0] tmpIO_0__PinLedRemoteBattLevelMed_net;
	wire [0:0] tmpINTERRUPT_0__PinLedRemoteBattLevelMed_net;
	electrical [0:0] tmpSIOVREF__PinLedRemoteBattLevelMed_net;

	cy_psoc3_pins_v1_10
		#(.id("5028f894-b8ad-4c4c-89ba-011b1b55b5f5"),
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
		PinLedRemoteBattLevelMed
		 (.oe(tmpOE__PinLedRemoteBattLevelMed_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinLedRemoteBattLevelMed_net[0:0]}),
		  .io({tmpIO_0__PinLedRemoteBattLevelMed_net[0:0]}),
		  .siovref(tmpSIOVREF__PinLedRemoteBattLevelMed_net),
		  .interrupt({tmpINTERRUPT_0__PinLedRemoteBattLevelMed_net[0:0]}));

	assign tmpOE__PinLedRemoteBattLevelMed_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinLedRemoteBattLevelLow_net;
	wire [0:0] tmpFB_0__PinLedRemoteBattLevelLow_net;
	wire [0:0] tmpIO_0__PinLedRemoteBattLevelLow_net;
	wire [0:0] tmpINTERRUPT_0__PinLedRemoteBattLevelLow_net;
	electrical [0:0] tmpSIOVREF__PinLedRemoteBattLevelLow_net;

	cy_psoc3_pins_v1_10
		#(.id("f08fc079-8ed1-412c-a26f-17c6a42d6a87"),
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
		PinLedRemoteBattLevelLow
		 (.oe(tmpOE__PinLedRemoteBattLevelLow_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinLedRemoteBattLevelLow_net[0:0]}),
		  .io({tmpIO_0__PinLedRemoteBattLevelLow_net[0:0]}),
		  .siovref(tmpSIOVREF__PinLedRemoteBattLevelLow_net),
		  .interrupt({tmpINTERRUPT_0__PinLedRemoteBattLevelLow_net[0:0]}));

	assign tmpOE__PinLedRemoteBattLevelLow_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinLedBoardBattLevelHigh_net;
	wire [0:0] tmpFB_0__PinLedBoardBattLevelHigh_net;
	wire [0:0] tmpIO_0__PinLedBoardBattLevelHigh_net;
	wire [0:0] tmpINTERRUPT_0__PinLedBoardBattLevelHigh_net;
	electrical [0:0] tmpSIOVREF__PinLedBoardBattLevelHigh_net;

	cy_psoc3_pins_v1_10
		#(.id("5c6ce117-1800-4e8d-95cb-87c75c123902"),
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
		PinLedBoardBattLevelHigh
		 (.oe(tmpOE__PinLedBoardBattLevelHigh_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinLedBoardBattLevelHigh_net[0:0]}),
		  .io({tmpIO_0__PinLedBoardBattLevelHigh_net[0:0]}),
		  .siovref(tmpSIOVREF__PinLedBoardBattLevelHigh_net),
		  .interrupt({tmpINTERRUPT_0__PinLedBoardBattLevelHigh_net[0:0]}));

	assign tmpOE__PinLedBoardBattLevelHigh_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinLedBoardBattLevelMed_net;
	wire [0:0] tmpFB_0__PinLedBoardBattLevelMed_net;
	wire [0:0] tmpIO_0__PinLedBoardBattLevelMed_net;
	wire [0:0] tmpINTERRUPT_0__PinLedBoardBattLevelMed_net;
	electrical [0:0] tmpSIOVREF__PinLedBoardBattLevelMed_net;

	cy_psoc3_pins_v1_10
		#(.id("d9a095e5-ec06-4806-ad4e-873125497aac"),
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
		PinLedBoardBattLevelMed
		 (.oe(tmpOE__PinLedBoardBattLevelMed_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinLedBoardBattLevelMed_net[0:0]}),
		  .io({tmpIO_0__PinLedBoardBattLevelMed_net[0:0]}),
		  .siovref(tmpSIOVREF__PinLedBoardBattLevelMed_net),
		  .interrupt({tmpINTERRUPT_0__PinLedBoardBattLevelMed_net[0:0]}));

	assign tmpOE__PinLedBoardBattLevelMed_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinLedBoardBattLevelLow_net;
	wire [0:0] tmpFB_0__PinLedBoardBattLevelLow_net;
	wire [0:0] tmpIO_0__PinLedBoardBattLevelLow_net;
	wire [0:0] tmpINTERRUPT_0__PinLedBoardBattLevelLow_net;
	electrical [0:0] tmpSIOVREF__PinLedBoardBattLevelLow_net;

	cy_psoc3_pins_v1_10
		#(.id("886b88bb-6ae6-4dde-bc51-9708b14ab37d"),
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
		PinLedBoardBattLevelLow
		 (.oe(tmpOE__PinLedBoardBattLevelLow_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinLedBoardBattLevelLow_net[0:0]}),
		  .io({tmpIO_0__PinLedBoardBattLevelLow_net[0:0]}),
		  .siovref(tmpSIOVREF__PinLedBoardBattLevelLow_net),
		  .interrupt({tmpINTERRUPT_0__PinLedBoardBattLevelLow_net[0:0]}));

	assign tmpOE__PinLedBoardBattLevelLow_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    CapSense_CSD_v3_10_1 CapSense (
        .clock(1'b0),
        .shield(Net_12),
        .vref(Net_13),
        .bclk(Net_14));

    UART_v2_10_2 UartXbee (
        .cts_n(1'b0),
        .tx(Net_16),
        .rts_n(Net_140),
        .tx_en(Net_141),
        .clock(1'b0),
        .reset(1'b0),
        .rx(Net_21),
        .tx_interrupt(Net_144),
        .rx_interrupt(Net_145),
        .tx_data(Net_146),
        .tx_clk(Net_147),
        .rx_data(Net_148),
        .rx_clk(Net_149));
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

	wire [0:0] tmpOE__PinUartXbeeRx_net;
	wire [0:0] tmpIO_0__PinUartXbeeRx_net;
	wire [0:0] tmpINTERRUPT_0__PinUartXbeeRx_net;
	electrical [0:0] tmpSIOVREF__PinUartXbeeRx_net;

	cy_psoc3_pins_v1_10
		#(.id("1425177d-0d0e-4468-8bcc-e638e5509a9b"),
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
		  .fb({Net_21}),
		  .io({tmpIO_0__PinUartXbeeRx_net[0:0]}),
		  .siovref(tmpSIOVREF__PinUartXbeeRx_net),
		  .interrupt({tmpINTERRUPT_0__PinUartXbeeRx_net[0:0]}));

	assign tmpOE__PinUartXbeeRx_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinUartXbeeTx_net;
	wire [0:0] tmpFB_0__PinUartXbeeTx_net;
	wire [0:0] tmpIO_0__PinUartXbeeTx_net;
	wire [0:0] tmpINTERRUPT_0__PinUartXbeeTx_net;
	electrical [0:0] tmpSIOVREF__PinUartXbeeTx_net;

	cy_psoc3_pins_v1_10
		#(.id("46f24aff-545f-461a-b0b3-794e7ddf425b"),
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
		  .y({Net_16}),
		  .fb({tmpFB_0__PinUartXbeeTx_net[0:0]}),
		  .io({tmpIO_0__PinUartXbeeTx_net[0:0]}),
		  .siovref(tmpSIOVREF__PinUartXbeeTx_net),
		  .interrupt({tmpINTERRUPT_0__PinUartXbeeTx_net[0:0]}));

	assign tmpOE__PinUartXbeeTx_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinXbeeIsSleep_net;
	wire [0:0] tmpFB_0__PinXbeeIsSleep_net;
	wire [0:0] tmpIO_0__PinXbeeIsSleep_net;
	wire [0:0] tmpINTERRUPT_0__PinXbeeIsSleep_net;
	electrical [0:0] tmpSIOVREF__PinXbeeIsSleep_net;

	cy_psoc3_pins_v1_10
		#(.id("43732a27-2728-466d-8bc0-34ee2becdb07"),
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
		PinXbeeIsSleep
		 (.oe(tmpOE__PinXbeeIsSleep_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinXbeeIsSleep_net[0:0]}),
		  .io({tmpIO_0__PinXbeeIsSleep_net[0:0]}),
		  .siovref(tmpSIOVREF__PinXbeeIsSleep_net),
		  .interrupt({tmpINTERRUPT_0__PinXbeeIsSleep_net[0:0]}));

	assign tmpOE__PinXbeeIsSleep_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    ADC_SAR_v1_71_3 AdcSar (
        .vplus(Net_76),
        .vminus(Net_155),
        .soc(1'b1),
        .eoc(Net_157),
        .aclk(1'b0),
        .vdac_ref(Net_159));

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
		  .analog({Net_85}),
		  .io({tmpIO_0__PinBattVolt_net[0:0]}),
		  .siovref(tmpSIOVREF__PinBattVolt_net),
		  .interrupt({tmpINTERRUPT_0__PinBattVolt_net[0:0]}));

	assign tmpOE__PinBattVolt_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    // -- AMux AMuxAdc start -- ***
    // -- Mux A --
    
    cy_psoc3_amux_v1_0 AMuxAdc(
        .muxin({
            Net_86,
            Net_85
            }),
        .vout(Net_76)
        );
    
    defparam AMuxAdc.muxin_width = 2;
    defparam AMuxAdc.init_mux_sel = 2'h0;
    defparam AMuxAdc.one_active = 0;
    
    // -- AMux AMuxAdc end --

	wire [0:0] tmpOE__PinThrottleVolt_net;
	wire [0:0] tmpFB_0__PinThrottleVolt_net;
	wire [0:0] tmpIO_0__PinThrottleVolt_net;
	wire [0:0] tmpINTERRUPT_0__PinThrottleVolt_net;
	electrical [0:0] tmpSIOVREF__PinThrottleVolt_net;

	cy_psoc3_pins_v1_10
		#(.id("0c1a724a-af5a-437d-a08d-d300a1e3c993"),
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
		PinThrottleVolt
		 (.oe(tmpOE__PinThrottleVolt_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinThrottleVolt_net[0:0]}),
		  .analog({Net_86}),
		  .io({tmpIO_0__PinThrottleVolt_net[0:0]}),
		  .siovref(tmpSIOVREF__PinThrottleVolt_net),
		  .interrupt({tmpINTERRUPT_0__PinThrottleVolt_net[0:0]}));

	assign tmpOE__PinThrottleVolt_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    UART_v2_10_4 UartDebug (
        .cts_n(1'b0),
        .tx(Net_114),
        .rts_n(Net_129),
        .tx_en(Net_130),
        .clock(1'b0),
        .reset(1'b0),
        .rx(1'b0),
        .tx_interrupt(Net_133),
        .rx_interrupt(Net_134),
        .tx_data(Net_135),
        .tx_clk(Net_136),
        .rx_data(Net_137),
        .rx_clk(Net_138));
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
    defparam UartDebug.RXEnable = 0;
    defparam UartDebug.TXEnable = 1;

	wire [0:0] tmpOE__PinDebug_net;
	wire [0:0] tmpFB_0__PinDebug_net;
	wire [0:0] tmpIO_0__PinDebug_net;
	wire [0:0] tmpINTERRUPT_0__PinDebug_net;
	electrical [0:0] tmpSIOVREF__PinDebug_net;

	cy_psoc3_pins_v1_10
		#(.id("c497fbeb-8d03-4adc-9f4c-7c26fa317668"),
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
		PinDebug
		 (.oe(tmpOE__PinDebug_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__PinDebug_net[0:0]}),
		  .io({tmpIO_0__PinDebug_net[0:0]}),
		  .siovref(tmpSIOVREF__PinDebug_net),
		  .interrupt({tmpINTERRUPT_0__PinDebug_net[0:0]}));

	assign tmpOE__PinDebug_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__PinUartDebugTx_net;
	wire [0:0] tmpFB_0__PinUartDebugTx_net;
	wire [0:0] tmpIO_0__PinUartDebugTx_net;
	wire [0:0] tmpINTERRUPT_0__PinUartDebugTx_net;
	electrical [0:0] tmpSIOVREF__PinUartDebugTx_net;

	cy_psoc3_pins_v1_10
		#(.id("356bab90-5c8e-415b-83d9-bd1d196e6cec"),
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
		  .y({Net_114}),
		  .fb({tmpFB_0__PinUartDebugTx_net[0:0]}),
		  .io({tmpIO_0__PinUartDebugTx_net[0:0]}),
		  .siovref(tmpSIOVREF__PinUartDebugTx_net),
		  .interrupt({tmpINTERRUPT_0__PinUartDebugTx_net[0:0]}));

	assign tmpOE__PinUartDebugTx_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_220));

    Timer_v2_20_5 TimerMainTick (
        .reset(Net_220),
        .interrupt(Net_230),
        .enable(1'b1),
        .trigger(1'b0),
        .capture(1'b0),
        .capture_out(Net_244),
        .tc(Net_245),
        .clock(Net_10));
    defparam TimerMainTick.CaptureCount = 2;
    defparam TimerMainTick.CaptureCounterEnabled = 0;
    defparam TimerMainTick.DeviceFamily = "PSoC5";
    defparam TimerMainTick.InterruptOnCapture = 0;
    defparam TimerMainTick.InterruptOnTC = 1;
    defparam TimerMainTick.Resolution = 8;
    defparam TimerMainTick.SiliconRevision = "1";


	cy_isr_v1_0
		#(.int_type(2'b10))
		IsrMainTick
		 (.int_signal(Net_245));



	cy_clock_v1_0
		#(.id("c0fb34bd-1044-4931-9788-16b01ce89812"),
		  .source_clock_id("315365C3-2E3E-4f04-84A2-BB564A173261"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(1))
		timer_clock
		 (.clock_out(Net_10));


	wire [0:0] tmpOE__PinXbeeSleep_net;
	wire [0:0] tmpFB_0__PinXbeeSleep_net;
	wire [0:0] tmpIO_0__PinXbeeSleep_net;
	wire [0:0] tmpINTERRUPT_0__PinXbeeSleep_net;
	electrical [0:0] tmpSIOVREF__PinXbeeSleep_net;

	cy_psoc3_pins_v1_10
		#(.id("539e19e1-c4d7-4d69-8e3f-80f819fda337"),
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



endmodule

