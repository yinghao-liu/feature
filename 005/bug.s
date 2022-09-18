	.arch armv8-a
	.file	"bug.c"
// GNU C17 (GCC) version 10.2.1 20200907 [ revision ce3001ff1d734e0763a1a5e434272bf89df1fe06] (aarch64-linux-gnu)
//	compiled by GNU C version 8.2.1 20180905 (Red Hat 8.2.1-3), GMP version 6.1.2, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.22-GMP

// GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
// options passed:  -imultiarch aarch64-linux-gnu
// -iprefix /opt/ambarella/linaro-aarch64-2020.09-gcc10.2-linux5.4/bin/../lib/gcc/aarch64-linux-gnu/10.2.1/
// -isysroot /opt/ambarella/linaro-aarch64-2020.09-gcc10.2-linux5.4/bin/../aarch64-linux-gnu/libc
// bug.c -march=armv8-a -mlittle-endian -mabi=lp64 -fverbose-asm
// options enabled:  -faggressive-loop-optimizations -fallocation-dce
// -fasynchronous-unwind-tables -fauto-inc-dec -fdelete-null-pointer-checks
// -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-symbols
// -feliminate-unused-debug-types -ffp-int-builtin-inexact -ffunction-cse
// -fgcse-lm -fgnu-unique -fident -finline-atomics -fipa-stack-alignment
// -fira-hoist-pressure -fira-share-save-slots -fira-share-spill-slots
// -fivopts -fkeep-static-consts -fleading-underscore -flifetime-dse
// -fmath-errno -fmerge-debug-strings -fomit-frame-pointer -fpeephole -fplt
// -fprefetch-loop-arrays -freg-struct-return
// -fsched-critical-path-heuristic -fsched-dep-count-heuristic
// -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
// -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
// -fsched-stalled-insns-dep -fschedule-fusion -fsemantic-interposition
// -fshow-column -fshrink-wrap-separate -fsigned-zeros
// -fsplit-ivs-in-unroller -fssa-backprop -fstdarg-opt
// -fstrict-volatile-bitfields -fsync-libcalls -ftrapping-math
// -ftree-cselim -ftree-forwprop -ftree-loop-if-convert -ftree-loop-im
// -ftree-loop-ivcanon -ftree-loop-optimize -ftree-parallelize-loops=
// -ftree-phiprop -ftree-reassoc -ftree-scev-cprop -funit-at-a-time
// -funwind-tables -fverbose-asm -fzero-initialized-in-bss
// -mfix-cortex-a53-835769 -mfix-cortex-a53-843419 -mglibc -mlittle-endian
// -momit-leaf-frame-pointer -moutline-atomics -mpc-relative-literal-loads

	.text
	.section	.rodata
	.align	3
.LC0:
	.string	"%04d%02d%02d%02d%2d%03lu"
	.align	3
.LC1:
	.string	"string: %s\n"
	.align	3
.LC2:
	.string	"expect: 193939393939099"
	.text
	.align	2
	.global	func
	.type	func, %function
func:
.LFB0:
	.cfi_startproc
	sub	sp, sp, #80	//,,
	.cfi_def_cfa_offset 80
	stp	x29, x30, [sp, 16]	//,,
	.cfi_offset 29, -64
	.cfi_offset 30, -56
	add	x29, sp, 16	//,,
// bug.c:5:     char string[32] = {}; 
	stp	xzr, xzr, [sp, 40]	// string
	stp	xzr, xzr, [sp, 56]	// string
// bug.c:6:     unsigned int a = 99; 
	mov	w0, 99	// tmp95,
	str	w0, [sp, 76]	// tmp95, a
// bug.c:7:     int val = 39;
	mov	w0, 39	// tmp96,
	str	w0, [sp, 72]	// tmp96, val
// bug.c:9:     snprintf(string, 32, "%04d%02d%02d%02d%2d%03lu", val+1900 ,val, val, val, val, a); 
	ldr	w0, [sp, 72]	// tmp97, val
	add	w1, w0, 1900	// _1, tmp97,
	add	x8, sp, 40	// tmp98,,
	ldr	w0, [sp, 76]	// tmp99, a
	str	w0, [sp]	// tmp99,
	ldr	w7, [sp, 72]	//, val
	ldr	w6, [sp, 72]	//, val
	ldr	w5, [sp, 72]	//, val
	ldr	w4, [sp, 72]	//, val
	mov	w3, w1	//, _1
	adrp	x0, .LC0	// tmp100,
	add	x2, x0, :lo12:.LC0	//, tmp100,
	mov	x1, 32	//,
	mov	x0, x8	//, tmp98
	bl	snprintf		//
// bug.c:10:     printf("string: %s\n", string);
	add	x0, sp, 40	// tmp101,,
	mov	x1, x0	//, tmp101
	adrp	x0, .LC1	// tmp102,
	add	x0, x0, :lo12:.LC1	//, tmp102,
	bl	printf		//
// bug.c:11:     printf("expect: 193939393939099\n");
	adrp	x0, .LC2	// tmp103,
	add	x0, x0, :lo12:.LC2	//, tmp103,
	bl	puts		//
// bug.c:12:     return 0;
	mov	w0, 0	// _9,
// bug.c:13: }
	ldp	x29, x30, [sp, 16]	//,,
	add	sp, sp, 80	//,,
	.cfi_restore 29
	.cfi_restore 30
	.cfi_def_cfa_offset 0
	ret	
	.cfi_endproc
.LFE0:
	.size	func, .-func
	.align	2
	.global	main
	.type	main, %function
main:
.LFB1:
	.cfi_startproc
	stp	x29, x30, [sp, -16]!	//,,,
	.cfi_def_cfa_offset 16
	.cfi_offset 29, -16
	.cfi_offset 30, -8
	mov	x29, sp	//,
// bug.c:16:     func();
	bl	func		//
// bug.c:17:     return 0;
	mov	w0, 0	// _3,
// bug.c:18: }
	ldp	x29, x30, [sp], 16	//,,,
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret	
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 10.2.1 20200907 [ revision ce3001ff1d734e0763a1a5e434272bf89df1fe06]"
	.section	.note.GNU-stack,"",@progbits
