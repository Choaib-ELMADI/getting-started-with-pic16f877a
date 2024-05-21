list p=16f877a
include "p16f877a.inc"

cblock 0x20
	m: 1				; 1ère variable de la série
	n: 2				; 2ème variable de la série
	p: 1				; 3ème variable de la série
endc

org 0x00
goto main

main:
	bsf STATUS, RP0		; accéder au bank 1
	movlw 0x00			; clear w (sorties)
	movwf TRISB			; configuration en sorties
	bcf STATUS, RP0		; retourner au bank 0

	movlw 0x00
	movwf PORTB			; clear PORTB

	movwf m				; initialiser m à 0
	movlw 0x01
	movwf n				; initialiser n à 1

loop:
	addwf m, 0			; w(n) + m ==> w
	movwf p				; w ==> p 
	
	movf n, 0			; n ==> w
	movwf m				; w ==> m
	
	movf p, 0			; p ==> w
	movwf n				; w ==> n
		
	movf p, 0			; p ==> w
	movwf PORTB			; visualiser le résultat
	
	goto loop

end