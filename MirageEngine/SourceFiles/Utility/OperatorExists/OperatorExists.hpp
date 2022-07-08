/**
 * @file  OperatorExists.hpp
 * @brief Check if an operator exists as a member of class
 */ 
#pragma once

// include
#include <type_traits>


namespace framework {
namespace utility {

    /**
     * @class HasNegationOperator
     * @brief Check if an operator~ exists as a member of class
     */
    template<typename DataType>
    class HasNegationOperator
    {
    private:

        /**
         * @brief  Check if an operator~ exists as a member of class
         *
         * @return true_type
         */
        template<typename Type = DataType>
        static auto check(Type) -> decltype(~std::declval<Type&>(), std::true_type{});

        /**
         * @brief  Check if an operator~ exists as a member of class
         *
         * @return false_type
         */
        static std::false_type check(...);

    public:

        //! exists flag
        static bool const type = decltype(check(std::declval<DataType>()))::value;
    };  // class HasNegationOperator

    /**
     * @class HasAdditionOperator
     * @brief Check if an operator+ exists as a member of class
     */
    template<typename DataType1, typename DataType2>
    class HasAdditionOperator
    {
    private:

        /**
         * @brief  Check if an operator+ exists as a member of class
         *
         * @return true_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static auto check(Type1, Type2) -> decltype(std::declval<Type1&>() + std::declval<Type2&>(), std::true_type{});

        /**
         * @brief  Check if an operator+ exists as a member of class
         *
         * @return false_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static std::false_type check(...);

    public:

        //! exists flag
        static bool const value = decltype(check(std::declval<DataType1>(), std::declval<DataType2>()))::value;
    };  // HasAdditionOperator

    /**
     * @class HasSubtractionOperator
     * @brief Check if an operator- exists as a member of class
     */
    template<typename DataType1, typename DataType2>
    class HasSubtractionOperator
    {
    private:

        /**
         * @brief  Check if an operator- exists as a member of class
         *
         * @return true_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static auto check(Type1, Type2) -> decltype(std::declval<Type1&>() - std::declval<Type2&>(), std::true_type{});

        /**
         * @brief  Check if an operator- exists as a member of class
         *
         * @return false_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static std::false_type check(...);

    public:

        //! exists flag
        static bool const value = decltype(check(std::declval<DataType1>(), std::declval<DataType2>()))::value;
    };  // HasSubtractionOperator

    /**
     * @class HasMultiplicationOperator
     * @brief Check if an operator* exists as a member of class
     */
    template<typename DataType1, typename DataType2>
    class HasMultiplicationOperator
    {
    private:

        /**
         * @brief  Check if an operator* exists as a member of class
         *
         * @return true_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static auto check(Type1, Type2) -> decltype(std::declval<Type1&>() * std::declval<Type2&>(), std::true_type{});

        /**
         * @brief  Check if an operator* exists as a member of class
         *
         * @return false_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static std::false_type check(...);

    public:

        //! exists flag
        static bool const value = decltype(check(std::declval<DataType1>(), std::declval<DataType2>()))::value;
    };  // HasMultiplicationOperator

    /**
     * @class HasDivisionOperator
     * @brief Check if an operator/ exists as a member of class
     */
    template<typename DataType1, typename DataType2>
    class HasDivisionOperator
    {
    private:

        /**
         * @brief  Check if an operator/ exists as a member of class
         *
         * @return true_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static auto check(Type1, Type2) -> decltype(std::declval<Type1&>() / std::declval<Type2&>(), std::true_type{});

        /**
         * @brief  Check if an operator/ exists as a member of class
         *
         * @return false_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static std::false_type check(...);

    public:

        //! exists flag
        static bool const value = decltype(check(std::declval<DataType1>(), std::declval<DataType2>()))::value;
    };  // HasDivisionOperator

    /**
     * @class HasRemainderOperator
     * @brief Check if an operator% exists as a member of class
     */
    template<typename DataType1, typename DataType2>
    class HasRemainderOperator
    {
    private:

