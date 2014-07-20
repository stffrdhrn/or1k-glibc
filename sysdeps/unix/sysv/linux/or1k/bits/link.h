#ifndef _LINK_H
# error "Never include <bits/link.h> directly; use <link.h> instead."
#endif

/* Registers for entry into PLT.  */
typedef struct La_or1k_regs
{
  uint32_t lr_reg[31];
} La_or1k_regs;

/* Return values for calls from PLT.  */
typedef struct La_or1k_retval
{
  uint32_t lr_r3;
} La_or1k_retval;


__BEGIN_DECLS

extern ElfW(Addr) la_or1k_gnu_pltenter (ElfW(Sym) *__sym, unsigned int __ndx,
                                        uintptr_t *__refcook,
                                        uintptr_t *__defcook,
                                        La_or1k_regs *__regs,
                                        unsigned int *__flags,
                                        const char *__symname,
                                        long int *__framesizep);
extern unsigned int la_or1k_gnu_pltexit (ElfW(Sym) *__sym, unsigned int __ndx,
                                         uintptr_t *__refcook,
                                         uintptr_t *__defcook,
                                         const La_or1k_regs *__inregs,
                                         La_or1k_retval *__outregs,
                                         const char *__symname);

__END_DECLS
