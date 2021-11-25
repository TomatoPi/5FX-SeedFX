EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
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
L Amplifier_Operational:LM324 U1
U 1 1 615FC22F
P 1750 1700
F 0 "U1" H 1750 1333 50  0000 C CNN
F 1 "LM324" H 1750 1424 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 1700 1800 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 1800 1900 50  0001 C CNN
	1    1750 1700
	1    0    0    1   
$EndComp
$Comp
L Device:R_POT_Small RV2
U 1 1 6160245E
P 1250 950
F 0 "RV2" V 1053 950 50  0000 C CNN
F 1 "20k" V 1144 950 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 1250 950 50  0001 C CNN
F 3 "~" H 1250 950 50  0001 C CNN
	1    1250 950 
	0    1    1    0   
$EndComp
$Comp
L Device:R_POT_Small RV1
U 1 1 61602C68
P 1500 2400
F 0 "RV1" H 1441 2446 50  0000 R CNN
F 1 "100k" H 1441 2355 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 1500 2400 50  0001 C CNN
F 3 "~" H 1500 2400 50  0001 C CNN
	1    1500 2400
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 616036B0
P 2450 1700
F 0 "R1" V 2243 1700 50  0000 C CNN
F 1 "8k2" V 2334 1700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 2380 1700 50  0001 C CNN
F 3 "~" H 2450 1700 50  0001 C CNN
	1    2450 1700
	0    1    1    0   
$EndComp
$Comp
L Amplifier_Operational:LM324 U1
U 4 1 616041F5
P 3100 1800
F 0 "U1" H 3100 1433 50  0000 C CNN
F 1 "LM324" H 3100 1524 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 3050 1900 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 3150 2000 50  0001 C CNN
	4    3100 1800
	1    0    0    1   
$EndComp
$Comp
L power:+12V #PWR01
U 1 1 61608015
P 3550 2100
F 0 "#PWR01" H 3550 1950 50  0001 C CNN
F 1 "+12V" H 3565 2273 50  0000 C CNN
F 2 "" H 3550 2100 50  0001 C CNN
F 3 "" H 3550 2100 50  0001 C CNN
	1    3550 2100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 61608584
P 3550 2900
F 0 "#PWR02" H 3550 2650 50  0001 C CNN
F 1 "GND" H 3555 2727 50  0000 C CNN
F 2 "" H 3550 2900 50  0001 C CNN
F 3 "" H 3550 2900 50  0001 C CNN
	1    3550 2900
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM324 U1
U 5 1 61608958
P 3650 2500
F 0 "U1" H 3608 2546 50  0000 L CNN
F 1 "LM324" H 3608 2455 50  0000 L CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 3600 2600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 3700 2700 50  0001 C CNN
	5    3650 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 2800 3550 2900
Wire Wire Line
	1250 1600 1450 1600
Wire Wire Line
	1350 950  2200 950 
Wire Wire Line
	2200 1700 2050 1700
Wire Wire Line
	2200 1700 2300 1700
Connection ~ 2200 1700
Wire Wire Line
	1450 1800 1250 1800
$Comp
L power:GND #PWR04
U 1 1 6160D064
P 1500 2800
F 0 "#PWR04" H 1500 2550 50  0001 C CNN
F 1 "GND" H 1505 2627 50  0000 C CNN
F 2 "" H 1500 2800 50  0001 C CNN
F 3 "" H 1500 2800 50  0001 C CNN
	1    1500 2800
	-1   0    0    -1  
$EndComp
$Comp
L power:+12V #PWR03
U 1 1 6160D3AE
P 1500 2150
F 0 "#PWR03" H 1500 2000 50  0001 C CNN
F 1 "+12V" H 1515 2323 50  0000 C CNN
F 2 "" H 1500 2150 50  0001 C CNN
F 3 "" H 1500 2150 50  0001 C CNN
	1    1500 2150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1250 1050 1250 1150
Wire Wire Line
	2200 950  2200 1150
Wire Wire Line
	2800 1700 2700 1700
$Comp
L power:GND #PWR06
U 1 1 61614BB8
P 2350 2800
F 0 "#PWR06" H 2350 2550 50  0001 C CNN
F 1 "GND" H 2355 2627 50  0000 C CNN
F 2 "" H 2350 2800 50  0001 C CNN
F 3 "" H 2350 2800 50  0001 C CNN
	1    2350 2800
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR05
U 1 1 61614BBE
P 2350 2150
F 0 "#PWR05" H 2350 2000 50  0001 C CNN
F 1 "+12V" H 2365 2323 50  0000 C CNN
F 2 "" H 2350 2150 50  0001 C CNN
F 3 "" H 2350 2150 50  0001 C CNN
	1    2350 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 1900 2800 1900
$Comp
L Device:R R2
U 1 1 61617923
P 3100 1200
F 0 "R2" V 2893 1200 50  0000 C CNN
F 1 "8k2" V 2984 1200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 3030 1200 50  0001 C CNN
F 3 "~" H 3100 1200 50  0001 C CNN
	1    3100 1200
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 61617D8D
P 3700 1800
F 0 "R4" V 3493 1800 50  0000 C CNN
F 1 "100" V 3584 1800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 3630 1800 50  0001 C CNN
F 3 "~" H 3700 1800 50  0001 C CNN
	1    3700 1800
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 61618087
P 3700 1350
F 0 "R3" V 3493 1350 50  0000 C CNN
F 1 "100" V 3584 1350 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 3630 1350 50  0001 C CNN
F 3 "~" H 3700 1350 50  0001 C CNN
	1    3700 1350
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 616185DC
P 3100 800
F 0 "C2" V 2848 800 50  0000 C CNN
F 1 "220p" V 2939 800 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P3.80mm" H 3138 650 50  0001 C CNN
F 3 "~" H 3100 800 50  0001 C CNN
	1    3100 800 
	0    1    1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 61618FF5
P 1750 1150
F 0 "C1" V 1498 1150 50  0000 C CNN
F 1 "22n" V 1589 1150 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W4.4mm_P5.00mm" H 1788 1000 50  0001 C CNN
F 3 "~" H 1750 1150 50  0001 C CNN
	1    1750 1150
	0    1    1    0   
$EndComp
Wire Wire Line
	1900 1150 2200 1150
Connection ~ 2200 1150
Wire Wire Line
	2200 1150 2200 1350
Wire Wire Line
	1600 1150 1250 1150
Connection ~ 1250 1150
Wire Wire Line
	1250 1150 1250 1600
Wire Wire Line
	3550 1800 3450 1800
Wire Wire Line
	3450 1800 3450 1200
Wire Wire Line
	3450 1200 3250 1200
Connection ~ 3450 1800
Wire Wire Line
	3450 1800 3400 1800
Wire Wire Line
	3450 1200 3450 800 
Wire Wire Line
	3450 800  3250 800 
Connection ~ 3450 1200
Wire Wire Line
	2950 800  2700 800 
Wire Wire Line
	2700 800  2700 1200
Connection ~ 2700 1700
Wire Wire Line
	2700 1700 2600 1700
Wire Wire Line
	2700 1200 2950 1200
Connection ~ 2700 1200
Wire Wire Line
	2700 1200 2700 1700
Wire Wire Line
	3550 1350 2200 1350
Connection ~ 2200 1350
Wire Wire Line
	2200 1350 2200 1700
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 6162EFAA
P 4250 1550
F 0 "J1" H 4330 1542 50  0000 L CNN
F 1 "Conn_01x02" H 4330 1451 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4250 1550 50  0001 C CNN
F 3 "~" H 4250 1550 50  0001 C CNN
	1    4250 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 1550 3900 1350
Wire Wire Line
	3900 1800 3900 1650
Text Label 3950 1550 0    50   ~ 0
X+
Text Label 3950 1650 0    50   ~ 0
X-
$Comp
L Device:R_POT_Small RV5
U 1 1 61682777
P 1250 4050
F 0 "RV5" V 1053 4050 50  0000 C CNN
F 1 "20k" V 1144 4050 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 1250 4050 50  0001 C CNN
F 3 "~" H 1250 4050 50  0001 C CNN
	1    1250 4050
	0    1    -1   0   
$EndComp
$Comp
L Device:R R5
U 1 1 61682783
P 2450 3300
F 0 "R5" V 2243 3300 50  0000 C CNN
F 1 "8k2" V 2334 3300 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 2380 3300 50  0001 C CNN
F 3 "~" H 2450 3300 50  0001 C CNN
	1    2450 3300
	0    1    -1   0   
$EndComp
$Comp
L Amplifier_Operational:LM324 U1
U 3 1 61682789
P 3100 3200
F 0 "U1" H 3100 3567 50  0000 C CNN
F 1 "LM324" H 3100 3476 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 3050 3300 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 3150 3400 50  0001 C CNN
	3    3100 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 3400 1450 3400
Wire Wire Line
	2200 3300 2050 3300
Wire Wire Line
	2200 3300 2300 3300
Connection ~ 2200 3300
Wire Wire Line
	1250 3950 1250 3850
Wire Wire Line
	2200 4050 2200 3850
Wire Wire Line
	2800 3300 2700 3300
Wire Wire Line
	2650 3100 2800 3100
$Comp
L Device:R R6
U 1 1 616827BE
P 3100 3800
F 0 "R6" V 2893 3800 50  0000 C CNN
F 1 "8k2" V 2984 3800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 3030 3800 50  0001 C CNN
F 3 "~" H 3100 3800 50  0001 C CNN
	1    3100 3800
	0    1    -1   0   
$EndComp
$Comp
L Device:R R7
U 1 1 616827C4
P 3700 3200
F 0 "R7" V 3493 3200 50  0000 C CNN
F 1 "100" V 3584 3200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 3630 3200 50  0001 C CNN
F 3 "~" H 3700 3200 50  0001 C CNN
	1    3700 3200
	0    1    -1   0   
$EndComp
$Comp
L Device:R R8
U 1 1 616827CA
P 3700 3650
F 0 "R8" V 3493 3650 50  0000 C CNN
F 1 "100" V 3584 3650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 3630 3650 50  0001 C CNN
F 3 "~" H 3700 3650 50  0001 C CNN
	1    3700 3650
	0    1    -1   0   
$EndComp
$Comp
L Device:C C4
U 1 1 616827D0
P 3100 4200
F 0 "C4" V 2848 4200 50  0000 C CNN
F 1 "220p" V 2939 4200 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P3.80mm" H 3138 4050 50  0001 C CNN
F 3 "~" H 3100 4200 50  0001 C CNN
	1    3100 4200
	0    1    -1   0   
$EndComp
$Comp
L Device:C C3
U 1 1 616827D6
P 1750 3850
F 0 "C3" V 1498 3850 50  0000 C CNN
F 1 "22n" V 1589 3850 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W4.4mm_P5.00mm" H 1788 3700 50  0001 C CNN
F 3 "~" H 1750 3850 50  0001 C CNN
	1    1750 3850
	0    1    -1   0   
$EndComp
Wire Wire Line
	1900 3850 2200 3850
Connection ~ 2200 3850
Wire Wire Line
	2200 3850 2200 3650
Wire Wire Line
	1600 3850 1250 3850
Connection ~ 1250 3850
Wire Wire Line
	1250 3850 1250 3400
Wire Wire Line
	3550 3200 3450 3200
Wire Wire Line
	3450 3200 3450 3800
Wire Wire Line
	3450 3800 3250 3800
Connection ~ 3450 3200
Wire Wire Line
	3450 3200 3400 3200
