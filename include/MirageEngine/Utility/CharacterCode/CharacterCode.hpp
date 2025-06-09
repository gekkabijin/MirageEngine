/**
 * @file CharacterCode.hpp
 * @brief Unicode/マルチバイト文字を切り替え可能な文字列型
 */
#ifndef MIRAGE_ENGINE_CHARACTERCODE_HPP
#define MIRAGE_ENGINE_CHARACTERCODE_HPP


 // インクルード
#include <fstream>
#include <sstream>
#include <string>
#include <tchar.h>

// 型定義
typedef std::basic_ifstream<TCHAR> tifstream;
typedef std::basic_ofstream<TCHAR> tofstream;
typedef std::basic_ostringstream<TCHAR> tstringstream;
typedef std::basic_string<TCHAR> tstring;


#endif  // MIRAGE_ENGINE_CHARACTERCODE_HPP
