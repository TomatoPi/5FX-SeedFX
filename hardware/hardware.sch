EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_01x20 J2
U 1 1 6020F3BC
P 2900 2850
F 0 "J2" H 2980 2842 50  0000 L CNN
F 1 "Conn_01x20" H 2980 2751 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x20_P2.54mm_Vertical" H 2900 2850 50  0001 C CNN
F 3 "~" H 2900 2850 50  0001 C CNN
	1    2900 2850
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x20 J3
U 1 1 60211ADD
P 3500 2950
F 0 "J3" H 3418 1725 50  0000 C CNN
F 1 "Conn_01x20" H 3418 1816 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x20_P2.54mm_Vertical" H 3500 2950 50  0001 C CNN
F 3 "~" H 3500 2950 50  0001 C CNN
	1    3500 2950
	-1   0    0    1   
$EndComp
$Comp
L Amplifier_Operational:OPA2134 U1
U 1 1 60215458
P 5600 1900
F 0 "U1" H 5600 2267 50  0000 C CNN
F 1 "OPA2134" H 5600 2176 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 5600 1900 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/opa134.pdf" H 5600 1900 50  0001 C CNN
	1    5600 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 2000 5250 2000
Wire Wire Line
	5250 2000 5250 2150
Wire Wire Line
	5250 2150 5950 2150
Wire Wire Line
	5950 2150 5950 1900
Wire Wire Line
	5950 1900 5900 1900
$Comp
L Device:R R4
U 1 1 60218DCF
P 5050 1500
F 0 "R4" H 5120 1546 50  0000 L CNN
F 1 "2M" H 5120 1455 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P1.90mm_Vertical" V 4980 1500 50  0001 C CNN
F 3 "~" H 5050 1500 50  0001 C CNN
	1    5050 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 602191AB
P 5050 2100
F 0 "R5" H 5120 2146 50  0000 L CNN
F 1 "2M" H 5120 2055 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P1.90mm_Vertical" V 4980 2100 50  0001 C CNN
F 3 "~" H 5050 2100 50  0001 C CNN
	1    5050 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 60219443
P 6150 1900
F 0 "R9" V 5943 1900 50  0000 C CNN
F 1 "100" V 6034 1900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P1.90mm_Vertical" V 6080 1900 50  0001 C CNN
F 3 "~" H 6150 1900 50  0001 C CNN
	1    6150 1900
	0    1    1    0   
$EndComp
$Comp
L Device:R R13
U 1 1 60219700
P 6800 2150
F 0 "R13" H 6870 2196 50  0000 L CNN
F 1 "2M" H 6870 2105 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P1.90mm_Vertical" V 6730 2150 50  0001 C CNN
F 3 "~" H 6800 2150 50  0001 C CNN
	1    6800 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 60219E10
P 4750 1800
F 0 "C7" V 4498 1800 50  0000 C CNN
F 1 "10u" V 4589 1800 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 4788 1650 50  0001 C CNN
F 3 "~" H 4750 1800 50  0001 C CNN
	1    4750 1800
	0    1    1    0   
$EndComp
$Comp
L Device:C C10
U 1 1 6021A678
P 6550 1900
F 0 "C10" V 6802 1900 50  0000 C CNN
F 1 "10u" V 6711 1900 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 6588 1750 50  0001 C CNN
F 3 "~" H 6550 1900 50  0001 C CNN
	1    6550 1900
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 6021AD39
P 5050 2400
F 0 "#PWR0101" H 5050 2150 50  0001 C CNN
F 1 "GND" H 5055 2227 50  0000 C CNN
F 2 "" H 5050 2400 50  0001 C CNN
F 3 "" H 5050 2400 50  0001 C CNN
	1    5050 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 6021B008
P 6800 2400
F 0 "#PWR0102" H 6800 2150 50  0001 C CNN
F 1 "GND" H 6805 2227 50  0000 C CNN
F 2 "" H 6800 2400 50  0001 C CNN
F 3 "" H 6800 2400 50  0001 C CNN
	1    6800 2400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 6021BB04
P 5050 1250
F 0 "#PWR0103" H 5050 1100 50  0001 C CNN
F 1 "+5V" H 5065 1423 50  0000 C CNN
F 2 "" H 5050 1250 50  0001 C CNN
F 3 "" H 5050 1250 50  0001 C CNN
	1    5050 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 1800 5050 1800
Wire Wire Line
	5050 1650 5050 1800
Connection ~ 5050 1800
Wire Wire Line
	5050 1800 5300 1800
Wire Wire Line
	5050 1800 5050 1950
Wire Wire Line
	5050 2250 5050 2400
Wire Wire Line
	5950 1900 6000 1900
Connection ~ 5950 1900
Wire Wire Line
	6300 1900 6400 1900
Wire Wire Line
	6700 1900 6800 1900
Wire Wire Line
	6800 1900 6800 2000
Wire Wire Line
	6800 2300 6800 2400