Wire Wire Line
	3450 3800 3450 4200
Wire Wire Line
	3450 4200 3250 4200
Connection ~ 3450 3800
Wire Wire Line
	2950 4200 2700 4200
Wire Wire Line
	2700 4200 2700 3800
Connection ~ 2700 3300
Wire Wire Line
	2700 3300 2600 3300
Wire Wire Line
	2700 3800 2950 3800
Connection ~ 2700 3800
Wire Wire Line
	2700 3800 2700 3300
Wire Wire Line
	3550 3650 2200 3650
Connection ~ 2200 3650
Wire Wire Line
	2200 3650 2200 3300
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 616827F4
P 4250 3450
F 0 "J2" H 4330 3442 50  0000 L CNN
F 1 "Conn_01x02" H 4330 3351 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4250 3450 50  0001 C CNN
F 3 "~" H 4250 3450 50  0001 C CNN
	1    4250 3450
	1    0    0    1   
$EndComp
Wire Wire Line
	3900 3450 3900 3650
Wire Wire Line
	3900 3200 3900 3350
Text Label 3950 3450 0    50   ~ 0
Y+
Text Label 3950 3350 0    50   ~ 0
Y-
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 61686ED1
P 650 950
F 0 "J3" H 568 1167 50  0000 C CNN
F 1 "Conn_01x02" H 568 1076 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 650 950 50  0001 C CNN
F 3 "~" H 650 950 50  0001 C CNN
	1    650  950 
	-1   0    0    -1  
$EndComp
Text Label 850  950  0    50   ~ 0
DAC0
Text Label 850  1050 0    50   ~ 0
DAC1
Text Notes 600  5550 0    50   ~ 0
Analog level Adapter :\nDAC range : 0.55V - 2.75V => 2.2V Cac\nOutput range : 10V differenciel : 1V - 11V\n\nCalcul du gain requis : 10Vcàc / 2.2Vcàc = 4.54\n\nCalcul du bias :\n  Par rapport à Vbias : Vin * Gain = Vout\n  Par rapport à GND :  (Vin - bias) * Gain = Vout - bias\n  Soit :  Bias = (Vout - Vin * gain) / (1 - gain) = 0.419V\n\nLes condensateurs srvent à créer un filtre passe bas évitant l'auto-oscillation de l'AOP\nFs1 = 2kHz, Fs2  = 8.8kHz\n\nLes lasers doivent avoir probablement une frequence de contrôle max de l'ordre de 100Hz
$Comp
L Amplifier_Operational:LM324 U1
U 2 1 61682771
P 1750 3300
F 0 "U1" H 1750 3667 50  0000 C CNN
F 1 "LM324" H 1750 3576 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 1700 3400 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 1800 3500 50  0001 C CNN
	2    1750 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 3200 1450 3200
Wire Wire Line
	1500 2150 1500 2300
Wire Wire Line
	1500 2500 1500 2800
Wire Wire Line
	3550 2100 3550 2200
$Comp
L Device:R_POT_Small RV3
U 1 1 616BDC4F
P 2350 2400
F 0 "RV3" H 2291 2446 50  0000 R CNN
F 1 "100k" H 2291 2355 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 2350 2400 50  0001 C CNN
F 3 "~" H 2350 2400 50  0001 C CNN
	1    2350 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 2150 2350 2300
Wire Wire Line
	2350 2500 2350 2800
$Comp
L Isolator:PC817 U3
U 1 1 616CBE2F
P 6700 1700
F 0 "U3" H 6700 2025 50  0000 C CNN
F 1 "PC817" H 6700 1934 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 6500 1500 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 6700 1700 50  0001 L CNN
	1    6700 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 616CC5E2
P 6200 1600
F 0 "R9" V 5993 1600 50  0000 C CNN
F 1 "100" V 6084 1600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 6130 1600 50  0001 C CNN
F 3 "~" H 6200 1600 50  0001 C CNN
	1    6200 1600
	0    1    1    0   
$EndComp
$Comp
L Device:R R11
U 1 1 616CCB6C
P 7100 1400
F 0 "R11" H 7170 1446 50  0000 L CNN
F 1 "4k7" H 7170 1355 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7030 1400 50  0001 C CNN
F 3 "~" H 7100 1400 50  0001 C CNN
	1    7100 1400
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM317_TO-220 U2
U 1 1 616CD977
P 1550 5900
F 0 "U2" H 1550 6142 50  0000 C CNN
F 1 "LM317_TO-220" H 1550 6051 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 1550 6150 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm317.pdf" H 1550 5900 50  0001 C CNN
	1    1550 5900
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM317_TO-220 U4
U 1 1 616CEAA5
P 3250 5900
F 0 "U4" H 3250 6142 50  0000 C CNN
F 1 "LM317_TO-220" H 3250 6051 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 3250 6150 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm317.pdf" H 3250 5900 50  0001 C CNN
	1    3250 5900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 616CF1FE
P 1950 6150
F 0 "R10" H 2020 6196 50  0000 L CNN
F 1 "2k2" H 2020 6105 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 1880 6150 50  0001 C CNN
F 3 "~" H 1950 6150 50  0001 C CNN
	1    1950 6150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R14
U 1 1 616CFB06
P 3650 6150
F 0 "R14" H 3720 6196 50  0000 L CNN
F 1 "2k2" H 3720 6105 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 3580 6150 50  0001 C CNN
F 3 "~" H 3650 6150 50  0001 C CNN
	1    3650 6150
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_Small RV6
U 1 1 616D0516
P 3650 6500
F 0 "RV6" H 3590 6546 50  0000 R CNN
F 1 "20k" H 3590 6455 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 3650 6500 50  0001 C CNN
F 3 "~" H 3650 6500 50  0001 C CNN
	1    3650 6500
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_POT_Small RV4
U 1 1 616D0B88
P 1950 6500
F 0 "RV4" H 1890 6546 50  0000 R CNN
F 1 "20k" H 1890 6455 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 1950 6500 50  0001 C CNN
F 3 "~" H 1950 6500 50  0001 C CNN
	1    1950 6500
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 616D7CA9
P 1950 6750
F 0 "#PWR09" H 1950 6500 50  0001 C CNN
F 1 "GND" H 1955 6577 50  0000 C CNN
F 2 "" H 1950 6750 50  0001 C CNN
F 3 "" H 1950 6750 50  0001 C CNN
	1    1950 6750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 616D8238
P 3650 6800
F 0 "#PWR011" H 3650 6550 50  0001 C CNN
F 1 "GND" H 3655 6627 50  0000 C CNN
F 2 "" H 3650 6800 50  0001 C CNN
F 3 "" H 3650 6800 50  0001 C CNN
	1    3650 6800
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR07
U 1 1 616D89EA
P 1000 5900
F 0 "#PWR07" H 1000 5750 50  0001 C CNN
F 1 "+12V" V 1015 6028 50  0000 L CNN
F 2 "" H 1000 5900 50  0001 C CNN
F 3 "" H 1000 5900 50  0001 C CNN
	1    1000 5900
	0    -1   -1   0   
$EndComp
$Comp
L power:+12V #PWR010
U 1 1 616D96D6
P 2800 5900
F 0 "#PWR010" H 2800 5750 50  0001 C CNN
F 1 "+12V" V 2815 6028 50  0000 L CNN
F 2 "" H 2800 5900 50  0001 C CNN
F 3 "" H 2800 5900 50  0001 C CNN
	1    2800 5900
	0    -1   -1   0   
$EndComp
Text GLabel 2050 5900 2    50   Input ~ 0
+8.5V
Text GLabel 3750 5900 2    50   Input ~ 0
+6V
Wire Wire Line
	3650 6800 3650 6600
Wire Wire Line
	3650 6400 3650 6350
Wire Wire Line
	3650 6000 3650 5900
Wire Wire Line
	3650 5900 3550 5900
Wire Wire Line
	3650 5900 3750 5900
Connection ~ 3650 5900
Wire Wire Line
	2950 5900 2800 5900
Wire Wire Line
	3250 6200 3250 6350
Wire Wire Line
	3250 6350 3450 6350
Connection ~ 3650 6350
Wire Wire Line
	3650 6350 3650 6300
Wire Wire Line
	3550 6500 3450 6500
Wire Wire Line
	3450 6500 3450 6350
Connection ~ 3450 6350
Wire Wire Line
	3450 6350 3650 6350
Wire Wire Line
	1950 6750 1950 6600
Wire Wire Line
	1950 6400 1950 6350
Wire Wire Line
	1950 6350 1750 6350
Wire Wire Line
	1550 6350 1550 6200
Connection ~ 1950 6350
Wire Wire Line
	1950 6350 1950 6300
Wire Wire Line
	1850 6500 1750 6500
Wire Wire Line
	1750 6500 1750 6350
Connection ~ 1750 6350
Wire Wire Line
	1750 6350 1550 6350
Wire Wire Line
	1950 6000 1950 5900
Wire Wire Line
	1950 5900 1850 5900
Wire Wire Line
	1950 5900 2050 5900
Connection ~ 1950 5900
Wire Wire Line
	1250 5900 1000 5900
Text Notes 650  7600 0    50   ~ 0
Régulateurs :\nutilisé pour convertir le PWM\nen signal analogique symétrique\n\nLe +8.5V sert pour le niveau haut de la ligne positive\nLe 6V correspond au point central des deux lignes\nLa ligne négative est générée par un inverseur de gain 1
$Comp
L Device:R R12
U 1 1 61703DE2
P 7350 1800
F 0 "R12" V 7143 1800 50  0000 C CNN
F 1 "8k2" V 7234 1800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7280 1800 50  0001 C CNN
F 3 "~" H 7350 1800 50  0001 C CNN
	1    7350 1800
	0    1    1    0   
$EndComp
$Comp
L Device:C C5
U 1 1 617045EB
P 7600 2050
F 0 "C5" H 7715 2096 50  0000 L CNN
F 1 "33n" H 7715 2005 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W4.4mm_P5.00mm" H 7638 1900 50  0001 C CNN
F 3 "~" H 7600 2050 50  0001 C CNN
	1    7600 2050
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM324 U5
U 1 1 61704ECD
P 8500 1900
F 0 "U5" H 8500 1533 50  0000 C CNN
F 1 "LM324" H 8500 1624 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 8450 2000 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 8550 2100 50  0001 C CNN
	1    8500 1900
	1    0    0    1   
$EndComp
$Comp
L Amplifier_Operational:LM324 U5
U 4 1 617066D3
P 9750 2000
F 0 "U5" H 9750 1633 50  0000 C CNN
F 1 "LM324" H 9750 1724 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 9700 2100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 9800 2200 50  0001 C CNN
	4    9750 2000
	1    0    0    1   
$EndComp
$Comp
L Device:R R17
U 1 1 6170768E
P 9150 1900
F 0 "R17" V 8943 1900 50  0000 C CNN
F 1 "8k2" V 9034 1900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 9080 1900 50  0001 C CNN
F 3 "~" H 9150 1900 50  0001 C CNN
	1    9150 1900
	0    1    1    0   
$EndComp
$Comp
L Device:R R13
U 1 1 61708CA3
P 7850 1800
F 0 "R13" V 7643 1800 50  0000 C CNN
F 1 "8k2" V 7734 1800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7780 1800 50  0001 C CNN
F 3 "~" H 7850 1800 50  0001 C CNN
	1    7850 1800
	0    1    1    0   
