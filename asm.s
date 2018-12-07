	AREA MYCODE, CODE
			
		ENTRY
		EXPORT _save_state
		IMPORT mpsp
		IMPORT os_curr_task
		IMPORT os_next_task
		
		
_save_state
			cpsid i
			
			MRS r1, psp
			STMDB r1!, {r4-r11}
			MSR psp,r1
			LDR r0, =mpsp
			STR r1,[r0]
			
			LDR r0, =os_curr_task
			STR r1,[r0]
			
			LDR r0, =os_next_task
			LDR r2, [r0]
			LDMFD r2!, {r4-r11}
			MSR psp, r2
			cpsie	i

			ldr r1, =0xfffffffd
			bx r1
			END