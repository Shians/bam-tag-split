#include "split_options.hpp"

options_t PRG_OPTS;

namespace fs = boost::filesystem;

void parse_args(int &argc, char *argv[]) {
    try {  
        TCLAP::CmdLine cmd("Command description message", ' ', "0.9.3");

        // arguments are pushed into order, so inserted from last to first
        int_arg    threads("@", "threads", "number of threads", false, 1, "integer", cmd);
        switch_arg output_all("a", "all", "set flag if reads missing specified tag", cmd, false);
        string_arg split_prefix("p", "prefix", "prefix for split files", false, "", "string", cmd);
        string_arg tag("t", "tag", "BAM tag to split by", true, "", "string", cmd);
        string_arg bam("i", "input", "BAM file for splitting", true, "", "BAM file", cmd);

        cmd.parse(argc, argv);

        PRG_OPTS.threads = threads.getValue();
        PRG_OPTS.output_all = output_all.getValue();
        PRG_OPTS.split_prefix = split_prefix.getValue();
        PRG_OPTS.tag = tag.getValue();

        PRG_OPTS.bam = bam.getValue();

        if (PRG_OPTS.split_prefix == "") {
            PRG_OPTS.split_prefix = PRG_OPTS.bam.substr(0, PRG_OPTS.bam.length() - 4) + "_" + PRG_OPTS.tag;
        }

	} catch (TCLAP::ArgException &e) {
        throw e;
    }
}

void check_args() {
    bool files_missing = false;

    if (!fs::exists(PRG_OPTS.bam)) {
        std::cerr << fmt::format("BAM does not exist: {}\n", PRG_OPTS.bam) << std::endl;
        files_missing = true;
    }

    if (files_missing) {
        exit(EXIT_FAILURE);
    }
}

void print_args() {
    std::cout << fmt::format("BAM file: {}", PRG_OPTS.bam) << std::endl;
    std::cout << fmt::format("Tag for splitting: {}", PRG_OPTS.tag) << std::endl;
    std::cout << fmt::format("Split prefix: {}", PRG_OPTS.split_prefix) << std::endl;
    std::cout << fmt::format("Output untagged: {}", PRG_OPTS.output_all) << std::endl;
}