$EndComp
$Comp
L Device:R R15
U 1 1 61709821
P 7600 1450
F 0 "R15" V 7393 1450 50  0000 C CNN
F 1 "8k2" V 7484 1450 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7530 1450 50  0001 C CNN
F 3 "~" H 7600 1450 50  0001 C CNN
	1    7600 1450
	-1   0    0    1   
$EndComp
$Comp
L Device:C C6
U 1 1 6170A0BC
P 8100 1450
F 0 "C6" V 7848 1450 50  0000 C CNN
F 1 "33n" V 7939 1450 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W4.4mm_P5.00mm" H 8138 1300 50  0001 C CNN
F 3 "~" H 8100 1450 50  0001 C CNN
	1    8100 1450
	-1   0    0    1   
$EndComp
$Comp
L Device:R R18
U 1 1 6170A877
P 9750 1500
F 0 "R18" V 9543 1500 50  0000 C CNN
F 1 "8k2" V 9634 1500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 9680 1500 50  0001 C CNN
F 3 "~" H 9750 1500 50  0001 C CNN
	1    9750 1500
	0    1    1    0   
$EndComp
$Comp
L Device:C C8
U 1 1 6170B0C6
P 9750 1150
F 0 "C8" V 10002 1150 50  0000 C CNN
F 1 "470p" V 9911 1150 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P3.80mm" H 9788 1000 50  0001 C CNN
F 3 "~" H 9750 1150 50  0001 C CNN
	1    9750 1150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R20
U 1 1 6170BA63
P 10400 2000
F 0 "R20" V 10193 2000 50  0000 C CNN
F 1 "100" V 10284 2000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 10330 2000 50  0001 C CNN
F 3 "~" H 10400 2000 50  0001 C CNN
	1    10400 2000
	0    1    1    0   
$EndComp
$Comp
L Device:R R19
U 1 1 6170C5CF
P 10400 850
F 0 "R19" V 10193 850 50  0000 C CNN
F 1 "100" V 10284 850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 10330 850 50  0001 C CNN
F 3 "~" H 10400 850 50  0001 C CNN
	1    10400 850 
	0    1    1    0   
$EndComp
Text GLabel 7000 2250 0    50   Input ~ 0
+6V
Wire Wire Line
	9150 2100 9450 2100
Wire Wire Line
	7700 1800 7600 1800
Wire Wire Line
	7200 1800 7100 1800
Text GLabel 7000 1250 0    50   Input ~ 0
+8.5V
Wire Wire Line
	7100 1250 7000 1250
Wire Wire Line
	7600 1900 7600 1800
Connection ~ 7600 1800
Wire Wire Line
	7600 1800 7500 1800
Wire Wire Line
	9450 1900 9400 1900
Wire Wire Line
	9400 1900 9400 1500
Wire Wire Line
	9400 1500 9600 1500
Connection ~ 9400 1900
Wire Wire Line
	9400 1900 9300 1900
Wire Wire Line
	9400 1500 9400 1150
Wire Wire Line
	9400 1150 9600 1150
Connection ~ 9400 1500
Wire Wire Line
	9900 1150 10150 1150
Wire Wire Line
	10150 1150 10150 1500
Wire Wire Line
	10150 2000 10050 2000
Wire Wire Line
	10150 2000 10250 2000
Connection ~ 10150 2000
Wire Wire Line
	10150 1500 9900 1500
Connection ~ 10150 1500
Wire Wire Line
	10150 1500 10150 2000
Wire Wire Line
	7950 2000 8200 2000
Wire Wire Line
	8000 1800 8100 1800
Wire Wire Line
	8100 1800 8100 1600
Connection ~ 8100 1800
Wire Wire Line
	8100 1800 8200 1800
Wire Wire Line
	7600 1600 7600 1800
Wire Wire Line
	7600 1300 7600 1200
Wire Wire Line
	7600 1200 8100 1200
Wire Wire Line
	8850 1200 8850 1900
Wire Wire Line
	8850 1900 8800 1900
Wire Wire Line
	8100 1300 8100 1200
Connection ~ 8100 1200
Wire Wire Line
	8100 1200 8850 1200
Connection ~ 8850 1900
Wire Wire Line
	10250 850  8950 850 
$Comp
L Connector_Generic:Conn_01x02 J8
U 1 1 61691AF9
P 10550 1350
F 0 "J8" H 10630 1342 50  0000 L CNN
F 1 "Conn_01x02" H 10630 1251 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 10550 1350 50  0001 C CNN
F 3 "~" H 10550 1350 50  0001 C CNN
	1    10550 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	10650 1650 10650 2000
Wire Wire Line
	10650 2000 10550 2000
Wire Wire Line
	10250 1650 10250 1450
Wire Wire Line
	10250 1450 10350 1450
Wire Wire Line
	10250 1650 10650 1650
Wire Wire Line
	10350 1350 10250 1350
Wire Wire Line
	10250 1350 10250 1150
Wire Wire Line
	10250 1150 10650 1150
Wire Wire Line
	10650 1150 10650 850 
Wire Wire Line
	10650 850  10550 850 
Text Label 10650 1050 0    50   ~ 0
Sig_0+
Text Label 10650 1900 0    50   ~ 0
Sig_0-
Text Label 5800 1600 0    50   ~ 0
PWM_0
Wire Wire Line
	6400 1600 6350 1600
$Comp
L Isolator:PC817 U6
U 1 1 616F9D5A
P 6700 3300
F 0 "U6" H 6700 3625 50  0000 C CNN
F 1 "PC817" H 6700 3534 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 6500 3100 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 6700 3300 50  0001 L CNN
	1    6700 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R16
U 1 1 616F9D60
P 6200 3200
F 0 "R16" V 5993 3200 50  0000 C CNN
F 1 "100" V 6084 3200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 6130 3200 50  0001 C CNN
F 3 "~" H 6200 3200 50  0001 C CNN
	1    6200 3200
	0    1    1    0   
$EndComp
$Comp
L Device:R R23
U 1 1 616F9D66
P 7100 3650
F 0 "R23" H 7170 3696 50  0000 L CNN
F 1 "4k7" H 7170 3605 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7030 3650 50  0001 C CNN
F 3 "~" H 7100 3650 50  0001 C CNN
	1    7100 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R26
U 1 1 616F9D6C
P 7350 3400
F 0 "R26" V 7143 3400 50  0000 C CNN
F 1 "8k2" V 7234 3400 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7280 3400 50  0001 C CNN
F 3 "~" H 7350 3400 50  0001 C CNN
	1    7350 3400
	0    1    1    0   
$EndComp
$Comp
L Device:C C7
U 1 1 616F9D72
P 7600 3650
F 0 "C7" H 7715 3696 50  0000 L CNN
F 1 "33n" H 7715 3605 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W4.4mm_P5.00mm" H 7638 3500 50  0001 C CNN
F 3 "~" H 7600 3650 50  0001 C CNN
	1    7600 3650
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM324 U5
U 2 1 616F9D78
P 8500 3500
F 0 "U5" H 8500 3133 50  0000 C CNN
F 1 "LM324" H 8500 3224 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 8450 3600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 8550 3700 50  0001 C CNN
	2    8500 3500
	1    0    0    1   
$EndComp
$Comp
L Amplifier_Operational:LM324 U5
U 3 1 616F9D7E
P 9750 3600
F 0 "U5" H 9750 3233 50  0000 C CNN
F 1 "LM324" H 9750 3324 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 9700 3700 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 9800 3800 50  0001 C CNN
	3    9750 3600
	1    0    0    1   
$EndComp
$Comp
L Device:R R35
U 1 1 616F9D84
P 9150 3500
F 0 "R35" V 8943 3500 50  0000 C CNN
F 1 "8k2" V 9034 3500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 9080 3500 50  0001 C CNN
F 3 "~" H 9150 3500 50  0001 C CNN
	1    9150 3500
	0    1    1    0   
$EndComp
$Comp
L Device:R R32
U 1 1 616F9D8A
P 7850 3400
F 0 "R32" V 7643 3400 50  0000 C CNN
F 1 "8k2" V 7734 3400 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7780 3400 50  0001 C CNN
F 3 "~" H 7850 3400 50  0001 C CNN
	1    7850 3400
	0    1    1    0   
$EndComp
$Comp
L Device:R R29
U 1 1 616F9D90
P 7600 3050
F 0 "R29" V 7393 3050 50  0000 C CNN
F 1 "8k2" V 7484 3050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7530 3050 50  0001 C CNN
F 3 "~" H 7600 3050 50  0001 C CNN
	1    7600 3050
	-1   0    0    1   
$EndComp
$Comp
L Device:C C11
U 1 1 616F9D96
P 8100 3050
F 0 "C11" V 7848 3050 50  0000 C CNN
F 1 "33n" V 7939 3050 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W4.4mm_P5.00mm" H 8138 2900 50  0001 C CNN
F 3 "~" H 8100 3050 50  0001 C CNN
	1    8100 3050
	-1   0    0    1   
$EndComp
$Comp
L Device:R R38
U 1 1 616F9D9C
P 9750 3100
F 0 "R38" V 9543 3100 50  0000 C CNN
F 1 "8k2" V 9634 3100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 9680 3100 50  0001 C CNN
F 3 "~" H 9750 3100 50  0001 C CNN
	1    9750 3100
	0    1    1    0   
$EndComp
$Comp
L Device:C C14
U 1 1 616F9DA2
P 9750 2750
F 0 "C14" V 10002 2750 50  0000 C CNN
F 1 "470p" V 9911 2750 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P3.80mm" H 9788 2600 50  0001 C CNN
F 3 "~" H 9750 2750 50  0001 C CNN
	1    9750 2750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R42
U 1 1 616F9DA8
P 10400 3600
F 0 "R42" V 10193 3600 50  0000 C CNN
F 1 "100" V 10284 3600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 10330 3600 50  0001 C CNN
F 3 "~" H 10400 3600 50  0001 C CNN
	1    10400 3600
	0    1    1    0   
$EndComp
$Comp
L Device:R R41
U 1 1 616F9DAE
P 10400 2450
F 0 "R41" V 10193 2450 50  0000 C CNN
F 1 "100" V 10284 2450 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 10330 2450 50  0001 C CNN
F 3 "~" H 10400 2450 50  0001 C CNN
	1    10400 2450
	0    1    1    0   
$EndComp
Text GLabel 7000 3850 0    50   Input ~ 0
+6V
Wire Wire Line
	9150 3700 9450 3700
Wire Wire Line
	7700 3400 7600 3400
Wire Wire Line
	7200 3400 7100 3400
Wire Wire Line
	7100 3400 7100 3500
Connection ~ 7100 3400
Wire Wire Line
	7100 3400 7000 3400
Text GLabel 7000 2850 0    50   Input ~ 0
+8.5V
Wire Wire Line
	7000 3200 7100 3200
Wire Wire Line
	7100 3200 7100 2850
Wire Wire Line
	7100 2850 7000 2850
Wire Wire Line
	7600 3500 7600 3400
Connection ~ 7600 3400
Wire Wire Line
	7600 3400 7500 3400
Wire Wire Line
	9450 3500 9400 3500
Wire Wire Line
	9400 3500 9400 3100
Wire Wire Line
	9400 3100 9600 3100
Connection ~ 9400 3500
Wire Wire Line
	9400 3500 9300 3500
Wire Wire Line
	9400 3100 9400 2750
Wire Wire Line
	9400 2750 9600 2750
Connection ~ 9400 3100
Wire Wire Line
	9900 2750 10150 2750
Wire Wire Line
	10150 2750 10150 3100
