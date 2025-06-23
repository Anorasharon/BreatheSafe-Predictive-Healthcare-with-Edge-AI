#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class SVM {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        float kernels[12] = { 0 };
                        float decisions[3] = { 0 };
                        int votes[3] = { 0 };
                        kernels[0] = compute_kernel(x,   110.0  , 99.0 );
                        kernels[1] = compute_kernel(x,   115.0  , 103.0 );
                        kernels[2] = compute_kernel(x,   45.0  , 92.0 );
                        kernels[3] = compute_kernel(x,   109.0  , 94.0 );
                        kernels[4] = compute_kernel(x,   40.0  , 85.0 );
                        kernels[5] = compute_kernel(x,   107.0  , 93.0 );
                        kernels[6] = compute_kernel(x,   55.0  , 97.0 );
                        kernels[7] = compute_kernel(x,   103.0  , 91.0 );
                        kernels[8] = compute_kernel(x,   85.0  , 94.0 );
                        kernels[9] = compute_kernel(x,   55.0  , 93.0 );
                        kernels[10] = compute_kernel(x,   105.0  , 98.0 );
                        kernels[11] = compute_kernel(x,   65.0  , 98.0 );
                        decisions[0] = -4.113801612811
                        + kernels[0]
                        + kernels[1] * 0.377999839813
                        + kernels[2] * 0.468375170743
                        + kernels[3] * 0.412616565804
                        + kernels[4]
                        - kernels[5]
                        - kernels[6]
                        - kernels[7]
                        + kernels[9] * -0.25899157636
                        ;
                        decisions[1] = 2.701970053702
                        + kernels[0] * 0.787041625144
                        + kernels[1] * 0.080597336838
                        + kernels[2] * 0.132361038019
                        - kernels[10]
                        ;
                        decisions[2] = 26.175555116998
                        + kernels[6] * 0.185870845701
                        + kernels[8] * 0.086983532894
                        + kernels[11] * -0.272854378594
                        ;
                        votes[decisions[0] > 0 ? 0 : 1] += 1;
                        votes[decisions[1] > 0 ? 0 : 2] += 1;
                        votes[decisions[2] > 0 ? 1 : 2] += 1;
                        int val = votes[0];
                        int idx = 0;

                        for (int i = 1; i < 3; i++) {
                            if (votes[i] > val) {
                                val = votes[i];
                                idx = i;
                            }
                        }

                        return idx;
                    }

                protected:
                    /**
                    * Compute kernel between feature vector and support vector.
                    * Kernel type: poly
                    */
                    float compute_kernel(float *x, ...) {
                        va_list w;
                        va_start(w, 2);
                        float kernel = 0.0;

                        for (uint16_t i = 0; i < 2; i++) {
                            kernel += x[i] * va_arg(w, double);
                        }

                        return pow((0.001 * kernel) + 0.0, 3);
                    }
                };
            }
        }
    }
