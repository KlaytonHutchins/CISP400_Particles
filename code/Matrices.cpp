#include "Matrices.h"

namespace Matrices
{
   // Constructor
   Matrix::Matrix(int _rows, int _cols) : rows(_rows), cols(_cols)
   {
      // Initialize the matrix with zeros
      a.resize(rows);
      for (int i = 0; i < rows; i++)
      {
         a[i].resize(cols, 0.0);
      }
   }

   // Matrix addition
   Matrices::Matrix operator+(const Matrices::Matrix& a, const Matrices::Matrix& b)
   {
      if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
      {
         throw runtime_error("Error: dimensions must agree");
      }

      Matrices::Matrix result(a.getRows(), a.getCols());

      for (int i = 0; i < a.getRows(); i++)
      {
         for (int j = 0; j < a.getCols(); j++)
         {
            result(i, j) = a(i, j) + b(i, j);
         }
      }

      return result;
   }

   // Matrix multiplication
   Matrices::Matrix operator*(const Matrices::Matrix& a, const Matrices::Matrix& b)
   {
      if (a.getCols() != b.getRows())
      {
         throw runtime_error("Error: dimensions must agree");
      }

      Matrices::Matrix result(a.getRows(), b.getCols());

      for (int i = 0; i < a.getRows(); i++)
      {
         for (int k = 0; k < b.getCols(); k++)
         {
            for (int j = 0; j < a.getCols(); j++)
            {
               result(i, k) += a(i, j) * b(j, k);
            }
         }
      }

      return result;
   }

   // Matrix comparison (equality)
   bool operator==(const Matrices::Matrix& a, const Matrices::Matrix& b)
   {
      if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
      {
         return false;
      }

      for (int i = 0; i < a.getRows(); i++)
      {
         for (int j = 0; j < a.getCols(); j++)
         {
            if (!(abs(a(i,j) - b(i,j)) < 0.001))
            {
               return false;
            }
         }
      }

      return true;
   }

   // Matrix comparison (inequality)
   bool operator!=(const Matrices::Matrix& a, const Matrices::Matrix& b) 
   {
      if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
      {
         return true;
      }

      for (int i = 0; i < a.getRows(); i++)
      {
         for (int j = 0; j < a.getCols(); j++)
         {
            if (abs(a(i,j) - b(i,j)) > 0.001)
            {
               return true;
            }
         }
      }

      return false;
   }
      
   // Output matrix
   ostream& operator<<(ostream& os, const Matrices::Matrix& a)
   {
      for (int i = 0; i < a.getRows(); i++)
      {
         for (int j = 0; j < a.getCols(); j++)   
         {   
            os << a(i, j) << " ";
         }
         os << "\n";
      }
    
      return os;
   }

RotationMatrix::RotationMatrix(double theta) : Matrix(2,2) {
	a[0][0] = cos(theta);
	a[0][1] = (-1.0) * sin(theta);
	a[1][0] = sin(theta);
	a[1][1] = cos(theta);
}

ScalingMatrix::ScalingMatrix(double scale) : Matrix(2,2) {
	a[0][0] = scale;
        a[0][1] = 0.0;
        a[1][0] = 0.0;
        a[1][1] = scale;
}

TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2,nCols) {}
	for (auto i = 0; i < nCols; i++) {
		a[0][i] = xShift;
		a[1][i] = yShift;
	}
}
