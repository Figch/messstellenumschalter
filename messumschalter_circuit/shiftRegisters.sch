EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 9700 2250 0    50   ~ 0
Latch
Text Label 9650 2550 0    50   ~ 0
Data
Text Label 9650 2650 0    50   ~ 0
Clock
Wire Wire Line
	9000 2250 8900 2250
Wire Wire Line
	9000 2750 9000 2250
Wire Wire Line
	8050 2750 9000 2750
Connection ~ 8000 1550
Wire Wire Line
	8000 1550 8000 3550
Entry Wire Line
	9300 4050 9400 4150
Entry Wire Line
	9300 3950 9400 4050
Entry Wire Line
	9300 3850 9400 3950
Entry Wire Line
	9300 3750 9400 3850
Entry Wire Line
	9300 3650 9400 3750
Entry Wire Line
	9300 3550 9400 3650
Entry Wire Line
	9300 3450 9400 3550
Entry Wire Line
	9300 3350 9400 3450
Text Label 9000 4050 0    50   ~ 0
Out15
Text Label 9000 3950 0    50   ~ 0
Out14
Text Label 9000 3850 0    50   ~ 0
Out13
Text Label 9000 3750 0    50   ~ 0
Out12
Text Label 9000 3650 0    50   ~ 0
Out11
Text Label 9000 3550 0    50   ~ 0
Out10
Text Label 9000 3450 0    50   ~ 0
Out9
Text Label 9000 3350 0    50   ~ 0
Out8
Wire Wire Line
	8900 4050 9300 4050
Wire Wire Line
	8900 3950 9300 3950
Wire Wire Line
	8900 3850 9300 3850
Wire Wire Line
	8900 3750 9300 3750
Wire Wire Line
	8900 3650 9300 3650
Wire Wire Line
	8900 3550 9300 3550
Wire Wire Line
	8900 3450 9300 3450
Wire Wire Line
	9300 3350 8900 3350
Wire Wire Line
	8050 3350 8100 3350
Wire Wire Line
	8050 2750 8050 3350
Wire Wire Line
	8100 3550 8000 3550
Wire Wire Line
	7850 3650 8100 3650
$Comp
L power:VCC #PWR?
U 1 1 5F938C17
P 7850 3650
AR Path="/5F938C17" Ref="#PWR?"  Part="1" 
AR Path="/5F8E5C53/5F938C17" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7850 3500 50  0001 C CNN
F 1 "VCC" H 7865 3823 50  0000 C CNN
F 2 "" H 7850 3650 50  0001 C CNN
F 3 "" H 7850 3650 50  0001 C CNN
	1    7850 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 4500 8500 4450
$Comp
L power:GND #PWR?
U 1 1 5F938C1E
P 8500 4500
AR Path="/5F938C1E" Ref="#PWR?"  Part="1" 
AR Path="/5F8E5C53/5F938C1E" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 8500 4250 50  0001 C CNN
F 1 "GND" H 8505 4327 50  0000 C CNN
F 2 "" H 8500 4500 50  0001 C CNN
F 3 "" H 8500 4500 50  0001 C CNN
	1    8500 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 3000 8500 3150
$Comp
L power:VCC #PWR?
U 1 1 5F938C25
P 8500 3000
AR Path="/5F938C25" Ref="#PWR?"  Part="1" 
AR Path="/5F8E5C53/5F938C25" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 8500 2850 50  0001 C CNN
F 1 "VCC" H 8515 3173 50  0000 C CNN
F 2 "" H 8500 3000 50  0001 C CNN
F 3 "" H 8500 3000 50  0001 C CNN
	1    8500 3000
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC595 U?
U 1 1 5F938C2B
P 8500 3750
AR Path="/5F938C2B" Ref="U?"  Part="1" 
AR Path="/5F8E5C53/5F938C2B" Ref="U?"  Part="1" 
F 0 "U?" H 8650 4450 50  0000 C CNN
F 1 "74HC595" H 8700 4350 50  0000 C CNN
F 2 "" H 8500 3750 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 8500 3750 50  0001 C CNN
	1    8500 3750
	1    0    0    -1  
