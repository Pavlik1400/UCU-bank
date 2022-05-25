#define LOG_ARG_0() 
    #define LOG_ARG(arg0) "\n\t" #arg0 ": " << arg0 <<
    #define LOG_ARG_2(arg0, arg1) LOG_ARG(arg0) LOG_ARG(arg1)
    #define LOG_ARG_3(arg0,arg1,arg2) LOG_ARG_2(arg0, arg1) LOG_ARG(arg2)
    #define LOG_ARG_4(arg0,arg1,arg2,arg3) LOG_ARG_3(arg0, arg1, arg2) LOG_ARG(arg3)
    #define LOG_ARG_5(arg0,arg1,arg2,arg3, arg4) LOG_ARG_3(arg0, arg1, arg2, arg3) LOG_ARG(arg4)
    #define USE_NTH(_1, _2, _3, _4, _5, N, ...) N
    #define LOG_FUNC(func, ...) "\n" #func "(" USE_NTH(func, ##__VA_ARGS__, \
            LOG_ARG_4,  \
            LOG_ARG_3,  \
            LOG_ARG_2,  \
            LOG_ARG,    \
            LOG_ARG_0)(__VA_ARGS__) ")"