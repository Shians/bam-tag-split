#include "main.hpp"

using namespace std;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

const string translate_aux_type(char c) {
    switch (c) {
        case 'A': return("character");
        case 'I': return("integer");
        case 'Z': return("string");
        default: throw runtime_error("Aux type not recognised");
    }
}

string get_aux_type(string &bam) {
    samFile *fp_in = hts_open(bam.c_str(), "r");
    bam_hdr_t *bam_hdr = sam_hdr_read(fp_in);
    bam1_t *aln = bam_init1();

    const int BAM_COUNT_MAX = 10000;

    int bam_count = 0;

    while (sam_read1(fp_in, bam_hdr, aln) > 0) {
        uint8_t *hap_ptr = bam_aux_get(aln, PRG_OPTS.tag.c_str());

        if (hap_ptr != nullptr) {
            char type = *hap_ptr;
            switch (type) {
                case 'A': return(translate_aux_type('A'));
                case 'C':
                case 'S':
                case 'c':
                case 's': return(translate_aux_type('I'));
                case 'z': return(translate_aux_type('S'));
                default: throw runtime_error("Only integer and string type tags accepted");
            }
        }

        bam_count++;
        if (bam_count == BAM_COUNT_MAX) {
            cout << "NOTE: No instance of tag found in first " << BAM_COUNT_MAX << " entries" << endl;
        }
    }

    throw runtime_error("Tag not found in bam file.");
}

void write_to_file(const bam1_t *b, BGZF *fp) {
    bam_write1(fp, b);
}

int main(int argc, char* argv[]) {
    parse_args(argc, argv);
    check_args();
    print_args();

    Timer timer;
    timer.start();

    // check tag type
    string aux_type = get_aux_type(PRG_OPTS.bam);
    cout << "Checking tag type..." << "\n";
    cout << "Tag type: " << aux_type << "\n";

    // initialise bam file
    samFile *fp_in = hts_open(PRG_OPTS.bam.c_str(), "r");
    bam_hdr_t *bam_hdr = sam_hdr_read(fp_in);
    bam1_t *aln = bam_init1();

    // set up thread pool
    htsThreadPool p = {NULL, 0};
    p.pool = hts_tpool_init(PRG_OPTS.threads);
    hts_set_opt(fp_in, HTS_OPT_THREAD_POOL, &p);

    // output files map
    unordered_map<string, BGZF*> file_map;

    BGZF *undetermined_file;
    if (PRG_OPTS.output_all) {
        // create file for tagless entries
        string fname = fmt::format("{}_undetermined.bam", PRG_OPTS.split_prefix).c_str();
        undetermined_file = bgzf_open(fname.c_str(), "w");
        bam_hdr_write(undetermined_file, bam_hdr);
    }

    while (sam_read1(fp_in, bam_hdr, aln) > 0) {
        uint8_t *hap_ptr = bam_aux_get(aln, PRG_OPTS.tag.c_str());

        if (hap_ptr == nullptr) {
            // if no tag found
            if (PRG_OPTS.output_all) {
                write_to_file(aln, undetermined_file);
            }
        } else {
            // convert tag value to string
            string hap_str;
            if (aux_type == "integer") {
                hap_str = to_string(bam_aux2i(hap_ptr));
            } else if (aux_type == "string") {
                hap_str = string(bam_aux2Z(hap_ptr));
            } else if (aux_type == "character") {
                hap_str = string(1, bam_aux2A(hap_ptr));
            }

            if (file_map.count(hap_str) == 0) {
                // if tag value not seen before
                // create new file
                string fname = fmt::format("{}_{}.bam", PRG_OPTS.split_prefix, hap_str);
                file_map[hap_str] = bgzf_open(fname.c_str(), "w");
                bam_hdr_write(file_map[hap_str], bam_hdr);
            }

            // write bam entry to matched tag file
            BGZF* out_file = file_map[hap_str];
            write_to_file(aln, out_file);
        }
    }

    // clean up
    bam_destroy1(aln);
    sam_close(fp_in);
    if (p.pool) hts_tpool_destroy(p.pool);
    for (auto x : file_map) { bgzf_close(x.second); }

    cout << "Time elapsed: " << timer.time_elapsed() << "\n";

    return 0;
}
