#include <check.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

#define PRECISION 1e-6

/*
 *
 * =============== TEST CASES: mat4_it_works ===============
 *
 */

START_TEST(tc01_mat4_it_works) {
  mat4_t mat = mat4_orthographic(0, 640, 480, 0, 1, 1000);
  mat4_t exp = {{0.003125, 0.000000, 0.000000, 0.000000, 0.000000, -0.004167,
                 0.000000, 0.000000, 0.000000, 0.000000, -0.002002, 0.000000,
                 -1.000000, 1.000000, -1.002002, 1.000000}};

  for (int i = 0; i < 16; i++)
    ck_assert_float_eq_tol(mat.data[i], exp.data[i], PRECISION);
}
END_TEST

START_TEST(tc02_mat4_it_works) {
  mat4_t mat = mat4_perspective(0.5, 640 / 480, 0.1, 1000);
  mat4_t exp = {{
      3.916318,
      0.000000,
      0.000000,
      0.000000,
      0.000000,
      3.916318,
      0.000000,
      0.000000,
      0.000000,
      0.000000,
      -1.000200,
      -1.000000,
      0.000000,
      0.000000,
      -0.200020,
      0.000000,
  }};

  for (int i = 0; i < 16; i++)
    ck_assert_float_eq_tol(mat.data[i], exp.data[i], PRECISION);
}
END_TEST

START_TEST(tc03_mat4_it_works) {
  mat4_t mat = mat4_translation(1, 2, 3);
  mat4_t exp = {{1.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000,
                 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000,
                 1.000000, 2.000000, 3.000000, 1.000000}};

  for (int i = 0; i < 16; i++)
    ck_assert_float_eq_tol(mat.data[i], exp.data[i], PRECISION);
}
END_TEST

START_TEST(tc04_mat4_it_works) {
  mat4_t mat = mat4_x_rotation(0.75);
  mat4_t exp = {{1.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.731689,
                 0.681639, 0.000000, 0.000000, -0.681639, 0.731689, 0.000000,
                 0.000000, 0.000000, 0.000000, 1.00000}};

  for (int i = 0; i < 16; i++)
    ck_assert_float_eq_tol(mat.data[i], exp.data[i], PRECISION);
}
END_TEST

START_TEST(tc05_mat4_it_works) {
  mat4_t mat = mat4_y_rotation(0.75);
  mat4_t exp = {{0.731689, 0.000000, -0.681639, 0.000000, 0.000000, 1.000000,
                 0.000000, 0.000000, 0.681639, 0.000000, 0.731689, 0.000000,
                 0.000000, 0.000000, 0.000000, 1.000000}};

  for (int i = 0; i < 16; i++)
    ck_assert_float_eq_tol(mat.data[i], exp.data[i], PRECISION);
}
END_TEST

START_TEST(tc06_mat4_it_works) {
  mat4_t mat = mat4_z_rotation(0.85);
  mat4_t exp = {{
      0.659983,
      0.751280,
      0.000000,
      0.000000,
      -0.751280,
      0.659983,
      0.000000,
      0.000000,
      0.000000,
      0.000000,
      1.000000,
      0.000000,
      0.000000,
      0.000000,
      0.000000,
      1.000000,
  }};

  for (int i = 0; i < 16; i++)
    ck_assert_float_eq_tol(mat.data[i], exp.data[i], PRECISION);
}
END_TEST

START_TEST(tc07_mat4_it_works) {
  mat4_t mat = mat4_scaling(2, 1, 2);
  mat4_t exp = {{2.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000,
                 0.000000, 0.000000, 0.000000, 0.000000, 2.000000, 0.000000,
                 0.000000, 0.000000, 0.000000, 1.000000}};

  for (int i = 0; i < 16; i++)
    ck_assert_float_eq_tol(mat.data[i], exp.data[i], PRECISION);
}
END_TEST

