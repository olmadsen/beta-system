/*********************************************************
 *                                                       *
 * Decide which architecture this is being compiled on   *
 * and supply sundry categories of architectures         *
 *                                                       *
 *********************************************************

/* Ensure that exactly one architecture symbol is defined */
 
#if defined(sun3)
#  define A_SUN3
#  undef  A_SUN4
#  undef  A_SUN4S
#  undef  A_OLDHP
#  undef  A_HPUX8
#  undef  A_SNAKE
#  undef  A_LINUX
#  undef  A_NT
#endif /* sun3 */

#if defined(sun4)
#  undef  A_SUN3
#  define A_SUN4
#  undef  A_SUN4S
#  undef  A_OLDHP
#  undef  A_HPUX8
#  undef  A_SNAKE
#  undef  A_LINUX
#  undef  A_NT
#endif /* sun4 */

#if defined(sun4s)
#  undef  A_SUN3
#  undef  A_SUN4
#  define A_SUN4S
#  undef  A_OLDHP
#  undef  A_HPUX8
#  undef  A_SNAKE
#  undef  A_LINUX
#  undef  A_NT
#endif /* sun4s */

#if defined(hp)
#  undef  A_SUN3
#  undef  A_SUN4
#  undef  A_SUN4S
#  define A_OLDHP
#  undef  A_HPUX8
#  undef  A_SNAKE
#  undef  A_LINUX
#  undef  A_NT
#endif /* hp */

#if defined(hpux8)
#  undef  A_SUN3
#  undef  A_SUN4
#  undef  A_SUN4S
#  undef  A_OLDHP
#  define A_HPUX8
#  undef  A_SNAKE
#  undef  A_LINUX
#  undef  A_NT
#endif /* hpux8 */

#if defined(hpux9mc)
#  undef  A_SUN3
#  undef  A_SUN4
#  undef  A_SUN4S
#  undef  A_OLDHP
#  define A_HPUX8
#  undef  A_SNAKE
#  undef  A_LINUX
#  undef  A_NT
#endif /* hpux8 */

#if defined(snake)
#  undef  A_SUN3
#  undef  A_SUN4
#  undef  A_SUN4S
#  undef  A_OLDHP
#  undef  A_HPUX8
#  define A_SNAKE
#  undef  A_LINUX
#  undef  A_NT
#endif /* snake */

#if defined(hpux9pa) /* datpete 22/8/94 */
#  undef  A_SUN3
#  undef  A_SUN4
#  undef  A_SUN4S
#  undef  A_OLDHP
#  undef  A_HPUX8
#  define A_SNAKE
#  undef  A_LINUX
#  undef  A_NT
#endif /* hpux9pa */


#if defined(linux) /* !!! new architecture - this might be wrong */
#  undef  A_SUN3
#  undef  A_SUN4
#  undef  A_SUN4S
#  undef  A_OLDHP
#  undef  A_HPUX8
#  undef  A_SNAKE
#  define A_LINUX
#  undef  A_NT
#endif /* linux */

#if defined(nt) /* !!! new architecture - this might be wrong */
#  undef  A_SUN3
#  undef  A_SUN4
#  undef  A_SUN4S
#  undef  A_OLDHP
#  undef  A_HPUX8
#  undef  A_SNAKE
#  undef  A_LINUX
#  define A_NT
#endif /* nt */

#if defined(A_SUN3) || defined(A_SUN4)
#  define A_SUN34
#endif

#if defined(A_SUN34) || defined(A_SUN4S)
#  define A_SUN
#endif

#if defined(A_OLDHP) || defined(A_HPUX8) || defined(A_SNAKE)
#  define A_HP
#endif

#if defined(A_SUN) || defined(A_HP)
#  define A_BIGEND
#endif

#if defined(A_LINUX) || defined(A_NT)
#  define A_LITTLEEND
#endif

#define ARCH_UNKNOWN "Unknown architecture"