Wire Wire Line
	10150 3600 10050 3600
Wire Wire Line
	10150 3600 10250 3600
Connection ~ 10150 3600
Wire Wire Line
	10150 3100 9900 3100
Connection ~ 10150 3100
Wire Wire Line
	10150 3100 10150 3600
Wire Wire Line
	7950 3600 8200 3600
Wire Wire Line
	8000 3400 8100 3400
Wire Wire Line
	8100 3400 8100 3200
Connection ~ 8100 3400
Wire Wire Line
	8100 3400 8200 3400
Wire Wire Line
	7600 3200 7600 3400
Wire Wire Line
	7600 2900 7600 2800
Wire Wire Line
	7600 2800 8100 2800
Wire Wire Line
	8850 2800 8850 3500
Wire Wire Line
	8850 3500 8800 3500
Wire Wire Line
	8100 2900 8100 2800
Connection ~ 8100 2800
Wire Wire Line
	8100 2800 8850 2800
Connection ~ 8850 3500
$Comp
L Connector_Generic:Conn_01x02 J9
U 1 1 616F9DF8
P 10550 2950
F 0 "J9" H 10630 2942 50  0000 L CNN
F 1 "Conn_01x02" H 10630 2851 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 10550 2950 50  0001 C CNN
F 3 "~" H 10550 2950 50  0001 C CNN
	1    10550 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	10650 3250 10650 3600
Wire Wire Line
	10650 3600 10550 3600
Wire Wire Line
	10250 3250 10250 3050
Wire Wire Line
	10250 3050 10350 3050
Wire Wire Line
	10250 3250 10650 3250
Wire Wire Line
	10350 2950 10250 2950
Wire Wire Line
	10250 2950 10250 2750
Wire Wire Line
	10250 2750 10650 2750
Text Label 10650 2650 0    50   ~ 0
Sig_1+
Text Label 10650 3500 0    50   ~ 0
Sig_1-
Text Label 5800 3200 0    50   ~ 0
PWM_1
Wire Wire Line
	6400 3200 6350 3200
Wire Wire Line
	5800 3200 6050 3200
$Comp
L Isolator:PC817 U7
U 1 1 61708372
P 6700 4900
F 0 "U7" H 6700 5225 50  0000 C CNN
F 1 "PC817" H 6700 5134 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 6500 4700 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 6700 4900 50  0001 L CNN
	1    6700 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R21
U 1 1 61708378
P 6200 4800
F 0 "R21" V 5993 4800 50  0000 C CNN
F 1 "100" V 6084 4800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 6130 4800 50  0001 C CNN
F 3 "~" H 6200 4800 50  0001 C CNN
	1    6200 4800
	0    1    1    0   
$EndComp
$Comp
L Device:R R24
U 1 1 6170837E
P 7100 5250
F 0 "R24" H 7170 5296 50  0000 L CNN
F 1 "4k7" H 7170 5205 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7030 5250 50  0001 C CNN
F 3 "~" H 7100 5250 50  0001 C CNN
	1    7100 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R27
U 1 1 61708384
P 7350 5000
F 0 "R27" V 7143 5000 50  0000 C CNN
F 1 "8k2" V 7234 5000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7280 5000 50  0001 C CNN
F 3 "~" H 7350 5000 50  0001 C CNN
	1    7350 5000
	0    1    1    0   
$EndComp
$Comp
L Device:C C9
U 1 1 6170838A
P 7600 5250
F 0 "C9" H 7715 5296 50  0000 L CNN
F 1 "33n" H 7715 5205 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W4.4mm_P5.00mm" H 7638 5100 50  0001 C CNN
F 3 "~" H 7600 5250 50  0001 C CNN
	1    7600 5250
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM324 U9
U 1 1 61708390
P 8500 5100
F 0 "U9" H 8500 4733 50  0000 C CNN
F 1 "LM324" H 8500 4824 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 8450 5200 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 8550 5300 50  0001 C CNN
	1    8500 5100
	1    0    0    1   
$EndComp
$Comp
L Amplifier_Operational:LM324 U9
U 4 1 61708396
P 9750 5200
F 0 "U9" H 9750 4833 50  0000 C CNN
F 1 "LM324" H 9750 4924 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 9700 5300 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 9800 5400 50  0001 C CNN
	4    9750 5200
	1    0    0    1   
$EndComp
$Comp
L Device:R R36
U 1 1 6170839C
P 9150 5100
F 0 "R36" V 8943 5100 50  0000 C CNN
F 1 "8k2" V 9034 5100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 9080 5100 50  0001 C CNN
F 3 "~" H 9150 5100 50  0001 C CNN
	1    9150 5100
	0    1    1    0   
$EndComp
$Comp
L Device:R R33
U 1 1 617083A2
P 7850 5000
F 0 "R33" V 7643 5000 50  0000 C CNN
F 1 "8k2" V 7734 5000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7780 5000 50  0001 C CNN
F 3 "~" H 7850 5000 50  0001 C CNN
	1    7850 5000
	0    1    1    0   
$EndComp
$Comp
L Device:R R30
U 1 1 617083A8
P 7600 4650
F 0 "R30" V 7393 4650 50  0000 C CNN
F 1 "8k2" V 7484 4650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7530 4650 50  0001 C CNN
F 3 "~" H 7600 4650 50  0001 C CNN
	1    7600 4650
	-1   0    0    1   
$EndComp
$Comp
L Device:C C12
U 1 1 617083AE
P 8100 4650
F 0 "C12" V 7848 4650 50  0000 C CNN
F 1 "33n" V 7939 4650 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W4.4mm_P5.00mm" H 8138 4500 50  0001 C CNN
F 3 "~" H 8100 4650 50  0001 C CNN
	1    8100 4650
	-1   0    0    1   
$EndComp
$Comp
L Device:R R39
U 1 1 617083B4
P 9750 4700
F 0 "R39" V 9543 4700 50  0000 C CNN
F 1 "8k2" V 9634 4700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 9680 4700 50  0001 C CNN
F 3 "~" H 9750 4700 50  0001 C CNN
	1    9750 4700
	0    1    1    0   
$EndComp
$Comp
L Device:C C15
U 1 1 617083BA
P 9750 4350
F 0 "C15" V 10002 4350 50  0000 C CNN
F 1 "470p" V 9911 4350 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P3.80mm" H 9788 4200 50  0001 C CNN
F 3 "~" H 9750 4350 50  0001 C CNN
	1    9750 4350
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R44
U 1 1 617083C0
P 10400 5200
F 0 "R44" V 10193 5200 50  0000 C CNN
F 1 "100" V 10284 5200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 10330 5200 50  0001 C CNN
F 3 "~" H 10400 5200 50  0001 C CNN
	1    10400 5200
	0    1    1    0   
$EndComp
$Comp
L Device:R R43
U 1 1 617083C6
P 10400 4050
F 0 "R43" V 10193 4050 50  0000 C CNN
F 1 "100" V 10284 4050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 10330 4050 50  0001 C CNN
F 3 "~" H 10400 4050 50  0001 C CNN
	1    10400 4050
	0    1    1    0   
$EndComp
Text GLabel 7000 5450 0    50   Input ~ 0
+6V
Wire Wire Line
	9150 5300 9450 5300
Wire Wire Line
	7700 5000 7600 5000
Wire Wire Line
	7200 5000 7100 5000
Wire Wire Line
	7100 5000 7100 5100
Connection ~ 7100 5000
Wire Wire Line
	7100 5000 7000 5000
Text GLabel 7000 4450 0    50   Input ~ 0
+8.5V
Wire Wire Line
	7000 4800 7100 4800
Wire Wire Line
	7100 4800 7100 4450
Wire Wire Line
	7100 4450 7000 4450
Wire Wire Line
	7600 5100 7600 5000
Connection ~ 7600 5000
Wire Wire Line
	7600 5000 7500 5000
Wire Wire Line
	9450 5100 9400 5100
Wire Wire Line
	9400 5100 9400 4700
Wire Wire Line
	9400 4700 9600 4700
Connection ~ 9400 5100
Wire Wire Line
	9400 5100 9300 5100
Wire Wire Line
	9400 4700 9400 4350
Wire Wire Line
	9400 4350 9600 4350
Connection ~ 9400 4700
Wire Wire Line
	9900 4350 10150 4350
Wire Wire Line
	10150 4350 10150 4700
Wire Wire Line
	10150 5200 10050 5200
Wire Wire Line
	10150 5200 10250 5200
Connection ~ 10150 5200
Wire Wire Line
	10150 4700 9900 4700
Connection ~ 10150 4700
Wire Wire Line
	10150 4700 10150 5200
Wire Wire Line
	7950 5200 8200 5200
Wire Wire Line
	8000 5000 8100 5000
Wire Wire Line
	8100 5000 8100 4800
Connection ~ 8100 5000
Wire Wire Line
	8100 5000 8200 5000
Wire Wire Line
	7600 4800 7600 5000
Wire Wire Line
	7600 4500 7600 4400
Wire Wire Line
	7600 4400 8100 4400
Wire Wire Line
	8850 4400 8850 5100
Wire Wire Line
	8850 5100 8800 5100
Wire Wire Line
	8100 4500 8100 4400
Connection ~ 8100 4400
Wire Wire Line
	8100 4400 8850 4400
Connection ~ 8850 5100
Wire Wire Line
	8850 5100 8950 5100
Wire Wire Line
	8950 5100 8950 4050
Connection ~ 8950 5100
Wire Wire Line
	8950 5100 9000 5100
Wire Wire Line
	10250 4050 8950 4050
$Comp
L Connector_Generic:Conn_01x02 J10
U 1 1 61708410
P 10550 4550
F 0 "J10" H 10630 4542 50  0000 L CNN
F 1 "Conn_01x02" H 10630 4451 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 10550 4550 50  0001 C CNN
F 3 "~" H 10550 4550 50  0001 C CNN
	1    10550 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	10650 4850 10650 5200
Wire Wire Line
	10650 5200 10550 5200
Wire Wire Line
	10250 4850 10250 4650
Wire Wire Line
	10250 4650 10350 4650
Wire Wire Line
	10250 4850 10650 4850
Wire Wire Line
	10350 4550 10250 4550
Wire Wire Line
	10250 4550 10250 4350
Wire Wire Line
	10250 4350 10650 4350
Wire Wire Line
	10650 4350 10650 4050
Wire Wire Line
	10650 4050 10550 4050
Text Label 10650 4250 0    50   ~ 0
Sig_2+
Text Label 10650 5100 0    50   ~ 0
Sig_2-
Text Label 5800 4800 0    50   ~ 0
PWM_2
Wire Wire Line
	6400 4800 6350 4800
$Comp
L Device:R R22
U 1 1 6171E40E
P 6200 6400
F 0 "R22" V 5993 6400 50  0000 C CNN
F 1 "100" V 6084 6400 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 6130 6400 50  0001 C CNN
F 3 "~" H 6200 6400 50  0001 C CNN
	1    6200 6400
	0    1    1    0   
$EndComp
$Comp
L Device:R R25
U 1 1 6171E414
P 7100 6850
F 0 "R25" H 7170 6896 50  0000 L CNN
F 1 "4k7" H 7170 6805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7030 6850 50  0001 C CNN
F 3 "~" H 7100 6850 50  0001 C CNN
	1    7100 6850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R28
U 1 1 6171E41A
P 7350 6600
F 0 "R28" V 7143 6600 50  0000 C CNN
F 1 "8k2" V 7234 6600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7280 6600 50  0001 C CNN
F 3 "~" H 7350 6600 50  0001 C CNN
	1    7350 6600
	0    1    1    0   
