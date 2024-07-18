#include <iostream>
//#ifndef function_h
#define function_h
#include <iostream>

using namespace std;

class Matrix
{
    friend std::ostream &operator<<(std::ostream &os, const Matrix &a);
    friend std::istream &operator>>(std::istream &is, Matrix &a);
public:
    Matrix(int s = 5);

    Matrix(const Matrix &a);// copy constructor

    ~Matrix();

    //Matrix &operator=(const Matrix &a);

    Matrix &clockwise90();
private:
    int **matrix;
    int *buf;   // 2D matrix stored in 1D raster scan order
    int size;
}; //end class Matrix
//Matrix &Matrix::operator=(const Matrix &a){}
//Matrix::~Matrix(){}
std::ostream &operator<<(std::ostream &os, const Matrix &a){
    for(int i =0;i<a.size;i++){
         for(int j =0 ; j<a.size;j++){
             if(j == a.size-1) os << a.matrix[i][j] << endl; 
             else os << a.matrix[i][j] << " "; 
            //os << a.matrix[i][j] << " \n"; 
        }
    }
    return os;
}
Matrix::Matrix(int s){
    this->size = s;
    this->matrix = new int*[s];
    for(int i=0;i<s;i++){
        this->matrix[i] = new int[s];
    }
}

Matrix::~Matrix(){
    
}

std::istream &operator>>(std::istream &is, Matrix &a){
    //scan all matrix inouts in this function
     for(int i =0;i<a.size;i++){
         for(int j =0 ; j<a.size;j++){
            is >> a.matrix[i][j]; 
        }
    }
    return is;
}

Matrix::Matrix(const Matrix &a){

    for(int i=0; i<this->size; i++){
        for(int j=0; j<this->size; j++){
             a.matrix[i][j];
        }
    }

}
Matrix &Matrix::clockwise90(){
    // int dummy_matrix[size][size];
    // for(int i=0; i<size; i++){
    //     for(int j=0; j<size; j++){
    //         dummy_matrix[i][j] = 0;
    //     }
    // }
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size - i; j++)
        {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[size - 1 - j][size - 1 - i];
            matrix[size - 1 - j][size - 1 - i] = temp;
        }
    }
     
    // Second rotation
    // with respect to middle row
    for(int i = 0; i < size / 2; i++)
    {
        for(int j = 0; j < size; j++)
        {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[size - 1 - i][j];
            matrix[size - 1 - i][j] = temp;
        }
    }
    return *this;
}


   