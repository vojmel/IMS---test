#include "data.h"


tExperimentData dataDB;
tExperimentData dataJava;


#ifdef USE_RAM512// Data pro DB ram 512
dataDB = {
        512,
        {//             rows  prav  1           10                      100     1000
                {100, 0.5, {2112786, 1292222, 1086848, 834386}},
                {200, 0.5, {9176030, 2694589, 1374892, 391202}},
        },
};

// Data pro DB ram 512
dataJava = {
        512,
        {
                {100, 0.5, {72162, 78375, 79187, 128254}},
                {200, 0.5, {113142, 121290, 116850, 107490}},
        },
};
#elif defined USE_RAM1024// Data pro DB ram 512
dataDB = {
        512,
        {//             rows  prav  1           10                      100     1000
                {100, 0.5, {2112786, 1292222, 1086848, 834386}},
                {200, 0.5, {9176030, 2694589, 1374892, 391202}},
        },
};

// Data pro DB ram 512
dataJava = {
        512,
        {
                {100, 0.5, {72162, 78375, 79187, 128254}},
                {200, 0.5, {113142, 121290, 116850, 107490}},
        },
};
#elif defined  USE_RAM1548// Data pro DB ram 512
dataDB = {
        512,
        {//             rows  prav  1           10                      100     1000
                {100, 0.5, {2112786, 1292222, 1086848, 834386}},
                {200, 0.5, {9176030, 2694589, 1374892, 391202}},
        },
};

// Data pro DB ram 512
dataJava = {
        512,
        {
                {100, 0.5, {72162, 78375, 79187, 128254}},
                {200, 0.5, {113142, 121290, 116850, 107490}},
        },
};
#endif

dataDbJava = {dataDB, dataJava};

dataDbJava.db = dataDB;
dataDbJava.java = dataJava;