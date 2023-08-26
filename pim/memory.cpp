#include "memory.h"
#include <iostream>

namespace pim{

    bool REGISTERS[CROSSBAR_R][NUM_CROSSBARS];
    size_t lastCrossbar = 0;

    address malloc(size_t n){

        pim::size_t numCrossbars = (n + CROSSBAR_HEIGHT - 1) / CROSSBAR_HEIGHT;

        // Search for free register
        for(size_t startCrossbar = lastCrossbar; startCrossbar != (lastCrossbar - 1) % NUM_CROSSBARS; startCrossbar++, startCrossbar %= NUM_CROSSBARS){
            size_t reg;
            for(reg = 0; reg < CROSSBAR_R; reg++){
                bool found = false;
                for(size_t crossbar = startCrossbar; crossbar < startCrossbar + numCrossbars; crossbar++){
                    if(REGISTERS[reg][crossbar]){
                        found = true; break;
                    }
                }
                if(!found) break;
            }
            if(reg < CROSSBAR_R) {
                for(size_t crossbar = startCrossbar; crossbar < startCrossbar + numCrossbars; crossbar++){
                    REGISTERS[reg][crossbar] = true;
                }

#ifdef VERBOSE
                std::cerr << "Allocated register " << reg << " from " << startCrossbar << " to " << startCrossbar + numCrossbars << std::endl;
#endif

                lastCrossbar = startCrossbar;

                return {startCrossbar, startCrossbar + numCrossbars, reg};

            }

        }

        std::cerr << "Out of Memory!" << std::endl;
        exit(1);

    }

    std::vector<address> mallocMulti(size_t n, size_t m){

        pim::size_t numCrossbars = (n + CROSSBAR_HEIGHT - 1) / CROSSBAR_HEIGHT;

        // Search for free register
        for(size_t startCrossbar = lastCrossbar; startCrossbar != (lastCrossbar - 1) % NUM_CROSSBARS; startCrossbar++, startCrossbar %= NUM_CROSSBARS){
            std::vector<size_t> regs;
            for(size_t reg = 0; reg < CROSSBAR_R; reg++){
                bool found = false;
                for(size_t crossbar = startCrossbar; crossbar < startCrossbar + numCrossbars; crossbar++){
                    if(REGISTERS[reg][crossbar]){
                        found = true; break;
                    }
                }
                if(!found) {
                    regs.push_back(reg);
                    if(regs.size() == m) break;
                }
            }
            if(regs.size() >= m) {
                for(size_t reg : regs) {
                    for (size_t crossbar = startCrossbar; crossbar < startCrossbar + numCrossbars; crossbar++) {
                        REGISTERS[reg][crossbar] = true;
                    }
                }

#ifdef VERBOSE
                std::cerr << "Allocated register " << reg << " from " << startCrossbar << " to " << startCrossbar + numCrossbars << std::endl;
#endif

                lastCrossbar = startCrossbar;

                std::vector<address> addresses;
                for(size_t reg : regs) addresses.push_back({startCrossbar, startCrossbar + numCrossbars, reg});
                return addresses;

            }

        }

        std::cerr << "Out of Memory!" << std::endl;
        exit(1);

    }

    void free(address vec){
        if(vec.reg != -1){
            for(size_t crossbar = vec.startArray; crossbar < vec.endArray; crossbar++){
                REGISTERS[vec.reg][crossbar] = false;
            }

#ifdef VERBOSE
            std::cerr << "Freed register " << vec.reg << std::endl;
#endif

        }
    }

}