START_TEST(tc08_mat4_it_works) {
  mat4_t ortho = mat4_orthographic(0, 640, 480, 0, 1, 1000);
  mat4_t t = mat4_translation(0.25, 1.66, 32);
  mat4_t mat = mat4_multiply(&ortho, &t);
  mat4_t exp = {{0.003125, 0.000000, 0.000000, 0.000000, 0.000000, -0.004167,
                 0.000000, 0.000000, 0.000000, 0.000000, -0.002002, 0.000000,
                 -0.750000, 2.660000, 30.997997, 1.000000}};

  for (int i = 0; i < 16; i++)
    ck_assert_float_eq_tol(mat.data[i], exp.data[i], PRECISION);
}
END_TEST

/*
 *
 * =============== TEST CASES: obj_parser_it_works ===============
 *
 */

START_TEST(tc01_obj_parser_it_works) {
  model_t model;

  model_create(&model);
  parser_v2(&model, "../objects/cube.obj");

  size_t expected_vert_len = 24, model_vert_len = model.vertices.len;
  size_t expected_ind_len = 72, model_ind_len = model.indices.len;

  ck_assert_int_eq(expected_vert_len, model_vert_len);
  ck_assert_int_eq(expected_ind_len, model_ind_len);
  ck_assert_float_eq_tol(model.vertices.data[0], 0.5, PRECISION);
  ck_assert_float_eq_tol(model.vertices.data[1], 0.5, PRECISION);
  ck_assert_float_eq_tol(model.vertices.data[2], -0.5, PRECISION);
  ck_assert_float_eq_tol(model.vertices.data[21], -0.5, PRECISION);
  ck_assert_float_eq_tol(model.vertices.data[22], -0.5, PRECISION);
  ck_assert_float_eq_tol(model.vertices.data[23], 0.5, PRECISION);

  model_free(&model);
}
END_TEST

START_TEST(tc02_obj_parser_it_works) {
  model_t model;

  model_create(&model);
  parser_v2(&model, "../objects/car.obj");

  size_t expected_vert_len = 4455, model_vert_len = model.vertices.len;
  size_t expected_ind_len = 10628, model_ind_len = model.indices.len;

  ck_assert_int_eq(expected_vert_len, model_vert_len);
  ck_assert_int_eq(expected_ind_len, model_ind_len);

  model_free(&model);
}
END_TEST

START_TEST(tc03_obj_parser_it_works) {
  model_t model;

  model_create(&model);
  parser_v2(&model, "not_exist.obj");

  ck_assert_int_eq(model.vertices.len, 0);
  ck_assert_int_eq(model.indices.len, 0);

  model_free(&model);
}
END_TEST

/*
 * ***********************************************************
 * ======================= TEST SUITES =======================
 * ***********************************************************
 */

Suite *ts_mat4_it_works() {
  Suite *suite = suite_create("ts_mat4_it_works");
  TCase *test_case = tcase_create("ts_mat4_it_works");

  tcase_add_test(test_case, tc01_mat4_it_works);
  tcase_add_test(test_case, tc02_mat4_it_works);
  tcase_add_test(test_case, tc03_mat4_it_works);
  tcase_add_test(test_case, tc04_mat4_it_works);
  tcase_add_test(test_case, tc05_mat4_it_works);
  tcase_add_test(test_case, tc06_mat4_it_works);
  tcase_add_test(test_case, tc07_mat4_it_works);
  tcase_add_test(test_case, tc08_mat4_it_works);
  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_obj_parser_it_works() {
  Suite *suite = suite_create("ts_obj_parser_it_works");
  TCase *test_case = tcase_create("ts_obj_parser_it_works");

  tcase_add_test(test_case, tc01_obj_parser_it_works);
  tcase_add_test(test_case, tc02_obj_parser_it_works);
  tcase_add_test(test_case, tc03_obj_parser_it_works);
  suite_add_tcase(suite, test_case);

  return suite;
}

int main(void) {
  Suite *test_suites[] = {ts_mat4_it_works(), ts_obj_parser_it_works(), NULL};
  int failed = 0;

  for (Suite **s = test_suites; *s != NULL; s++) {
    SRunner *runner = srunner_create(*s);
    srunner_run_all(runner, CK_NORMAL);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  return failed;
}