        /**
         * @brief  Check if an operator% exists as a member of class
         *
         * @return true_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static auto check(Type1, Type2) -> decltype(std::declval<Type1&>() % std::declval<Type2&>(), std::true_type{});

        /**
         * @brief  Check if an operator% exists as a member of class
         *
         * @return false_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static std::false_type check(...);

    public:

        //! exists flag
        static bool const value = decltype(check(std::declval<DataType1>(), std::declval<DataType2>()))::value;
    };  // HasRemainderOperator

    /**
     * @class HasDisjunctionOperator
     * @brief Check if an operator| exists as a member of class
     */
    template<typename DataType1, typename DataType2>
    class HasDisjunctionOperator
    {
    private:

        /**
         * @brief  Check if an operator| exists as a member of class
         *
         * @return true_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static auto check(Type1, Type2) -> decltype(std::declval<Type1&>() | std::declval<Type2&>(), std::true_type{});

        /**
         * @brief  Check if an operator| exists as a member of class
         *
         * @return false_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static std::false_type check(...);

    public:

        //! exists flag
        static bool const value = decltype(check(std::declval<DataType1>(), std::declval<DataType2>()))::value;
    };  // HasDisjunctionOperator

    /**
     * @class HasConjunctionOperator
     * @brief Check if an operator& exists as a member of class
     */
    template<typename DataType1, typename DataType2>
    class HasConjunctionOperator
    {
    private:

        /**
         * @brief  Check if an operator& exists as a member of class
         *
         * @return true_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static auto check(Type1, Type2) -> decltype(std::declval<Type1&>() & std::declval<Type2&>(), std::true_type{});

        /**
         * @brief  Check if an operator& exists as a member of class
         *
         * @return false_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static std::false_type check(...);

    public:

        //! exists flag
        static bool const value = decltype(check(std::declval<DataType1>(), std::declval<DataType2>()))::value;
    };  // HasConjunctionOperator

    /**
     * @class HasLogicalExclusiveDisunctionOperator
     * @brief Check if an operator^ exists as a member of class
     */
    template<typename DataType1, typename DataType2>
    class HasLogicalExclusiveDisunctionOperator
    {
    private:

        /**
         * @brief  Check if an operator^ exists as a member of class
         *
         * @return true_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static auto check(Type1, Type2) -> decltype(std::declval<Type1&>() ^ std::declval<Type2&>(), std::true_type{});

        /**
         * @brief  Check if an operator^ exists as a member of class
         *
         * @return false_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static std::false_type check(...);

    public:

        //! exists flag
        static bool const value = decltype(check(std::declval<DataType1>(), std::declval<DataType2>()))::value;
    };  // HasLogicalExclusiveDisunctionOperator

    /**
     * @class HasAdditionAssigmentOperator
     * @brief Check if an operator+= exists as a member of class
     */
    template<typename DataType1, typename DataType2>
    class HasAdditionAssigmentOperator
    {
    private:

        /**
         * @brief  Check if an operator+= exists as a member of class
         *
         * @return true_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static auto check(Type1, Type2) -> decltype(std::declval<Type1&>() += std::declval<Type2&>(), std::true_type{});

        /**
         * @brief  Check if an operator+= exists as a member of class
         *
         * @return false_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static std::false_type check(...);

    public:

        //! exists flag
        static bool const value = decltype(check(std::declval<DataType1>(), std::declval<DataType2>()))::value;
    };  // HasAdditionAssigmentOperator

    /**
     * @class HasSubtractionAssigmentOperator
     * @brief Check if an operator-= exists as a member of class
     */
    template<typename DataType1, typename DataType2>
    class HasSubtractionAssigmentOperator
    {
    private:

        /**
         * @brief  Check if an operator-= exists as a member of class
         *
         * @return true_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static auto check(Type1, Type2) -> decltype(std::declval<Type1&>() -= std::declval<Type2&>(), std::true_type{});

        /**
         * @brief  Check if an operator-= exists as a member of class
         *
         * @return false_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static std::false_type check(...);

    public:

        //! exists flag
        static bool const value = decltype(check(std::declval<DataType1>(), std::declval<DataType2>()))::value;
    };  // HasSubtractionAssigmentOperator

    /**
     * @class HasMultiplicationAssigmentOperator
     * @brief Check if an operator*= exists as a member of class
     */
    template<typename DataType1, typename DataType2>
    class HasMultiplicationAssigmentOperator
    {
    private:

