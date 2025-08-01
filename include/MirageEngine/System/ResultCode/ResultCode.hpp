/**
 * @file ResultCode.hpp
 * @brief リザルトコードの定義
 */
#ifndef MIRAGE_ENGINE_SYSTEM_RESULT_CODE_HPP
#define MIRAGE_ENGINE_SYSTEM_RESULT_CODE_HPP


// インクルード
#include <cstdint>

namespace mirage_engine {
namespace system {

    /**
     * @enum MirageEngineResultCode
     * @brief リザルトコード
     */
    enum class MirageEngineResultCode : uint32_t
    {
        /**
         * @brief 成功
         */
        Successful = 0x00000000,

        /**
         * @brief ウィンドウが既に作成されているため失敗
         */
        FailedToCreateWindowAlreadyExists = 0x00000001,

        /**
         * @brief ウィンドウクラスの登録に失敗
         */
        FailedToRegisterWindowClass = 0x80000001,

        /**
         * @brief ウィンドウクラス名が既に登録されているため失敗
         */
        FailedToRegisterWindowClassAlreadyExists = 0x80000002,

        /**
         * @brief ウィンドウプロシージャが重複したため失敗
         */
        ErrorWindowProcedureConflict = 0x80000003,

        /**
         * @brief ウィンドウの作成に失敗
         */
        FailedToCreateWindow = 0x80000004,

    };  // class MirageEngineResultCode

}   // namespace system
}   // namespace mirage_engine


#endif  // MIRAGE_ENGINE_SYSTEM_RESULT_CODE_HPP
