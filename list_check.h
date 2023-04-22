#if defined(DEBUG)
#define LIST_CHECK(condition, error_mes)                                                                 \
        if (!(condition))                                                                                \
        {                                                                                                \
            list_error (error_mes, CUR_POS_IN_PROG);                                                     \
            exit (1);                                                                                    \
        }                                                                                                \

#else
#define LIST_CHECK;

#endif
