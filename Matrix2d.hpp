#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <iostream>
#include <cstring>
#include <cassert>
/*
 *
 */
template <typename T>
class Matrix2d
{
public:
	Matrix2d();
	Matrix2d(int iColumn, int iRow);
	Matrix2d(int iColumn, int iRow, const T *pData);
	virtual ~Matrix2d();
	virtual inline T * getMatrix2dData(){ return const_cast<T *>(this->m_pData); };
	virtual inline int getMatrix2dRow(){ return this->m_iRow; };
	virtual inline int getMatrix2dColumn(){ return this->m_iColumn; };
	virtual inline void setMatrix2dData(T * pData){ this->m_pData = pData; };
	virtual inline void setMatrix2dRow(int iRow){ this->m_iRow = iRow; };
	virtual inline void setMatrix2dColumn(int iColumn){ this->m_iColumn = iColumn;};
	virtual Matrix2d<T>& operator +(Matrix2d<T> &op);
	virtual Matrix2d<T>& operator -(Matrix2d<T> &op);
	virtual Matrix2d<T>& operator =(Matrix2d<T> &op);
	virtual Matrix2d<T>& operator *(Matrix2d<T> &op);
	virtual Matrix2d<T>& operator *(const T &op);
	virtual Matrix2d<T>& operator ~();
 	template <typename T> friend std::ostream& operator <<(std::ostream &OutStream, const Matrix2d<T> &MatrixObj);
private:
	void initAttributes();

private:
	const T *m_pData;
	int m_iRow;
	int m_iColumn;
};



template <typename T> Matrix2d<T>::Matrix2d()
{
	initAttributes();
}

template <typename T> void Matrix2d<T>::initAttributes()
{
	this->m_iColumn = 0;
	this->m_iRow = 0;
	this->m_pData = NULL;
}
template <typename T> Matrix2d<T>::Matrix2d(int iColumn, int iRow)
{
	assert(iColumn && iRow);
	this->m_iRow = iRow;
	this->m_iColumn = iColumn;
	this->m_pData = new T[iRow*iColumn];
	memset(const_cast<T *>(this->m_pData), 0, sizeof(T)*this->m_iColumn*this->m_iRow);
}
template <typename T> Matrix2d<T>::Matrix2d(int iColumn, int iRow, const T *pData)
{
	assert(iColumn && iRow && pData != NULL);
	this->m_iRow = iRow;
	this->m_iColumn = iColumn;
	this->m_pData = new T[this->m_iColumn*this->m_iRow];
	memcpy(const_cast<T *>(this->m_pData), pData, sizeof(T)*this->m_iColumn*this->m_iRow);
}
template <typename T> Matrix2d<T>::~Matrix2d()
{
	if(this->m_pData){
		delete[] this->m_pData;
		this->m_pData = NULL;
	}
}
template <typename T> Matrix2d<T>& Matrix2d<T>::operator +(Matrix2d<T> &op)
{
	assert(op.m_iRow == this->m_iRow && op.m_iColumn == this->m_iColumn);
	for(int i = 0; i < this->m_iRow; i++){
		for(int j = 0; j < this->m_iColumn; j++){
			*(const_cast<T *>(this->m_pData) + i*this->m_iColumn + j) += (*(op.m_pData + i*op.m_iColumn + j));
		}
	}
	return (*this);
}
template <typename T> Matrix2d<T>& Matrix2d<T>::operator -(Matrix2d<T> &op)
{
	assert(op.m_iRow == this->m_iRow && op.m_iColumn == this->m_iColumn);
	for(int i = 0; i < this->m_iRow; i++){
		for(int j = 0; j < this->m_iColumn; j++){
			*(const_cast<T *>(this->m_pData) + i*this->m_iColumn + j) -= *(op.m_pData + i*op.m_iColumn + j);
		}
	}
	return (*this);

}

template <typename T> Matrix2d<T>& Matrix2d<T>::operator =(Matrix2d<T> &op)
{
	assert(op.m_iRow == this->m_iRow && op.m_iColumn == this->m_iColumn);
	for(int i = 0; i < this->m_iRow; i++){
		for(int j = 0; j < this->m_iColumn; j++){
			*(const_cast<T *>(this->m_pData) + i*this->m_iColumn + j) = *(op.m_pData + i*op.m_iColumn + j);
		}
	}
	return (*this);
}

template <typename T> Matrix2d<T>& Matrix2d<T>::operator *(Matrix2d<T> &op)
{
	assert( this->m_iColumn == op.m_iRow);
	Matrix2d<T> * pMatrix2dResult = new Matrix2d(op.m_iColumn, this->m_iRow);
	for(int i = 0, m = 0; i < pMatrix2dResult->m_iRow; i++, m++){
		for(int j = 0; j < pMatrix2dResult->m_iColumn; j++){
			for(int k = 0; k < this->m_iColumn; k++){
				*(const_cast<T*>(pMatrix2dResult->m_pData) + i*pMatrix2dResult->m_iColumn + j) += (*(this->m_pData + i*this->m_iColumn + k)) \
					* (*(op.m_pData + k*op.m_iColumn + j));
			}
		}
	}
	return (*pMatrix2dResult);
}
template <typename T> Matrix2d<T>& Matrix2d<T>::operator *(const T &op)
{
	for(int i = 0; i < this->m_iRow; i++){
		for(int j = 0; j < this->m_iColumn; j++){
			*(const_cast<T *>(this->m_pData) + i*this->m_iColumn + j) *= op;
		}
	}
	return (*this);
}
template <typename T> Matrix2d<T>& Matrix2d<T>::operator ~()
{
	assert(this->m_iRow && this->m_iColumn && this->m_pData != NULL);
	T * pDataTmp = new T[this->m_iRow * this->m_iColumn];
	for(int i = 0; i < this->m_iColumn; i++){
		for(int j = 0; j < this->m_iRow; j++){
			*(pDataTmp + i*this->m_iRow + j) = *(const_cast<T *>(this->m_pData) + j*this->m_iColumn + i);  
		}
	}
	memcpy(const_cast<T *>(this->m_pData), pDataTmp, sizeof(T)* this->m_iColumn * this->m_iRow);
	int iTmp = this->m_iColumn;
	this->setMatrix2dColumn(this->m_iRow);
	this->setMatrix2dRow(iTmp);
	if(pDataTmp){
		delete[] pDataTmp;
		pDataTmp = NULL;
	}
 	return (*this);
}
template <typename T> std::ostream& operator << (std::ostream &OutStream, const Matrix2d<T> &MatrixObj)
{
	Matrix2d<T> *pMatrixTmp =const_cast<Matrix2d<T> *>( &MatrixObj );
	for(int i = 0; i < pMatrixTmp->getMatrix2dRow(); i++){
		OutStream << "|"<< " ";
		for(int j = 0; j < pMatrixTmp->getMatrix2dColumn(); j++){
			OutStream << *(pMatrixTmp->getMatrix2dData() + i*pMatrixTmp->getMatrix2dColumn() + j)<< " ";
		}
		OutStream << "|" << std::endl;
	}

	return OutStream;
}
#endif /*_MATRIX_HPP_*/