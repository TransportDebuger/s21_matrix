#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <stdlib.h>

//result codes
#define RES_OK 0
#define RES_INCORECT_MATRIX 1
#define RES_CALC_ERROR 2

//matrix comparison result codes
#define SUCCESS 1
#define FAILURE 0

//matrix type definition
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

//constructor
int s21_create_matrix(int rows, int columns, matrix_t *result);

//destructor
void s21_remove_matrix(matrix_t *A);

//matrix comparison
int s21_eq_matrix(matrix_t *A, matrix_t *B);

//matrix arithmetic functions
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_transpose(matrix_t *A, matrix_t *result);

int s21_calc_complements(matrix_t *A, matrix_t *result);

int s21_determinant(matrix_t *A, double *result);

int s21_inverse_matrix(matrix_t *A, matrix_t *result);


#endif