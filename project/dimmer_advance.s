	.arch msp430g2553
	.p2align 1,0
	.text			; jt is constant (in flash)

	
	.extern changed
	.extern led_changed
	.extern red_led_on
	.extern both_off
	.extern led_update
	.global dimmer_advance
	
jt:
	.word case0		; jt[0]
	.word case1		; jt[1]

dimmer_advance:
	;; range check on selector (changed)
	cmp.b #2, &changed	; changed-2 doesn't borrow if changed>1
	jhs end			; jmp if changed > 1

	;; index into jt
	mov.b &changed, r12
	add.b r12, r12		; r12 = 2*changed
	mov jt(r12), r0		; jmp jt[changed]

	;; switch table options
	;; same order as in source
case0:	call #red_led_on	; red_led_on()
	add.b #1, &changed	; changed++
	jmp end			; break

case1:	call #both_off		; both_off()
	mov.b #0, &changed	; changed = 0
	jmp end			; break
end:	mov #1, &led_changed
	call #led_update	; led_update()
	pop r0
