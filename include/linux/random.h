/*
 * include/linux/random.h
 *
 * Include file for the random number generator.
 */
#ifndef _LINUX_RANDOM_H
#define _LINUX_RANDOM_H

#include <linux/list.h>
#include <uapi/linux/random.h>

struct random_ready_callback {
	struct list_head list;
	void (*func)(struct random_ready_callback *rdy);
	struct module *owner;
};

static inline void add_latent_entropy(void) {}
extern void add_device_randomness(const void *, unsigned int);
extern void add_input_randomness(unsigned int type, unsigned int code,
				 unsigned int value);
extern void add_interrupt_randomness(int irq, int irq_flags);

extern void get_random_bytes(void *buf, int nbytes);
extern void get_random_bytes_arch(void *buf, int nbytes);
extern int wait_for_random_bytes(void);
extern int add_random_ready_callback(struct random_ready_callback *rdy);
extern void del_random_ready_callback(struct random_ready_callback *rdy);
extern void get_random_bytes_arch(void *buf, int nbytes);

#ifndef MODULE
extern const struct file_operations random_fops, urandom_fops;
#endif

u32 get_random_u32(void);
u64 get_random_u64(void);
static inline unsigned int get_random_int(void)
{
	return get_random_u32();
}
static inline unsigned long get_random_long(void)
{
#if BITS_PER_LONG == 64
	return get_random_u64();
#else
	return get_random_u32();
#endif
}

unsigned long randomize_page(unsigned long start, unsigned long range);

u32 prandom_u32(void);
void prandom_bytes(void *buf, int nbytes);
void prandom_seed(u32 seed);

u32 prandom_u32_state(struct rnd_state *);
void prandom_bytes_state(struct rnd_state *state, void *buf, int nbytes);

/*
 * Handle minimum values for seeds
 */
static inline u32 __seed(u32 x, u32 m)
{
	return (x < m) ? x + m : x;
}

/**
 * prandom_seed_state - set seed for prandom_u32_state().
 * @state: pointer to state structure to receive the seed.
 * @seed: arbitrary 64-bit value to use as a seed.
 */
static inline void prandom_seed_state(struct rnd_state *state, u64 seed)
{
	u32 i = (seed >> 32) ^ (seed << 10) ^ seed;

	state->s1 = __seed(i, 2);
	state->s2 = __seed(i, 8);
	state->s3 = __seed(i, 16);
}

#ifdef CONFIG_ARCH_RANDOM
# include <asm/archrandom.h>
#else
static inline bool arch_get_random_long(unsigned long *v)
{
	return 0;
}
static inline bool arch_get_random_int(unsigned int *v)
{
	return 0;
}
static inline bool arch_has_random(void)
{
	return 0;
}
static inline bool arch_get_random_seed_long(unsigned long *v)
{
	return 0;
}
static inline bool arch_get_random_seed_int(unsigned int *v)
{
	return 0;
}
static inline bool arch_has_random_seed(void)
{
	return 0;
}
#endif

/* Pseudo random number generator from numerical recipes. */
static inline u32 next_pseudo_random32(u32 seed)
{
	return seed * 1664525 + 1013904223;
}

#endif /* _LINUX_RANDOM_H */