$EndComp
$Comp
L Device:C C10
U 1 1 6171E420
P 7600 6850
F 0 "C10" H 7715 6896 50  0000 L CNN
F 1 "33n" H 7715 6805 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W4.4mm_P5.00mm" H 7638 6700 50  0001 C CNN
F 3 "~" H 7600 6850 50  0001 C CNN
	1    7600 6850
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM324 U9
U 2 1 6171E426
P 8500 6700
F 0 "U9" H 8500 6333 50  0000 C CNN
F 1 "LM324" H 8500 6424 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 8450 6800 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 8550 6900 50  0001 C CNN
	2    8500 6700
	1    0    0    1   
$EndComp
$Comp
L Amplifier_Operational:LM324 U9
U 3 1 6171E42C
P 9750 6800
F 0 "U9" H 9750 6433 50  0000 C CNN
F 1 "LM324" H 9750 6524 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 9700 6900 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 9800 7000 50  0001 C CNN
	3    9750 6800
	1    0    0    1   
$EndComp
$Comp
L Device:R R37
U 1 1 6171E432
P 9150 6700
F 0 "R37" V 8943 6700 50  0000 C CNN
F 1 "8k2" V 9034 6700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 9080 6700 50  0001 C CNN
F 3 "~" H 9150 6700 50  0001 C CNN
	1    9150 6700
	0    1    1    0   
$EndComp
$Comp
L Device:R R34
U 1 1 6171E438
P 7850 6600
F 0 "R34" V 7643 6600 50  0000 C CNN
F 1 "8k2" V 7734 6600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7780 6600 50  0001 C CNN
F 3 "~" H 7850 6600 50  0001 C CNN
	1    7850 6600
	0    1    1    0   
$EndComp
$Comp
L Device:R R31
U 1 1 6171E43E
P 7600 6250
F 0 "R31" V 7393 6250 50  0000 C CNN
F 1 "8k2" V 7484 6250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7530 6250 50  0001 C CNN
F 3 "~" H 7600 6250 50  0001 C CNN
	1    7600 6250
	-1   0    0    1   
$EndComp
$Comp
L Device:C C13
U 1 1 6171E444
P 8100 6250
F 0 "C13" V 7848 6250 50  0000 C CNN
F 1 "33n" V 7939 6250 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W4.4mm_P5.00mm" H 8138 6100 50  0001 C CNN
F 3 "~" H 8100 6250 50  0001 C CNN
	1    8100 6250
	-1   0    0    1   
$EndComp
$Comp
L Device:R R40
U 1 1 6171E44A
P 9750 6300
F 0 "R40" V 9543 6300 50  0000 C CNN
F 1 "8k2" V 9634 6300 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 9680 6300 50  0001 C CNN
F 3 "~" H 9750 6300 50  0001 C CNN
	1    9750 6300
	0    1    1    0   
$EndComp
$Comp
L Device:C C16
U 1 1 6171E450
P 9750 5950
F 0 "C16" V 10002 5950 50  0000 C CNN
F 1 "470p" V 9911 5950 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P3.80mm" H 9788 5800 50  0001 C CNN
F 3 "~" H 9750 5950 50  0001 C CNN
	1    9750 5950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R46
U 1 1 6171E456
P 10400 6800
F 0 "R46" V 10193 6800 50  0000 C CNN
F 1 "100" V 10284 6800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 10330 6800 50  0001 C CNN
F 3 "~" H 10400 6800 50  0001 C CNN
	1    10400 6800
	0    1    1    0   
$EndComp
$Comp
L Device:R R45
U 1 1 6171E45C
P 10400 5650
F 0 "R45" V 10193 5650 50  0000 C CNN
F 1 "100" V 10284 5650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 10330 5650 50  0001 C CNN
F 3 "~" H 10400 5650 50  0001 C CNN
	1    10400 5650
	0    1    1    0   
$EndComp
Text GLabel 6950 7150 0    50   Input ~ 0
+6V
Wire Wire Line
	6950 7150 7100 7150
Wire Wire Line
	7600 7150 7600 7000
Wire Wire Line
	7100 7000 7100 7150
Wire Wire Line
	7600 7150 7950 7150
Wire Wire Line
	9150 7150 9150 6900
Wire Wire Line
	9150 6900 9450 6900
Wire Wire Line
	7950 6800 7950 7150
Wire Wire Line
	7700 6600 7600 6600
Wire Wire Line
	7200 6600 7100 6600
Wire Wire Line
	7100 6600 7100 6700
Connection ~ 7100 6600
Wire Wire Line
	7100 6600 7000 6600
Text GLabel 7000 6050 0    50   Input ~ 0
+8.5V
Wire Wire Line
	7000 6400 7100 6400
Wire Wire Line
	7100 6400 7100 6050
Wire Wire Line
	7100 6050 7000 6050
Wire Wire Line
	7600 6700 7600 6600
Connection ~ 7600 6600
Wire Wire Line
	7600 6600 7500 6600
Wire Wire Line
	9450 6700 9400 6700
Wire Wire Line
	9400 6700 9400 6300
Wire Wire Line
	9400 6300 9600 6300
Connection ~ 9400 6700
Wire Wire Line
	9400 6700 9300 6700
Wire Wire Line
	9400 6300 9400 5950
Wire Wire Line
	9400 5950 9600 5950
Connection ~ 9400 6300
Wire Wire Line
	9900 5950 10150 5950
Wire Wire Line
	10150 5950 10150 6300
Wire Wire Line
	10150 6800 10050 6800
Wire Wire Line
	10150 6800 10250 6800
Connection ~ 10150 6800
Wire Wire Line
	10150 6300 9900 6300
Connection ~ 10150 6300
Wire Wire Line
	10150 6300 10150 6800
Connection ~ 7950 7150
Wire Wire Line
	7950 6800 8200 6800
Wire Wire Line
	8000 6600 8100 6600
Wire Wire Line
	8100 6600 8100 6400
Connection ~ 8100 6600
Wire Wire Line
	8100 6600 8200 6600
Wire Wire Line
	7600 6400 7600 6600
Wire Wire Line
	7600 6100 7600 6000
Wire Wire Line
	7600 6000 8100 6000
Wire Wire Line
	8850 6000 8850 6700
Wire Wire Line
	8850 6700 8800 6700
Wire Wire Line
	8100 6100 8100 6000
Connection ~ 8100 6000
Wire Wire Line
	8100 6000 8850 6000
Wire Wire Line
	7950 7150 9150 7150
Connection ~ 8850 6700
Wire Wire Line
	8850 6700 8950 6700
Wire Wire Line
	8950 6700 8950 5650
Connection ~ 8950 6700
Wire Wire Line
	8950 6700 9000 6700
Wire Wire Line
	7600 7150 7100 7150
Connection ~ 7600 7150
Connection ~ 7100 7150
Wire Wire Line
	10250 5650 8950 5650
$Comp
L Connector_Generic:Conn_01x02 J11
U 1 1 6171E4A6
P 10550 6150
F 0 "J11" H 10630 6142 50  0000 L CNN
F 1 "Conn_01x02" H 10630 6051 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 10550 6150 50  0001 C CNN
F 3 "~" H 10550 6150 50  0001 C CNN
	1    10550 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	10650 6450 10650 6800
Wire Wire Line
	10650 6800 10550 6800
Wire Wire Line
	10250 6450 10250 6250
Wire Wire Line
	10250 6250 10350 6250
Wire Wire Line
	10250 6450 10650 6450
Wire Wire Line
	10350 6150 10250 6150
Wire Wire Line
	10250 6150 10250 5950
Wire Wire Line
	10250 5950 10650 5950
Wire Wire Line
	10650 5950 10650 5650
Wire Wire Line
	10650 5650 10550 5650
Text Label 10650 5850 0    50   ~ 0
Sig_3+
Text Label 10650 6700 0    50   ~ 0
Sig_3-
Text Label 5800 6400 0    50   ~ 0
PWM_3
Wire Wire Line
	6400 6400 6350 6400
Wire Wire Line
	1350 4050 2200 4050
Wire Wire Line
	850  1050 1050 1050
Wire Wire Line
	1050 4050 1150 4050
Wire Wire Line
	1150 950  850  950 
Wire Wire Line
	1050 4050 1050 1050
Wire Wire Line
	1250 1800 1250 2400
Wire Wire Line
	2650 3100 2650 2400
Wire Wire Line
	2650 2400 2450 2400
Connection ~ 2650 2400
Wire Wire Line
	2650 2400 2650 1900
Wire Wire Line
	1400 2400 1250 2400
Connection ~ 1250 2400
Wire Wire Line
	1250 2400 1250 3200
Wire Wire Line
	4050 1650 3900 1650
Wire Wire Line
	3900 1550 4050 1550
Wire Wire Line
	4050 3350 3900 3350
Wire Wire Line
	3900 3450 4050 3450
Wire Wire Line
	3900 1350 3850 1350
Wire Wire Line
	3850 1800 3900 1800
Wire Wire Line
	3900 3200 3850 3200
Wire Wire Line
	3850 3650 3900 3650
Text Notes 1400 850  0    50   ~ 0
Gain X
Text Notes 1400 4200 0    50   ~ 0
Gain Y
Text Notes 1600 2250 0    50   ~ 0
Bias
Text Notes 1900 2600 0    50   ~ 0
V/2 Adjust
Wire Wire Line
	8850 3500 8950 3500
Wire Wire Line
	7000 5450 7100 5450
Wire Wire Line
	9150 5450 9150 5300
Wire Wire Line
	7950 5200 7950 5450
Connection ~ 7950 5450
Wire Wire Line
	7950 5450 9150 5450
Wire Wire Line
	7600 5450 7600 5400
Connection ~ 7600 5450
Wire Wire Line
	7600 5450 7950 5450
Wire Wire Line
	7100 5400 7100 5450
Connection ~ 7100 5450
Wire Wire Line
	7100 5450 7600 5450
Wire Wire Line
	7000 3850 7100 3850
Wire Wire Line
	9150 3850 9150 3700
Wire Wire Line
	7950 3600 7950 3850
Connection ~ 7950 3850
Wire Wire Line
	7950 3850 9150 3850
Wire Wire Line
	7600 3850 7600 3800
Connection ~ 7600 3850
Wire Wire Line
	7600 3850 7950 3850
Wire Wire Line
	7100 3800 7100 3850
Connection ~ 7100 3850
Wire Wire Line
	7100 3850 7600 3850
Wire Wire Line
	9150 2250 9150 2100
Wire Wire Line
	7950 2000 7950 2250
Connection ~ 7950 2250
Wire Wire Line
	7950 2250 9150 2250
Wire Wire Line
	7600 2250 7600 2200
Connection ~ 7600 2250
Wire Wire Line
	7600 2250 7950 2250
Wire Wire Line
	10650 2750 10650 2450
Wire Wire Line
	10650 2450 10550 2450
Wire Wire Line
	10250 2450 8950 2450
Wire Wire Line
	8950 2450 8950 3500
Connection ~ 8950 3500
Wire Wire Line
	8950 3500 9000 3500
Wire Wire Line
	8950 1900 9000 1900
Wire Wire Line
	8850 1900 8950 1900
Connection ~ 8950 1900
Wire Wire Line
	8950 1900 8950 850 
