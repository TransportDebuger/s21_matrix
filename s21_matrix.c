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
        err_code = RES_INCORRECT_MATRIX;
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
            if (fabs(A->matrix[row][col] - B->matrix[row][col]) >= EQ_PRECISE) {
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
        err_code = RES_INCORRECT_MATRIX;
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
        err_code = RES_INCORRECT_MATRIX;
    }

    return err_code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int err_code = RES_OK;

  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int row = 0; row < A->rows; row++) {
      for (int col = 0; col < A->columns; col++) {
        result->matrix[row][col] = A->matrix[row][col] * number;
      }
    }
  } else {
    err_code = RES_INCORRECT_MATRIX;
  }

  return err_code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int err_code = RES_OK;

    if (A != NULL && B != NULL && A->matrix != NULL && B->matrix != NULL &&
        A->rows > 0 && B->rows > 0 && A->columns > 0 && B->columns > 0) {
        if (A->columns == B->rows) {
            s21_create_matrix(A->rows, B->columns, result);
            for (int row = 0; row < A->rows; row++) {
                for (int col = 0; col < B->columns; col++) {
                    for (int i = 0; i < A->columns; i++) {
                        result->matrix[row][col] += A->matrix[row][i] * B->matrix[i][col];
                    }
                }
            }
        } else {
            err_code = RES_CALC_ERROR;
        }
    } else {
        err_code = RES_INCORRECT_MATRIX;
    }

    return err_code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int err_code = RES_OK;

  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int row = 0; row < A->rows; row++) {
      for (int col = 0; col < A->columns; col++) {
        result->matrix[col][row] = A->matrix[row][col];
      }
    }
  } else {
    err_code = RES_INCORRECT_MATRIX;
  }
  
  return err_code;
}

int s21_determinant(matrix_t *A, double *result) {
  int err_code = RES_OK;
  *result = 0;

  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    if (A->rows == A-> columns) {
      if (A->rows == 1) {
        *result = A->matrix[0][0];
      } else if (A->rows == 2) {
        *result = A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
      } else {
        for (int i = 0; i < A->columns; i++) {

        }
      }
    } else {
      err_code = RES_CALC_ERROR;
    }
  } else {
    err_code = RES_INCORRECT_MATRIX;
  }

  return err_code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int err_code = 0;

  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    if (A->rows == A->columns) {

    } else {
      err_code = RES_CALC_ERROR;
    }
  } else {
    err_code = RES_INCORRECT_MATRIX;
  }

  return err_code;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int err_code = 0;

  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    if (A->rows == A->columns) {

    } else {
      err_code = RES_CALC_ERROR;
    }
  } else {
    err_code = RES_INCORRECT_MATRIX;
  }

  return err_code;
}