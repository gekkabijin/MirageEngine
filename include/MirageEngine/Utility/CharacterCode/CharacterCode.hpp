/**
 * @file CharacterCode.hpp
 * @brief Unicode/マルチバイト文字を切り替え可能な型
 */
#ifndef MIRAGE_ENGINE_UTILITY_CHARACTER_CODE_HPP
#define MIRAGE_ENGINE_UTILITY_CHARACTER_CODE_HPP


 // インクルード
#include <fstream>
#include <sstream>
#include <string>
#include <tchar.h>

namespace mirage_engine {
namespace utility {

    // 型定義

    /**
     * @brief TCHAR対応の入力ファイルストリーム型
     */
    typedef std::basic_ifstream<TCHAR> tifstream;

    /**
     * @brief TCHAR対応の出力ファイルストリーム型
     */
    typedef std::basic_ofstream<TCHAR> tofstream;

    /**
     * @brief TCHAR対応の文字列ストリーム型
     */
    typedef std::basic_ostringstream<TCHAR> tstringstream;

    /**
     * @brief TCHAR対応の文字列型
     */
    typedef std::basic_string<TCHAR> tstring;

}   // namespace utility
}   // namespace mirage_engine

#endif  // MIRAGE_ENGINE_UTILITY_CHARACTER_CODE_HPP
