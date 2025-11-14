#ifndef __USER_DEF_H
#define __USER_DEF_H

#ifndef TRUE
# define TRUE                   ((u8)1)
#endif
#ifndef FALSE
# define FALSE                  ((u8)0)
#endif
#ifndef ENABLE
# define ENABLE                 ((u8)1)
#endif
#ifndef DISABLE
# define DISABLE                ((u8)0)
#endif
#ifndef SUCCESS
# define SUCCESS                ((u8)0)
#endif
#ifndef FAILED
# define FAILED                 ((u8)1)
#endif

#ifndef Bit_SET
#define Bit_SET                 (1)
#endif
#ifndef Bit_RESET
#define Bit_RESET               (0)
#endif

#define USER_UNUSED(x)          (void)(x)

#endif
