#ifndef PARAM_PARSE_H
#define PARAM_PARSE_H

#include <iostream>
#include <string>
#include <getopt.h>
 
namespace parse {

class Parse {
public :
    std::string config_file;
    std::string model_file;

    bool be_fill;
};

void printHelp()
{
    std::cout << "--config_file <str>:           gstreamer pipeline`s configure file\n\t\
                                you not need to set other param if set it\n"
        "--model_file <str>:     model file path for inference\n"
        "--help:              Show help\n";
    exit(1);
}
 
Parse parseArgs(int argc, char** argv)
{
    const char* const short_opts = "c:m:h:?";
    const option long_opts[] = {
        {"config_file", required_argument, nullptr, 'c'},
        {"model_file", required_argument, nullptr, 'm'},
        {"help", no_argument, nullptr, '?'},
        {nullptr, no_argument, nullptr, 0}
    };
    Parse param_set;
    while (true)
    {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);
 
        if (-1 == opt)
            break;
 
        switch (opt) {
            case 'c':param_set.config_file = std::string(optarg);break;
            case 'm':param_set.model_file = std::string(optarg);break;
            case '?': // Unrecognized option
            default:
                printHelp();
                param_set.be_fill = false;
                break;
        }
    }
    if(!param_set.config_file.empty() && !param_set.model_file.empty()) {
        param_set.be_fill = true;
    }
    return param_set;
}
}
#endif