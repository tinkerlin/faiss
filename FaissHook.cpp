
// -*- c++ -*-

#include <iostream>
#include <mutex>

#include <faiss/FaissHook.h>
#include <faiss/impl/FaissAssert.h>
// #include <faiss/impl/ScalarQuantizerDC.h>
// #include <faiss/impl/ScalarQuantizerDC_avx512.h>
#include <faiss/utils/distances.h>
#include <faiss/utils/distances_avx512.h>
// #include <faiss/utils/instruction_set.h>

namespace faiss {

bool faiss_use_avx512 = true;

/* set default to AVX */
fvec_func_ptr fvec_inner_product = fvec_inner_product_avx512;
fvec_func_ptr fvec_L2sqr = fvec_L2sqr_avx512;
fvec_func_ptr fvec_L1 = fvec_L1_avx512;
fvec_func_ptr fvec_Linf = fvec_Linf_avx512;

// sq_get_func_ptr sq_get_distance_computer_L2 = sq_get_distance_computer_L2_avx;
// sq_get_func_ptr sq_get_distance_computer_IP = sq_get_distance_computer_IP_avx;
// sq_sel_func_ptr sq_sel_quantizer = sq_select_quantizer_avx;


/*****************************************************************************/

bool support_avx512() {
    if (!faiss_use_avx512) return false;

    InstructionSet& instruction_set_inst = InstructionSet::GetInstance();
    return (instruction_set_inst.AVX512F() &&
            instruction_set_inst.AVX512DQ() &&
            instruction_set_inst.AVX512BW());
}

bool support_avx() {
    InstructionSet& instruction_set_inst = InstructionSet::GetInstance();
    return (instruction_set_inst.AVX2());
}

bool support_sse() {
    InstructionSet& instruction_set_inst = InstructionSet::GetInstance();
    return (instruction_set_inst.SSE());
}

// void hook_init() {
//     static std::mutex hook_mutex;
//     std::lock_guard<std::mutex> lock(hook_mutex);
//
//     if (support_avx512()) {
//         [> for IVFFLAT <]
//         fvec_inner_product = fvec_inner_product_avx512;
//         fvec_L2sqr = fvec_L2sqr_avx512;
//         fvec_L1 = fvec_L1_avx512;
//         fvec_Linf = fvec_Linf_avx512;
//
//         [> for IVFSQ <]
//         sq_get_distance_computer_L2 = sq_get_distance_computer_L2_avx512;
//         sq_get_distance_computer_IP = sq_get_distance_computer_IP_avx512;
//         sq_sel_quantizer = sq_select_quantizer_avx512;
//
//         std::cout << "FAISS hook AVX512" << std::endl;
//     } else if (support_avx()) {
//         [> for IVFFLAT <]
//         fvec_inner_product = fvec_inner_product_avx;
//         fvec_L2sqr = fvec_L2sqr_avx;
//         fvec_L1 = fvec_L1_avx;
//         fvec_Linf = fvec_Linf_avx;
//
//         [> for IVFSQ <]
//         sq_get_distance_computer_L2 = sq_get_distance_computer_L2_avx;
//         sq_get_distance_computer_IP = sq_get_distance_computer_IP_avx;
//         sq_sel_quantizer = sq_select_quantizer_avx;
//
//         std::cout << "FAISS hook AVX" << std::endl;
//     } else if (support_sse()) {
//         [> for IVFFLAT <]
//         fvec_inner_product = fvec_inner_product_sse;
//         fvec_L2sqr = fvec_L2sqr_sse;
//         fvec_L1 = fvec_L1_sse;
//         fvec_Linf = fvec_Linf_sse;
//
//         [> for IVFSQ <]
//         sq_get_distance_computer_L2 = sq_get_distance_computer_L2_sse;
//         sq_get_distance_computer_IP = sq_get_distance_computer_IP_sse;
//         sq_sel_quantizer = sq_select_quantizer_sse;
//
//         std::cout << "FAISS hook SSE" << std::endl;
//     } else {
//         FAISS_ASSERT_MSG(false, "CPU not supported!");
//     }
// }

} // namespace faiss
