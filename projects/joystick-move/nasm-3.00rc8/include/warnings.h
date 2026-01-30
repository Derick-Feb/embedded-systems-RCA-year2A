#ifndef NASM_WARNINGS_H
#define NASM_WARNINGS_H

#ifndef WARN_SHR
# error "warnings.h should only be included from within error.h"
#endif

enum warn_index {
	WARN_IDX_NONE                    =   0, /* not suppressible */
	WARN_IDX_DB_EMPTY                =   1, /* no operand for data declaration */
	WARN_IDX_EA_ABSOLUTE             =   2, /* absolute address cannot be RIP-relative */
	WARN_IDX_EA_DISPSIZE             =   3, /* displacement size ignored on absolute address */
	WARN_IDX_FLOAT_DENORM            =   4, /* floating point denormal */
	WARN_IDX_FLOAT_OVERFLOW          =   5, /* floating point overflow */
	WARN_IDX_FLOAT_TOOLONG           =   6, /* too many digits in floating-point number */
	WARN_IDX_FLOAT_UNDERFLOW         =   7, /* floating point underflow */
	WARN_IDX_FORWARD                 =   8, /* forward reference may have unpredictable results */
	WARN_IDX_IMPLICIT_ABS_DEPRECATED =   9, /* implicit DEFAULT ABS is deprecated */
	WARN_IDX_LABEL_ORPHAN            =  10, /* labels alone on lines without trailing \c{:} */
	WARN_IDX_LABEL_REDEF             =  11, /* label redefined to an identical value */
	WARN_IDX_LABEL_REDEF_LATE        =  12, /* label (re)defined during code generation */
	WARN_IDX_NUMBER_DEPRECATED_HEX   =  13, /* $ prefix for hexadecimal is deprecated */
	WARN_IDX_NUMBER_OVERFLOW         =  14, /* numeric constant does not fit */
	WARN_IDX_OBSOLETE_NOP            =  15, /* instruction obsolete and is a noop on the target CPU */
	WARN_IDX_OBSOLETE_REMOVED        =  16, /* instruction obsolete and removed on the target CPU */
	WARN_IDX_OBSOLETE_VALID          =  17, /* instruction obsolete but valid on the target CPU */
	WARN_IDX_PHASE                   =  18, /* phase error during stabilization */
	WARN_IDX_PP_ELSE_ELIF            =  19, /* \c{%elif} after \c{%else} */
	WARN_IDX_PP_ELSE_ELSE            =  20, /* \c{%else} after \c{%else} */
	WARN_IDX_PP_EMPTY_BRACES         =  21, /* empty \c{%\{\}} construct */
	WARN_IDX_PP_ENVIRONMENT          =  22, /* nonexistent environment variable */
	WARN_IDX_PP_MACRO_DEF_CASE_SINGLE =  23, /* single-line macro defined both case sensitive and insensitive */
	WARN_IDX_PP_MACRO_DEF_GREEDY_SINGLE =  24, /* single-line macro */
	WARN_IDX_PP_MACRO_DEF_PARAM_SINGLE =  25, /* single-line macro defined with and without parameters */
	WARN_IDX_PP_MACRO_DEFAULTS       =  26, /* macros with more default than optional parameters */
	WARN_IDX_PP_MACRO_PARAMS_LEGACY  =  27, /* improperly calling multi-line macro for legacy support */
	WARN_IDX_PP_MACRO_PARAMS_MULTI   =  28, /* multi-line macro calls with wrong parameter count */
	WARN_IDX_PP_MACRO_PARAMS_SINGLE  =  29, /* single-line macro calls with wrong parameter count */
	WARN_IDX_PP_MACRO_REDEF_MULTI    =  30, /* redefining multi-line macro */
	WARN_IDX_PP_OPEN_BRACES          =  31, /* unterminated \c{%\{...\}} */
	WARN_IDX_PP_OPEN_BRACKETS        =  32, /* unterminated \c{%[...]} */
	WARN_IDX_PP_OPEN_STRING          =  33, /* unterminated string */
	WARN_IDX_PP_REP_NEGATIVE         =  34, /* regative \c{%rep} count */
	WARN_IDX_PP_SEL_RANGE            =  35, /* \c{%sel()} argument out of range */
	WARN_IDX_PP_TRAILING             =  36, /* trailing garbage ignored */
	WARN_IDX_PRAGMA_BAD              =  37, /* malformed \c{%pragma} */
	WARN_IDX_PRAGMA_EMPTY            =  38, /* empty \c{%pragma} directive */
	WARN_IDX_PRAGMA_NA               =  39, /* \c{%pragma} not applicable to this compilation */
	WARN_IDX_PRAGMA_UNKNOWN          =  40, /* unknown \c{%pragma} facility or directive */
	WARN_IDX_PREFIX_BND              =  41, /* invalid \c{BND} prefix */
	WARN_IDX_PREFIX_HINT_DROPPED     =  42, /* invalid branch hint prefix dropped */
	WARN_IDX_PREFIX_HLE              =  43, /* invalid HLE prefix */
	WARN_IDX_PREFIX_INVALID          =  44, /* invalid prefix for instruction */
	WARN_IDX_PREFIX_LOCK_ERROR       =  45, /* \c{LOCK} prefix on unlockable instruction */
	WARN_IDX_PREFIX_LOCK_XCHG        =  46, /* superfluous \c{LOCK} prefix on \c{XCHG} instruction */
	WARN_IDX_PREFIX_OPSIZE           =  47, /* invalid operand size prefix */
	WARN_IDX_PREFIX_SEG              =  48, /* segment prefix ignored in 64-bit mode */
	WARN_IDX_PTR                     =  49, /* non-NASM keyword used in other assemblers */
	WARN_IDX_REGSIZE                 =  50, /* register size specification ignored */
	WARN_IDX_RELOC_ABS_BYTE          =  51, /* 8-bit absolute section-crossing relocation */
	WARN_IDX_RELOC_ABS_DWORD         =  52, /* 32-bit absolute section-crossing relocation */
	WARN_IDX_RELOC_ABS_QWORD         =  53, /* 64-bit absolute section-crossing relocation */
	WARN_IDX_RELOC_ABS_WORD          =  54, /* 16-bit absolute section-crossing relocation */
	WARN_IDX_RELOC_REL_BYTE          =  55, /* 8-bit relative section-crossing relocation */
	WARN_IDX_RELOC_REL_DWORD         =  56, /* 32-bit relative section-crossing relocation */
	WARN_IDX_RELOC_REL_QWORD         =  57, /* 64-bit relative section-crossing relocation */
	WARN_IDX_RELOC_REL_WORD          =  58, /* 16-bit relative section-crossing relocation */
	WARN_IDX_SECTION_ALIGNMENT_ROUNDED =  59, /* section alignment rounded up */
	WARN_IDX_UNKNOWN_WARNING         =  60, /* unknown warning in \c{-W}/\c{-w} or warning directive */
	WARN_IDX_USER                    =  61, /* \c{%warning} directives */
	WARN_IDX_WARN_STACK_EMPTY        =  62, /* warning stack empty */
	WARN_IDX_ZEROING                 =  63, /* \c{RES}\e{x} in initialized section becomes zero */
	WARN_IDX_ZEXT_RELOC              =  64, /* relocation zero-extended to match output format */
	WARN_IDX_OTHER                   =  65, /* any warning not specifically mentioned above */
	WARN_IDX_ALL                     =  66  /* all possible warnings */
};

