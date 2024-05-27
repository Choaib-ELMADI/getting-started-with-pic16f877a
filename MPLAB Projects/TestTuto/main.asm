list p=16f877a
include "p16f877a.inc"

	cblock 0x20
		num1: 1
		num2: 1
	endc

	movlw 0x00
	movwf num1

	bsf STATUS, 5
	bsf STATUS, 6

	main:
		bsf STATUS, 5
		bsf STATUS, 6
		goto main
	
end