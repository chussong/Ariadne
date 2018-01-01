#ifndef MATRIX_HPP
#define MATRIX_HPP

// general purpose matrix.hpp

#include <vector>
#include <array>
#include <iostream>

template<typename T>
class Matrix {
	private:
		const std::size_t _rows;
		const std::size_t _cols;
		std::vector<T> data;

	public:
		typedef std::array<std::size_t,2> Coords;
		static constexpr Coords NullCoords {{-1ul, -1ul}};

		Matrix(std::size_t rows, std::size_t cols): _rows(rows), _cols(cols),
				data(rows*cols) {}

		T& operator()(const std::size_t row, const std::size_t col) {
			return data.at(row*cols() + col);
		}
		T& operator()(const Coords& coords) {
			return (*this)(coords[0], coords[1]);
		}

		const T& operator()(const std::size_t row, const std::size_t col) const {
			return data.at(row*cols() + col);
		}
		const T& operator()(const Coords& coords) const {
			return (*this)(coords[0], coords[1]);
		}

		std::size_t rows() const {
			return _rows;
		}

		std::size_t cols() const {
			return _cols;
		}
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat) {
	os << "{";
	for (std::size_t i = 0; i < mat.rows(); ++i) {
		os << "{";
		for (std::size_t j = 0; j < mat.cols()-1; ++j) {
			os << mat(i,j) << ", ";
		}
		os << mat(i, mat.cols()-1) << "}\n";
	}

	os << "{";
	for (std::size_t j = 0; j < mat.cols()-1; ++j) {
		os << mat(mat.rows()-1, j) << ", ";
	}
	os << mat(mat.rows()-1, mat.cols()-1) << "}}";
}

#endif
