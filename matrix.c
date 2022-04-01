#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);//행렬 생성 함수
void print_matrix(int** matrix, int row, int col); //행렬 출력 함수
int free_matrix(int** matrix, int row, int col);//동적 메모리 할당 해제
int fill_data(int** matrix, int row, int col);//데이터 삽입
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);//행렬 더하는 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);//행렬 빼는 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);//전치행렬 구하는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);//전치행렬과 행렬을 곱하는 함수

int main()
{
    char command;
    printf("[----- [이선주]  [2021041042] -----]\n");

	int row, col;
	srand(time(NULL));//랜덤으로 수 생성

	printf("Input row and col : ");
	scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col);//이중포인터 변수에 생성된 행렬 값 넣기
	int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) {return -1;}//행렬이 비었으면 -1 반환

	do{//메뉴 출력
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z'://z, Z 입력시 rand()로 성분값 채우기
		    printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col);//성분값 채우기
			fill_data(matrix_b, row, col);
			break;
        case 'p': case 'P'://p,P 입력시 행렬 출력
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col);//행렬 출력 함수
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col);// 행렬 출력 함수
			break;
        case 'a': case 'A'://a,A 입력시 두 행렬 더하기
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col);//행렬 더하기 함수 호출
			break;
        case 's': case 'S'://s,S 입력시 두 행렬 빼기
			printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);//행렬 빼기 함수 호출
			break;
        case 't': case 'T'://t,T 입력시 전치행렬 구하기
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);//전치 행렬 구하는 함수 호출
            print_matrix(matrix_a_t, col, row);//전치 행렬 구한 뒤 행렬 출력
			break;
        case 'm': case 'M'://m,M 입력시 두 행렬 곱하기
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);//전치 행렬 구하는 함수 호출
            multiply_matrix(matrix_a, matrix_a_t, row, col);//두 행렬 곱하는 함수 호출
			break;
        case 'q': case 'Q'://q, Q 입력시 동적 메모리 할당 해제
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);//메모리 해제
            free_matrix(matrix_a, row, col);//메모리 해제
            free_matrix(matrix_b, row, col);//메모리 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)//행렬 생성 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {//행 또는 열이 음수면 Null 반환
		printf("Check the size of row and col!\n");
		return NULL;
	}

	int** matrix = (int**)malloc(sizeof(int*) * row);//동적 메모리 할당
	for (int r = 0; r < row; r++) {
		matrix[r] = (int*)malloc(sizeof(int) * col);//동적 메모리 할당하여 배열생성
	}

	/* Check post conditions */
	if (matrix == NULL) {//행렬 비었음
		printf("Memory Allocation Failed.\n");
		return NULL;
	}

	return matrix;
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)//행렬 출력 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			printf("%3d ", matrix[matrix_row][matrix_col]);//행렬 출력
		printf("\n");
	}
	printf("\n");
	/* Check post conditions */
	 if (matrix == NULL) {//행렬이 비면 아래 문장 출력
		printf("Memory Allocation Failed.\n");
		return;
	}


	return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)//행렬에 동적 메모리 할당
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {//값이 음수면 -1 반환
		printf("Check the size of row and col!\n");
		return -1;
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		free(matrix[matrix_row]);//동적 메모리 해제
	}

	free(matrix);//동적 메모리 해제
	return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)//데이터 채우는 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++)
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix[matrix_row][matrix_col] = rand() % 20;//0 ∼ 19 사이의 값을 갖는 랜덤값 생성
	/* Check post conditions */
    if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	return 1;
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)//행렬 더하기 함수
{
    int** matrix_sum = create_matrix(row, col);//행렬 생성 함수 호출하여 총합 변수에 넣기
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {//행렬 총합 구하기
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	print_matrix(matrix_sum, row, col);//행렬 출력
	free_matrix(matrix_sum, row, col);//동적 메모리 해제
	return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)//행렬 빼기 함수
{
    int** matrix_sub = create_matrix(row, col);//행렬 생성 함수 호출하여 빼기값을 담을 변수에 넣기
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {//행렬 차 구하여 변수 sub에 넣기
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {//행렬 값이 비었다면 -1 반환
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_sub, row, col);//행렬 출력
	free_matrix(matrix_sub, row, col);//동적 메모리 할당 해제

	return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)//전치 행렬 구하는 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {//행과 열 바꾸어 전치행렬 생성
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row];
	}
	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)//행렬 곱하는 함수
{
    int** matrix_axt = create_matrix(row, row);
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) {//temp변수에 두 행렬을 곱한 값 넣기
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) {
			int temp = 0;
			for (int matrix_col = 0; matrix_col < col; matrix_col++)
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];
			matrix_axt[matrix_a_row][matrix_t_row] = temp;
		}
	}
	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_axt, row, row);//행렬 출력
	free_matrix(matrix_axt, row, col);//동적 메모리 할당 해제
	return 1;
}

