#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <fstream>

#include <htslib/sam.h>
#include <htslib/hfile.h>
#include <htslib/bgzf.h>
#include <htslib/thread_pool.h>

#include "fmt/format.h"
#include "extract_options.hpp"
#include "Timer.hpp"
