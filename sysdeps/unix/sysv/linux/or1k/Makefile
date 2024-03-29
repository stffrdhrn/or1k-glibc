ifeq ($(subdir),misc)
sysdep_routines += or1k_clone
endif

ifeq ($(subdir),stdlib)
gen-as-const-headers += ucontext_i.sym
endif

abi-variants := soft hard

ifeq (,$(filter $(default-abi),$(abi-variants)))
Unknown ABI, must be one of $(abi-variants)
endif

abi-includes :=
abi-soft-condition := !defined __or1k_hard_float__
abi-hard-condition := defined __or1k_hard_float__