$EndComp
Text Label 9000 2050 0    50   ~ 0
Out7
Text Label 9000 1950 0    50   ~ 0
Out6
Text Label 9000 1850 0    50   ~ 0
Out5
Text Label 9000 1750 0    50   ~ 0
Out4
Text Label 9000 1650 0    50   ~ 0
Out3
Text Label 9000 1550 0    50   ~ 0
Out2
Text Label 9000 1450 0    50   ~ 0
Out1
Text Label 9000 1350 0    50   ~ 0
Out0
Wire Wire Line
	8900 2050 9300 2050
Wire Wire Line
	8900 1950 9300 1950
Wire Wire Line
	8900 1850 9300 1850
Wire Wire Line
	8900 1750 9300 1750
Wire Wire Line
	8900 1650 9300 1650
Wire Wire Line
	8900 1550 9300 1550
Wire Wire Line
	8900 1450 9300 1450
Wire Wire Line
	9300 1350 8900 1350
Entry Wire Line
	9300 2050 9400 2150
Entry Wire Line
	9300 1950 9400 2050
Entry Wire Line
	9300 1850 9400 1950
Entry Wire Line
	9300 1750 9400 1850
Entry Wire Line
	9300 1650 9400 1750
Entry Wire Line
	9300 1550 9400 1650
Entry Wire Line
	9300 1450 9400 1550
Entry Wire Line
	9300 1350 9400 1450
Wire Wire Line
	8050 1350 8100 1350
Wire Wire Line
	8050 750  8050 1350
Wire Wire Line
	9550 750  8050 750 
Wire Wire Line
	9550 2550 9550 750 
Wire Wire Line
	9600 700  9600 2650
Wire Wire Line
	8000 700  9600 700 
Wire Wire Line
	8000 1550 8000 700 
Wire Wire Line
	8100 1550 8000 1550
Wire Wire Line
	9650 650  9650 2250
Wire Wire Line
	7650 650  9650 650 
Wire Wire Line
	7850 1650 8100 1650
$Comp
L power:VCC #PWR?
U 1 1 5F938C54
P 7850 1650
AR Path="/5F938C54" Ref="#PWR?"  Part="1" 
AR Path="/5F8E5C53/5F938C54" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7850 1500 50  0001 C CNN
F 1 "VCC" H 7865 1823 50  0000 C CNN
F 2 "" H 7850 1650 50  0001 C CNN
F 3 "" H 7850 1650 50  0001 C CNN
	1    7850 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 2500 8500 2450
$Comp
L power:GND #PWR?
U 1 1 5F938C5B
P 8500 2500
AR Path="/5F938C5B" Ref="#PWR?"  Part="1" 
AR Path="/5F8E5C53/5F938C5B" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 8500 2250 50  0001 C CNN
F 1 "GND" H 8505 2327 50  0000 C CNN
F 2 "" H 8500 2500 50  0001 C CNN
F 3 "" H 8500 2500 50  0001 C CNN
	1    8500 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 1000 8500 1150
$Comp
L power:VCC #PWR?
U 1 1 5F938C62
P 8500 1000
AR Path="/5F938C62" Ref="#PWR?"  Part="1" 
AR Path="/5F8E5C53/5F938C62" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 8500 850 50  0001 C CNN
F 1 "VCC" H 8515 1173 50  0000 C CNN
F 2 "" H 8500 1000 50  0001 C CNN
F 3 "" H 8500 1000 50  0001 C CNN
	1    8500 1000
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC595 U?
U 1 1 5F938C68
P 8500 1750
AR Path="/5F938C68" Ref="U?"  Part="1" 
AR Path="/5F8E5C53/5F938C68" Ref="U?"  Part="1" 
F 0 "U?" H 8650 2450 50  0000 C CNN
F 1 "74HC595" H 8700 2350 50  0000 C CNN
F 2 "" H 8500 1750 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 8500 1750 50  0001 C CNN
	1    8500 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 4250 9000 4250
