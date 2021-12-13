#ifndef COMMON_H
#define COMMON_H

namespace inference {
namespace snpe {

typedef enum {
    INIT_ERROR = -3,
    EXECUTE_ERROR = -2,
    INVALID_INPUT = -1,
    NO_ERROR = 0
}state_t;

typedef enum  {
    CPU         = 0,
    GPU         = 1,
    DSP         = 2,
    APU         = 3
}runtime_t;

typedef enum {
    NCHW = 0,
    NHWC = 1
} DataFormat;

}
}
#endif
