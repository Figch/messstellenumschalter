EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
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
L MCU_Module:Arduino_UNO_R3 A?
U 1 1 5F4609A4
P 5450 2200
F 0 "A?" H 5450 3381 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 5300 3300 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 5450 2200 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 5450 2200 50  0001 C CNN
	1    5450 2200
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 5F46D766
P 5650 900
F 0 "#PWR?" H 5650 750 50  0001 C CNN
F 1 "VCC" H 5665 1073 50  0000 C CNN
F 2 "" H 5650 900 50  0001 C CNN
F 3 "" H 5650 900 50  0001 C CNN
	1    5650 900 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F46FB5D
P 5350 3500
F 0 "#PWR?" H 5350 3250 50  0001 C CNN
F 1 "GND" H 5355 3327 50  0000 C CNN
F 2 "" H 5350 3500 50  0001 C CNN
F 3 "" H 5350 3500 50  0001 C CNN
	1    5350 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 3500 5350 3400
Wire Wire Line
	5350 3400 5450 3400
Wire Wire Line
	5450 3400 5450 3300
Connection ~ 5350 3400
Wire Wire Line
	5350 3400 5350 3300
Wire Wire Line
	5450 3400 5550 3400
Wire Wire Line
	5550 3400 5550 3300
Connection ~ 5450 3400
$Sheet
S 3250 1550 600  1700
U 5F8E5C53
F0 "shiftRegisters" 50
F1 "shiftRegisters.sch" 50
F2 "latch" I R 3850 2400 50 
F3 "clock" I R 3850 2800 50 
F4 "data" I R 3850 2700 50 
$EndSheet
Wire Wire Line
	4950 2800 3850 2800
Wire Wire Line
	3850 2700 4950 2700
Wire Wire Line
	4950 2400 3850 2400
Wire Wire Line
	5650 1200 5650 900 
$EndSCHEMATC