Wire Wire Line
	4600 1800 4200 1800
Wire Wire Line
	4200 1800 4200 2050
Wire Wire Line
	4200 2050 3700 2050
Wire Wire Line
	5050 1350 5050 1250
$Comp
L power:GND #PWR0104
U 1 1 6021DC4A
P 3900 1750
F 0 "#PWR0104" H 3900 1500 50  0001 C CNN
F 1 "GND" H 3905 1577 50  0000 C CNN
F 2 "" H 3900 1750 50  0001 C CNN
F 3 "" H 3900 1750 50  0001 C CNN
	1    3900 1750
	-1   0    0    1   
$EndComp
Wire Wire Line
	3900 1750 3900 1950
Wire Wire Line
	3900 1950 3700 1950
$Comp
L Amplifier_Operational:OPA2134 U1
U 2 1 602489B6
P 5900 3150
F 0 "U1" H 5900 3517 50  0000 C CNN
F 1 "OPA2134" H 5900 3426 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 5900 3150 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/opa134.pdf" H 5900 3150 50  0001 C CNN
	2    5900 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 3250 5550 3250
Wire Wire Line
	5550 3250 5550 3400
Wire Wire Line
	5550 3400 6250 3400
Wire Wire Line
	6250 3400 6250 3150
Wire Wire Line
	6250 3150 6200 3150
$Comp
L Device:R R6
U 1 1 602489C1
P 5350 2750
F 0 "R6" H 5420 2796 50  0000 L CNN
F 1 "2M" H 5420 2705 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P1.90mm_Vertical" V 5280 2750 50  0001 C CNN
F 3 "~" H 5350 2750 50  0001 C CNN
	1    5350 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 602489C7
P 5350 3350
F 0 "R7" H 5420 3396 50  0000 L CNN
F 1 "2M" H 5420 3305 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P1.90mm_Vertical" V 5280 3350 50  0001 C CNN
F 3 "~" H 5350 3350 50  0001 C CNN
	1    5350 3350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R12
U 1 1 602489CD
P 6450 3150
F 0 "R12" V 6243 3150 50  0000 C CNN
F 1 "100" V 6334 3150 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P1.90mm_Vertical" V 6380 3150 50  0001 C CNN
F 3 "~" H 6450 3150 50  0001 C CNN
	1    6450 3150
	0    1    1    0   
$EndComp
$Comp
L Device:R R15
U 1 1 602489D3
P 7100 3400
F 0 "R15" H 7170 3446 50  0000 L CNN
F 1 "2M" H 7170 3355 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P1.90mm_Vertical" V 7030 3400 50  0001 C CNN
F 3 "~" H 7100 3400 50  0001 C CNN
	1    7100 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 602489D9
P 5050 3050
F 0 "C8" V 4798 3050 50  0000 C CNN
F 1 "10u" V 4889 3050 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 5088 2900 50  0001 C CNN
F 3 "~" H 5050 3050 50  0001 C CNN
	1    5050 3050
	0    1    1    0   
$EndComp
$Comp
L Device:C C12
U 1 1 602489DF
P 6850 3150
F 0 "C12" V 7102 3150 50  0000 C CNN
F 1 "10u" V 7011 3150 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 6888 3000 50  0001 C CNN
F 3 "~" H 6850 3150 50  0001 C CNN
	1    6850 3150
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 602489E5
P 5350 3650
F 0 "#PWR0105" H 5350 3400 50  0001 C CNN
F 1 "GND" H 5355 3477 50  0000 C CNN
F 2 "" H 5350 3650 50  0001 C CNN
F 3 "" H 5350 3650 50  0001 C CNN
	1    5350 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 602489EB
P 7100 3650
F 0 "#PWR0106" H 7100 3400 50  0001 C CNN
F 1 "GND" H 7105 3477 50  0000 C CNN
F 2 "" H 7100 3650 50  0001 C CNN
F 3 "" H 7100 3650 50  0001 C CNN
	1    7100 3650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0107
U 1 1 602489F1
P 5350 2500
F 0 "#PWR0107" H 5350 2350 50  0001 C CNN
F 1 "+5V" H 5365 2673 50  0000 C CNN
F 2 "" H 5350 2500 50  0001 C CNN
F 3 "" H 5350 2500 50  0001 C CNN
	1    5350 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 3050 5350 3050
Wire Wire Line
	5350 2900 5350 3050
Connection ~ 5350 3050
Wire Wire Line
	5350 3050 5600 3050
Wire Wire Line
	5350 3050 5350 3200
Wire Wire Line
	5350 3500 5350 3650
Wire Wire Line
	6250 3150 6300 3150
Connection ~ 6250 3150
Wire Wire Line
	6600 3150 6700 3150
Wire Wire Line
	7000 3150 7100 3150
Wire Wire Line
	7100 3150 7100 3250
Wire Wire Line
	7100 3550 7100 3650