Wire Wire Line
	9000 4250 9000 4850
$Comp
L Device:C C?
U 1 1 5F938E15
P 7300 1150
AR Path="/5F938E15" Ref="C?"  Part="1" 
AR Path="/5F8E5C53/5F938E15" Ref="C?"  Part="1" 
F 0 "C?" H 7400 1150 50  0000 L CNN
F 1 "100n" H 7350 1250 50  0000 L CNN
F 2 "" H 7338 1000 50  0001 C CNN
F 3 "~" H 7300 1150 50  0001 C CNN
	1    7300 1150
	-1   0    0    1   
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 5F938E1B
P 7300 1000
AR Path="/5F938E1B" Ref="#PWR?"  Part="1" 
AR Path="/5F8E5C53/5F938E1B" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7300 850 50  0001 C CNN
F 1 "VCC" H 7315 1173 50  0000 C CNN
F 2 "" H 7300 1000 50  0001 C CNN
F 3 "" H 7300 1000 50  0001 C CNN
	1    7300 1000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F938E21
P 7300 1300
AR Path="/5F938E21" Ref="#PWR?"  Part="1" 
AR Path="/5F8E5C53/5F938E21" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7300 1050 50  0001 C CNN
F 1 "GND" H 7305 1127 50  0000 C CNN
F 2 "" H 7300 1300 50  0001 C CNN
F 3 "" H 7300 1300 50  0001 C CNN
	1    7300 1300
	1    0    0    -1  
$EndComp
Text HLabel 10100 2250 2    50   Input ~ 0
latch
Text HLabel 10100 2650 2    50   Input ~ 0
clock
Text HLabel 10100 2550 2    50   Input ~ 0
data
Wire Wire Line
	9550 2550 10100 2550
Wire Wire Line
	10100 2250 9650 2250
Wire Wire Line
	9600 2650 10100 2650
Text GLabel 9400 5600 3    50   Input ~ 0
Relaiscard0
Text HLabel 9000 4850 3    50   Output ~ 0
data_out
Text HLabel 7050 1950 0    50   Input ~ 0
enable
Wire Wire Line
	7650 650  7650 1850
Connection ~ 7650 1850
Wire Wire Line
	7650 1850 7650 3850
Wire Wire Line
	7650 3850 8100 3850
Wire Wire Line
	8100 1850 7650 1850
$Comp
L power:GND #PWR?
U 1 1 5F938DA6
P 7650 4350
AR Path="/5F938DA6" Ref="#PWR?"  Part="1" 
AR Path="/5F8E5C53/5F938DA6" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7650 4100 50  0001 C CNN
F 1 "GND" H 7655 4177 50  0000 C CNN
F 2 "" H 7650 4350 50  0001 C CNN
F 3 "" H 7650 4350 50  0001 C CNN
	1    7650 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F938DAF
P 7650 4200
AR Path="/5F938DAF" Ref="C?"  Part="1" 
AR Path="/5F8E5C53/5F938DAF" Ref="C?"  Part="1" 
F 0 "C?" H 7750 4200 50  0000 L CNN
F 1 "100n" H 7700 4300 50  0000 L CNN
F 2 "" H 7688 4050 50  0001 C CNN
F 3 "~" H 7650 4200 50  0001 C CNN
	1    7650 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 4050 7650 3850
Connection ~ 7650 3850
Wire Wire Line
	8100 3950 7450 3950
Wire Wire Line
	7450 3950 7450 1950
Wire Wire Line
	7450 1950 8100 1950
Wire Wire Line
	7450 1950 7050 1950
Connection ~ 7450 1950
Wire Bus Line
	9400 1450 9400 5600
$EndSCHEMATC
