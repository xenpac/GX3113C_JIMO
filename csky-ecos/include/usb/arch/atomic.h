/*
 *  linux/include/asm-arm/atomic.h
 *
 *  Copyright (C) 1996 Russell King.
 *  Copyright (C) 2002 Deep Blue Solutions Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __ASM_ARM_ATOMIC_H
#define __ASM_ARM_ATOMIC_H

#include <usb/arch/system.h>

typedef struct { volatile int counter; } atomic_t;

#define ATOMIC_INIT(i)	{ (i) }
#define atomic_read(v)	((v)->counter)
#define atomic_set(v,i)	(((v)->counter) = (i))

static inline int atomic_add_return(int i, atomic_t *v)
{
	int val;
	unsigned int flag;

	local_irq_save(flag);
	val = v->counter;
	v->counter = val += i;
	local_irq_restore(flag);

	return val;
}

static inline int atomic_sub_return(int i, atomic_t *v)
{
	int val;
	unsigned int flag;

	local_irq_save(flag);
	val = v->counter;
	v->counter = val -= i;
	local_irq_restore(flag);

	return val;
}

static inline int atomic_cmpxchg(atomic_t *v, int old, int new)
{
	int ret;
	unsigned int flag;

	local_irq_save(flag);
	ret = v->counter;
	if (likely(ret == old))
		v->counter = new;
	local_irq_restore(flag);

	return ret;
}

static inline void atomic_clear_mask(unsigned long mask, unsigned long *addr)
{
	unsigned int flag;

	local_irq_save(flag);
	*addr &= ~mask;
	local_irq_restore(flag);
}

#define atomic_xchg(v, new) (xchg(&((v)->counter), new))

static inline int atomic_add_unless(atomic_t *v, int a, int u)
{
	int c, old;

	c = atomic_read(v);
	while (c != u && (old = atomic_cmpxchg((v), c, c + a)) != c)
		c = old;
	return c != u;
}

#define atomic_inc_not_zero(v) atomic_add_unless((v), 1, 0)

#define atomic_add(i, v)	(void) atomic_add_return(i, v)
#define atomic_inc(v)		(void) atomic_add_return(1, v)
#define atomic_sub(i, v)	(void) atomic_sub_return(i, v)
#define atomic_dec(v)		(void) atomic_sub_return(1, v)

#define atomic_inc_and_test(v)	(atomic_add_return(1, v) == 0)
#define atomic_dec_and_test(v)	(atomic_sub_return(1, v) == 0)
#define atomic_inc_return(v)    (atomic_add_return(1, v))
#define atomic_dec_return(v)    (atomic_sub_return(1, v))
#define atomic_sub_and_test(i, v) (atomic_sub_return(i, v) == 0)

#define atomic_add_negative(i,v) (atomic_add_return(i, v) < 0)

/* Atomic operations are already serializing on ARM */
#define smp_mb__before_atomic_dec()	barrier()
#define smp_mb__after_atomic_dec()	barrier()
#define smp_mb__before_atomic_inc()	barrier()
#define smp_mb__after_atomic_inc()	barrier()

#endif