Wire Wire Line
	5350 2600 5350 2500
Wire Wire Line
	4200 3050 4200 2150
Wire Wire Line
	4200 2150 3700 2150
Wire Wire Line
	4200 3050 4900 3050
$Comp
L Connector:AudioJack2 J6
U 1 1 6024A5C0
P 7350 1900
F 0 "J6" H 7170 1883 50  0000 R CNN
F 1 "AudioJack2" H 7170 1974 50  0000 R CNN
F 2 "Connector_Audio:Jack_6.35mm_Neutrik_NMJ4HFD2_Horizontal" H 7350 1900 50  0001 C CNN
F 3 "~" H 7350 1900 50  0001 C CNN
	1    7350 1900
	-1   0    0    1   
$EndComp
$Comp
L Connector:AudioJack2 J7
U 1 1 6024ACA5
P 7650 3150
F 0 "J7" H 7470 3133 50  0000 R CNN
F 1 "AudioJack2" H 7470 3224 50  0000 R CNN
F 2 "Connector_Audio:Jack_6.35mm_Neutrik_NMJ4HFD2_Horizontal" H 7650 3150 50  0001 C CNN
F 3 "~" H 7650 3150 50  0001 C CNN
	1    7650 3150
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 6024B135
P 7050 2100
F 0 "#PWR0108" H 7050 1850 50  0001 C CNN
F 1 "GND" H 7055 1927 50  0000 C CNN
F 2 "" H 7050 2100 50  0001 C CNN
F 3 "" H 7050 2100 50  0001 C CNN
	1    7050 2100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 6024B580
P 7350 3350
F 0 "#PWR0109" H 7350 3100 50  0001 C CNN
F 1 "GND" H 7355 3177 50  0000 C CNN
F 2 "" H 7350 3350 50  0001 C CNN
F 3 "" H 7350 3350 50  0001 C CNN
	1    7350 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 1900 6800 1900
Connection ~ 6800 1900
Wire Wire Line
	7050 2100 7050 2000
Wire Wire Line
	7050 2000 7150 2000
Wire Wire Line
	7450 3150 7100 3150
Connection ~ 7100 3150
Wire Wire Line
	7350 3350 7350 3250
Wire Wire Line
	7350 3250 7450 3250
$Comp
L Device:CP C1
U 1 1 6024F0E8
P 1400 4800
F 0 "C1" H 1518 4846 50  0000 L CNN
F 1 "10u" H 1518 4755 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 1438 4650 50  0001 C CNN
F 3 "~" H 1400 4800 50  0001 C CNN
	1    1400 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 60250F2A
P 1700 4800
F 0 "C2" H 1815 4846 50  0000 L CNN
F 1 "100n" H 1815 4755 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 1738 4650 50  0001 C CNN
F 3 "~" H 1700 4800 50  0001 C CNN
	1    1700 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 6025135A
P 2100 4800
F 0 "C3" H 2215 4846 50  0000 L CNN
F 1 "100n" H 2215 4755 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 2138 4650 50  0001 C CNN
F 3 "~" H 2100 4800 50  0001 C CNN
	1    2100 4800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Jack-DC J1
U 1 1 60251A4C
P 700 4450
F 0 "J1" H 757 4775 50  0000 C CNN
F 1 "Jack-DC" H 757 4684 50  0000 C CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x02_P1.27mm_Horizontal" H 750 4410 50  0001 C CNN
F 3 "~" H 750 4410 50  0001 C CNN
	1    700  4450
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM317L_TO92 U4
U 1 1 60252CA5
P 2600 4550
F 0 "U4" H 2600 4792 50  0000 C CNN
F 1 "LM317L_TO92" H 2600 4701 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 2600 4775 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/snvs775k/snvs775k.pdf" H 2600 4550 50  0001 C CNN
	1    2600 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 60253366
P 3000 4850
F 0 "R1" H 3070 4896 50  0000 L CNN
F 1 "240" H 3070 4805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P1.90mm_Vertical" V 2930 4850 50  0001 C CNN
F 3 "~" H 3000 4850 50  0001 C CNN
	1    3000 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV1
U 1 1 60255F86
P 2600 5300
F 0 "RV1" H 2530 5346 50  0000 R CNN
F 1 "5k" H 2530 5255 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296W_Vertical" H 2600 5300 50  0001 C CNN
F 3 "~" H 2600 5300 50  0001 C CNN
	1    2600 5300
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C4
U 1 1 602567A8
P 3000 5300
F 0 "C4" H 3118 5346 50  0000 L CNN
F 1 "10u" H 3118 5255 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 3038 5150 50  0001 C CNN
F 3 "~" H 3000 5300 50  0001 C CNN
	1    3000 5300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4001 D2
U 1 1 60257A51
P 3300 4850
F 0 "D2" V 3254 4930 50  0000 L CNN
F 1 "1N4001" V 3345 4930 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 3300 4675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 3300 4850 50  0001 C CNN
	1    3300 4850
	0    1    1    0   
