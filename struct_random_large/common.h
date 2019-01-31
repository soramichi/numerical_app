#if !defined(__COMMON_H)
#define __COMMON_H

#define PADDING_SIZE 2

#define ID_TYPE long
#define SCORE_DECLARATION struct {    \
    double score;		      \
    double __padding__[PADDING_SIZE]; \
  }

typedef ID_TYPE id_type;
typedef SCORE_DECLARATION score_type;

#undef ID_TYPE
#undef SCORE_TYPE

#endif