enum warn_const {
	WARN_NONE                        =   0 << WARN_SHR,
	WARN_DB_EMPTY                    =   1 << WARN_SHR,
	WARN_EA_ABSOLUTE                 =   2 << WARN_SHR,
	WARN_EA_DISPSIZE                 =   3 << WARN_SHR,
	WARN_FLOAT_DENORM                =   4 << WARN_SHR,
	WARN_FLOAT_OVERFLOW              =   5 << WARN_SHR,
	WARN_FLOAT_TOOLONG               =   6 << WARN_SHR,
	WARN_FLOAT_UNDERFLOW             =   7 << WARN_SHR,
	WARN_FORWARD                     =   8 << WARN_SHR,
	WARN_IMPLICIT_ABS_DEPRECATED     =   9 << WARN_SHR,
	WARN_LABEL_ORPHAN                =  10 << WARN_SHR,
	WARN_LABEL_REDEF                 =  11 << WARN_SHR,
	WARN_LABEL_REDEF_LATE            =  12 << WARN_SHR,
	WARN_NUMBER_DEPRECATED_HEX       =  13 << WARN_SHR,
	WARN_NUMBER_OVERFLOW             =  14 << WARN_SHR,
	WARN_OBSOLETE_NOP                =  15 << WARN_SHR,
	WARN_OBSOLETE_REMOVED            =  16 << WARN_SHR,
	WARN_OBSOLETE_VALID              =  17 << WARN_SHR,
	WARN_PHASE                       =  18 << WARN_SHR,
	WARN_PP_ELSE_ELIF                =  19 << WARN_SHR,
	WARN_PP_ELSE_ELSE                =  20 << WARN_SHR,
	WARN_PP_EMPTY_BRACES             =  21 << WARN_SHR,
	WARN_PP_ENVIRONMENT              =  22 << WARN_SHR,
	WARN_PP_MACRO_DEF_CASE_SINGLE    =  23 << WARN_SHR,
	WARN_PP_MACRO_DEF_GREEDY_SINGLE  =  24 << WARN_SHR,
	WARN_PP_MACRO_DEF_PARAM_SINGLE   =  25 << WARN_SHR,
	WARN_PP_MACRO_DEFAULTS           =  26 << WARN_SHR,
	WARN_PP_MACRO_PARAMS_LEGACY      =  27 << WARN_SHR,
	WARN_PP_MACRO_PARAMS_MULTI       =  28 << WARN_SHR,
	WARN_PP_MACRO_PARAMS_SINGLE      =  29 << WARN_SHR,
	WARN_PP_MACRO_REDEF_MULTI        =  30 << WARN_SHR,
	WARN_PP_OPEN_BRACES              =  31 << WARN_SHR,
	WARN_PP_OPEN_BRACKETS            =  32 << WARN_SHR,
	WARN_PP_OPEN_STRING              =  33 << WARN_SHR,
	WARN_PP_REP_NEGATIVE             =  34 << WARN_SHR,
	WARN_PP_SEL_RANGE                =  35 << WARN_SHR,
	WARN_PP_TRAILING                 =  36 << WARN_SHR,
	WARN_PRAGMA_BAD                  =  37 << WARN_SHR,
	WARN_PRAGMA_EMPTY                =  38 << WARN_SHR,
	WARN_PRAGMA_NA                   =  39 << WARN_SHR,
	WARN_PRAGMA_UNKNOWN              =  40 << WARN_SHR,
	WARN_PREFIX_BND                  =  41 << WARN_SHR,
	WARN_PREFIX_HINT_DROPPED         =  42 << WARN_SHR,
	WARN_PREFIX_HLE                  =  43 << WARN_SHR,
	WARN_PREFIX_INVALID              =  44 << WARN_SHR,
	WARN_PREFIX_LOCK_ERROR           =  45 << WARN_SHR,
	WARN_PREFIX_LOCK_XCHG            =  46 << WARN_SHR,
	WARN_PREFIX_OPSIZE               =  47 << WARN_SHR,
	WARN_PREFIX_SEG                  =  48 << WARN_SHR,
	WARN_PTR                         =  49 << WARN_SHR,
	WARN_REGSIZE                     =  50 << WARN_SHR,
	WARN_RELOC_ABS_BYTE              =  51 << WARN_SHR,
	WARN_RELOC_ABS_DWORD             =  52 << WARN_SHR,
	WARN_RELOC_ABS_QWORD             =  53 << WARN_SHR,
	WARN_RELOC_ABS_WORD              =  54 << WARN_SHR,
	WARN_RELOC_REL_BYTE              =  55 << WARN_SHR,
	WARN_RELOC_REL_DWORD             =  56 << WARN_SHR,
	WARN_RELOC_REL_QWORD             =  57 << WARN_SHR,
	WARN_RELOC_REL_WORD              =  58 << WARN_SHR,
	WARN_SECTION_ALIGNMENT_ROUNDED   =  59 << WARN_SHR,
	WARN_UNKNOWN_WARNING             =  60 << WARN_SHR,
	WARN_USER                        =  61 << WARN_SHR,
	WARN_WARN_STACK_EMPTY            =  62 << WARN_SHR,
	WARN_ZEROING                     =  63 << WARN_SHR,
	WARN_ZEXT_RELOC                  =  64 << WARN_SHR,
	WARN_OTHER                       =  65 << WARN_SHR
};

struct warning_alias {
	const char *name;
	enum warn_index warning;
};

#define NUM_WARNING_ALIAS 82
extern const char * const warning_name[67];
extern const char * const warning_help[67];
extern const struct warning_alias warning_alias[NUM_WARNING_ALIAS];
extern const uint8_t warning_default[66];
extern uint8_t warning_state[66];

#endif /* NASM_WARNINGS_H */