$EndComp
$Comp
L Device:CP C5
U 1 1 6025842C
P 3750 5050
F 0 "C5" H 3868 5096 50  0000 L CNN
F 1 "1u" H 3868 5005 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 3788 4900 50  0001 C CNN
F 3 "~" H 3750 5050 50  0001 C CNN
	1    3750 5050
	1    0    0    -1  
$EndComp
$Comp
L pspice:INDUCTOR L1
U 1 1 60258E40
P 4150 4550
F 0 "L1" H 4150 4765 50  0000 C CNN
F 1 "INDUCTOR" H 4150 4674 50  0000 C CNN
F 2 "Inductor_THT:L_Radial_D6.0mm_P4.00mm" H 4150 4550 50  0001 C CNN
F 3 "~" H 4150 4550 50  0001 C CNN
	1    4150 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C6
U 1 1 60259574
P 4550 5050
F 0 "C6" H 4668 5096 50  0000 L CNN
F 1 "10u" H 4668 5005 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 4588 4900 50  0001 C CNN
F 3 "~" H 4550 5050 50  0001 C CNN
	1    4550 5050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0110
U 1 1 6025A19B
P 4550 4450
F 0 "#PWR0110" H 4550 4300 50  0001 C CNN
F 1 "+5V" H 4565 4623 50  0000 C CNN
F 2 "" H 4550 4450 50  0001 C CNN
F 3 "" H 4550 4450 50  0001 C CNN
	1    4550 4450
	1    0    0    -1  
$EndComp
$Comp
L power:+9V #PWR0111
U 1 1 6025AF62
P 1700 4400
F 0 "#PWR0111" H 1700 4250 50  0001 C CNN
F 1 "+9V" H 1715 4573 50  0000 C CNN
F 2 "" H 1700 4400 50  0001 C CNN
F 3 "" H 1700 4400 50  0001 C CNN
	1    1700 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 6025B6A3
P 1400 5050
F 0 "#PWR0112" H 1400 4800 50  0001 C CNN
F 1 "GND" H 1405 4877 50  0000 C CNN
F 2 "" H 1400 5050 50  0001 C CNN
F 3 "" H 1400 5050 50  0001 C CNN
	1    1400 5050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 6025BDCF
P 1700 5050
F 0 "#PWR0113" H 1700 4800 50  0001 C CNN
F 1 "GND" H 1705 4877 50  0000 C CNN
F 2 "" H 1700 5050 50  0001 C CNN
F 3 "" H 1700 5050 50  0001 C CNN
	1    1700 5050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 6025DE94
P 2100 5050
F 0 "#PWR0114" H 2100 4800 50  0001 C CNN
F 1 "GND" H 2105 4877 50  0000 C CNN
F 2 "" H 2100 5050 50  0001 C CNN
F 3 "" H 2100 5050 50  0001 C CNN
	1    2100 5050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 6025E73B
P 2600 5550
F 0 "#PWR0115" H 2600 5300 50  0001 C CNN
F 1 "GND" H 2605 5377 50  0000 C CNN
F 2 "" H 2600 5550 50  0001 C CNN
F 3 "" H 2600 5550 50  0001 C CNN
	1    2600 5550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 6025EFC0
P 3000 5550
F 0 "#PWR0116" H 3000 5300 50  0001 C CNN
F 1 "GND" H 3005 5377 50  0000 C CNN
F 2 "" H 3000 5550 50  0001 C CNN
F 3 "" H 3000 5550 50  0001 C CNN
	1    3000 5550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 6025F9AA
P 3750 5300
F 0 "#PWR0117" H 3750 5050 50  0001 C CNN
F 1 "GND" H 3755 5127 50  0000 C CNN
F 2 "" H 3750 5300 50  0001 C CNN
F 3 "" H 3750 5300 50  0001 C CNN
	1    3750 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 60260365
P 4550 5300
F 0 "#PWR0118" H 4550 5050 50  0001 C CNN
F 1 "GND" H 4555 5127 50  0000 C CNN
F 2 "" H 4550 5300 50  0001 C CNN
F 3 "" H 4550 5300 50  0001 C CNN
	1    4550 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 60260D74
P 1150 4250
F 0 "#PWR0119" H 1150 4000 50  0001 C CNN
F 1 "GND" H 1155 4077 50  0000 C CNN
F 2 "" H 1150 4250 50  0001 C CNN
F 3 "" H 1150 4250 50  0001 C CNN
	1    1150 4250
	-1   0    0    1   
$EndComp
Wire Wire Line
	1000 4350 1150 4350
Wire Wire Line
	1150 4350 1150 4250
Wire Wire Line
	1400 4550 1400 4650
Wire Wire Line
	1400 4550 1700 4550
Wire Wire Line
	1700 4550 1700 4650
Wire Wire Line
	1700 4550 2100 4550