Text Notes 5550 7850 0    50   ~ 0
Étage d'analogisation d'une sortie PWM :\nL'optocoupleur permet de faire simplement la translation de niveau.\nEnsuite un filtre du second ordre lisse le signal (Fs = 600Hz), \nsuivit par un inverseur pour générer une paire symétrique\n\nNote :\nPas besoin de potars pour régler les niveaux ici, le réglage se fera par les tensions des rails +8.5V et +6V\n
$Comp
L power:+12V #PWR015
U 1 1 61ECC6F7
P 11500 1800
F 0 "#PWR015" H 11500 1650 50  0001 C CNN
F 1 "+12V" H 11515 1973 50  0000 C CNN
F 2 "" H 11500 1800 50  0001 C CNN
F 3 "" H 11500 1800 50  0001 C CNN
	1    11500 1800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 61ECC6FD
P 11500 2600
F 0 "#PWR016" H 11500 2350 50  0001 C CNN
F 1 "GND" H 11505 2427 50  0000 C CNN
F 2 "" H 11500 2600 50  0001 C CNN
F 3 "" H 11500 2600 50  0001 C CNN
	1    11500 2600
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM324 U5
U 5 1 61ECC703
P 11600 2200
F 0 "U5" H 11558 2246 50  0000 L CNN
F 1 "LM324" H 11558 2155 50  0000 L CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 11550 2300 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 11650 2400 50  0001 C CNN
	5    11600 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	11500 1800 11500 1900
$Comp
L power:+12V #PWR017
U 1 1 61EECD53
P 11500 5000
F 0 "#PWR017" H 11500 4850 50  0001 C CNN
F 1 "+12V" H 11515 5173 50  0000 C CNN
F 2 "" H 11500 5000 50  0001 C CNN
F 3 "" H 11500 5000 50  0001 C CNN
	1    11500 5000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR018
U 1 1 61EECD59
P 11500 5800
F 0 "#PWR018" H 11500 5550 50  0001 C CNN
F 1 "GND" H 11505 5627 50  0000 C CNN
F 2 "" H 11500 5800 50  0001 C CNN
F 3 "" H 11500 5800 50  0001 C CNN
	1    11500 5800
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM324 U9
U 5 1 61EECD5F
P 11600 5400
F 0 "U9" H 11558 5446 50  0000 L CNN
F 1 "LM324" H 11558 5355 50  0000 L CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 11550 5500 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 11650 5600 50  0001 C CNN
	5    11600 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	11500 5700 11500 5800
Wire Wire Line
	11500 5000 11500 5100
Text Notes 12350 5650 0    50   ~ 0
Adaptation niveau logique leds :\nInterface entre l'arduino (3.3V) et les leds (5V)
$Comp
L Connector:Conn_01x03_Female J13
U 1 1 61C73A7B
P 2350 8450
F 0 "J13" H 2242 8735 50  0000 C CNN
F 1 "Conn_01x03_Female" H 2242 8644 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 2350 8450 50  0001 C CNN
F 3 "~" H 2350 8450 50  0001 C CNN
	1    2350 8450
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_BJT:2N2219 Q1
U 1 1 61C7BF9D
P 2600 9700
F 0 "Q1" H 2790 9746 50  0000 L CNN
F 1 "2N2219" H 2790 9655 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92" H 2800 9625 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 2600 9700 50  0001 L CNN
	1    2600 9700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R47
U 1 1 61C7F513
P 2150 9700
F 0 "R47" V 1943 9700 50  0000 C CNN
F 1 "2k2" V 2034 9700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 2080 9700 50  0001 C CNN
F 3 "~" H 2150 9700 50  0001 C CNN
	1    2150 9700
	0    1    1    0   
$EndComp
$Comp
L power:+12V #PWR021
U 1 1 61C80AAB
P 2700 8200
F 0 "#PWR021" H 2700 8050 50  0001 C CNN
F 1 "+12V" H 2715 8373 50  0000 C CNN
F 2 "" H 2700 8200 50  0001 C CNN
F 3 "" H 2700 8200 50  0001 C CNN
	1    2700 8200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR019
U 1 1 61C823AE
P 2550 10150
F 0 "#PWR019" H 2550 9900 50  0001 C CNN
F 1 "GND" H 2555 9977 50  0000 C CNN
F 2 "" H 2550 10150 50  0001 C CNN
F 3 "" H 2550 10150 50  0001 C CNN
	1    2550 10150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J12
U 1 1 61C8508E
P 1650 9700
F 0 "J12" H 1758 9881 50  0000 C CNN
F 1 "Conn_01x01_Male" H 1758 9790 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1650 9700 50  0001 C CNN
F 3 "~" H 1650 9700 50  0001 C CNN
	1    1650 9700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 9700 2000 9700
Wire Wire Line
	2300 9700 2350 9700
Wire Wire Line
	2700 9500 2700 9400
$Comp
L power:GND #PWR020
U 1 1 61FEA0AC
P 2600 8600
F 0 "#PWR020" H 2600 8350 50  0001 C CNN
F 1 "GND" H 2605 8427 50  0000 C CNN
F 2 "" H 2600 8600 50  0001 C CNN
F 3 "" H 2600 8600 50  0001 C CNN
	1    2600 8600
	1    0    0    -1  
$EndComp
Text Notes 1800 8100 0    50   ~ 0
Commande manuelle
Text Notes 1500 9850 0    50   ~ 0
Commande logique
$Comp
L Device:R R48
U 1 1 6202E38D
P 2350 9900
F 0 "R48" H 2420 9946 50  0000 L CNN
F 1 "47k" H 2420 9855 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 2280 9900 50  0001 C CNN
F 3 "~" H 2350 9900 50  0001 C CNN
	1    2350 9900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 10150 2550 10100
Wire Wire Line
	2550 10100 2350 10100
Wire Wire Line
	2350 10100 2350 10050
Wire Wire Line
	2550 10100 2700 10100
Wire Wire Line
	2700 9900 2700 10100
Connection ~ 2550 10100
Wire Wire Line
	2350 9750 2350 9700
Connection ~ 2350 9700
Wire Wire Line
	2350 9700 2400 9700
Wire Wire Line
	2700 8450 2550 8450
Wire Wire Line
	2700 8450 2700 8800
Wire Wire Line
	2550 8550 2600 8550
Wire Wire Line
	2600 8550 2600 8600
Wire Wire Line
	2550 8350 2700 8350
Wire Wire Line
	2700 8350 2700 8200
Text Notes 1600 10550 0    50   ~ 0
Sécurité alimentation laser
$Comp
L Relay:FINDER-36.11 K1
U 1 1 6230468A
P 2900 9100
F 0 "K1" H 3330 9146 50  0000 L CNN
F 1 "FINDER-36.11" H 3330 9055 50  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_Finder_36.11" H 4170 9070 50  0001 C CNN
F 3 "https://gfinder.findernet.com/public/attachments/36/EN/S36EN.pdf" H 2900 9100 50  0001 C CNN
	1    2900 9100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J14
U 1 1 62306622
P 3700 8800
F 0 "J14" H 3780 8792 50  0000 L CNN
F 1 "Conn_01x02" H 3780 8701 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3700 8800 50  0001 C CNN
F 3 "~" H 3700 8800 50  0001 C CNN
	1    3700 8800
	1    0    0    1   
$EndComp
Wire Wire Line
	3200 8700 3200 8800
Wire Wire Line
	3500 8700 3200 8700
Wire Wire Line
	3500 8800 3400 8800
Wire Wire Line
	3400 8800 3400 9500
Wire Wire Line
	3400 9500 3100 9500
Wire Wire Line
	3100 9500 3100 9400
$Comp
L Connector:Screw_Terminal_01x02 J25
U 1 1 624114BD
P 4150 7650
F 0 "J25" H 4230 7642 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 4230 7551 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 4150 7650 50  0001 C CNN
F 3 "~" H 4150 7650 50  0001 C CNN
	1    4150 7650
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR022
U 1 1 62413346
P 3850 7550
F 0 "#PWR022" H 3850 7400 50  0001 C CNN
F 1 "+12V" H 3865 7723 50  0000 C CNN
F 2 "" H 3850 7550 50  0001 C CNN
F 3 "" H 3850 7550 50  0001 C CNN
	1    3850 7550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR023
U 1 1 62414854
P 3850 7850
F 0 "#PWR023" H 3850 7600 50  0001 C CNN
F 1 "GND" H 3855 7677 50  0000 C CNN
F 2 "" H 3850 7850 50  0001 C CNN
F 3 "" H 3850 7850 50  0001 C CNN
	1    3850 7850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J24
U 1 1 6241677E
P 3550 7650
F 0 "J24" H 3658 7831 50  0000 C CNN
F 1 "Conn_01x02_Male" H 3658 7740 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3550 7650 50  0001 C CNN
F 3 "~" H 3550 7650 50  0001 C CNN
	1    3550 7650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 7650 3850 7650
Wire Wire Line
	3850 7650 3850 7550
Connection ~ 3850 7650
Wire Wire Line
	3850 7650 3750 7650
Wire Wire Line
	3750 7750 3850 7750
Wire Wire Line
	3850 7750 3850 7850
Connection ~ 3850 7750
Wire Wire Line
	3850 7750 3950 7750
NoConn ~ 3000 8800
Wire Wire Line
	11500 2500 11500 2600
$Comp
L Isolator:PC817 U8
U 1 1 6171E408
P 6700 6500
F 0 "U8" H 6700 6825 50  0000 C CNN
F 1 "PC817" H 6700 6734 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 6500 6300 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 6700 6500 50  0001 L CNN
	1    6700 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 6600 6200 5000
Wire Wire Line
	6200 1800 6400 1800
Wire Wire Line
	6200 6600 6400 6600
Wire Wire Line
	6200 2000 5550 2000
Connection ~ 6200 2000
Wire Wire Line
	6200 2000 6200 1800
Wire Wire Line
	5550 1600 6050 1600
Wire Wire Line
	5550 1700 5800 1700
Wire Wire Line
	5800 1700 5800 3200
Wire Wire Line
	5550 1800 5750 1800
Wire Wire Line
	5750 1800 5750 4800
Wire Wire Line
	5750 4800 6050 4800
Wire Wire Line
	5700 6400 5700 1900
Wire Wire Line
	5700 1900 5550 1900
Wire Wire Line
	5700 6400 6050 6400
Wire Wire Line
	6200 3400 6400 3400
Connection ~ 6200 3400
Wire Wire Line
	6200 3400 6200 2000
Wire Wire Line
	6200 5000 6400 5000
Connection ~ 6200 5000
Wire Wire Line
	6200 5000 6200 3400
$Comp
L Connector:Conn_01x04_Male J4
U 1 1 62522029
P 5350 1700
F 0 "J4" H 5458 1981 50  0000 C CNN
F 1 "Conn_01x04_Male" H 5458 1890 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 5350 1700 50  0001 C CNN
F 3 "~" H 5350 1700 50  0001 C CNN
	1    5350 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 62523A7B
P 5550 2050
F 0 "#PWR08" H 5550 1800 50  0001 C CNN
F 1 "GND" H 5555 1877 50  0000 C CNN
F 2 "" H 5550 2050 50  0001 C CNN
F 3 "" H 5550 2050 50  0001 C CNN
	1    5550 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 2000 5550 2050
