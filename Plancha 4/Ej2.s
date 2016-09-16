.text
.arm
.global campesino

campesino:
        mov r3, #0

loop:
        cmp r1, #1
        beq exit
        ands r4, r1, #1
        addne r3, r3, r0
        subne r1, r1, #1
        lsleq r0, r0, #1
        lsreq r1, r1, #1
        bal loop
exit:
        add r0, r3, r0
        bx lr