Wire Wire Line
	2100 4550 2100 4650
Connection ~ 1700 4550
Wire Wire Line
	1700 4400 1700 4550
Wire Wire Line
	2100 4550 2300 4550
Connection ~ 2100 4550
Wire Wire Line
	2100 4950 2100 5050
Wire Wire Line
	1700 5050 1700 4950
Wire Wire Line
	1400 4950 1400 5050
Wire Wire Line
	2600 4850 2600 5050
Wire Wire Line
	2600 5050 3000 5050
Wire Wire Line
	3000 5050 3000 5000
Connection ~ 2600 5050
Wire Wire Line
	2600 5050 2600 5150
Wire Wire Line
	3000 5050 3000 5150
Connection ~ 3000 5050
Wire Wire Line
	3000 5450 3000 5550
Wire Wire Line
	2600 5550 2600 5500
Wire Wire Line
	2600 5500 2800 5500
Wire Wire Line
	2800 5500 2800 5300
Wire Wire Line
	2800 5300 2750 5300
Connection ~ 2600 5500
Wire Wire Line
	2600 5500 2600 5450
Wire Wire Line
	3900 4550 3750 4550
Wire Wire Line
	3000 4550 3000 4700
Connection ~ 3000 4550
Wire Wire Line
	3000 4550 2900 4550
Wire Wire Line
	3300 4700 3300 4550
Connection ~ 3300 4550
Wire Wire Line
	3300 4550 3000 4550
Wire Wire Line
	3300 5000 3300 5050
Wire Wire Line
	3300 5050 3000 5050
Wire Wire Line
	3750 4900 3750 4550
Connection ~ 3750 4550
Wire Wire Line
	3750 4550 3300 4550
Wire Wire Line
	3750 5200 3750 5300
Wire Wire Line
	4550 5300 4550 5200
Wire Wire Line
	4550 4900 4550 4550
Wire Wire Line
	4550 4550 4400 4550
Wire Wire Line
	4550 4450 4550 4550
Connection ~ 4550 4550
$Comp
L Amplifier_Operational:OPA2134 U2
U 1 1 60292AAF
P 5500 4400
F 0 "U2" H 5500 4033 50  0000 C CNN
F 1 "OPA2134" H 5500 4124 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 5500 4400 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/opa134.pdf" H 5500 4400 50  0001 C CNN
	1    5500 4400
	-1   0    0    1   
$EndComp
$Comp
L Device:R R8
U 1 1 6029402C
P 5900 4750
F 0 "R8" H 5970 4796 50  0000 L CNN
F 1 "2M" H 5970 4705 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P1.90mm_Vertical" V 5830 4750 50  0001 C CNN
F 3 "~" H 5900 4750 50  0001 C CNN
	1    5900 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R11
U 1 1 6029481C
P 6400 4250
F 0 "R11" H 6470 4296 50  0000 L CNN
F 1 "2M" H 6470 4205 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P1.90mm_Vertical" V 6330 4250 50  0001 C CNN
F 3 "~" H 6400 4250 50  0001 C CNN
	1    6400 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C9
U 1 1 602955D0
P 6150 4500
F 0 "C9" V 5898 4500 50  0000 C CNN
F 1 "10u" V 5989 4500 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 6188 4350 50  0001 C CNN
F 3 "~" H 6150 4500 50  0001 C CNN
	1    6150 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	5800 4300 5850 4300
Wire Wire Line
	5850 4300 5850 3950
Wire Wire Line
	5850 3950 5100 3950
Wire Wire Line
	5100 3950 5100 4400
Wire Wire Line
	5100 4400 5200 4400
Wire Wire Line
	5100 4400 4950 4400
Wire Wire Line
	4950 4400 4950 3300
Wire Wire Line
	4950 3300 4050 3300
Wire Wire Line
	4050 3300 4050 2250
Wire Wire Line
	4050 2250 3700 2250
Connection ~ 5100 4400
Wire Wire Line
	6000 4500 5900 4500
Wire Wire Line
	5900 4500 5900 4600
Connection ~ 5900 4500
Wire Wire Line
	5900 4500 5800 4500
Wire Wire Line
	6300 4500 6400 4500
Wire Wire Line
	6400 4500 6400 4400
$Comp
L power:+2V5 #PWR0120
U 1 1 602A7BB9
P 5900 5000
F 0 "#PWR0120" H 5900 4850 50  0001 C CNN
F 1 "+2V5" H 5915 5173 50  0000 C CNN
F 2 "" H 5900 5000 50  0001 C CNN
F 3 "" H 5900 5000 50  0001 C CNN
	1    5900 5000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0121
U 1 1 602A84D5
P 6400 4000
F 0 "#PWR0121" H 6400 3750 50  0001 C CNN
F 1 "GND" H 6405 3827 50  0000 C CNN
F 2 "" H 6400 4000 50  0001 C CNN
F 3 "" H 6400 4000 50  0001 C CNN
	1    6400 4000
	-1   0    0    1   
