#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int err_code = RES_OK;

    if (rows > 0 && columns > 0) {
        result->rows = rows;
        result->columns = columns;
        result->matrix = (double **)calloc(rows, sizeof(double *));
        for (int i = 0; i < rows; i++) {
            result->matrix[i] = (double *)calloc(columns, sizeof(double));
        }
    } else {
        err_code = RES_INCORECT_MATRIX;
    }

    return err_code;
}

void s21_remove_matrix(matrix_t *A) {
    if (A != NULL && A->matrix != NULL) {
        for (int i = 0; i < A->rows; i++) {
            free(A->matrix[i]);
        }
        free(A->matrix);
        A->rows = 0;
        A->columns = 0;
        A->matrix = NULL;
    }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result_code = SUCCESS;

  if (A != NULL && B != NULL && A->matrix != NULL && B->matrix != NULL &&
      A->rows > 0 && B->rows > 0 && A->columns > 0 && B->columns > 0 &&
      A->rows == B->rows && A->columns == B->columns) {
    for (int row = 0; row < A->rows; row++) {
        for (int col = 0; col < A->columns; col++) {
            if (fabs(A->matrix[row][col] - B->matrix[row][col]) >= 1E-7) {
                result_code = FAILURE;
                break;
            }
        }
        if (result_code == FAILURE) break;
    }
  } else {
    result_code = FAILURE;
  }

  return result_code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int err_code = RES_OK;

    if (A != NULL && B != NULL && A->matrix != NULL && B->matrix != NULL &&
      A->rows > 0 && B->rows > 0 && A->columns > 0 && B->columns > 0) {
        if (A->rows == B->rows && A->columns == B->columns) {
            s21_create_matrix(A->rows, A->columns, result);
            for (int row = 0; row < A->rows; row++) {
                for (int col = 0; col < A->columns; col++) {
                    result->matrix[row][col] = A->matrix[row][col] + B->matrix[row][col];
                }
             }
        } else {
            err_code = RES_CALC_ERROR;
        }
    } else {
        err_code = RES_INCORECT_MATRIX;
    }

    return err_code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int err_code = RES_OK;

    if (A != NULL && B != NULL && A->matrix != NULL && B->matrix != NULL &&
      A->rows > 0 && B->rows > 0 && A->columns > 0 && B->columns > 0) {
        if (A->rows == B->rows && A->columns == B->columns) {
            s21_create_matrix(A->rows, A->columns, result);
            for (int row = 0; row < A->rows; row++) {
                for (int col = 0; col < A->columns; col++) {
                    result->matrix[row][col] = A->matrix[row][col] - B->matrix[row][col];
                }
             }
        } else {
            err_code = RES_CALC_ERROR;
        }
    } else {
        err_code = RES_INCORECT_MATRIX;
    }

    return err_code;
}