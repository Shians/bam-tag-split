#define FMT_HEADER_ONLY
#pragma once
#include <fmt/format.h>

#include <algorithm>
#include <boost/filesystem.hpp>
#include <string>
#include <tclap/CmdLine.h>

struct options_t {
    int threads;
    bool output_all;
    std::string output;
    std::string tag;
    std::string bam;
};

extern options_t PRG_OPTS;

typedef TCLAP::ValueArg<std::string> string_arg;
typedef TCLAP::ValueArg<int> int_arg;
typedef TCLAP::SwitchArg switch_arg;

void parse_args(int &argc, char *argv[]);
void check_args();
void print_args();