$EndComp
Wire Wire Line
	6400 4000 6400 4100
Wire Wire Line
	5900 4900 5900 5000
$Comp
L Connector:AudioJack2 J4
U 1 1 602AF393
P 6700 4500
F 0 "J4" H 6520 4483 50  0000 R CNN
F 1 "AudioJack2" H 6520 4574 50  0000 R CNN
F 2 "Connector_Audio:Jack_6.35mm_Neutrik_NMJ4HFD2_Horizontal" H 6700 4500 50  0001 C CNN
F 3 "~" H 6700 4500 50  0001 C CNN
	1    6700 4500
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 602B0191
P 6400 4700
F 0 "#PWR0122" H 6400 4450 50  0001 C CNN
F 1 "GND" H 6405 4527 50  0000 C CNN
F 2 "" H 6400 4700 50  0001 C CNN
F 3 "" H 6400 4700 50  0001 C CNN
	1    6400 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 4500 6400 4500
Connection ~ 6400 4500
Wire Wire Line
	6400 4700 6400 4600
Wire Wire Line
	6400 4600 6500 4600
$Comp
L Amplifier_Operational:OPA2134 U3
U 1 1 602C0D9B
P 5050 6400
F 0 "U3" H 5050 6767 50  0000 C CNN
F 1 "OPA2134" H 5050 6676 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 5050 6400 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/opa134.pdf" H 5050 6400 50  0001 C CNN
	1    5050 6400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 602D950C
P 4400 6050
F 0 "R2" H 4470 6096 50  0000 L CNN
F 1 "100k" H 4470 6005 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P1.90mm_Vertical" V 4330 6050 50  0001 C CNN
F 3 "~" H 4400 6050 50  0001 C CNN
	1    4400 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 602D9E6A
P 4400 6550
F 0 "R3" H 4470 6596 50  0000 L CNN
F 1 "100k" H 4470 6505 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P1.90mm_Vertical" V 4330 6550 50  0001 C CNN
F 3 "~" H 4400 6550 50  0001 C CNN
	1    4400 6550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0123
U 1 1 602E365E
P 4400 5800
F 0 "#PWR0123" H 4400 5650 50  0001 C CNN
F 1 "+5V" H 4415 5973 50  0000 C CNN
F 2 "" H 4400 5800 50  0001 C CNN
F 3 "" H 4400 5800 50  0001 C CNN
	1    4400 5800
	1    0    0    -1  
$EndComp
$Comp
L power:+2V5 #PWR0124
U 1 1 602E3E3B
P 5450 6300
F 0 "#PWR0124" H 5450 6150 50  0001 C CNN
F 1 "+2V5" H 5465 6473 50  0000 C CNN
F 2 "" H 5450 6300 50  0001 C CNN
F 3 "" H 5450 6300 50  0001 C CNN
	1    5450 6300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0125
U 1 1 602E49DB
P 4400 6800
F 0 "#PWR0125" H 4400 6550 50  0001 C CNN
F 1 "GND" H 4405 6627 50  0000 C CNN
F 2 "" H 4400 6800 50  0001 C CNN
F 3 "" H 4400 6800 50  0001 C CNN
	1    4400 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 5800 4400 5900
Wire Wire Line
	4400 6200 4400 6300
Wire Wire Line
	4400 6700 4400 6800
Wire Wire Line
	4400 6300 4750 6300
Connection ~ 4400 6300
Wire Wire Line
	4400 6300 4400 6400
Wire Wire Line
	4750 6500 4700 6500
Wire Wire Line
	4700 6500 4700 6650
Wire Wire Line
	4700 6650 5450 6650
Wire Wire Line
	5450 6650 5450 6400
Wire Wire Line
	5450 6400 5350 6400
Connection ~ 5450 6400
Wire Wire Line
	5450 6400 5450 6300
$Comp
L Amplifier_Operational:OPA2134 U2
U 2 1 6030807F
P 5950 5800
F 0 "U2" H 5950 5433 50  0000 C CNN
F 1 "OPA2134" H 5950 5524 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 5950 5800 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/opa134.pdf" H 5950 5800 50  0001 C CNN
	2    5950 5800
	-1   0    0    1   
$EndComp
$Comp
L Device:R R10
U 1 1 60308085
P 6350 6150
F 0 "R10" H 6420 6196 50  0000 L CNN
F 1 "2M" H 6420 6105 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P1.90mm_Vertical" V 6280 6150 50  0001 C CNN
F 3 "~" H 6350 6150 50  0001 C CNN
	1    6350 6150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R14
U 1 1 6030808B
P 6850 5650
F 0 "R14" H 6920 5696 50  0000 L CNN
F 1 "2M" H 6920 5605 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P1.90mm_Vertical" V 6780 5650 50  0001 C CNN
F 3 "~" H 6850 5650 50  0001 C CNN
	1    6850 5650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C11
