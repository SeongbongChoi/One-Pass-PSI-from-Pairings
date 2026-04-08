#include <relic/relic.h>
#include <stdio.h>
#include <string.h>
int main() {
    if (core_init() != RLC_OK) return 1;
    if (pc_param_set_any() != RLC_OK) return 1;
    printf("=== Testing G1 (EP) ===\n");
    g1_t g1_1, g1_2;
    g1_null(g1_1); g1_new(g1_1);
    g1_null(g1_2); g1_new(g1_2);
    g1_get_gen(g1_1);
    uint8_t g1_buffer[RLC_PC_BYTES + 1];
    memset(g1_buffer, 0, sizeof(g1_buffer));
    g1_write_bin(g1_buffer, sizeof(g1_buffer), g1_1, 1);
    printf("G1 buffer size: %lu bytes\n", sizeof(g1_buffer));
    g1_read_bin(g1_2, g1_buffer, sizeof(g1_buffer));
    if (g1_cmp(g1_1, g1_2) != RLC_EQ) {
        printf("G1 test FAILED\n"); return 1;
    }
    printf("G1 test PASSED\n");
    printf("=== Testing G2 (EP2) ===\n");
    g2_t g2_1, g2_2;
    g2_null(g2_1); g2_new(g2_1);
    g2_null(g2_2); g2_new(g2_2);
    g2_get_gen(g2_1);
    printf("EP2 size: %d bytes\n", g2_size_bin(g2_1, 0));
    uint8_t g2_buffer[4 * RLC_PC_BYTES + 1];
    memset(g2_buffer, 0, sizeof(g2_buffer));
    g2_write_bin(g2_buffer, sizeof(g2_buffer), g2_1, 0);
    printf("G2 buffer size: %lu bytes\n", sizeof(g2_buffer));
    g2_read_bin(g2_2, g2_buffer, sizeof(g2_buffer));
    if (g2_cmp(g2_1, g2_2) != RLC_EQ) {
        printf("G2 comparison failed\n"); return 1;
    }
    printf("G2 test PASSED\n");
    printf("=== Testing GT (Pairing Result) ===\n");
    gt_t gt_1, gt_2;
    gt_null(gt_1); gt_new(gt_1);
    gt_null(gt_2); gt_new(gt_2);
    pc_map(gt_1, g1_1, g2_1);
    uint8_t gt_buffer[12 * RLC_PC_BYTES];
    memset(gt_buffer, 0, sizeof(gt_buffer));
    gt_write_bin(gt_buffer, sizeof(gt_buffer), gt_1, 0);
    printf("GT buffer size: %lu bytes\n", sizeof(gt_buffer));
    gt_read_bin(gt_2, gt_buffer, sizeof(gt_buffer));
    if (gt_cmp(gt_1, gt_2) != RLC_EQ) {
        printf("GT comparison failed\n"); return 1;
    }
    printf("GT test PASSED\n");
    printf("=== Testing BN (Big Number) ===\n");
    bn_t bn_1, bn_2;
    bn_null(bn_1); bn_new(bn_1);
    bn_null(bn_2); bn_new(bn_2);
    bn_set_dig(bn_1, 12345678);
    uint8_t bn_buffer[RLC_FC_BYTES];
    memset(bn_buffer, 0, sizeof(bn_buffer));
    bn_write_bin(bn_buffer, sizeof(bn_buffer), bn_1);
    printf("BN buffer size: %lu bytes\n", sizeof(bn_buffer));
    bn_read_bin(bn_2, bn_buffer, sizeof(bn_buffer));
    if (bn_cmp(bn_1, bn_2) != RLC_EQ) {
        printf("BN comparison failed\n"); return 1;
    }
    printf("BN test PASSED\n");
    printf("=== All Tests Summary ===\n");
    printf("PC_BYTES: %d\n", RLC_PC_BYTES);
    printf("FC_BYTES: %d\n", RLC_FC_BYTES);
    printf("All serialization/deserialization tests PASSED\n");
    g1_free(g1_1); g1_free(g1_2);
    g2_free(g2_1); g2_free(g2_2);
    gt_free(gt_1); gt_free(gt_2);
    bn_free(bn_1); bn_free(bn_2);
    core_clean(); return 0;
}
