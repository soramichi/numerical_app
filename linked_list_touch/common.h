#if !defined(__COMMON_H)
#define __COMMON_H

#define PADDING_SIZE 0

#define VALUE_DECLARATION struct {    \
    long value; 		      \
    long __padding__[PADDING_SIZE];   \
  }

typedef VALUE_DECLARATION value_type;

#undef ID_TYPE
#undef SCORE_TYPE

#endif