U 1 1 60308091
P 6600 5900
F 0 "C11" V 6348 5900 50  0000 C CNN
F 1 "10u" V 6439 5900 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 6638 5750 50  0001 C CNN
F 3 "~" H 6600 5900 50  0001 C CNN
	1    6600 5900
	0    1    1    0   
$EndComp
Wire Wire Line
	6250 5700 6300 5700
Wire Wire Line
	6300 5700 6300 5350
Wire Wire Line
	6300 5350 5550 5350
Wire Wire Line
	5550 5350 5550 5800
Wire Wire Line
	5550 5800 5650 5800
Connection ~ 5550 5800
Wire Wire Line
	6450 5900 6350 5900
Wire Wire Line
	6350 5900 6350 6000
Connection ~ 6350 5900
Wire Wire Line
	6350 5900 6250 5900
Wire Wire Line
	6750 5900 6850 5900
Wire Wire Line
	6850 5900 6850 5800
$Comp
L power:+2V5 #PWR0126
U 1 1 603080A4
P 6350 6400
F 0 "#PWR0126" H 6350 6250 50  0001 C CNN
F 1 "+2V5" H 6365 6573 50  0000 C CNN
F 2 "" H 6350 6400 50  0001 C CNN
F 3 "" H 6350 6400 50  0001 C CNN
	1    6350 6400
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0127
U 1 1 603080AA
P 6850 5400
F 0 "#PWR0127" H 6850 5150 50  0001 C CNN
F 1 "GND" H 6855 5227 50  0000 C CNN
F 2 "" H 6850 5400 50  0001 C CNN
F 3 "" H 6850 5400 50  0001 C CNN
	1    6850 5400
	-1   0    0    1   
$EndComp
Wire Wire Line
	6850 5400 6850 5500
Wire Wire Line
	6350 6300 6350 6400
$Comp
L Connector:AudioJack2 J5
U 1 1 603080B2
P 7150 5900
F 0 "J5" H 6970 5883 50  0000 R CNN
F 1 "AudioJack2" H 6970 5974 50  0000 R CNN
F 2 "Connector_Audio:Jack_6.35mm_Neutrik_NMJ4HFD2_Horizontal" H 7150 5900 50  0001 C CNN
F 3 "~" H 7150 5900 50  0001 C CNN
	1    7150 5900
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0128
U 1 1 603080B8
P 6850 6100
F 0 "#PWR0128" H 6850 5850 50  0001 C CNN
F 1 "GND" H 6855 5927 50  0000 C CNN
F 2 "" H 6850 6100 50  0001 C CNN
F 3 "" H 6850 6100 50  0001 C CNN
	1    6850 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 5900 6850 5900
Connection ~ 6850 5900
Wire Wire Line
	6850 6100 6850 6000
Wire Wire Line
	6850 6000 6950 6000
Wire Wire Line
	4850 5800 4850 3400
Wire Wire Line
	4850 3400 3950 3400
Wire Wire Line
	3950 3400 3950 2350
Wire Wire Line
	3950 2350 3700 2350
Wire Wire Line
	4850 5800 5550 5800
$Comp
L power:+9V #PWR0129
U 1 1 60313EB8
P 2450 3650
F 0 "#PWR0129" H 2450 3500 50  0001 C CNN
F 1 "+9V" H 2465 3823 50  0000 C CNN
F 2 "" H 2450 3650 50  0001 C CNN
F 3 "" H 2450 3650 50  0001 C CNN
	1    2450 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0130
U 1 1 603148F4
P 2450 3950
F 0 "#PWR0130" H 2450 3700 50  0001 C CNN
F 1 "GND" H 2455 3777 50  0000 C CNN
F 2 "" H 2450 3950 50  0001 C CNN
F 3 "" H 2450 3950 50  0001 C CNN
	1    2450 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 3950 2450 3850
Wire Wire Line
	2450 3850 2700 3850
Wire Wire Line
	2700 3750 2450 3750
Wire Wire Line
	2450 3750 2450 3650
$Comp
L Amplifier_Operational:OPA2134 U1
U 3 1 60321F10
P 9250 1100
F 0 "U1" H 9208 1146 50  0000 L CNN
F 1 "OPA2134" H 9208 1055 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 9250 1100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/opa134.pdf" H 9250 1100 50  0001 C CNN
	3    9250 1100
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:OPA2134 U2
U 3 1 60325F09
P 9500 2150
F 0 "U2" H 9458 2196 50  0000 L CNN
F 1 "OPA2134" H 9458 2105 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 9500 2150 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/opa134.pdf" H 9500 2150 50  0001 C CNN
	3    9500 2150
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:OPA2134 U3
U 3 1 6032F8DD
P 9250 3250
F 0 "U3" H 9208 3296 50  0000 L CNN
F 1 "OPA2134" H 9208 3205 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 9250 3250 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/opa134.pdf" H 9250 3250 50  0001 C CNN
	3    9250 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C13