$Comp
L Connector:Conn_01x10_Female J5
U 1 1 61A5AD9C
P 12150 1750
F 0 "J5" H 12042 1025 50  0000 C CNN
F 1 "Conn_01x10_Female" H 12042 1116 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x10_P2.54mm_Vertical" H 12150 1750 50  0001 C CNN
F 3 "~" H 12150 1750 50  0001 C CNN
	1    12150 1750
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR012
U 1 1 61A8E7FA
P 12450 2050
F 0 "#PWR012" H 12450 1900 50  0001 C CNN
F 1 "+3.3V" V 12465 2178 50  0000 L CNN
F 2 "" H 12450 2050 50  0001 C CNN
F 3 "" H 12450 2050 50  0001 C CNN
	1    12450 2050
	0    1    1    0   
$EndComp
Wire Wire Line
	12450 2050 12400 2050
Wire Wire Line
	13900 1200 13900 1050
Wire Wire Line
	13550 1200 13900 1200
Wire Wire Line
	13550 850  13600 850 
Connection ~ 13550 850 
Wire Wire Line
	13550 850  13550 900 
Wire Wire Line
	13500 850  13550 850 
Wire Wire Line
	14450 650  13900 650 
Wire Wire Line
	13200 850  13100 850 
$Comp
L power:+3.3V #PWR014
U 1 1 61B5D031
P 13100 850
F 0 "#PWR014" H 13100 700 50  0001 C CNN
F 1 "+3.3V" V 13115 978 50  0000 L CNN
F 2 "" H 13100 850 50  0001 C CNN
F 3 "" H 13100 850 50  0001 C CNN
	1    13100 850 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	14400 750  14400 800 
Wire Wire Line
	14450 750  14400 750 
$Comp
L power:GND #PWR031
U 1 1 61A8B897
P 14400 800
F 0 "#PWR031" H 14400 550 50  0001 C CNN
F 1 "GND" H 14405 627 50  0000 C CNN
F 2 "" H 14400 800 50  0001 C CNN
F 3 "" H 14400 800 50  0001 C CNN
	1    14400 800 
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J6
U 1 1 61A89B1B
P 14650 650
F 0 "J6" H 14678 626 50  0000 L CNN
F 1 "Conn_01x02_Female" H 14678 535 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 14650 650 50  0001 C CNN
F 3 "~" H 14650 650 50  0001 C CNN
	1    14650 650 
	1    0    0    -1  
$EndComp
$Comp
L Device:R R49
U 1 1 61A88770
P 13350 850
F 0 "R49" V 13143 850 50  0000 C CNN
F 1 "1k" V 13234 850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 13280 850 50  0001 C CNN
F 3 "~" H 13350 850 50  0001 C CNN
	1    13350 850 
	0    1    1    0   
$EndComp
$Comp
L Device:R R57
U 1 1 61A870C0
P 13550 1050
F 0 "R57" H 13480 1004 50  0000 R CNN
F 1 "47k" H 13480 1095 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 13480 1050 50  0001 C CNN
F 3 "~" H 13550 1050 50  0001 C CNN
	1    13550 1050
	-1   0    0    1   
$EndComp
$Comp
L Transistor_BJT:2N2219 Q2
U 1 1 61A5ECC6
P 13800 850
F 0 "Q2" H 13990 896 50  0000 L CNN
F 1 "2N2219" H 13990 805 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92" H 14000 775 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 13800 850 50  0001 L CNN
	1    13800 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	13900 1800 13900 1650
Wire Wire Line
	13550 1800 13900 1800
Wire Wire Line
	13550 1450 13600 1450
Connection ~ 13550 1450
Wire Wire Line
	13550 1450 13550 1500
Wire Wire Line
	13500 1450 13550 1450
Wire Wire Line
	14450 1250 13900 1250
Wire Wire Line
	13200 1450 13100 1450
$Comp
L power:+3.3V #PWR024
U 1 1 61E83BB4
P 13100 1450
F 0 "#PWR024" H 13100 1300 50  0001 C CNN
F 1 "+3.3V" V 13115 1578 50  0000 L CNN
F 2 "" H 13100 1450 50  0001 C CNN
F 3 "" H 13100 1450 50  0001 C CNN
	1    13100 1450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	14400 1350 14400 1400
Wire Wire Line
	14450 1350 14400 1350
$Comp
L power:GND #PWR032
U 1 1 61E83BBC
P 14400 1400
F 0 "#PWR032" H 14400 1150 50  0001 C CNN
F 1 "GND" H 14405 1227 50  0000 C CNN
F 2 "" H 14400 1400 50  0001 C CNN
F 3 "" H 14400 1400 50  0001 C CNN
	1    14400 1400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J7
U 1 1 61E83BC2
P 14650 1250
F 0 "J7" H 14678 1226 50  0000 L CNN
F 1 "Conn_01x02_Female" H 14678 1135 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 14650 1250 50  0001 C CNN
F 3 "~" H 14650 1250 50  0001 C CNN
	1    14650 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R50
U 1 1 61E83BC8
P 13350 1450
F 0 "R50" V 13143 1450 50  0000 C CNN
F 1 "1k" V 13234 1450 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 13280 1450 50  0001 C CNN
F 3 "~" H 13350 1450 50  0001 C CNN
	1    13350 1450
	0    1    1    0   
$EndComp
$Comp
L Device:R R58
U 1 1 61E83BCE
P 13550 1650
F 0 "R58" H 13480 1604 50  0000 R CNN
F 1 "47k" H 13480 1695 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 13480 1650 50  0001 C CNN
F 3 "~" H 13550 1650 50  0001 C CNN
	1    13550 1650
	-1   0    0    1   
$EndComp
$Comp
L Transistor_BJT:2N2219 Q3
U 1 1 61E83BD4
P 13800 1450
F 0 "Q3" H 13990 1496 50  0000 L CNN
F 1 "2N2219" H 13990 1405 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92" H 14000 1375 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 13800 1450 50  0001 L CNN
	1    13800 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	13900 2400 13900 2250
Wire Wire Line
	13550 2400 13900 2400
Wire Wire Line
	13550 2050 13600 2050
Connection ~ 13550 2050
Wire Wire Line
	13550 2050 13550 2100
Wire Wire Line
	13500 2050 13550 2050
Wire Wire Line
	14450 1850 13900 1850
Wire Wire Line
	13200 2050 13100 2050
$Comp
L power:+3.3V #PWR025
U 1 1 61EB435C
P 13100 2050
F 0 "#PWR025" H 13100 1900 50  0001 C CNN
F 1 "+3.3V" V 13115 2178 50  0000 L CNN
F 2 "" H 13100 2050 50  0001 C CNN
F 3 "" H 13100 2050 50  0001 C CNN
	1    13100 2050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	14400 1950 14400 2000
Wire Wire Line
	14450 1950 14400 1950
$Comp
L power:GND #PWR033
U 1 1 61EB4364
P 14400 2000
F 0 "#PWR033" H 14400 1750 50  0001 C CNN
F 1 "GND" H 14405 1827 50  0000 C CNN
F 2 "" H 14400 2000 50  0001 C CNN
F 3 "" H 14400 2000 50  0001 C CNN
	1    14400 2000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J15
U 1 1 61EB436A
P 14650 1850
F 0 "J15" H 14678 1826 50  0000 L CNN
F 1 "Conn_01x02_Female" H 14678 1735 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 14650 1850 50  0001 C CNN
F 3 "~" H 14650 1850 50  0001 C CNN
	1    14650 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R51
U 1 1 61EB4370
P 13350 2050
F 0 "R51" V 13143 2050 50  0000 C CNN
F 1 "1k" V 13234 2050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 13280 2050 50  0001 C CNN
F 3 "~" H 13350 2050 50  0001 C CNN
	1    13350 2050
	0    1    1    0   
$EndComp
$Comp
L Device:R R59
U 1 1 61EB4376
P 13550 2250
F 0 "R59" H 13480 2204 50  0000 R CNN
F 1 "47k" H 13480 2295 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 13480 2250 50  0001 C CNN
F 3 "~" H 13550 2250 50  0001 C CNN
	1    13550 2250
	-1   0    0    1   
$EndComp
$Comp
L Transistor_BJT:2N2219 Q4
U 1 1 61EB437C
P 13800 2050
F 0 "Q4" H 13990 2096 50  0000 L CNN
F 1 "2N2219" H 13990 2005 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92" H 14000 1975 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 13800 2050 50  0001 L CNN
	1    13800 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	13900 3000 13900 2850
Wire Wire Line
	13550 3000 13900 3000
Wire Wire Line
	13550 2650 13600 2650
Connection ~ 13550 2650
Wire Wire Line
	13550 2650 13550 2700
Wire Wire Line
	13500 2650 13550 2650
Wire Wire Line
	14450 2450 13900 2450
Wire Wire Line
	13200 2650 13100 2650
$Comp
L power:+3.3V #PWR026
U 1 1 61EB438A
P 13100 2650
F 0 "#PWR026" H 13100 2500 50  0001 C CNN
F 1 "+3.3V" V 13115 2778 50  0000 L CNN
F 2 "" H 13100 2650 50  0001 C CNN
F 3 "" H 13100 2650 50  0001 C CNN
	1    13100 2650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	14400 2550 14400 2600
Wire Wire Line
	14450 2550 14400 2550
$Comp
L power:GND #PWR034
U 1 1 61EB4392
P 14400 2600
F 0 "#PWR034" H 14400 2350 50  0001 C CNN
F 1 "GND" H 14405 2427 50  0000 C CNN
F 2 "" H 14400 2600 50  0001 C CNN
F 3 "" H 14400 2600 50  0001 C CNN
	1    14400 2600
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J16
U 1 1 61EB4398
P 14650 2450
F 0 "J16" H 14678 2426 50  0000 L CNN
F 1 "Conn_01x02_Female" H 14678 2335 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 14650 2450 50  0001 C CNN
F 3 "~" H 14650 2450 50  0001 C CNN
	1    14650 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R52
U 1 1 61EB439E
P 13350 2650
F 0 "R52" V 13143 2650 50  0000 C CNN
F 1 "1k" V 13234 2650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 13280 2650 50  0001 C CNN
F 3 "~" H 13350 2650 50  0001 C CNN
	1    13350 2650
	0    1    1    0   
$EndComp
$Comp
L Device:R R60
U 1 1 61EB43A4
P 13550 2850
F 0 "R60" H 13480 2804 50  0000 R CNN
F 1 "47k" H 13480 2895 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 13480 2850 50  0001 C CNN
F 3 "~" H 13550 2850 50  0001 C CNN
	1    13550 2850
	-1   0    0    1   
$EndComp
$Comp
L Transistor_BJT:2N2219 Q5
U 1 1 61EB43AA
P 13800 2650
F 0 "Q5" H 13990 2696 50  0000 L CNN
F 1 "2N2219" H 13990 2605 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92" H 14000 2575 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 13800 2650 50  0001 L CNN
	1    13800 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	13900 3600 13900 3450
Wire Wire Line
	13550 3600 13900 3600
Wire Wire Line
	13550 3250 13600 3250
Connection ~ 13550 3250
Wire Wire Line
	13550 3250 13550 3300
Wire Wire Line
	13500 3250 13550 3250
Wire Wire Line
	14450 3050 13900 3050
Wire Wire Line
	13200 3250 13100 3250
$Comp
L power:+3.3V #PWR027
U 1 1 61EF5BDE
P 13100 3250
F 0 "#PWR027" H 13100 3100 50  0001 C CNN
F 1 "+3.3V" V 13115 3378 50  0000 L CNN
F 2 "" H 13100 3250 50  0001 C CNN
F 3 "" H 13100 3250 50  0001 C CNN
	1    13100 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	14400 3150 14400 3200
