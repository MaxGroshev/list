#if defined(DEBUG)
#define LIST_CHECK(condition)                                                                            \
        if (!(condition))                                                                                \
        {                                                                                                \
            list_check (box, __FILE__, __FUNCTION__, __LINE__ );                                         \
            exit (1);                                                                                    \
        }                                                                                                \

#else
#define LIST_CHECK;

#endif