U 1 1 6034CB88
P 8850 1100
F 0 "C13" H 8965 1146 50  0000 L CNN
F 1 "100n" H 8965 1055 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 8888 950 50  0001 C CNN
F 3 "~" H 8850 1100 50  0001 C CNN
	1    8850 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C15
U 1 1 6034D6B8
P 9100 2150
F 0 "C15" H 9215 2196 50  0000 L CNN
F 1 "100n" H 9215 2105 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 9138 2000 50  0001 C CNN
F 3 "~" H 9100 2150 50  0001 C CNN
	1    9100 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C14
U 1 1 6034E52C
P 8850 3250
F 0 "C14" H 8965 3296 50  0000 L CNN
F 1 "100n" H 8965 3205 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 8888 3100 50  0001 C CNN
F 3 "~" H 8850 3250 50  0001 C CNN
	1    8850 3250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0131
U 1 1 6034F25E
P 8850 1500
F 0 "#PWR0131" H 8850 1250 50  0001 C CNN
F 1 "GND" H 8855 1327 50  0000 C CNN
F 2 "" H 8850 1500 50  0001 C CNN
F 3 "" H 8850 1500 50  0001 C CNN
	1    8850 1500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0132
U 1 1 6034FED9
P 9100 2550
F 0 "#PWR0132" H 9100 2300 50  0001 C CNN
F 1 "GND" H 9105 2377 50  0000 C CNN
F 2 "" H 9100 2550 50  0001 C CNN
F 3 "" H 9100 2550 50  0001 C CNN
	1    9100 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0133
U 1 1 60350A46
P 8850 3650
F 0 "#PWR0133" H 8850 3400 50  0001 C CNN
F 1 "GND" H 8855 3477 50  0000 C CNN
F 2 "" H 8850 3650 50  0001 C CNN
F 3 "" H 8850 3650 50  0001 C CNN
	1    8850 3650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0134
U 1 1 60351932
P 8850 2850
F 0 "#PWR0134" H 8850 2700 50  0001 C CNN
F 1 "+5V" H 8865 3023 50  0000 C CNN
F 2 "" H 8850 2850 50  0001 C CNN
F 3 "" H 8850 2850 50  0001 C CNN
	1    8850 2850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0135
U 1 1 60352841
P 9100 1750
F 0 "#PWR0135" H 9100 1600 50  0001 C CNN
F 1 "+5V" H 9115 1923 50  0000 C CNN
F 2 "" H 9100 1750 50  0001 C CNN
F 3 "" H 9100 1750 50  0001 C CNN
	1    9100 1750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0136
U 1 1 6035372B
P 8850 700
F 0 "#PWR0136" H 8850 550 50  0001 C CNN
F 1 "+5V" H 8865 873 50  0000 C CNN
F 2 "" H 8850 700 50  0001 C CNN
F 3 "" H 8850 700 50  0001 C CNN
	1    8850 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 950  8850 750 
Wire Wire Line
	8850 1250 8850 1450
Wire Wire Line
	9100 1750 9100 1800
Wire Wire Line
	9100 2300 9100 2500
Wire Wire Line
	8850 2850 8850 2900
Wire Wire Line
	8850 3400 8850 3600
Wire Wire Line
	8850 3600 9150 3600
Wire Wire Line
	9150 3600 9150 3550
Connection ~ 8850 3600
Wire Wire Line
	8850 3600 8850 3650
Wire Wire Line
	9150 2950 9150 2900
Wire Wire Line
	9150 2900 8850 2900
Connection ~ 8850 2900
Wire Wire Line
	8850 2900 8850 3100
Wire Wire Line
	9100 2500 9400 2500
Wire Wire Line
	9400 2500 9400 2450
Connection ~ 9100 2500
Wire Wire Line
	9100 2500 9100 2550
Wire Wire Line
	9400 1850 9400 1800
Wire Wire Line
	9400 1800 9100 1800
Connection ~ 9100 1800
Wire Wire Line
	9100 1800 9100 2000
Wire Wire Line
	9150 1400 9150 1450
Wire Wire Line
	9150 1450 8850 1450
Connection ~ 8850 1450
Wire Wire Line
	8850 1450 8850 1500
Wire Wire Line
	8850 750  9150 750 
Wire Wire Line
	9150 750  9150 800 
Connection ~ 8850 750 
Wire Wire Line
	8850 750  8850 700 
$Comp
L Diode:1N4001 D1
U 1 1 603E431F
P 1200 4550
F 0 "D1" H 1200 4333 50  0000 C CNN
F 1 "1N4001" H 1200 4424 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 1200 4375 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 1200 4550 50  0001 C CNN
	1    1200 4550
	-1   0    0    1   
$EndComp
Wire Wire Line
	1050 4550 1000 4550
Wire Wire Line
	1350 4550 1400 4550
Connection ~ 1400 4550
$EndSCHEMATC