Wire Wire Line
	14450 3150 14400 3150
$Comp
L power:GND #PWR035
U 1 1 61EF5BE6
P 14400 3200
F 0 "#PWR035" H 14400 2950 50  0001 C CNN
F 1 "GND" H 14405 3027 50  0000 C CNN
F 2 "" H 14400 3200 50  0001 C CNN
F 3 "" H 14400 3200 50  0001 C CNN
	1    14400 3200
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J17
U 1 1 61EF5BEC
P 14650 3050
F 0 "J17" H 14678 3026 50  0000 L CNN
F 1 "Conn_01x02_Female" H 14678 2935 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 14650 3050 50  0001 C CNN
F 3 "~" H 14650 3050 50  0001 C CNN
	1    14650 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R53
U 1 1 61EF5BF2
P 13350 3250
F 0 "R53" V 13143 3250 50  0000 C CNN
F 1 "1k" V 13234 3250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 13280 3250 50  0001 C CNN
F 3 "~" H 13350 3250 50  0001 C CNN
	1    13350 3250
	0    1    1    0   
$EndComp
$Comp
L Device:R R61
U 1 1 61EF5BF8
P 13550 3450
F 0 "R61" H 13480 3404 50  0000 R CNN
F 1 "47k" H 13480 3495 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 13480 3450 50  0001 C CNN
F 3 "~" H 13550 3450 50  0001 C CNN
	1    13550 3450
	-1   0    0    1   
$EndComp
$Comp
L Transistor_BJT:2N2219 Q6
U 1 1 61EF5BFE
P 13800 3250
F 0 "Q6" H 13990 3296 50  0000 L CNN
F 1 "2N2219" H 13990 3205 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92" H 14000 3175 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 13800 3250 50  0001 L CNN
	1    13800 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	13900 4200 13900 4050
Wire Wire Line
	13550 4200 13900 4200
Wire Wire Line
	13550 3850 13600 3850
Connection ~ 13550 3850
Wire Wire Line
	13550 3850 13550 3900
Wire Wire Line
	13500 3850 13550 3850
Wire Wire Line
	14450 3650 13900 3650
Wire Wire Line
	13200 3850 13100 3850
$Comp
L power:+3.3V #PWR028
U 1 1 61EF5C0C
P 13100 3850
F 0 "#PWR028" H 13100 3700 50  0001 C CNN
F 1 "+3.3V" V 13115 3978 50  0000 L CNN
F 2 "" H 13100 3850 50  0001 C CNN
F 3 "" H 13100 3850 50  0001 C CNN
	1    13100 3850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	14400 3750 14400 3800
Wire Wire Line
	14450 3750 14400 3750
$Comp
L power:GND #PWR036
U 1 1 61EF5C14
P 14400 3800
F 0 "#PWR036" H 14400 3550 50  0001 C CNN
F 1 "GND" H 14405 3627 50  0000 C CNN
F 2 "" H 14400 3800 50  0001 C CNN
F 3 "" H 14400 3800 50  0001 C CNN
	1    14400 3800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J18
U 1 1 61EF5C1A
P 14650 3650
F 0 "J18" H 14678 3626 50  0000 L CNN
F 1 "Conn_01x02_Female" H 14678 3535 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 14650 3650 50  0001 C CNN
F 3 "~" H 14650 3650 50  0001 C CNN
	1    14650 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R54
U 1 1 61EF5C20
P 13350 3850
F 0 "R54" V 13143 3850 50  0000 C CNN
F 1 "1k" V 13234 3850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 13280 3850 50  0001 C CNN
F 3 "~" H 13350 3850 50  0001 C CNN
	1    13350 3850
	0    1    1    0   
$EndComp
$Comp
L Device:R R62
U 1 1 61EF5C26
P 13550 4050
F 0 "R62" H 13480 4004 50  0000 R CNN
F 1 "47k" H 13480 4095 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 13480 4050 50  0001 C CNN
F 3 "~" H 13550 4050 50  0001 C CNN
	1    13550 4050
	-1   0    0    1   
$EndComp
$Comp
L Transistor_BJT:2N2219 Q7
U 1 1 61EF5C2C
P 13800 3850
F 0 "Q7" H 13990 3896 50  0000 L CNN
F 1 "2N2219" H 13990 3805 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92" H 14000 3775 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 13800 3850 50  0001 L CNN
	1    13800 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	13900 4800 13900 4650
Wire Wire Line
	13550 4800 13900 4800
Wire Wire Line
	13550 4450 13600 4450
Connection ~ 13550 4450
Wire Wire Line
	13550 4450 13550 4500
Wire Wire Line
	13500 4450 13550 4450
Wire Wire Line
	14450 4250 13900 4250
Wire Wire Line
	13200 4450 13100 4450
$Comp
L power:+3.3V #PWR029
U 1 1 61EF5C3A
P 13100 4450
F 0 "#PWR029" H 13100 4300 50  0001 C CNN
F 1 "+3.3V" V 13115 4578 50  0000 L CNN
F 2 "" H 13100 4450 50  0001 C CNN
F 3 "" H 13100 4450 50  0001 C CNN
	1    13100 4450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	14400 4350 14400 4400
Wire Wire Line
	14450 4350 14400 4350
$Comp
L power:GND #PWR037
U 1 1 61EF5C42
P 14400 4400
F 0 "#PWR037" H 14400 4150 50  0001 C CNN
F 1 "GND" H 14405 4227 50  0000 C CNN
F 2 "" H 14400 4400 50  0001 C CNN
F 3 "" H 14400 4400 50  0001 C CNN
	1    14400 4400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J19
U 1 1 61EF5C48
P 14650 4250
F 0 "J19" H 14678 4226 50  0000 L CNN
F 1 "Conn_01x02_Female" H 14678 4135 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 14650 4250 50  0001 C CNN
F 3 "~" H 14650 4250 50  0001 C CNN
	1    14650 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R55
U 1 1 61EF5C4E
P 13350 4450
F 0 "R55" V 13143 4450 50  0000 C CNN
F 1 "1k" V 13234 4450 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 13280 4450 50  0001 C CNN
F 3 "~" H 13350 4450 50  0001 C CNN
	1    13350 4450
	0    1    1    0   
$EndComp
$Comp
L Device:R R63
U 1 1 61EF5C54
P 13550 4650
F 0 "R63" H 13480 4604 50  0000 R CNN
F 1 "47k" H 13480 4695 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 13480 4650 50  0001 C CNN
F 3 "~" H 13550 4650 50  0001 C CNN
	1    13550 4650
	-1   0    0    1   
$EndComp
$Comp
L Transistor_BJT:2N2219 Q8
U 1 1 61EF5C5A
P 13800 4450
F 0 "Q8" H 13990 4496 50  0000 L CNN
F 1 "2N2219" H 13990 4405 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92" H 14000 4375 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 13800 4450 50  0001 L CNN
	1    13800 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	13900 5400 13900 5250
Wire Wire Line
	13550 5400 13900 5400
Wire Wire Line
	13550 5050 13600 5050
Connection ~ 13550 5050
Wire Wire Line
	13550 5050 13550 5100
Wire Wire Line
	13500 5050 13550 5050
Wire Wire Line
	14450 4850 13900 4850
Wire Wire Line
	13200 5050 13100 5050
$Comp
L power:+3.3V #PWR030
U 1 1 61EF5C68
P 13100 5050
F 0 "#PWR030" H 13100 4900 50  0001 C CNN
F 1 "+3.3V" V 13115 5178 50  0000 L CNN
F 2 "" H 13100 5050 50  0001 C CNN
F 3 "" H 13100 5050 50  0001 C CNN
	1    13100 5050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	14400 4950 14400 5000
Wire Wire Line
	14450 4950 14400 4950
$Comp
L power:GND #PWR038
U 1 1 61EF5C70
P 14400 5000
F 0 "#PWR038" H 14400 4750 50  0001 C CNN
F 1 "GND" H 14405 4827 50  0000 C CNN
F 2 "" H 14400 5000 50  0001 C CNN
F 3 "" H 14400 5000 50  0001 C CNN
	1    14400 5000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J20
U 1 1 61EF5C76
P 14650 4850
F 0 "J20" H 14678 4826 50  0000 L CNN
F 1 "Conn_01x02_Female" H 14678 4735 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 14650 4850 50  0001 C CNN
F 3 "~" H 14650 4850 50  0001 C CNN
	1    14650 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R56
U 1 1 61EF5C7C
P 13350 5050
F 0 "R56" V 13143 5050 50  0000 C CNN
F 1 "1k" V 13234 5050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 13280 5050 50  0001 C CNN
F 3 "~" H 13350 5050 50  0001 C CNN
	1    13350 5050
	0    1    1    0   
$EndComp
$Comp
L Device:R R64
U 1 1 61EF5C82
P 13550 5250
F 0 "R64" H 13480 5204 50  0000 R CNN
F 1 "47k" H 13480 5295 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 13480 5250 50  0001 C CNN
F 3 "~" H 13550 5250 50  0001 C CNN
	1    13550 5250
	-1   0    0    1   
$EndComp
$Comp
L Transistor_BJT:2N2219 Q9
U 1 1 61EF5C88
P 13800 5050
F 0 "Q9" H 13990 5096 50  0000 L CNN
F 1 "2N2219" H 13990 5005 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92" H 14000 4975 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 13800 5050 50  0001 L CNN
	1    13800 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	12350 1250 13550 1250
Wire Wire Line
	13550 1250 13550 1200
Connection ~ 13550 1200
Wire Wire Line
	12350 1350 12950 1350
Wire Wire Line
	12950 1350 12950 1800
Wire Wire Line
	12950 1800 13550 1800
Connection ~ 13550 1800
Wire Wire Line
	12350 1450 12900 1450
Wire Wire Line
	12900 1450 12900 2400
Wire Wire Line
	12900 2400 13550 2400
Connection ~ 13550 2400
Wire Wire Line
	13550 3000 12850 3000
Wire Wire Line
	12850 3000 12850 1550
Wire Wire Line
	12850 1550 12350 1550
Connection ~ 13550 3000
Wire Wire Line
	12350 1650 12800 1650
Wire Wire Line
	12800 1650 12800 3600
Wire Wire Line
	12800 3600 13550 3600
Connection ~ 13550 3600
Wire Wire Line
	13550 4200 12750 4200
Wire Wire Line
	12750 4200 12750 1750
Wire Wire Line
	12750 1750 12350 1750
Connection ~ 13550 4200
Wire Wire Line
	12350 1850 12700 1850
Wire Wire Line
	12700 1850 12700 4800
Wire Wire Line
	12700 4800 13550 4800
Connection ~ 13550 4800
Wire Wire Line
	13550 5400 12650 5400
Wire Wire Line
	12650 5400 12650 1950
Wire Wire Line
	12650 1950 12350 1950
Connection ~ 13550 5400
Wire Wire Line
	12350 2150 12400 2150
Wire Wire Line
	12400 2150 12400 2050
Connection ~ 12400 2050
Wire Wire Line
	12400 2050 12350 2050
Wire Wire Line
	7000 2250 7050 2250
Wire Wire Line
	7100 1800 7100 1600
Wire Wire Line
	7100 1600 7000 1600
Connection ~ 7100 1600
Wire Wire Line
	7100 1600 7100 1550
Wire Wire Line
	7000 1800 7050 1800
Wire Wire Line
	7050 1800 7050 2250
Connection ~ 7050 2250
Wire Wire Line
	7050 2250 7600 2250
$EndSCHEMATC