        /**
         * @brief  Check if an operator*= exists as a member of class
         *
         * @return true_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static auto check(Type1, Type2) -> decltype(std::declval<Type1&>() *= std::declval<Type2&>(), std::true_type{});

        /**
         * @brief  Check if an operator*= exists as a member of class
         *
         * @return false_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static std::false_type check(...);

    public:

        //! exists flag
        static bool const value = decltype(check(std::declval<DataType1>(), std::declval<DataType2>()))::value;
    };  // HasMultiplicationAssigmentOperator

    /**
     * @class HasDivisionAssigmentOperator
     * @brief Check if an operator/= exists as a member of class
     */
    template<typename DataType1, typename DataType2>
    class HasDivisionAssigmentOperator
    {
    private:

        /**
         * @brief  Check if an operator/= exists as a member of class
         *
         * @return true_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static auto check(Type1, Type2) -> decltype(std::declval<Type1&>() /= std::declval<Type2&>(), std::true_type{});

        /**
         * @brief  Check if an operator/= exists as a member of class
         *
         * @return false_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static std::false_type check(...);

    public:

        //! exists flag
        static bool const value = decltype(check(std::declval<DataType1>(), std::declval<DataType2>()))::value;
    };  // HasDivisionAssigmentOperator

    /**
     * @class HasRemainderAssigmentOperator
     * @brief Check if an operator%= exists as a member of class
     */
    template<typename DataType1, typename DataType2>
    class HasRemainderAssigmentOperator
    {
    private:

        /**
         * @brief  Check if an operator%= exists as a member of class
         *
         * @return true_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static auto check(Type1, Type2) -> decltype(std::declval<Type1&>() %= std::declval<Type2&>(), std::true_type{});

        /**
         * @brief  Check if an operator%= exists as a member of class
         *
         * @return false_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static std::false_type check(...);

    public:

        //! exists flag
        static bool const value = decltype(check(std::declval<DataType1>(), std::declval<DataType2>()))::value;
    };  // HasRemainderAssigmentOperator

    /**
     * @class HasDisjunctionAssigmentOperator
     * @brief Check if an operator|= exists as a member of class
     */
    template<typename DataType1, typename DataType2>
    class HasDisjunctionAssigmentOperator
    {
    private:

        /**
         * @brief  Check if an operator|= exists as a member of class
         *
         * @return true_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static auto check(Type1, Type2) -> decltype(std::declval<Type1&>() |= std::declval<Type2&>(), std::true_type{});

        /**
         * @brief  Check if an operator|= exists as a member of class
         *
         * @return false_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static std::false_type check(...);

    public:

        //! exists flag
        static bool const value = decltype(check(std::declval<DataType1>(), std::declval<DataType2>()))::value;
    };  // HasDisjunctionAssigmentOperator

    /**
     * @class HasConjunctionAssigmentOperator
     * @brief Check if an operator&= exists as a member of class
     */
    template<typename DataType1, typename DataType2>
    class HasConjunctionAssigmentOperator
    {
    private:

        /**
         * @brief  Check if an operator&= exists as a member of class
         *
         * @return true_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static auto check(Type1, Type2) -> decltype(std::declval<Type1&>() &= std::declval<Type2&>(), std::true_type{});

        /**
         * @brief  Check if an operator&= exists as a member of class
         *
         * @return false_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static std::false_type check(...);

    public:

        //! exists flag
        static bool const value = decltype(check(std::declval<DataType1>(), std::declval<DataType2>()))::value;
    };  // HasConjunctionAssigmentOperator

    /**
     * @class HasLogicalExclusiveDisunctionAssigmentOperator
     * @brief Check if an operator^= exists as a member of class
     */
    template<typename DataType1, typename DataType2>
    class HasLogicalExclusiveDisunctionAssigmentOperator
    {
    private:

        /**
         * @brief  Check if an operator^= exists as a member of class
         *
         * @return true_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static auto check(Type1, Type2) -> decltype(std::declval<Type1&>() ^= std::declval<Type2&>(), std::true_type{});

        /**
         * @brief  Check if an operator^= exists as a member of class
         *
         * @return false_type
         */
        template<typename Type1 = DataType1, typename Type2 = DataType2>
        static std::false_type check(...);

    public:

        //! exists flag
        static bool const value = decltype(check(std::declval<DataType1>(), std::declval<DataType2>()))::value;
    };  // HasLogicalExclusiveDisunctionAssigmentOperator

}   // namespace utility
}   // namespace framework
